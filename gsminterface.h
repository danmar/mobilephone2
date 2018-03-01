#ifndef GSMINTERFACE_H
#define GSMINTERFACE_H

#include <QString>

class GsmInterface
{
public:
    GsmInterface();
    ~GsmInterface();
    QString sendAndReceive(const char cmd[]);
    bool writeLine(const char cmd[]);
    QString readLine();
private:
    int fd;
};

extern GsmInterface gsmInterface;

#endif // GSMINTERFACE_H
