#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "global.h"

class FloatRect //float版本的Rect类
{

public:

    float x = 0, y = 0, width = 0, height = 0;

    FloatRect(float x = 0, float y = 0, float width = 0, float height = 0)
        :x(x), y(y), width(width), height(height) { }

    ~FloatRect() { }

};

class GameObject : public QWidget
{
    Q_OBJECT

private:

    QPixmap img; //物体图片

public:

    QMatrix matrix; //物体旋转矩阵

    state propup = false; //是否被向上支撑

    state propleft = false; //是否被向左支撑

    state propright = false; //是否被向右支撑

    state pushleft = false; //是否被向左推

    state pushright = false; //是否被向右推

    state bounceup = false; //是否应当向上弹（调用函数后立即恢复）

    state bouncedown = false; //是否应当向下弹（调用函数后立即恢复）

    state bounceleft = false; //是否应当向左弹（调用函数后立即恢复）

    state bounceright = false; //是否应当向右弹（调用函数后立即恢复）

    GameObject* downObject = nullptr; //脚下的物体

    GameObject* leftObject = nullptr; //左边紧靠的物体

    GameObject* rightObject = nullptr; //右边紧靠的物体

    float aX = 0, aY = 0; //物体横纵加速度

    float realSpeedX = 0, realSpeedY = 0, realSpeedRad = 0; //物体实际的三种速度（地面参考系下）

    float& cameraSpeedX, cameraSpeedY; //相机速度，引用GamePage中的cameraSpeedX和cameraSpeedY

    float realX = 0, realY = 0, realRad = 0; //物体实际的位置（地面参考系下）

    float& cameraX, cameraY; //相机左上角位置，引用GamePage中的cameraX和cameraY

    int xLower = MIN, xUpper = MAX, yLower = MIN, yUpper = MAX; //物体反弹边界

    attribute collision = true;   //是否参与碰撞

    attribute stubborn = true;   //是否撞不动

    attribute grativity = false;   //是否受重力下落

    int collisionX = 0, collisionY = 0, collisionWidth = -1, collisionHeight = -1; //碰撞矩形在图片中的相对位置，-1代表图片的宽和高

    //基本函数：

    GameObject(GamePage *parent, QString str, float realX, float realY, float realSpeedX = 0, float realSpeedY = 0, float realSpeedRad = 0, int xLower = MIN, int xUpper = MAX, int yLower = MIN, int yUpper = MAX, attribute collision = true, attribute stubborn = true, attribute grativity = false, int collisionx = 0, int collisiony = 0, int collisionwidth = -1, int collisionheight = -1); //-1代表未指定，默认为图片的宽和高

    virtual ~GameObject(){}

    void paintEvent() = delete;

    //get函数：

    QPixmap getImg(); //返回应该显示的旋转后图片

    FloatRect getCollisionRect(); //返回碰撞矩形的绝对坐标

    //set函数：

    void setLocation(float x, float y); //更改位置

    void setX(float x); //更改水平坐标

    void setY(float y); //更改垂直坐标

    void setSpeed(float x, float y, float rad); //设置速度

    void setXSpeed(float x); //设置水平速度

    void setYSpeed(float y); //设置垂直速度

    void setRadSpeed(float rad); //设置角速度

    void setReverseSpeed(); //设为反向速度

    void setXReverseSpeed(); //设为水平反向速度

    void setYReverseSpeed(); //设为垂直反向速度

    void setLeftSpeed(); //设置水平速度向左

    void setRightSpeed(); //设置水平速度向右

    void setUpSpeed(); //设置垂直速度向上

    void setDownSpeed(); //设置垂直速度向下

    //主功能函数：

    void checkBorder(); //边界反弹

    void checkState(); //检查当前状态，避免矛盾

    void useState(); //使用当前状态设置加速度、速度、位置

    void updateSpeed(); //根据加速度刷新速度

    void updateLocation(); //根据速度刷新位置

    void selfUpdate(); //实际接口，依次调用checkBorder,checkState,useState,updateSpeed,updateLocation

signals:

public slots:

    //槽函数：

};

class VirtualObject : public GameObject
{
    Q_OBJECT

public:

    state breakin = false;    //是否被主角穿过

    VirtualObject(GamePage *parent, QString str, float realX, float realY, float realSpeedX = 0, float realSpeedY = 0, float realSpeedRad = 0, int xLower = MIN, int xUpper = MAX, int yLower = MIN, int yUpper = MAX, attribute grativity = false, int collisionx = 0, int collisiony = 0, int collisionwidth = -1, int collisionheight = -1)
        : GameObject(parent, str, realX, realY, realSpeedX, realSpeedY, realSpeedRad, xLower, xUpper, yLower, yUpper, false, true, grativity, collisionx, collisiony, collisionwidth, collisionheight) { }

    ~VirtualObject() { }

};//不参与碰撞的物体

class HeavyBody : public GameObject
{
    Q_OBJECT

public:

    state weighdown = false;    //是否被压下去

    HeavyBody(GamePage *parent, QString str, float realX, float realY, float realSpeedX = 0, float realSpeedY = 0, float realSpeedRad = 0, int xLower = MIN, int xUpper = MAX, int yLower = MIN, int yUpper = MAX, attribute grativity = false, int collisionx = 0, int collisiony = 0, int collisionwidth = -1, int collisionheight = -1)
        : GameObject(parent, str, realX, realY, realSpeedX, realSpeedY, realSpeedRad, xLower, xUpper, yLower, yUpper, true, true, grativity, collisionx, collisiony, collisionwidth, collisionheight) { }

    ~HeavyBody() { }

};//参与碰撞，且碰撞不改变运动状态的物体

class Pushable : public GameObject
{
    Q_OBJECT

public:

    state weighdown = false;    //是否被压下去

    Pushable(GamePage *parent, QString str, float realX, float realY, float realSpeedX = 0, float realSpeedY = 0, float realSpeedRad = 0, int xLower = MIN, int xUpper = MAX, int yLower = MIN, int yUpper = MAX, attribute grativity = false, int collisionx = 0, int collisiony = 0, int collisionwidth = -1, int collisionheight = -1)
        : GameObject(parent, str, realX, realY, realSpeedX, realSpeedY, realSpeedRad, xLower, xUpper, yLower, yUpper, true, false, grativity, collisionx, collisiony, collisionwidth, collisionheight) { }

    ~Pushable() { }

};//可以通过碰撞改变运动状态的物体

class Role : public GameObject
{
    Q_OBJECT

public:

    state killed = false;   //是否死亡

};//所有角色，包括npc

class Player : public Role
{
    Q_OBJECT

public:

};//主角

#endif // GAMEOBJECT_H
