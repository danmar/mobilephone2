#include "smslistwidget.h"
#include <QtWidgets>

static const int ITEM_HEIGHT = 45;

SmsListWidget::SmsListWidget(QWidget *parent) : QWidget(parent), y(0)
{
    position = 0;
    boldFont = QFont("Serif", 10, QFont::Bold);
    normalFont = QFont("Serif", 10, QFont::Normal);
}

void SmsListWidget::addItem(QString text)
{
    lines << text;
    update();
}

void SmsListWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.setBrush(QColor(255,255,255));
    painter.drawRect(rect());

    for (int i = 0; i < lines.size(); ++i) {
        const QString &line = lines[i];
        int y = ITEM_HEIGHT * i - position;
        int nl = line.indexOf('\n');
        const QString line1 = (nl>=0) ? line.mid(0,nl) : line;
        const QString line2 = (nl>=0) ? line.mid(nl+1, 20) : QString();
        const QFontMetrics fontMetrics(normalFont);
        painter.setFont(boldFont);
        painter.drawText(5, y + fontMetrics.height(), line1);
        painter.setFont(normalFont);
        painter.drawText(5, y + 2 * fontMetrics.height(), line2);

        // >
        const int y1 = y + ITEM_HEIGHT / 2;
        painter.setPen(QColor(0, 0, 0x40));
        painter.drawLine(width()-20, y1-8, width()-12, y1);
        painter.drawLine(width()-20, y1+8, width()-12, y1);

        painter.setPen(QColor(0x40, 0x40, 0x40));
        painter.drawLine(0, y+40, width(), y+40);
    }
}

void SmsListWidget::resizeEvent(QResizeEvent*)
{
    update();
}

void SmsListWidget::mousePressEvent(QMouseEvent *event)
{
    y = event->y();
}

void SmsListWidget::mouseMoveEvent(QMouseEvent *event)
{
    int oldpos = position;
    position += y - event->y();
    if (position < 0)
        position = 0;
    if (position > 20 * lines.size())
        position = 20 * lines.size();
    y = event->y();
    if (position != oldpos)
        update();
}

void SmsListWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->x() < width() - 20)
        return;
    const int y = position + event->y();
    const int itemIndex = y / ITEM_HEIGHT;
    qDebug() << itemIndex;
}
