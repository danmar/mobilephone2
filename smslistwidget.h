#ifndef SMSLISTWIDGET_H
#define SMSLISTWIDGET_H

#include <QWidget>
#include <QtWidgets>

class SmsListWidget : public QWidget {
    Q_OBJECT
public:
    explicit SmsListWidget(QWidget *parent = 0);

    void addItem(QString text);

signals:
    void openItem(QString phoneNumber);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void listAll();
    void details(int i);
    void drawMainScreen();
    void drawDetailsScreen();

    QStringList lines;
    int position;
    int y;
    enum { MAIN_SCREEN, DETAILS_SCREEN } screen;
    QFont boldFont;
    QFont normalFont;
};

#endif // SMSLISTWIDGET_H
