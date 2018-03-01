#ifndef PHONESCREEN_H
#define PHONESCREEN_H

#include <QWidget>

namespace Ui {
class PhoneScreen;
}

class PhoneScreen : public QWidget
{
    Q_OBJECT

public:
    explicit PhoneScreen(QWidget *parent = 0);
    ~PhoneScreen();

public slots:
    void nr(int);
    void delNr();
    void call();

signals:
    void gotoHomeScreen();
    void gotoHangUpScreen();

private:
    Ui::PhoneScreen *ui;
    QString number;
};

#endif // DIALSCREEN_H
