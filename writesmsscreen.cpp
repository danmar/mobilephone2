#include "writesmsscreen.h"
#include "ui_writesmsscreen.h"
#include "virtualkeyboard.h"
#include "gsminterface.h"
#include <cstring>

WriteSmsScreen::WriteSmsScreen(QWidget *parent, QString phoneNumber) :
    QWidget(parent),
    ui(new Ui::WriteSmsScreen)
{
    ui->setupUi(this);
    connect(ui->virtualKeyboard, &VirtualKeyboard::keyPress, this, &WriteSmsScreen::virtualKeyPress);
    connect(ui->buttonHome, &QPushButton::clicked, this, &WriteSmsScreen::gotoHomeScreen);
    connect(ui->buttonSend, &QPushButton::clicked, this, &WriteSmsScreen::sendSms);
    ui->editTo->setText(phoneNumber);
    ui->editText->setFocus();
}

WriteSmsScreen::~WriteSmsScreen()
{
    delete ui;
}

void WriteSmsScreen::virtualKeyPress(const char *key)
{
    QLineEdit *edit;
    if (ui->editTo->hasFocus())
        edit = ui->editTo;
    else
        edit = ui->editText;

    if (std::strcmp(key,"BACKSPACE")==0)
        edit->backspace();
    else
        edit->insert(key);
}

void WriteSmsScreen::sendSms()
{
    gsmInterface.sendSms(ui->editTo->text().toStdString().c_str(), ui->editText->text().toStdString().c_str());
    emit(gotoHomeScreen());
}
