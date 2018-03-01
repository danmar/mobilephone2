#include "hangupscreen.h"
#include "ui_hangupscreen.h"

#include "gsminterface.h"

HangUpScreen::HangUpScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HangUpScreen)
{
    ui->setupUi(this);
    connect(ui->buttonHangUp, &QPushButton::clicked, this, &HangUpScreen::hangUp);
}

HangUpScreen::~HangUpScreen()
{
    delete ui;
}

void HangUpScreen::hangUp()
{
    gsmInterface.hangUp();
    emit(gotoHomeScreen());
}
