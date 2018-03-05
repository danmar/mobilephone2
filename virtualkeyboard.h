#ifndef VIRTUALKEYBOARD_H
#define VIRTUALKEYBOARD_H

#include <QWidget>

class VirtualKeyboard : public QWidget {
    Q_OBJECT
public:
    explicit VirtualKeyboard(QWidget *parent = 0);

signals:
    void keyPress(const char *key);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *) override;

private:
    void keyPress1(const char * const * keys, int keyIndex, int numkeys);
};

#endif // VIRTUALKEYBOARD_H
