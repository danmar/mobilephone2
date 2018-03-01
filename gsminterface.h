#ifndef GSMINTERFACE_H
#define GSMINTERFACE_H

#include <QString>

class GsmInterface
{
public:
    GsmInterface();
    ~GsmInterface();

    bool AT() {
        return sendAndReceive("AT") == "OK";
    }

    void dial(const QString &number) {
        if (number.startsWith("070") && number.size() == 10)
            writeLine(("ATD" + number).toStdString().c_str());
    }

    int getsind() const {
        return sind;
    }

private:
    QString sendAndReceive(const char cmd[]);
    bool writeLine(const char cmd[]);
    QString readLine();

    int fd;
    int sind;
};

extern GsmInterface gsmInterface;

#endif // GSMINTERFACE_H
