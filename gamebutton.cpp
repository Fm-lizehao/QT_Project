#include "gamebutton.h"
#include "gamepage.h"

GameButton::GameButton(GamePage *parent, QString pic1, QString pic2, QString text, int x, int y, QObject* receiver, const char* method)
    : QWidget(parent), img(pic1), img2(pic2), text(text)
{
    changeMode = 1;
    setFixedSize(QSize(img.width(), img.height()));
    move(x, y);
    connect(this, SIGNAL(clicked()), receiver, method);
}

GameButton::GameButton(GamePage *parent, QString pic, QString text, int x, int y, QObject* receiver, const char* method)
    : QWidget(parent), img(pic), img2(pic), text(text)
{
    changeMode = 2;
    setFixedSize(QSize(img.width(), img.height()));
    move(x, y);
    connect(this, SIGNAL(clicked()), receiver, method);
}

QPixmap GameButton::getImg()
{
    if (flipped) return img2;
    else         return img;
}

void GameButton::enterEvent(QEvent *event)
{
    if (changeMode == 1)
    {
        setFixedSize(QSize(img2.width(), img2.height()));
        move(x() + img.width()/2 - img2.width()/2, y() + img.height()/2 - img2.height()/2 + 2);
        flipped = true;
    }
    else if (changeMode == 2) move(x(), y() + 5);
}

void GameButton::leaveEvent(QEvent *event)
{
    if (changeMode == 1)
    {
        setFixedSize(QSize(img.width(), img.height()));
        move(x() + img2.width()/2 - img.width()/2, y() + img2.height()/2 - img.height()/2 - 2);
        flipped = false;
    }
    else if (changeMode == 2) move(x(), y() - 5);
}

void GameButton::mouseReleaseEvent(QMouseEvent *event) { emit clicked(); }
