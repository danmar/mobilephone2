#ifndef SMSSCREEN_H
#define SMSSCREEN_H

#include <QWidget>

namespace Ui {
    class SmsScreen;
}

class SmsScreen : public QWidget {
    Q_OBJECT

public:
    explicit SmsScreen(QWidget *parent = 0);
    ~SmsScreen();

signals:
    void gotoHomeScreen();

private:
    Ui::SmsScreen *ui;
    QStringList smstitles;
};

#endif // SMSSCREEN_H
