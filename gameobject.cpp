#include "gameobject.h"

GameObject::GameObject(QWidget *parent, QString str, int x, int y, int speedX, int speedY, int speedRad, int xLower, int xUpper, int yLower, int yUpper, attribute collision, attribute stubborn, attribute grativity, int collisionX, int collisionY, int collisionWidth, int collisionHeight)
    : QWidget(parent), img(str), speedX(speedX), speedY(speedY), speedRad(speedRad), xLower(xLower), xUpper(xUpper), yLower(yLower), yUpper(yUpper), collision(collision), stubborn(stubborn), grativity(grativity), collisionX(collisionX), collisionY(collisionY), collisionWidth(collisionWidth), collisionHeight(collisionHeight)
{
    setFixedSize(QSize(img.width(), img.height()));
    move(x, y);
    if (collisionWidth == -1)collisionWidth = img.width();
    if (collisionHeight == -1)collisionHeight = img.height();
}

QPixmap GameObject::getImg()
{
    QRect rect(0, 0, img.width(), img.height());
    auto retImg = img.transformed(matrix, Qt::SmoothTransformation);
    rect.moveCenter(retImg.rect().center());
    return retImg.copy(rect);
}

QRect GameObject::getCollisionRect()
{
    return QRect(x() + collisionX, y() + collisionY, collisionWidth, collisionHeight);
}

void GameObject::setLocation(int x, int y)
{
    move(x,y);
}

void GameObject::setX(int x)
{
    move(x,y());
}

void GameObject::setY(int y)
{
    move(x(),y);
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

void GameObject::setLeftSpeed()
{
    speedX = -abs(speedX);
}

void GameObject::setRightSpeed()
{
    speedX = abs(speedX);
}

void GameObject::setUpSpeed()
{
    speedY = -abs(speedY);
}

void GameObject::setDownSpeed()
{
    speedY = abs(speedY);
}

state GameObject::collisionWith(GameObject& other)
{
    return getCollisionRect().intersects(other.getCollisionRect());
}

void GameObject::checkOutBorder()
{
    if (x() < xLower){speedX = abs(speedX);}
    if (x() + width() > xUpper){speedX = -abs(speedX);}
    if (y() < yLower){speedY = abs(speedY);}
    if (y() + height() > yUpper){speedY = -abs(speedY);}
}

void GameObject::updateLocation()
{
    matrix.translate(img.width() / 2.0, img.height() / 2.0);
    matrix.rotate(speedRad);
    matrix.translate(-img.width() / 2.0, -img.height() / 2.0);
    move(x() + speedX, y() + speedY);
}

VirtualObject::VirtualObject(QWidget *parent, QString str, int x, int y, int speedX, int speedY, int speedRad, int xLower, int xUpper, int yLower, int yUpper, attribute grativity, int collisionX, int collisionY, int collisionWidth, int collisionHeight)
    : GameObject(parent, str, x, y, speedX, speedY, speedRad, xLower, xUpper, yLower, yUpper, false, true, grativity, collisionX, collisionY, collisionWidth, collisionHeight)
{

}

HeavyBody::HeavyBody(QWidget *parent, QString str, int x, int y, int speedX, int speedY, int speedRad, int xLower, int xUpper, int yLower, int yUpper, attribute grativity, int collisionX, int collisionY, int collisionWidth, int collisionHeight)
    : GameObject(parent, str, x, y, speedX, speedY, speedRad, xLower, xUpper, yLower, yUpper, true, true, grativity, collisionX, collisionY, collisionWidth, collisionHeight)
{

}
Pushable::Pushable(QWidget *parent, QString str, int x, int y, int speedX, int speedY, int speedRad, int xLower, int xUpper, int yLower, int yUpper, attribute grativity, int collisionX, int collisionY, int collisionWidth, int collisionHeight)
    : GameObject(parent, str, x, y, speedX, speedY, speedRad, xLower, xUpper, yLower, yUpper, true, false, grativity, collisionX, collisionY, collisionWidth, collisionHeight)
{

}
