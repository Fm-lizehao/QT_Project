#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "global.h"

class GameObject : public QWidget
{
    Q_OBJECT

private:

    QPixmap img;

public:

    QMatrix matrix;

    int speedX,speedY,speedRad;

    int xLower,xUpper,yLower,yUpper;

    bool isStubborn;   //能不能被撞得动

    GameObject(){}

    GameObject(QWidget *parent, QString str, int x, int y, int speedX=0, int speedY=0, int speedRad=0, int xLower=MIN, int xUpper=MAX, int yLower=MIN, int yUpper=MAX, bool stubborn=true);

    ~GameObject();

    int getX();

    int getY();

    int getWidth();

    int getHeight();

    QPixmap getImg();

    void setSpeed(int speedx,int speedy,int speedRad);

    void setReverseSpeed();

    void checkOutBorder();

    bool isCollision(GameObject& other);

signals:

public slots:

    void updateLocation();

};


class IllusoryObject : public GameObject
{
    Q_OBJECT

public:

    IllusoryObject(){}

    IllusoryObject(QWidget *parent, QString str, int x, int y, int speedX=0, int speedY=0, int speedRad=0, int xLower=MIN, int xUpper=MAX, int yLower=MIN, int yUpper=MAX, bool stubborn=true);

    ~IllusoryObject();

};


class RealObject : public GameObject
{
    Q_OBJECT

public:

    RealObject(){}

    RealObject(QWidget *parent, QString str, int x, int y, int speedX=0, int speedY=0, int speedRad=0, int xLower=MIN, int xUpper=MAX, int yLower=MIN, int yUpper=MAX, bool stubborn=true);

    ~RealObject();

};


class LineBarrier : public RealObject
{
    Q_OBJECT
};


class Role : public RealObject
{
    Q_OBJECT
};

#endif // GAMEOBJECT_H
