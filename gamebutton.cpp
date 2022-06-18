#include "gamepage.h"

GameButton::GameButton(GamePage *parent, initializer_list<QString> img_str, initializer_list<QString> text, QPoint point, QObject* receiver, const char* method)
    : QWidget(parent), source(img_str), text(text)
{
    for(auto i : img_str) img.push_back(QPixmap(i));
    resize(img[imgNow].size());
    move(point);
    connect(this, SIGNAL(clicked(GameButton*)), receiver, method);
}

void GameButton::enterEvent(QEvent *event)
{
    if (img.size() == 1) move(x(), y() + 2);
    else {
        resize(img[1].size());
        move(x() + img[0].width() / 2 - img[1].width() / 2, y() + img[0].height() / 2 - img[1].height() / 2 + 2);
        imgNow = 1; }
}

void GameButton::leaveEvent(QEvent *event)
{
   if (img.size() == 1) move(x(), y() - 2);
   else {
       resize(img[0].size());
       move(x() + img[1].width() / 2 - img[0].width() / 2, y() + img[1].height() / 2 - img[0].height() / 2 - 2);
       imgNow = 0; }
}

void GameButton::mouseReleaseEvent(QMouseEvent *event) {if(event->button()==Qt::LeftButton) emit clicked(this); }
