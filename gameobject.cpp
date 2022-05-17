#include "gameobject.h"

GameObject::GameObject(QWidget *parent, QString str, int x, int y, int speedX, int speedY, int speedRad, int xLower, int xUpper, int yLower, int yUpper, bool collision, bool stubborn, bool grativity): QWidget(parent), img(str), speedX(speedX), speedY(speedY), speedRad(speedRad), xLower(xLower), xUpper(xUpper), yLower(yLower), yUpper(yUpper), inCollision(collision), isStubborn(stubborn), grativity(grativity)
{
	setFixedSize(QSize(img.width(), img.height()));
	move(x, y);
    INTIME(updateLocation);
}

GameObject::~GameObject()
{

}

int GameObject::getX()
{
	return x();
}

int GameObject::getY()
{
	return y();
}

int GameObject::getWidth()
{
	return width();
}

int GameObject::getHeight()
{
	return height();
}

QPixmap GameObject::getImg()
{
    QRect rect(0,0,img.width(),img.height());
    auto retImg=img.transformed(matrix, Qt::SmoothTransformation);
    rect.moveCenter(retImg.rect().center());
    return retImg.copy(rect);
}

void GameObject::setSpeed(int speedx, int speedy, int speedrad)
{
	speedX = speedx;
	speedY = speedy;
	speedRad = speedrad;
	update();
}

void GameObject::setReverseSpeed()
{
	speedX = -speedX;
	speedY = -speedY;
	update();
}

void GameObject::setXReverseSpeed()
{
    speedX = -speedX;
    update();
}

void GameObject::setYReverseSpeed()
{
    speedY = -speedY;
    update();
}

void GameObject::checkOutBorder()
{
	if (x() < xLower)speedX = abs(speedX);
	if (x() + width() > xUpper)speedX = -abs(speedX);
	if (y() < yLower)speedY = abs(speedY);
	if (y() + height() > yUpper)speedY = -abs(speedY);
}

bool GameObject::isCollision(GameObject& other)
{
	return rect().intersects(other.rect());
}

void GameObject::updateLocation()
{
	checkOutBorder();
    matrix.translate(img.width()/2.0, img.height()/2.0);
	matrix.rotate(speedRad);
    matrix.translate(-img.width()/2.0, -img.height()/2.0);
	move(x() + speedX, y() + speedY);
	update();
}

VirtualObject::VirtualObject(QWidget *parent, QString str, int x, int y, int speedX, int speedY, int speedRad, int xLower, int xUpper, int yLower, int yUpper, bool grativity) : GameObject(parent, str, x, y, speedX, speedY, speedRad, xLower, xUpper, yLower, yUpper, false, true, grativity)
{

}

VirtualObject::~VirtualObject()
{

}

HeavyBody::HeavyBody(QWidget *parent, QString str, int x, int y, int speedX, int speedY, int speedRad, int xLower, int xUpper, int yLower, int yUpper, bool grativity) : GameObject(parent, str, x, y, speedX, speedY, speedRad, xLower, xUpper, yLower, yUpper, true, true, grativity)
{

}

HeavyBody::~HeavyBody()
{

}

Pushable::Pushable(QWidget *parent, QString str, int x, int y, int speedX, int speedY, int speedRad, int xLower, int xUpper, int yLower, int yUpper, bool grativity) : GameObject(parent, str, x, y, speedX, speedY, speedRad, xLower, xUpper, yLower, yUpper, true, false, grativity)
{

}

Pushable::~Pushable()
{

}
