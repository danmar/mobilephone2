
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
    gsmInterface.listSmsMessages();
    while (gsmInterface.isListingSmsMessages()) {
        usleep(100000);
    }
    std::vector<GsmInterface::SmsMessage> v = gsmInterface.getSmsMessages();
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i].phoneNumber << ':' << v[i].time << ':' << v[i].text << std::endl;
    }
    return 0;
}

