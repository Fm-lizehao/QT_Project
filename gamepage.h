#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include "global.h"

class GamePage : public QWidget
{
    Q_OBJECT
public:
    int pageWidth = windowWidth; //物理空间宽度
    int pageHeight = windowHeight; //物理空间高度

    QPixmap background; //背景图
    QRect backgroundArea; //背景图区域

    map<QString, GameButton*> buttons; //页面中的按钮
    map<QString, VirtualObject*> virtualObjects; //页面中不碰撞的物体
    map<QString, HeavyBody*> heavyBodies; //页面中碰撞不改变运动状态的物体
    map<QString, Pushable*> pushables; //页面中碰撞会改变运动状态的物体
    vector<NPC*> npcs; //页面中的npc角色
    Player* player = nullptr; //主角

    QPointF cameraP = {0,0}; //相机左上角位置
    QPointF cameraV = {0,0}; //相机速度

    explicit GamePage(MainWindow *parent = nullptr, int wid = windowWidth, int heig = windowHeight, QString bg = "", QRect bgarea = {0,0,windowWidth,windowHeight}, QPointF cameraP = {0,0});
    virtual ~GamePage();
    void paintEvent(QPaintEvent *event);

    QRect PageRect() {return QRect(0,0,pageWidth,pageHeight); } //返回页面矩形

    void updateCamera(); //更新相机位置和速度
signals:
public slots:
    void updateAll(); //更新所有物体的速度和位置并刷新页面
};

class StartPage : public GamePage
{
    Q_OBJECT
public:
    explicit StartPage(MainWindow *parent = nullptr, int wid = windowWidth, int heig = windowHeight);
    ~StartPage() {}
signals:
public slots:
}; //开始页面

class PlayPage : public GamePage
{
    Q_OBJECT
public:
    explicit PlayPage(MainWindow *parent = nullptr, int wid = windowWidth, int heig = windowHeight);
    ~PlayPage() {}
signals:
public slots:
}; //游戏页面

#endif // GAMEPAGE_H
