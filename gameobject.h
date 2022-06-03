#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "global.h"

class GameObject : public QWidget
{
    Q_OBJECT

private:

    QPixmap img; //物体图片

public:

    QMatrix matrix; //物体旋转矩阵

    int speedX = 0, speedY = 0, speedRad = 0; //物体三种速度

    int xLower = MIN, xUpper = MAX, yLower = MIN, yUpper = MAX; //物体反弹边界

    nature collision = true;   //是否参与碰撞

    nature stubborn = true;   //是否撞不动

    nature grativity = false;   //是否受重力下落

    int collisionX = 0, collisionY = 0, collisionWidth = -1, collisionHeight = -1; //碰撞矩形在图片中的相对位置

    state falling = false;

    state cameraMoving = false;

    state propUp = false;

    state bounceUp = false;

    state weighDown = false;

    state propLeft = false;

    state propRight = false;

    state pushLeft = false;

    state pushRight = false;

    state breakIn = false;

    //基本函数：

    GameObject(QWidget *parent, QString str, int x, int y, int speedX = 0, int speedY = 0, int speedRad = 0, int xLower = MIN, int xUpper = MAX, int yLower = MIN, int yUpper = MAX, nature collision = true, nature stubborn = true, nature grativity = false, int collisionX = 0, int collisionY = 0, int collisionWidth = -1, int collisionHeight = -1); //-1代表未指定

    virtual ~GameObject(){}

    void paintEvent() = delete;

    //get函数：

    QPixmap getImg(); //返回应该显示的旋转后图片

    QRect getCollisionRect(); //返回碰撞矩形的绝对坐标

    //set函数：

    void setLocation(int x, int y);

    void setX(int x);

    void setY(int y);

    void setSpeed(int speedx, int speedy, int speedRad);

    void setReverseSpeed();

    void setXReverseSpeed();

    void setYReverseSpeed();

    void setLeftSpeed();

    void setRightSpeed();

    void setUpSpeed();

    void setDownSpeed();

    //主功能函数：

    state collisionWith(GameObject& other); //判断是否和另一物体碰撞

    void checkOutBorder(); //边界反弹

    void updateLocation(); //根据速度刷新位置

signals:

public slots:

};

class VirtualObject : public GameObject
{
    Q_OBJECT

public:

    VirtualObject(QWidget *parent, QString str, int x, int y, int speedX = 0, int speedY = 0, int speedRad = 0, int xLower = MIN, int xUpper = MAX, int yLower = MIN, int yUpper = MAX, nature grativity = false, int collisionX = 0, int collisionY = 0, int collisionWidth = -1, int collisionHeight = -1);

    ~VirtualObject(){}

};//不参与碰撞的物体

class HeavyBody : public GameObject
{
    Q_OBJECT

public:

    HeavyBody(QWidget *parent, QString str, int x, int y, int speedX = 0, int speedY = 0, int speedRad = 0, int xLower = MIN, int xUpper = MAX, int yLower = MIN, int yUpper = MAX, nature grativity = false, int collisionX = 0, int collisionY = 0, int collisionWidth = -1, int collisionHeight = -1);

    ~HeavyBody(){}

};//参与碰撞，且碰撞不改变运动状态的物体

class Pushable : public GameObject
{
    Q_OBJECT

public:

    Pushable(QWidget *parent, QString str, int x, int y, int speedX = 0, int speedY = 0, int speedRad = 0, int xLower = MIN, int xUpper = MAX, int yLower = MIN, int yUpper = MAX, nature grativity = false, int collisionX = 0, int collisionY = 0, int collisionWidth = -1, int collisionHeight = -1);

    ~Pushable(){}

};//可以通过碰撞改变运动状态的物体

class Role : public GameObject
{
    Q_OBJECT

    state killed = false;

};//所有角色，包括npc

class Player : public Role
{
    Q_OBJECT

    state leftKey = false;

    state rightKey = false;

    state upKey = false;

};//主角

#endif // GAMEOBJECT_H
