#ifndef DIALSCREEN_H
#define DIALSCREEN_H

#include <QWidget>

namespace Ui {
class DialScreen;
}

class DialScreen : public QWidget
{
    Q_OBJECT

public:
    explicit DialScreen(QWidget *parent = 0);
    ~DialScreen();

public slots:
    void nr(int);
    void delNr();

private:
    Ui::DialScreen *ui;
    QString number;
};

#endif // DIALSCREEN_H
