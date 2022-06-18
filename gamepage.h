#ifndef GAMEPAGE_H
#define GAMEPAGE_H
#include "gamebutton.h"
#include "gameobject.h"
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
    QRect pageRect() {return QRect(0,0,pageWidth,pageHeight); } //返回页面矩形
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

class EditPage : public GamePage
{
    Q_OBJECT
public:
    ofstream outFile;
    GameButton* current = nullptr;
    explicit EditPage(MainWindow *parent = nullptr, int wid = windowWidth, int heig = windowHeight);
    ~EditPage() { }
signals:
public slots:
    void clicked(GameButton* ptr)
    {   setCursor(QCursor(ptr->getImg()));
        current = ptr; }
    void print()
    {   outFile.open("Usermap.map");
        for(auto i : virtualObjects)
            outFile<<i.second->p.x()<<' '<<i.second->p.y()<<' '<<i.second->source[0].toStdString()<<endl;
        outFile.close(); }
    void erase(int x,int y)
    {   for(auto i=virtualObjects.begin(); i!=virtualObjects.end(); i++)
            if(i->second->getRect().contains(x,y))
                virtualObjects.erase(i); }
    void valuate() {if(true) print(); }
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
}; //地图编辑页面

class PVZPage : public GamePage
{
    Q_OBJECT
public:
    explicit PVZPage(MainWindow *parent = nullptr, int wid = windowWidth, int heig = windowHeight);
    ~PVZPage() {}
    static const int N_Enemy = 14;
    static const int N_Last = 8;
    static const int N_Bullet = 1000;
    static const int FishTime = 1;
    static const int EnemyTime = 5;
    static const int CoinGainTime = 600;
    static const int BulletGainTime = 400;
    static const int BulletFlyTime = 1;
    int EnemyGainTime[N_Enemy]={200,1200,2400,2600,3000,3400,3800,4200,16700,16701,16702,17500,17501,17502};
    int EnemyType[N_Enemy]={0,0,0,0,0,0,1,1,2,2,2,2,2,2};
    int EnemyRow[N_Enemy]={0,1,2,0,1,2,0,1,0,1,2,0,1,2};
    int EnemyHp[3]={80,120,160};
    int EnemyPer[3]={};
    QString EnemyStr[N_Enemy]={};
    QTimer T;
    GameButton *btn1,*btn2,*btn3,*btn4;
    int Time=0;
    int coins=0;
    int type=0;
    int Killed=0;
    bool is_selected=false;
    int Fc[3]={},Fx[3]={},Fy[3]{};
    VirtualObject *F[3];
    QString Fs[3];
    int A[3][6];
    int StartTime[3][6];
    GameButton *B[3][6];
    VirtualObject *C[3][6];
    QString s[3][6];
    int ex[N_Enemy],ey[N_Enemy],hp[N_Enemy],ec;
    VirtualObject *e[N_Enemy];
    QString es[N_Enemy];
    GameButton *eb[N_Enemy];
    int bx[N_Bullet],by[N_Bullet],bc;
    VirtualObject *b[N_Bullet];
    QString bs[N_Bullet];
signals:
public slots:
    void empty();
    void swap();
    void Timeout();
    void selectplt(int type);
    void selectpos(int x,int y);
    void SelectEnemy(int i);
    void UpdateCoins();
    void GameWin();
    void GameLose();
}; //彩蛋页面

#endif // GAMEPAGE_H
