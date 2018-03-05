#include "smsscreen.h"
#include "ui_smsscreen.h"
#include "gsminterface.h"

SmsScreen::SmsScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmsScreen)
{
    ui->setupUi(this);
    connect(ui->buttonHome, SIGNAL(clicked()), this, SIGNAL(gotoHomeScreen()));

    std::list<std::string> nrs;
    for (const struct GsmInterface::SmsMessage &m : gsmInterface.smsMessages()) {
        if (std::find(nrs.begin(), nrs.end(), m.phoneNumber) == nrs.end()) {
            nrs.push_back(m.phoneNumber);
        }
    }
    nrs.reverse();
    for (int i = 0; i < 10; i++)
        nrs.push_back("+46709124262" + QString::number(i).toStdString() + "\nabcd");
    for (std::string phoneNumber : nrs) {
        if (phoneNumber.compare(0,3,"+46")==0)
            phoneNumber = '0' + phoneNumber.substr(3);
        if (phoneNumber == "0709124262")
            phoneNumber = "Daniel Marjamäki";
        ui->listWidget->addItem(QString::fromStdString(phoneNumber));
    }
}

SmsScreen::~SmsScreen()
{
    delete ui;
}

