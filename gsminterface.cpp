#include "gsminterface.h"

#include <cstring>
#include <cstdlib>

#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

static const char PORT[] = "/dev/ttyUSB0";

#define   DEBUG   if (debug) (*debug)

#define INVALID_FD   (-1)

GsmInterface gsmInterface;

static void setflags(int fd)
{
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
    serialPortSettings.c_iflag = IGNPAR;
    serialPortSettings.c_oflag = 0;

    /* Setting Time outs -- non-blocking read */
    serialPortSettings.c_cc[VMIN]  = 0; /* Read 10 characters */
    serialPortSettings.c_cc[VTIME] = 0;  /* Return quickly */

    tcsetattr(fd, TCSANOW, &serialPortSettings);
}

GsmInterface::GsmInterface() : debug(nullptr), status(SIND_RESTARTING)
{
    fd = open(PORT, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == INVALID_FD) {
        DEBUG << "Failed to open port " << PORT << std::endl;
        return;
    }
    fcntl(fd, F_SETFL, 0);
    setflags(fd);
    sendAndReceive("");
}

GsmInterface::~GsmInterface()
{
    if (fd != INVALID_FD)
        close(fd);
}

bool GsmInterface::sendSms(const char phoneNumber[], const char text[])
{
    if (fd == INVALID_FD || status != SIND_CONNECTED)
        return false;
    if (sendAndReceive("AT+CMGF=1") != "OK") // set text format
        return false;

    std::string line = "AT+CMGS=\"" + std::string(phoneNumber) + '\"';
    writeLine(line.c_str());
    usleep(10000);
    write(fd, text, strlen(text));
    const char ctrlz[] = "\x1A";
    write(fd, ctrlz, 1);
}

std::string GsmInterface::sendAndReceive(const char cmd[])
{
    if (!writeLine(cmd)) {
        DEBUG << "Write failed" << std::endl;
        return "";
    }
    usleep(100000); // sleep 100 milliseconds
    return readLine();
}

bool GsmInterface::writeLine(const char cmd[])
{
    DEBUG << "W:" << cmd << std::endl;
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
        DEBUG << "R:" << line.c_str() << std::endl;
        if (line.compare(0, 7, "+SIND: ") == 0) {
            int sind = std::atoi(start + 7);
            if (sind == SIND_DISCONNECTED || sind == SIND_CONNECTED) {
                status = (STATUS)sind;
            }
        } else {
            resp = line;
        }
    }
    return resp;
}
