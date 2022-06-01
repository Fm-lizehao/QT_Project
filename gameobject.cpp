#include "gameobject.h"

GameObject::GameObject(QWidget *parent, QString str, int x, int y, int speedX, int speedY, int speedRad, int xLower, int xUpper, int yLower, int yUpper, bool collision, bool stubborn, bool grativity, int collisionX, int collisionY, int collisionWidth, int collisionHeight): QWidget(parent), img(str), speedX(speedX), speedY(speedY), speedRad(speedRad), xLower(xLower), xUpper(xUpper), yLower(yLower), yUpper(yUpper), collision(collision), stubborn(stubborn), grativity(grativity), collisionX(collisionX), collisionY(collisionY), collisionWidth(collisionWidth), collisionHeight(collisionHeight)
{
	setFixedSize(QSize(img.width(), img.height()));
	move(x, y);
	if (collisionWidth == -1)collisionWidth = img.width();
	if (collisionHeight == -1)collisionHeight = img.height();
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

QRect GameObject::collisionRect()
{
	return QRect(x() + collisionX, y() + collisionY, collisionWidth, collisionHeight);
}

QPixmap GameObject::getImg()
{
	QRect rect(0, 0, img.width(), img.height());
	auto retImg = img.transformed(matrix, Qt::SmoothTransformation);
	rect.moveCenter(retImg.rect().center());
	return retImg.copy(rect);
}

void GameObject::setSpeed(int speedx, int speedy, int speedrad)
{
	speedX = speedx;
	speedY = speedy;
	speedRad = speedrad;
}

void GameObject::setReverseSpeed()
{
	speedX = -speedX;
	speedY = -speedY;
}

void GameObject::setXReverseSpeed()
{
	speedX = -speedX;
}

void GameObject::setYReverseSpeed()
{
	speedY = -speedY;
}

void GameObject::checkOutBorder()
{
	if (x() < xLower)speedX = abs(speedX);
	if (x() + width() > xUpper)speedX = -abs(speedX);
	if (y() < yLower)speedY = abs(speedY);
	if (y() + height() > yUpper)speedY = -abs(speedY);
}

bool GameObject::collisionWith(GameObject& other)
{
	return collisionRect().intersects(other.collisionRect());
}

void GameObject::updateLocation()
{
	matrix.translate(img.width() / 2.0, img.height() / 2.0);
	matrix.rotate(speedRad);
	matrix.translate(-img.width() / 2.0, -img.height() / 2.0);
	move(x() + speedX, y() + speedY);
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
