#include "dialscreen.h"
#include "ui_dialscreen.h"

DialScreen::DialScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialScreen)
{
    ui->setupUi(this);
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
    connect(ui->buttonDel, &QPushButton::clicked, this, &DialScreen::delNr);
//    connect(ui->buttonOk, &QPushButton::clicked, this, %Dial::ok);
//    connect(ui->buttonAvbryt, &QPushButton::clicked, this, %Dial::avbryt);
}

DialScreen::~DialScreen()
{
    delete ui;
}

void DialScreen::nr(int digit) {
    number += QString::number(digit);
    ui->label->setText(tr("Number: %0").arg(number));
}

void DialScreen::delNr() {
    number.chop(1);
    ui->label->setText(tr("Number: %0").arg(number));
}
