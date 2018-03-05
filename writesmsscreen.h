#ifndef WRITESMSSCREEN_H
#define WRITESMSSCREEN_H

#include <QWidget>

namespace Ui {
    class WriteSmsScreen;
}

class WriteSmsScreen : public QWidget {
    Q_OBJECT

public:
    explicit WriteSmsScreen(QWidget *parent, QString phoneNumber);
    ~WriteSmsScreen();

public slots:
    void virtualKeyPress(const char *key);
    void sendSms();

signals:
    void gotoHomeScreen();

private:
    Ui::WriteSmsScreen *ui;
};

#endif // WRITESMSSCREEN_H
