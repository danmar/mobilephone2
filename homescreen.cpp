#include "homescreen.h"
#include "ui_homescreen.h"
#include "gsminterface.h"
#include <QTimer>

HomeScreen::HomeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeScreen)
{
    ui->setupUi(this);
    connect(ui->buttonPhone, SIGNAL(clicked()), this, SIGNAL(gotoPhoneScreen()));
    connect(ui->buttonSms, SIGNAL(clicked()), this, SIGNAL(gotoSmsScreen()));
    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    timer->setSingleShot(false);
    timer->start();
    connect(timer, &QTimer::timeout, this, &HomeScreen::status);
}

HomeScreen::~HomeScreen()
{
    delete ui;
}

void HomeScreen::status()
{
    GsmInterface::STATUS status = gsmInterface.getStatus();
    const char *str = "";
    switch (status) {
    case GsmInterface::STATUS::SIND_RESTARTING:
        str = "Restarting...";
        break;
    case GsmInterface::STATUS::SIND_DISCONNECTED:
        str = "Disconnected";
        break;
    case GsmInterface::STATUS::SIND_CONNECTED:
        str = "Connected";
        break;
    }
    ui->label->setText(str);
}
