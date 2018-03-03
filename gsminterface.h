#ifndef GSMINTERFACE_H
#define GSMINTERFACE_H

#include <string>

class GsmInterface
{
public:
    GsmInterface();
    ~GsmInterface();

    void restart() {
        sind = -1;
        writeLine("AT+CFUN=1,1");
    }

    bool AT() {
        return sendAndReceive("AT") == "OK";
    }

    void dial(const std::string &number) {
        writeLine(("ATD" + number).c_str());
    }

    void hangUp() {
        writeLine("ATH");
    }

    int getsind();

private:
    std::string sendAndReceive(const char cmd[]);
    bool writeLine(const char cmd[]);
    std::string readLine();

    int fd;
    int sind;
};

extern GsmInterface gsmInterface;

#endif // GSMINTERFACE_H
