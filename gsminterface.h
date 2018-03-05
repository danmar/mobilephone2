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
    }

    bool AT();

    void dial(const std::string &number) {
        if (status == SIND_CONNECTED)
            writeLine(("ATD" + number).c_str());
    }

    void answer() {
        if (ringing)
            sendAndReceive("ATA");
        ringing = false;
        clip.clear();
    }

    bool isRinging() {
        readLine();
        return ringing;
    }

    std::string callerPhoneNumber() {
        return clip;
    }

    bool sendSms(const char phoneNumber[], const char text[]);

    void hangUp() {
        sendAndReceive("ATH");
        ringing = false;
        clip.clear();
    }

    void setDebug(std::ostream &ostr) {
        debug = &ostr;
    }

    STATUS getStatus() {
        readLine();
        return status;
    }

    struct SmsMessage {
        SmsMessage(const std::string &in);
        bool received;
        bool read;
        std::string phoneNumber;
        std::string time;
        std::string text;
    };

    void fetchSmsMessages() {
        if (fetchingSms)
            return;
        clearInputBuffer();
        if (sendAndReceive("AT+CMGF=1") == "OK") {
            writeLine("AT+CMGL=\"ALL\"");
            fetchingSms = true;
            _smsMessages.clear();
        }
    }

    void fetchSmsMessagesFromFile();

    bool isFetchingSmsMessages() {
        if (fetchingSms)
            readLine();
        return fetchingSms;
    }

    const std::vector<struct SmsMessage> &smsMessages() const {
        return _smsMessages;
    }

    void setAutoFetchSms(bool b) {
        autoFetchSms = b;
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
    enum STATUS status;
    std::vector<struct SmsMessage> _smsMessages;
    bool fetchingSms;  // AT+CMGL command is in progress
    bool autoFetchSms;
    bool ringing;
    std::string clip;
};

extern GsmInterface gsmInterface;

#endif // GSMINTERFACE_H
