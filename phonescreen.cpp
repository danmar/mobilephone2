#include "phonescreen.h"
#include "ui_phonescreen.h"
#include "gsminterface.h"

PhoneScreen::PhoneScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PhoneScreen)
{
    ui->setupUi(this);
    ui->label->setText("");
    connect(ui->button0, &QPushButton::clicked, this, [this]{ nr(0); });
    connect(ui->button1, &QPushButton::clicked, this, [this]{ nr(1); });
    connect(ui->button2, &QPushButton::clicked, this, [this]{ nr(2); });
    connect(ui->button3, &QPushButton::clicked, this, [this]{ nr(3); });
    connect(ui->button4, &QPushButton::clicked, this, [this]{ nr(4); });
    connect(ui->button5, &QPushButton::clicked, this, [this]{ nr(5); });
    connect(ui->button6, &QPushButton::clicked, this, [this]{ nr(6); });
    connect(ui->button7, &QPushButton::clicked, this, [this]{ nr(7); });
    connect(ui->button8, &QPushButton::clicked, this, [this]{ nr(8); });
    connect(ui->button9, &QPushButton::clicked, this, [this]{ nr(9); });
    connect(ui->buttonDel, &QPushButton::clicked, this, &PhoneScreen::delNr);
    connect(ui->buttonHome, &QPushButton::clicked, this, &PhoneScreen::gotoHomeScreen);
    connect(ui->buttonCall, &QPushButton::clicked, this, [this]{ gsmInterface.dial(number); });
}

PhoneScreen::~PhoneScreen()
{
    delete ui;
}

void PhoneScreen::nr(int digit) {
    number += QString::number(digit);
    ui->label->setText(number);
}

void PhoneScreen::delNr() {
    number.chop(1);
    ui->label->setText(number);
}
