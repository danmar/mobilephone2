#include "gsminterface.h"

#include <cstring>
#include <cstdlib>
#include <fstream>

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

GsmInterface::GsmInterface() : debug(nullptr), status(SIND_RESTARTING), fetchingSms(false), autoFetchSms(false)
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

void GsmInterface::fetchSmsMessagesFromFile()
{
    std::ifstream fin("/home/danielm/mobilephone2/sms-list.txt");
    if (!fin.is_open())
        return;
    _smsMessages.clear();
    std::string line;
    while (std::getline(fin, line)) {
        if (line.compare(0,6,"+CMGL:")==0)
            _smsMessages.push_back(SmsMessage(line.substr(6)));
        else if (!_smsMessages.empty())
            _smsMessages.back().text += line;
    }
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
    DEBUG << "W:" << text << "\\1A" << std::endl;
    write(fd, text, strlen(text));
    const char ctrlz[] = "\x1A";
    write(fd, ctrlz, 1);
    return true;
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
        if (line.compare(0, 6, "+CMGL:") == 0) {
            _smsMessages.push_back(SmsMessage(line.substr(6)));
        } else if (line.compare(0, 7, "+SIND: ") == 0) {
            int sind = std::atoi(start + 7);
            if (sind == SIND_DISCONNECTED || sind == SIND_CONNECTED)
                status = (STATUS)sind;
            if (sind == 4 && autoFetchSms && !fetchingSms)
                fetchSmsMessages();
        } else {
            resp = line;
            if (resp == "OK")
                fetchingSms = false;
            else if (fetchingSms && !_smsMessages.empty())
                _smsMessages.back().text += line;
        }
    }
    return resp;
}

GsmInterface::SmsMessage::SmsMessage(const std::string &in)
{
    std::vector<std::string> split;
    std::string current;
    bool instr = false;
    for (std::string::size_type i = 0; i < in.size(); ++i) {
        if (!instr && in[i] == ',') {
            split.push_back(current);
            current.clear();
        } else {
            if (in[i] == '\"')
                instr = !instr;
            else
                current += in[i];
        }
    }
    split.push_back(current);

    received = split.size() > 2 && split[2].compare(0, 4, "REC ") == 0;
    read = split.size() > 2 && split[2].find("READ") != std::string::npos;
    phoneNumber = split.size() > 3 ? split[3] : std::string();
    if (phoneNumber.compare(0,3,"+46")==0)
        phoneNumber = '0' + phoneNumber.substr(3);
    if (phoneNumber == "0709124262")
        phoneNumber = "Daniel Marjamäki";
    time = split.size() > 4 ? split[4] : std::string();
}

