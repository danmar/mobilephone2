#ifndef GSMINTERFACE_H
#define GSMINTERFACE_H

#include <string>
#include <ostream>

class GsmInterface {
public:
    GsmInterface();
    ~GsmInterface();

    enum STATUS { SIND_RESTARTING=0, SIND_DISCONNECTED=8, SIND_CONNECTED=11 };

    void restart() {
        writeLine("AT+CFUN=1,1");
        status = SIND_RESTARTING;
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

    void setDebug(std::ostream &ostr) {
        debug = &ostr;
    }

    STATUS getStatus() {
        readLine();
        return status;
    }

private:
    std::string sendAndReceive(const char cmd[]);
    bool writeLine(const char cmd[]);
    std::string readLine();

    int fd;
    std::ostream *debug;
    enum STATUS status;
};

extern GsmInterface gsmInterface;

#endif // GSMINTERFACE_H
