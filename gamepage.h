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
    void empty() {MUSIC(Audio_gold); }
    void brickFall() { MUSIC(Audio_spring); heavyBodies["018:Brick"]->grativity=true; heavyBodies["019:Brick"]->grativity=true; heavyBodies["020:Brick"]->grativity=true;
        heavyBodies["021:Brick"]->grativity=true; heavyBodies["022:Brick"]->grativity=true; triggers[5]->triggered=triggers[6]->triggered=true; }
    void newBrick1() {heavyBodies.insert(make_pair("101:Brick",new HeavyBody(this,{pic(UnknownBrickOver)},{640,450}))); MUSIC(Audio_ao); }
    void newBoard1() {heavyBodies.insert(make_pair("102:Board",new HeavyBody(this,{pic(HelloBoard_1)},{1485,430}))); MUSIC(Audio_error); }
    void newSlime1() {npcs.push_back(new NPC(this,slimeImg,{265,605},{pushSpeed/2.0,0})); MUSIC(Audio_gold); }
    void newSlime2() {npcs.push_back(new NPC(this,slimeImg,{463,605},{-pushSpeed/2.0,0})); MUSIC(Audio_gold); }
    void slimeActivate() {pushables.insert(make_pair("001:Slimegirl",new Pushable(this,{pic(Slime_girl)},{1005,820})));
                npcs[0]->v.setX(-pushSpeed/3.0); virtualObjects["010:HelloBoard"]->deleteLater(); virtualObjects.erase("010:HelloBoard"); MUSIC(Audio_gold); }
    void kingActivate() {npcs.push_back(new NPC(this,{pic(ShitKing_sword),pic(ShitKing)},{2450,820})); npcs[npcs.size()-1]->setImg(1); npcs[npcs.size()-1]->vicBounce=false;
                virtualObjects.insert(make_pair("101:Dialog",new VirtualObject(this,{pic(HelloBoard_4)},{2250,700}))); MUSIC(Audio_kim_laugh); }
    void kingNormal() {virtualObjects["101:Dialog"]->deleteLater(); virtualObjects.erase("101:Dialog"); }
    void kingKill() {npcs[npcs.size()-1]->v.setX(pushSpeed*2); MUSIC(Audio_miss); MUSIC_VOL(Audio_liangfeifan,defaultVolume*1.5); }
}; //关卡1

class PlayPage2 : public PlayPage
{
    Q_OBJECT
public:
    explicit PlayPage2(MainWindow *parent = nullptr, int Iq = 250);
    ~PlayPage2() {}
signals:
public slots:
    void brickFall_010() {heavyBodies["010:Brick"]->grativity=true;}
    void brickFall_011() {heavyBodies["011:Brick"]->grativity=true;}
    void brickFall_017() {heavyBodies["017:Brick"]->grativity=true;}
    void newSaw() {virtualObjects.insert(make_pair("500:Saw", new VirtualObject(this,{pic(Saw_48x12_top)}, {850, 0}, {0, 0.25}, 0.0, noBorder, false,true)));}
}; //关卡2

class PlayPage3 : public PlayPage
{
    Q_OBJECT
public:
    explicit PlayPage3(MainWindow *parent = nullptr, int Iq = 250);
    ~PlayPage3() {}
signals:
public slots:
    void empty() {MUSIC(Audio_gold); }
    void board() { if(player&&player->flying)virtualObjects["001:Board"]->breakin=true; }
    void insert();
    void fly() {if(player) player->flying=true; }
    void fish() { virtualObjects.insert(make_pair("200:Fish1",new VirtualObject(this,{pic(Fish)},{900,720},{0,-0.5},0,noBorder,false,true)));
                  virtualObjects.insert(make_pair("201:Fish2",new VirtualObject(this,{pic(Fish)},{940,720},{0,-0.5},0,noBorder,false,true)));
                  virtualObjects.insert(make_pair("202:Fish3",new VirtualObject(this,{pic(Fish)},{980,720},{0,-0.5},0,noBorder,false,true)));}
}; //关卡3

class EditPage : public PlayPage
{
    Q_OBJECT
public:
    int tot=0;
    ofstream outFile;
    GameButton* current = nullptr;
    explicit EditPage(MainWindow *parent = nullptr, int Iq = 250, int wid = windowWidth, int heig = windowHeight);
    ~EditPage() { }
signals:
public slots:
    void clicked(QMouseEvent* event, GameButton* ptr)
    {   setCursor(QCursor(ptr->getImg()));
        current = ptr; }
    void print()
    {   outFile.open("Usermap.txt");
        for(auto i : virtualObjects) //画上去的物体实际x2 y2值与在地图编辑页面上x y值的关系：x2=1280-(1280-x)*4/3; y2=y*4/3;
        {   int tmpx=1280-(1280-i.second->p.x())*4/3,tmpy=i.second->p.y()*4/3;
            if(i.second->p.y()<560) outFile<<tmpx<<' '<<tmpy<<' '<<i.second->source[0].toStdString()<<endl; }
        outFile.close(); }
    void erase(QPoint pos)
    {   for(auto i=virtualObjects.begin(); i!=virtualObjects.end(); i++)
            if(i->second->getRect().contains(pos))
                virtualObjects.erase(i); }
    void valuate()
    {   int val=0;
        for(auto i : virtualObjects){ if(i.second->p.y()>=560) continue; if(i.first[0]=='0') val++; else val--; }
        if(val>=3){ print();
            next();
        }
        else{char temp[10]={}; sprintf(temp,"9999999");
            virtualObjects.insert(make_pair(temp, new VirtualObject(this,{pic(mapedit_failed)},QPoint(700,570)))); }
    }
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
}; //地图编辑页面


class PVZPage : public PlayPage
{
    Q_OBJECT
public:
    explicit PVZPage(MainWindow *parent = nullptr, int Iq = 250, int wid = windowWidth, int heig = windowHeight);
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
