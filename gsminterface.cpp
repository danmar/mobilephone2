#include "gsminterface.h"

//#include <stdio.h>   /* Standard input/output definitions */
//#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */


#define INVALID_FD   (-1)

GsmInterface gsmInterface;

GsmInterface::GsmInterface()
{
    fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd != INVALID_FD)
        fcntl(fd, F_SETFL, 0);
}

GsmInterface::~GsmInterface()
{
    if (fd != INVALID_FD)
        close(fd);
}

QString GsmInterface::sendAndReceive(const char cmd[])
{
    if (!writeLine(cmd))
        return QString();
    usleep(100000); // sleep 100 milliseconds
    return readLine();
}

bool GsmInterface::writeLine(const char cmd[])
{
    if (fd != INVALID_FD)
        return write(fd, cmd, strlen(cmd)) >= 0 && write(fd, "\r", 1) == 1;
    return false;
}

QString GsmInterface::readLine()
{
    if (fd == INVALID_FD)
        return QString();

    char buf[1024] = {0};
    int n = read(fd, buf, sizeof(buf)-1);
    if (n>0)
        buf[n] = '\0';
    return buf;
}
