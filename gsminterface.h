#ifndef GSMINTERFACE_H
#define GSMINTERFACE_H

#include <QString>

class GsmInterface
{
public:
    GsmInterface();
    ~GsmInterface();

    bool AT() { return sendAndReceive("AT") == "OK"; }

private:
    QString sendAndReceive(const char cmd[]);
    bool writeLine(const char cmd[]);
    QString readLine();

    int fd;
};

extern GsmInterface gsmInterface;

#endif // GSMINTERFACE_H
