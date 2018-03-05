#include "mainwindow.h"
#include <QApplication>
#include <fstream>
#include "gsminterface.h"
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.showMaximized();

    std::ofstream fout((QDir::homePath() + "/gsminterface.log").toStdString().c_str());
    if (fout.is_open())
        gsmInterface.setDebug(fout);
    gsmInterface.AT();
    gsmInterface.restart();
    gsmInterface.setAutoFetchSms(true);
    gsmInterface.fetchSmsMessagesFromFile();

    return a.exec();
}
