#include "mainwindow.h"
#include <QApplication>

#include "gsminterface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.showMaximized();

    gsmInterface.AT();
    gsmInterface.restart();
    gsmInterface.setAutoFetchSms(true);
    gsmInterface.fetchSmsMessagesFromFile();

    return a.exec();
}
