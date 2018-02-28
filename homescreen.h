#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>

namespace Ui {
class HomeScreen;
}

class HomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HomeScreen(QWidget *parent = 0);
    ~HomeScreen();

signals:
    void gotoPhoneScreen();
    void gotoSmsScreen();

private:
    Ui::HomeScreen *ui;
};

#endif // HOMESCREEN_H
