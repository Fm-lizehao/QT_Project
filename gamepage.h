#ifndef GAMEPAGE_H
#define GAMEPAGE_H
#include "gamebutton.h"
#include "gameobject.h"
#include "global.h"
class GamePage : public QWidget
{
    Q_OBJECT
public:
    QMediaPlayer * music = NULL; //音乐播放器
    QMediaPlaylist * playlist = NULL; //播放列表
    int pageWidth = windowWidth; //物理空间宽度
    int pageHeight = windowHeight; //物理空间高度
    QPixmap background; //背景图
    QRect backgroundArea; //背景图区域
    map<QString, VirtualObject*> topVirtualObjects; //顶层遮挡物
    vector<TextItem> topText; //顶层文字
    QPixmap* img = nullptr; //储存顶层文字图片
    map<QString, GameButton*> topButtons; //顶层按钮
    map<QString, GameButton*> buttons; //页面中的按钮
    map<QString, VirtualObject*> virtualObjects; //页面中不碰撞的物体
    map<QString, HeavyBody*> heavyBodies; //页面中碰撞不改变运动状态的物体
    map<QString, Pushable*> pushables; //页面中碰撞会改变运动状态的物体
    vector<NPC*> npcs; //页面中的npc角色
    Player* player = nullptr; //主角
    vector<Trigger*> triggers; //事件触发器
    QPointF cameraP = {0,0}; //相机左上角位置
    QPointF cameraV = {0,0}; //相机速度
    explicit GamePage(MainWindow *parent = nullptr, int wid = windowWidth, int heig = windowHeight, QString bg = "", QRect bgarea = {0,0,windowWidth,windowHeight}, QPointF cameraP = {0,0});
    virtual ~GamePage() {delete img; }
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
    int level = 1;
    int IQ = 250;
    const QString comment[5] = {"卧梅又闻花\n卧枝伤恨底\n鱼闻卧石水\n卧石答春绿","君有疾在脑门\n不治而将恐深","手残者剁手即愈\n脑残者无药医也","赞你妹！\n这关这么简单\n你怎么还没过？","牡丹初放却先残\n未捣黄龙死不甘\n冒险正常何所惧\n拼将热血洒红毡"};
    explicit PlayPage(MainWindow *parent = nullptr, int wid = windowWidth, int heig = windowHeight, int Level = 1, int Iq = 250, QString bgm = "", QString bg = "", QRect bgarea = {0,0,windowWidth,windowHeight}, QPointF cameraP = {0,0});
    ~PlayPage() {}
signals:
    void restartSignal(int Level, int Iq); //告诉主窗口重新来过
    void nextSignal(int Level); //告诉主窗口开始下一关
public slots:
    void playerKilled(); //死亡画面
    void victory(); //胜利画面
    void restart() {restartSignal(level,IQ); } //重新来过
    void next() {nextSignal(level+1); } //开始下一关
}; //游戏页面

class PlayPage1 : public PlayPage
{
    Q_OBJECT
public:
    explicit PlayPage1(MainWindow *parent = nullptr, int Iq = 250);
    ~PlayPage1() {}
signals:
public slots:
    void brickFall();
    void newBrick();
}; //关卡1

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
    void clicked(QMouseEvent* event, GameButton* ptr)
    {   setCursor(QCursor(ptr->getImg()));
        current = ptr; }
    void print()
    {   outFile.open("Usermap.map");
        for(auto i : virtualObjects)
            outFile<<i.second->p.x()<<' '<<i.second->p.y()<<' '<<i.second->source[0].toStdString()<<endl;
        outFile.close(); }
    void erase(QPoint pos)
    {   for(auto i=virtualObjects.begin(); i!=virtualObjects.end(); i++)
            if(i->second->getRect().contains(pos))
                virtualObjects.erase(i); }
    void valuate() {if(true) print(); }
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
}; //地图编辑页面

class PVZPage : public GamePage
{
    Q_OBJECT

public:

    explicit PVZPage(MainWindow *parent = nullptr, int wid = 1280, int heig = 720);

    ~PVZPage() {}

    static const int N_Enemy = 14;      //敌人个数
    static const int N_Last = 8;    //最后一波之前的敌人个数
    static const int N_Bullet = 1000;    //子弹数量上限
    static const int FishTime = 1;    //鱼的前进周期
    static const int EnemyTime = 5;    //敌人的前进周期
    static const int CoinGainTime = 600;    //生产硬币的周期
    static const int BulletGainTime = 400;    //生产子弹的周期
    static const int BulletFlyTime = 1;    //子弹的飞行周期

    int EnemyGainTime[N_Enemy]={200,1200,2400,2600,3000,3400,3800,4200,16700,16701,16702,17500,17501,17502};    //敌人的生成时间
    int EnemyType[N_Enemy]={0,0,0,0,0,0,1,1,2,2,2,2,2,2};    //敌人种类
    int EnemyRow[N_Enemy]={0,1,2,0,1,2,0,1,0,1,2,0,1,2};    //敌人所在行
    int EnemyHp[3]={80,120,160};    //敌人血量上限
    int EnemyPer[3]={0,1,2};    //敌人所在行的排列

    QString EnemyStr[N_Enemy]={};      //用于存敌人的标识串名
    QTimer T;       //计时器
    GameButton *btn1,*btn2,*btn3,*btn4;       //向日葵、豌豆射手、铲子、金币数的按钮
    int Time=0;       //计时器的计数器
    int Coins=100;    //硬币数量
    int Type=0;       //当前选择的植物种类（向日葵/豌豆射手）
    int numKill=0;    //已杀死的敌人数量
    bool isSelected = false;    //是否处于向日葵/豌豆射手/铲子的选中状态
    int Plant[3][6]={};       //该格子已种植物类型
    int StartTime[3][6]={};       //种下这个植物的时间

    QString strPlt[3][6]={};       //用于存植物的标识串名
    GameButton *btnPlt[3][6]={};       //植物的按钮（用于选中铲子时）
    VirtualObject *picPlt[3][6]={};       //植物图片（用于没选中铲子时）

    int cFish[3]={},xFish[3]={250,250,250},yFish[3]={225,325,425};       //鱼的状态、横纵坐标
    QString strFish[3]={"Fish1","Fish2","Fish3"};       //用于存鱼的标识串名
    VirtualObject *picFish[3]={};       //鱼对象

    int xEne[N_Enemy]={},yEne[N_Enemy]={},Hp[N_Enemy]={},cntEne=0;       //敌人横纵坐标、血量、计数器
    QString strEne[N_Enemy]={};       //用于存敌人的标识串名
    GameButton *btnEne[N_Enemy]={};       //用于挖掉敌人的按钮
    VirtualObject *picEne[N_Enemy]={};       //敌人对象

    int xBul[N_Bullet]={},yBul[N_Bullet]={},cntBul=0;       //子弹横纵坐标、计数器
    QString strBul[N_Bullet]={};       //用于存子弹的标识串名
    VirtualObject *picBul[N_Bullet]={};       //子弹对象

signals:

public slots:

    void empty() { }
    void swap();
    void Timeout();
    void selectplt(QMouseEvent* event,GameButton* btn);
    void selectpos(int x,int y);
    void SelectEnemy(int i);
    void UpdateCoins();
    void GameWin();
    void GameLose();
}; //开始页面

#endif // GAMEPAGE_H
