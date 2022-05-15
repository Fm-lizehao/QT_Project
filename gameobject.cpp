#include "global.h"

#include "gameobject.h"

GameObject::GameObject(QWidget *parent, QString str, int x, int y, int speedX, int speedY, int speedRad, int xLower, int xUpper, int yLower, int yUpper, bool stubborn):QWidget(parent),img(str), speedX(speedX), speedY(speedY), speedRad(speedRad), xLower(xLower), xUpper(xUpper), yLower(yLower), yUpper(yUpper), isStubborn(stubborn)
{
    setFixedSize(QSize(img.width(),img.height()));
    move(x,y);
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
    return img.transformed(matrix,Qt::FastTransformation);
}

void GameObject::setSpeed(int speedx,int speedy,int speedrad)
{
    speedX=speedx;
    speedY=speedy;
    speedRad=speedrad;
    update();
}

void GameObject::setReverseSpeed()
{
    speedX=-speedX;
    speedY=-speedY;
    update();
}

void GameObject::checkOutBorder()
{
    if(x()<xLower)speedX=abs(speedX);
    if(x()+width()>xUpper)speedX=-abs(speedX);
    if(y()<yLower)speedY=abs(speedY);
    if(y()+height()>yUpper)speedY=-abs(speedY);
}

bool GameObject::isCollision(GameObject& other)
{
    return rect().intersects(other.rect());
}

void GameObject::updateLocation()
{
    checkOutBorder();
    matrix.rotate(speedRad);
    move(x()+speedX,y()+speedY);
    update();
}



IllusoryObject::IllusoryObject(QWidget *parent, QString str, int x, int y, int speedX, int speedY, int speedRad, int xLower, int xUpper, int yLower, int yUpper, bool stubborn):GameObject(parent, str, x, y, speedX, speedY, speedRad, xLower, xUpper, yLower, yUpper,stubborn)
{

}

IllusoryObject::~IllusoryObject()
{

}


RealObject::RealObject(QWidget *parent, QString str, int x, int y, int speedX, int speedY, int speedRad, int xLower, int xUpper, int yLower, int yUpper, bool stubborn):GameObject(parent, str, x, y, speedX, speedY, speedRad, xLower, xUpper, yLower, yUpper, stubborn)
{

}

RealObject::~RealObject()
{

}
