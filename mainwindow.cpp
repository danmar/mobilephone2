#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "homescreen.h"
#include "smsscreen.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currentScreen = nullptr;
    gotoHomeScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::gotoHomeScreen()
{
    delete currentScreen;
    HomeScreen *homeScreen = new HomeScreen(this);
    connect(homeScreen, &HomeScreen::gotoSmsScreen, this, &MainWindow::gotoSmsScreen);
    currentScreen = homeScreen;
    ui->centralWidget->layout()->addWidget(currentScreen);
}

void MainWindow::gotoSmsScreen()
{
    delete currentScreen;
    SmsScreen *smsScreen = new SmsScreen(this);
    ui->centralWidget->layout()->addWidget(smsScreen);
    connect(smsScreen, &SmsScreen::gotoHomeScreen, this, &MainWindow::gotoHomeScreen);
    currentScreen = smsScreen;
    ui->centralWidget->layout()->addWidget(currentScreen);
}
