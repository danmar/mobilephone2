#include "ringscreen.h"
#include "ui_ringscreen.h"
#include "gsminterface.h"
#include <QTimer>

RingScreen::RingScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RingScreen)
{
    ui->setupUi(this);
    connect(ui->buttonAnswer, &QPushButton::clicked, this, &RingScreen::answer);
    connect(ui->buttonHangup, &QPushButton::clicked, this, &RingScreen::hangup);

    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    timer->setSingleShot(false);
    timer->start();
    connect(timer, &QTimer::timeout, this, &RingScreen::gsm);
    gsm();
}

RingScreen::~RingScreen()
{
    delete ui;
}

void RingScreen::gsm()
{
    std::string phoneNumber = gsmInterface.callerPhoneNumber();
    if (!gsmInterface.isRinging())
        emit(gotoHomeScreen());
    else
        ui->callerPhoneNumber->setText(phoneNumber.c_str());
}

void RingScreen::answer()
{
    gsmInterface.answer();
    emit(gotoHangupScreen());
}

void RingScreen::hangup()
{
    gsmInterface.hangUp();
    emit(gotoHomeScreen());
}
