#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "global.h"

class GameObject : public QWidget
{
    Q_OBJECT

private:

    std::vector<QPixmap> img; //物体图片

    std::vector<QRect> collisionRect; //各个图片的碰撞区域

    int imgNow = 0; //当前图片序号

    QMatrix matrix; //物体旋转矩阵

public:

    //状态与属性：

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

    QPointF p = {0,0}; //物体实际位置

    QPointF v = {0,0}; //物体实际速度

    qreal omega = 0; //物体实际角速度

    QPointF a = {0,0}; //物体实际加速度

    QPointF& cameraP; //引用相机左上角位置

    QPointF& cameraV; //引用相机速度

    QRect border = noBorder; //物体反弹边界

    attribute collision = true;   //是否参与碰撞

    attribute stubborn = true;   //是否撞不动

    attribute grativity = false;   //是否受重力下落

    //基本函数：

    GameObject(GamePage *parent, std::initializer_list<QString> img_str, QPointF p, QPointF v = {0,0}, qreal omega = 0, QRect border = noBorder, attribute collision = true, attribute stubborn = true, attribute grativity = false);

    virtual ~GameObject() {}

    void paintEvent() = delete;

    //get函数：

    int getImgNumTotal()const {return img.size(); } //返回图片总数

    int getImgNumNow()const {return imgNow; } //返回当前图片序号

    QPixmap getImg()const //返回应显示的旋转后图片
    {
        auto retImg = img[imgNow].transformed(matrix, Qt::SmoothTransformation);
        QRect rect = img[imgNow].rect();
        rect.moveCenter(retImg.rect().center());
        return retImg.copy(rect);
    }

    QRect getRect()const {return rect().translated(pos()); } //取得应显示的区域

    QRectF getCollisionRect()const {return QRectF(collisionRect[imgNow]).translated(p); } //取得碰撞矩形的绝对坐标

    //set函数：

    void setImg(int imgnow) { imgNow = imgnow % img.size(); resize(img[imgNow].size()); } //更改图片

    void setLocation(QPointF p1) { p=p1; move((p-cameraP).toPoint()); } //更改位置

    void setSpeed(QPointF v1) { v=v1; } //设置速度

    void setRadSpeed(qreal omega1) { omega=omega1; } //设置角速度

    void setReverseSpeed() { v.setX(-v.x()); v.setY(-v.y()); } //设为反向速度

    void setXReverseSpeed() { v.setX(-v.x()); } //设为水平反向速度

    void setYReverseSpeed() { v.setY(-v.y()); } //设为垂直反向速度

    void setLeftSpeed() { v.setX(-std::abs(v.x())); } //设置水平速度向左

    void setRightSpeed() { v.setX(std::abs(v.x())); } //设置水平速度向右

    void setUpSpeed() { v.setY(-std::abs(v.y())); } //设置垂直速度向上

    void setDownSpeed() { v.setY(std::abs(v.y())); } //设置垂直速度向下

    //主功能函数：

    virtual void checkBorder(); //边界反弹

    virtual void checkState(); //检查当前状态，避免矛盾

    virtual void useState(); //使用当前状态设置加速度、速度、位置

    virtual void updateSpeed(); //根据加速度刷新速度

    virtual void updateLocation(); //根据速度刷新位置

    virtual void selfUpdate(); //实际接口，依次调用checkBorder,checkState,useState,updateSpeed,updateLocation

signals:

public slots:

};

class VirtualObject : public GameObject
{
    Q_OBJECT

public:

    state breakin = false;    //是否被主角穿过

    VirtualObject(GamePage *parent, std::initializer_list<QString> img_str, QPointF p, QPointF v = {0,0}, qreal omega = 0, QRect border = noBorder, attribute grativity = false)
        : GameObject(parent, img_str, p, v, omega, border, false, true, grativity) { }

    ~VirtualObject() { }

signals:

public slots:

};//不参与碰撞的物体

class HeavyBody : public GameObject
{
    Q_OBJECT

public:

    state weighdown = false;    //是否被压下去

    HeavyBody(GamePage *parent, std::initializer_list<QString> img_str, QPointF p, QPointF v = {0,0}, qreal omega = 0, QRect border = noBorder, attribute grativity = false)
        : GameObject(parent, img_str, p, v, omega, border, true, true, grativity) { }

    ~HeavyBody() { }

signals:

public slots:

};//参与碰撞，且碰撞不改变运动状态的物体

class Pushable : public GameObject
{
    Q_OBJECT

public:

    state weighdown = false;    //是否被压下去

    Pushable(GamePage *parent, std::initializer_list<QString> img_str, QPointF p, QPointF v = {0,0}, qreal omega = 0, QRect border = noBorder, attribute grativity = true)
        : GameObject(parent, img_str, p, v, omega, border, true, false, grativity) { }

    ~Pushable() { }

signals:

public slots:

};//可以通过碰撞改变运动状态的物体

class Role : public GameObject
{
    Q_OBJECT

public:

    state killed = false;   //是否死亡

    QTimer timer;    //自动切换图片计时器

    Role(GamePage *parent, std::initializer_list<QString> img_str, QPointF p, QPointF v = {0,0}, qreal omega = 0, QRect border = noBorder, attribute grativity = true)
        : GameObject(parent, img_str, p, v, omega, border, true, false, grativity) { }

    ~Role() { }

signals:

public slots:

};//所有角色的基类

class NPC : public Role
{
    Q_OBJECT

public:

    NPC(GamePage *parent, std::initializer_list<QString> img_str, QPointF p, QPointF v = {0,0}, qreal omega = 0, QRect border = noBorder, attribute grativity = true)
        : Role(parent, img_str, p, v, omega, border, grativity)
    {
        connect(&timer,SIGNAL(timeout()),this,SLOT(changeImg()),Qt::AutoConnection);
        timer.setInterval(500);
        timer.start();
    }

    ~NPC() { }

signals:

public slots:

    void changeImg() {setImg(getImgNumNow()+1); } //同一状态切换图片

};//NPC

class Player : public Role
{
    Q_OBJECT

public:

    state flying = false; //是否在飞

    Player(GamePage *parent, QPointF p)
        : Role(parent, playerImg, p, {0,0}, 0, noBorder, true)
    {
        connect(&timer,SIGNAL(timeout()),this,SLOT(changeImg()),Qt::AutoConnection);
        timer.setInterval(500);
        timer.start();
    }

    ~Player() { }

    void useState(); //使用当前状态设置加速度、速度、位置、图片，并对飞行中的bounceup行为作出修改

signals:

public slots:

    void changeImg() {setImg(flip[getImgNumNow()]); } //同一状态切换图片

};//主角

#endif // GAMEOBJECT_H
