#include "smsscreen.h"
#include "ui_smsscreen.h"

SmsScreen::SmsScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmsScreen)
{
    ui->setupUi(this);
    connect(ui->buttonHome, SIGNAL(clicked()), this, SIGNAL(gotoHomeScreen()));
    for (int i = 1; i <= 100; i++)
        smstitles << ("Message" + QString::number(i));
    ui->listWidget->addItems(smstitles);
}

SmsScreen::~SmsScreen()
{
    delete ui;
}
