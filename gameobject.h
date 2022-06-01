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

    int speedX, speedY, speedRad;

    int xLower, xUpper, yLower, yUpper; //boundary

    int collisionX, collisionY, collisionWidth, collisionHeight;//碰撞矩形在图片中的相对位置

    bool collision;   //是否参与碰撞

    bool stubborn;   //能不能被撞得动

    bool grativity;   //是否受重力下落

    GameObject() {}

    GameObject(QWidget *parent, QString str, int x, int y, int speedX = 0, int speedY = 0, int speedRad = 0, int xLower = MIN, int xUpper = MAX, int yLower = MIN, int yUpper = MAX, bool collision = true, bool stubborn = true, bool grativity = false, int collisionX = 0, int collisionY = 0, int collisionWidth = -1, int collisionHeight = -1); //-1代表未指定

    virtual ~GameObject(){}

    void paintEvent() = delete;

    int getX();

    int getY();

    int getWidth();

    int getHeight();

    QRect collisionRect();//返回碰撞矩形的绝对坐标

    QPixmap getImg();

    void setSpeed(int speedx, int speedy, int speedRad);

    void setReverseSpeed();

    void setXReverseSpeed();

    void setYReverseSpeed();

    void checkOutBorder();

    bool collisionWith(GameObject& other);

signals:

public slots:

    void updateLocation();

};

class VirtualObject : public GameObject
{
    Q_OBJECT

public:

    VirtualObject(QWidget *parent, QString str, int x, int y, int speedX = 0, int speedY = 0, int speedRad = 0, int xLower = MIN, int xUpper = MAX, int yLower = MIN, int yUpper = MAX, bool grativity = false, int collisionX = 0, int collisionY = 0, int collisionWidth = -1, int collisionHeight = -1);

    ~VirtualObject(){}

};//不参与碰撞的物体

class HeavyBody : public GameObject
{
    Q_OBJECT

public:

    HeavyBody(QWidget *parent, QString str, int x, int y, int speedX = 0, int speedY = 0, int speedRad = 0, int xLower = MIN, int xUpper = MAX, int yLower = MIN, int yUpper = MAX, bool grativity = false, int collisionX = 0, int collisionY = 0, int collisionWidth = -1, int collisionHeight = -1);

    ~HeavyBody(){}

};//参与碰撞，且碰撞不改变运动状态的物体

class Pushable : public GameObject
{
    Q_OBJECT

public:

    Pushable(QWidget *parent, QString str, int x, int y, int speedX = 0, int speedY = 0, int speedRad = 0, int xLower = MIN, int xUpper = MAX, int yLower = MIN, int yUpper = MAX, bool grativity = false, int collisionX = 0, int collisionY = 0, int collisionWidth = -1, int collisionHeight = -1);

    ~Pushable(){}

};//可以通过碰撞改变运动状态的物体

class Role : public GameObject
{
    Q_OBJECT
};

class LineBarrier : public GameObject
{
    Q_OBJECT
};

#endif // GAMEOBJECT_H
