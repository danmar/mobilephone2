#include "virtualkeyboard.h"
#include <QtWidgets>

static const char * const DIGITS[] = {"1","2","3","4","5","6","7","8","9", "0", "BACKSPACE"};
static const char * const KEYS1[] = {"q","w","e","r","t","y","u","i","o","p","å"};
static const char * const KEYS2[] = {"a","s","d","f","g","h","j","k","l","ö","ä"};
static const char * const KEYS3[] = {"z","x","c","v","b","n","m",",",".","-"};

VirtualKeyboard::VirtualKeyboard(QWidget *parent) : QWidget(parent)
{

}

static int getTextHeight(int fontSize)
{
    QFontMetrics fm(QFont("Serif", fontSize, QFont::Normal));
    return fm.height();
}

static void drawRow(QPainter &painter, int left, int top, int width, int div, const QFontMetrics &fontMetrics, const char * const * const keys, int numkeys)
{
    for (int i = 0; i < numkeys; i++) {
        int x1 = left + i * width / div;
        int x2 = (i+1) * width / div;
        int y1 = top;
        int y2 = top + width / div;
        QString s(keys[i]);
        if (s == "BACKSPACE")
            s = "<";
        painter.drawRect(x1, y1, x2-x1, y2-y1);
        painter.drawText((x1+x2-fontMetrics.width(s))/2, (y1+y2+fontMetrics.width(s))/2, s);
    }
}

void VirtualKeyboard::paintEvent(QPaintEvent *)
{
    const int kbwidth = width() - 10;
    const int divisor = 11;

    int fontSize = 24;
    while (fontSize > 8 && getTextHeight(fontSize) > kbwidth / divisor)
        fontSize -= 2;

    QPainter painter(this);
    const QFont font("Serif",fontSize,QFont::Normal);
    painter.setFont(font);
    const QFontMetrics fontMetrics(font);

    drawRow(painter, 5, 5, kbwidth, divisor, fontMetrics, DIGITS, sizeof(DIGITS) / sizeof(DIGITS[0]));
    drawRow(painter, 5, 5+kbwidth/divisor, kbwidth, divisor, fontMetrics, KEYS1, sizeof(KEYS1) / sizeof(KEYS1[0]));
    drawRow(painter, 5, 5+2*(kbwidth/divisor), kbwidth, divisor, fontMetrics, KEYS2, sizeof(KEYS2) / sizeof(KEYS2[0]));
    drawRow(painter, 5, 5+3*(kbwidth/divisor), kbwidth, divisor, fontMetrics, KEYS3, sizeof(KEYS3) / sizeof(KEYS3[0]));
    painter.drawRect(5, 5+4*(kbwidth/divisor), kbwidth, kbwidth/divisor);
}

void VirtualKeyboard::mousePressEvent(QMouseEvent *event)
{
    const int kbwidth = width() - 10;
    const int divisor = 11;
    const int keyIndex = (event->x() - 5) / (kbwidth / divisor);
    switch ((event->y() - 5) / (kbwidth / divisor)) {
    case 0:
        keyPress1(DIGITS, keyIndex, sizeof(DIGITS) / sizeof(DIGITS[0]));
        break;
    case 1:
        keyPress1(KEYS1, keyIndex, sizeof(KEYS1) / sizeof(KEYS1[0]));
        break;
    case 2:
        keyPress1(KEYS2, keyIndex, sizeof(KEYS2) / sizeof(KEYS2[0]));
        break;
    case 3:
        keyPress1(KEYS3, keyIndex, sizeof(KEYS3) / sizeof(KEYS3[0]));
        break;
    case 4:
        keyPress(" ");
    }
}

void VirtualKeyboard::keyPress1(const char * const * keys, int keyIndex, int numkeys)
{
    if (keyIndex >= 0 && keyIndex < numkeys)
        emit(keyPress(keys[keyIndex]));
}
