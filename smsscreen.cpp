#include "smsscreen.h"
#include "ui_smsscreen.h"
#include "gsminterface.h"

SmsScreen::SmsScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmsScreen)
{
    ui->setupUi(this);
    connect(ui->buttonHome, SIGNAL(clicked()), this, SIGNAL(gotoHomeScreen()));
}

SmsScreen::~SmsScreen()
{
    delete ui;
}

