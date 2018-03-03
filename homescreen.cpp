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

void HomeScreen::status() {
    int sind = gsmInterface.getsind();
    const char *status;
    switch (sind) {
    case -1:
        status = "Unknown status";
        break;
    case 0:
        status = "SIM card removed";
        break;
    case 1:
        status = "SIM card inserted";
        break;
    case 3:
        status = "AT module is partially ready";
        break;
    case 4:
        status = "AT module is totally ready";
        break;
    case 8:
        status = "The network is lost";
        break;
    case 11:
        status = "Registered to network";
        break;
    default:
        status = "";
        break;
    }
    ui->label->setText(status);
}
