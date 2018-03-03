#include "gsminterface.h"

#include <cstring>
#include <cstdlib>

#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#ifdef NO_QT
#include <iostream>
#define DEBUG   std::cout
#define ENDL    std::endl
#else
#include <QDebug>
#define DEBUG   qDebug()
#define ENDL    ""
#endif
static const char PORT[] = "/dev/ttyUSB0";

#define INVALID_FD   (-1)

GsmInterface gsmInterface;

GsmInterface::GsmInterface()
{
    fd = open(PORT, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == INVALID_FD) {
        DEBUG << "Failed to open port " << PORT << ENDL;
        return;
    }
    fcntl(fd, F_SETFL, 0);
    struct termios serialPortSettings = {0};
    tcgetattr(fd, &serialPortSettings);
    cfsetispeed(&serialPortSettings, B115200);
    cfsetospeed(&serialPortSettings, B115200);
    serialPortSettings.c_cflag &= ~PARENB;   // No Parity
    serialPortSettings.c_cflag &= ~CSTOPB; //Stop bits = 1
    serialPortSettings.c_cflag &= ~CSIZE; /* Clears the Mask       */
    serialPortSettings.c_cflag |=  CS8;   /* Set the data bits = 8 */
    serialPortSettings.c_cflag &= ~CRTSCTS;
    serialPortSettings.c_cflag |= CREAD | CLOCAL;
    serialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);
    serialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    /* Setting Time outs -- non-blocking read */
    serialPortSettings.c_cc[VMIN]  = 0; /* Read 10 characters */
    serialPortSettings.c_cc[VTIME] = 0;  /* Return quickly */

    tcsetattr(fd, TCSANOW, &serialPortSettings);
}

GsmInterface::~GsmInterface()
{
    if (fd != INVALID_FD)
        close(fd);
}

std::string GsmInterface::sendAndReceive(const char cmd[])
{
    if (!writeLine(cmd)) {
        DEBUG << "Write failed" << ENDL;
        return "";
    }
    usleep(100000); // sleep 100 milliseconds
    return readLine();
}

bool GsmInterface::writeLine(const char cmd[])
{
    DEBUG << "W:" << cmd << ENDL;
    if (fd != INVALID_FD)
        return write(fd, cmd, std::strlen(cmd)) >= 0 && write(fd, "\r", 1) == 1;
    return false;
}

std::string GsmInterface::readLine()
{
    if (fd == INVALID_FD)
        return "";

    char buf[4096] = {0};
    int n = read(fd, buf, sizeof(buf)-1);
    if (n>0)
        buf[n] = '\0';
    std::string resp;
    const char *p = buf;
    while (const char *end = std::strstr(p,"\r\n")) {
        const char * const start = p;
        p = end + 2;
        if (start == end)
            continue;

        const std::string line(start, end-start);
        DEBUG << "r:" << line.c_str() << ENDL;
        if (line.compare(0, 7, "+SIND: ") == 0)
            sind = std::atoi(start + 7);
        else
            resp = line;
    }

    DEBUG << "R:" << resp.c_str() << ENDL;

    return resp;
}

int GsmInterface::getsind() {
    readLine();
    return sind;
}
