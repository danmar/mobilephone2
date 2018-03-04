#include <iostream>
#include <ctime>
#include <unistd.h>
#include "gsminterface.h"

int main()
{
    gsmInterface.setDebug(std::cout);
    gsmInterface.restart();
    int count = 0;
    while (1) {
        count++;
        usleep(1000*1000);
        GsmInterface::STATUS status = gsmInterface.getStatus();

        std::cout << count << std::endl;

        if (count >= 50 && status == GsmInterface::STATUS::SIND_CONNECTED) {
            std::cout << "dial" << std::endl;
            gsmInterface.dial("0709124262");
            return 0;
        }

        if (status == GsmInterface::STATUS::SIND_DISCONNECTED && count > 1000) {
            gsmInterface.restart();
            count = 0;
        }
    }
    return 0;
}
