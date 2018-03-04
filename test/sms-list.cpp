
#include <iostream>
#include <ctime>
#include <unistd.h>
#include "gsminterface.h"

int main()
{
    gsmInterface.setDebug(std::cout);
    //gsmInterface.restart();
    if (!gsmInterface.AT()) {
        std::cout << "AT failed\n";
        return 1;
    }
    gsmInterface.fetchSmsMessages();
    while (gsmInterface.isFetchingSmsMessages()) {
        usleep(100000);
    }
    const std::vector<GsmInterface::SmsMessage> &v = gsmInterface.smsMessages();
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i].phoneNumber << ':' << v[i].time << ':' << v[i].text << std::endl;
    }
    return 0;
}

