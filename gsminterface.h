#ifndef GSMINTERFACE_H
#define GSMINTERFACE_H

#include <string>

class GsmInterface
{
public:
    GsmInterface();
    ~GsmInterface();

    bool AT() {
        return sendAndReceive("AT") == "OK";
    }

    void dial(const std::string &number) {
        writeLine(("ATD" + number).c_str());
    }

    void hangUp() {
        writeLine("ATH");
    }

    int getsind() const {
        return sind;
    }

private:
    std::string sendAndReceive(const char cmd[]);
    bool writeLine(const char cmd[]);
    std::string readLine();

    int fd;
    int sind;
};

extern GsmInterface gsmInterface;

#endif // GSMINTERFACE_H
