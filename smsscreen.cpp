#include "smsscreen.h"
#include "ui_smsscreen.h"
#include "gsminterface.h"

SmsScreen::SmsScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmsScreen)
{
    ui->setupUi(this);
    connect(ui->buttonHome, &QPushButton::clicked, this, &SmsScreen::gotoHomeScreen);
    connect(ui->buttonAdd, &QPushButton::clicked, this, [this] { emit(SmsScreen::gotoWriteSmsScreen(ui->listWidget->getPhoneNumber())); });
}

SmsScreen::~SmsScreen()
{
    delete ui;
}

