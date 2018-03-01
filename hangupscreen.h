#ifndef HANGUPSCREEN_H
#define HANGUPSCREEN_H

#include <QWidget>

namespace Ui {
class HangUpScreen;
}

class HangUpScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HangUpScreen(QWidget *parent = 0);
    ~HangUpScreen();

public slots:
    void hangUp();

signals:
    void gotoHomeScreen();

private:
    Ui::HangUpScreen *ui;
};

#endif // HANGUPSCREEN_H
