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
    for (std::string phoneNumber : nrs) {
        if (phoneNumber == "0709124262")
            phoneNumber = "DM";
        ui->listWidget->addItem(QString::fromStdString(phoneNumber));
    }
}

SmsScreen::~SmsScreen()
{
    delete ui;
}

