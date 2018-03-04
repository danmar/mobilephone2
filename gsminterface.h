#ifndef GSMINTERFACE_H
#define GSMINTERFACE_H

#include <string>
#include <ostream>
#include <vector>

class GsmInterface {
public:
    GsmInterface();
    ~GsmInterface();

    enum STATUS { SIND_RESTARTING=0, SIND_DISCONNECTED=8, SIND_CONNECTED=11 };

    void restart() {
        clearInputBuffer();
        writeLine("AT+CFUN=1,1");
        status = SIND_RESTARTING;
        lastSind = -1;
    }

    bool AT() {
        return sendAndReceive("AT") == "OK";
    }

    void dial(const std::string &number) {
        if (status == SIND_CONNECTED)
            writeLine(("ATD" + number).c_str());
    }

    bool sendSms(const char phoneNumber[], const char text[]);

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

    int getLastSind() {
        readLine();
        return lastSind;
    }

    struct SmsMessage {
        SmsMessage(const std::string &in);
        bool received;
        bool read;
        std::string phoneNumber;
        std::string time;
        std::string text;
    };

    void listSmsMessages() {
        clearInputBuffer();
        if (sendAndReceive("AT+CMGF=1") == "OK") {
            writeLine("AT+CMGL=\"REC ALL\"");
            listingSms = true;
        }
    }

    bool isListingSmsMessages() {
        if (listingSms)
            readLine();
        return listingSms;
    }

    std::vector<struct SmsMessage> getSmsMessages() const {
        return smsMessages;
    }

private:
    std::string sendAndReceive(const char cmd[]);
    bool writeLine(const char cmd[]);
    std::string readLine();
    void clearInputBuffer() {
        readLine();
    }

    int fd;
    std::ostream *debug;
    int lastSind;
    enum STATUS status;
    std::vector<struct SmsMessage> smsMessages;
    bool listingSms;  // AT+CMGL command is in progress
};

extern GsmInterface gsmInterface;

#endif // GSMINTERFACE_H
