#include "homescreen.h"
#include "ui_homescreen.h"

HomeScreen::HomeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeScreen)
{
    ui->setupUi(this);
    connect(ui->buttonPhone, SIGNAL(clicked()), this, SIGNAL(gotoPhoneScreen()));
    connect(ui->buttonSms, SIGNAL(clicked()), this, SIGNAL(gotoSmsScreen()));
}

HomeScreen::~HomeScreen()
{
    delete ui;
}