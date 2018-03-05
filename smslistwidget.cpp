#include "smslistwidget.h"
#include <QtWidgets>
#include "gsminterface.h"
#include <list>

static const int ITEM_HEIGHT = 45;

SmsListWidget::SmsListWidget(QWidget *parent) : QWidget(parent), y(0)
{
    position = 0;
    boldFont = QFont("Serif", 10, QFont::Bold);
    normalFont = QFont("Serif", 10, QFont::Normal);
    listAll();
}

void SmsListWidget::listAll()
{
    currentPhoneNumber.clear();
    screen = MAIN_SCREEN;
    lines.clear();

    std::list<std::string> nrs;
    for (const struct GsmInterface::SmsMessage &m : gsmInterface.smsMessages()) {
        if (std::find(nrs.begin(), nrs.end(), m.phoneNumber) == nrs.end()) {
            nrs.push_back(m.phoneNumber);
        }
    }
    nrs.reverse();
    for (std::string phoneNumber : nrs) {
        lines << QString::fromStdString(phoneNumber);
    }

    update();
}

void SmsListWidget::details(int i)
{
    screen = DETAILS_SCREEN;
    currentPhoneNumber = lines[i];
    lines.clear();
    for (const struct GsmInterface::SmsMessage &m : gsmInterface.smsMessages()) {
        if (currentPhoneNumber == m.phoneNumber.c_str())
            lines << QString::fromStdString((m.received ? 'R' : 'S') + m.text);
    }
    update();
}

void SmsListWidget::addItem(QString text)
{
    lines << text;
    update();
}

void SmsListWidget::paintEvent(QPaintEvent*)
{
    if (screen == MAIN_SCREEN)
        drawMainScreen();
    else
        drawDetailsScreen();
}

void SmsListWidget::drawMainScreen()
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

static QStringList wordWrap(QString str, int width, const QFontMetrics &fontMetrics)
{
    QStringList ret;
    int i1 = 0, i2 = 0;
    QString currentLine = "";
    while ((i2 = str.indexOf(' ', i1+1)) >= 0) {
        QString word = str.mid(i1, i2-i1);
        i1 = i2;
        int tw = fontMetrics.width(currentLine + word);
        if (tw > width) {
            ret << currentLine.trimmed();
            currentLine = word.trimmed();
        } else {
            currentLine += word;
        }
    }
    ret << (currentLine + str.mid(i1));
    return ret;
}

void SmsListWidget::drawDetailsScreen()
{
    QPainter painter(this);
    painter.setBrush(QColor(255,255,255));
    painter.drawRect(rect());
    painter.setFont(normalFont);

    QFontMetrics fontMetrics(normalFont);
    int y = -position;
    for (int i = 0; i < lines.size(); ++i) {
        bool received = lines[i].startsWith("R");
        QStringList wrapped = wordWrap(lines[i].mid(1), 3 * width() / 4, fontMetrics);
        foreach (QString s, wrapped) {
            y += fontMetrics.height();
            painter.drawText(received ? (width() / 4 - 5) : 5, y, s);
        }
        y += 5;
        painter.drawLine(0,y,width(),y);
        y += 5;
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
    if (event->x() >= width() - 20) {
        const int y = position + event->y();
        details(y / ITEM_HEIGHT);
    } else {
        // soft scroll..
    }
}
