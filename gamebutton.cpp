#include "gamebutton.h"

GameButton::GameButton(QWidget *parent, QString pic1, QString pic2, QString text, int x, int y, QObject* receiver, const char* method): QWidget(parent), img(pic1), img2(pic2), text(text)
{
	setFixedSize(QSize(img.width(), img.height()));
	move(x, y);
	connect(this, SIGNAL(clicked()), receiver, method);
}

GameButton::GameButton(QWidget *parent, QString pic, QString text, int x, int y, QObject* receiver, const char* method): QWidget(parent), img(pic), img2(pic), text(text)
{
	setFixedSize(QSize(img.width(), img.height()));
	move(x, y);
	connect(this, SIGNAL(clicked()), receiver, method);
}

GameButton::~GameButton()
{

}

void GameButton::enterEvent(QEvent *event)
{
	setFixedSize(QSize(img2.width(), img2.height()));
	move(x() + img.width() / 2 - img2.width() / 2, y() + img.height() / 2 - img2.height() / 2);
	flipped = true;
	update();
}

void GameButton::leaveEvent(QEvent *event)
{
	setFixedSize(QSize(img.width(), img.height()));
	move(x() + img2.width() / 2 - img.width() / 2, y() + img2.height() / 2 - img.height() / 2);
	flipped = false;
	update();
}

void GameButton::mouseReleaseEvent(QMouseEvent *e)
{
	emit clicked();
}
