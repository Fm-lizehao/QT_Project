#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cmath>
#include <map>
#include <utility>
#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QFont>
#include <QPaintEvent>
#include <QPainter>
#include <QtMultimedia/QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui
{
    class MainWindow;
}

extern QTimer main_timer;

extern QFont standard_font;

#define INTIME(x) connect(&main_timer,&QTimer::timeout,this,x,Qt::DirectConnection)

#define MIN -2147483648

#define MAX 2147483647

//-------------------------------------------------------------------

class GameButton : public QWidget
{
    Q_OBJECT

public:

    QPixmap img;

    QPixmap img2;//change

    bool flipped = false;

    QString text;



    explicit GameButton(){}

    explicit GameButton(QWidget *parent, QString pic1,QString pic2,QString text,int x,int y,auto receiver, auto method);

    explicit GameButton(QWidget *parent, QString pic,QString text,int x,int y,auto receiver, auto method);

    ~GameButton();

    void enterEvent(QEvent *event); //鼠标移入函数

    void leaveEvent(QEvent *event);  //鼠标移出函数

    void mouseReleaseEvent(QMouseEvent *e);  //鼠标点击

signals:

    void clicked();

public slots:

};

//-------------------------------------------------------------------
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

class LineBarrier : public GameObject
{
    Q_OBJECT
};

class Role : public RealObject
{
    Q_OBJECT
};

//-------------------------------------------------------------------

class GamePage : public QWidget
{
    Q_OBJECT

public:

    QPixmap background;

    std::map<QString,GameButton*> button;

    std::map<QString,GameObject*> object;



    explicit GamePage(QString bg, QWidget *parent = nullptr,int wid=1280,int heig=720);

    virtual ~GamePage();

    virtual void init();

    virtual void paintEvent(QPaintEvent *event);

signals:

public slots:

};

class StartPage : public GamePage
{
    Q_OBJECT

public:

    explicit StartPage(QString bg, QWidget *parent = nullptr,int wid=1280,int heig=720);

    ~StartPage();

    void init();

    void paintEvent(QPaintEvent *event);

signals:

public slots:

};

//-------------------------------------------------------------------

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    Ui::MainWindow *ui;

public:

    GamePage *page=NULL;

    QMediaPlayer * music=NULL;

    QMediaPlaylist * playlist=NULL;



    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

signals:

public slots:

    void startGame();

    void mapEdit();

    void readMe();

    void setConfig();

    void exit();

};

#endif // MAINWINDOW_H
