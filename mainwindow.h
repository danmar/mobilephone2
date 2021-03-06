#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void gsm();
    void gotoHomeScreen();
    void gotoPhoneScreen();
    void gotoHangUpScreen();
    void gotoSmsScreen();
    void gotoWriteSmsScreen(QString phoneNumber);

private:
    Ui::MainWindow *ui;
    QWidget *currentScreen;
};

#endif // MAINWINDOW_H
