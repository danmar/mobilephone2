#ifndef RINGSCREEN_H
#define RINGSCREEN_H

#include <QWidget>

namespace Ui {
    class RingScreen;
}

class RingScreen : public QWidget {
    Q_OBJECT

public:
    explicit RingScreen(QWidget *parent = 0);
    ~RingScreen();

public slots:
    void gsm();
    void answer();
    void hangup();

signals:
    void gotoHomeScreen();
    void gotoHangupScreen();

private:
    Ui::RingScreen *ui;
};

#endif // RINGSCREEN_H
