#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gsminterface.h"
#include "homescreen.h"
#include "phonescreen.h"
#include "hangupscreen.h"
#include "ringscreen.h"
#include "smsscreen.h"
#include "writesmsscreen.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentScreen(nullptr)
{
    ui->setupUi(this);
    gotoHomeScreen();

    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    timer->setSingleShot(false);
    timer->start();
    connect(timer, &QTimer::timeout, this, &MainWindow::gsm);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::gsm()
{
    if (gsmInterface.isRinging()) {
        delete currentScreen;
        RingScreen *ringScreen = new RingScreen(this);
        connect(ringScreen, &RingScreen::gotoHomeScreen, this, &MainWindow::gotoHomeScreen);
        connect(ringScreen, &RingScreen::gotoHangupScreen, this, &MainWindow::gotoHangUpScreen);
        currentScreen = ringScreen;
        ui->centralWidget->layout()->addWidget(currentScreen);
    }
}

void MainWindow::gotoHomeScreen()
{
    delete currentScreen;
    HomeScreen *homeScreen = new HomeScreen(this);
    connect(homeScreen, &HomeScreen::gotoPhoneScreen, this, &MainWindow::gotoPhoneScreen);
    connect(homeScreen, &HomeScreen::gotoSmsScreen, this, &MainWindow::gotoSmsScreen);
    currentScreen = homeScreen;
    ui->centralWidget->layout()->addWidget(currentScreen);
}

void MainWindow::gotoPhoneScreen()
{
    delete currentScreen;
    PhoneScreen *phoneScreen = new PhoneScreen(this);
    connect(phoneScreen, &PhoneScreen::gotoHomeScreen, this, &MainWindow::gotoHomeScreen);
    connect(phoneScreen, &PhoneScreen::gotoHangUpScreen, this, &MainWindow::gotoHangUpScreen);
    currentScreen = phoneScreen;
    ui->centralWidget->layout()->addWidget(currentScreen);
}

void MainWindow::gotoHangUpScreen()
{
    delete currentScreen;
    HangUpScreen *hangUpScreen = new HangUpScreen(this);
    connect(hangUpScreen, &HangUpScreen::gotoHomeScreen, this, &MainWindow::gotoHomeScreen);
    currentScreen = hangUpScreen;
    ui->centralWidget->layout()->addWidget(currentScreen);
}

void MainWindow::gotoSmsScreen()
{
    delete currentScreen;
    SmsScreen *smsScreen = new SmsScreen(this);
    ui->centralWidget->layout()->addWidget(smsScreen);
    connect(smsScreen, &SmsScreen::gotoHomeScreen, this, &MainWindow::gotoHomeScreen);
    connect(smsScreen, &SmsScreen::gotoWriteSmsScreen, this, &MainWindow::gotoWriteSmsScreen);
    currentScreen = smsScreen;
    ui->centralWidget->layout()->addWidget(currentScreen);
}

void MainWindow::gotoWriteSmsScreen(QString phoneNumber)
{
    delete currentScreen;
    WriteSmsScreen *writeSmsScreen = new WriteSmsScreen(this, phoneNumber);
    ui->centralWidget->layout()->addWidget(writeSmsScreen);
    connect(writeSmsScreen, &WriteSmsScreen::gotoHomeScreen, this, &MainWindow::gotoHomeScreen);
    currentScreen = writeSmsScreen;
    ui->centralWidget->layout()->addWidget(currentScreen);
}
