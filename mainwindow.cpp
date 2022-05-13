#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resources.h"

//-------------------------------------------------------------------
GameButton::GameButton(QWidget *parent, QString pic1, QString pic2, QString text, int x, int y, auto receiver, auto method):QWidget(parent),img(pic1),img2(pic2),text(text)
{
    setFixedSize(QSize(img.width(),img.height()));
    move(x,y);
    connect(this,&GameButton::clicked,receiver,method);
}

GameButton::GameButton(QWidget *parent, QString pic, QString text, int x, int y, auto receiver, auto method):QWidget(parent),img(pic),img2(pic),text(text)
{
    setFixedSize(QSize(img.width(),img.height()));
    move(x,y);
    connect(this,&GameButton::clicked,receiver,method);
}

GameButton::~GameButton()
{

}

void GameButton::enterEvent(QEvent *event)
{
    setFixedSize(QSize(img2.width(),img2.height()));
    move(x()+img.width()/2-img2.width()/2,y()+img.height()/2-img2.height()/2);
    flipped=true;
    update();
}

void GameButton::leaveEvent(QEvent *event)
{
    setFixedSize(QSize(img.width(),img.height()));
    move(x()+img2.width()/2-img.width()/2,y()+img2.height()/2-img.height()/2);
    flipped=false;
    update();
}

void GameButton::mouseReleaseEvent(QMouseEvent *e)
{
    emit clicked();
}

//-------------------------------------------------------------------
GameObject::GameObject(QWidget *parent, QString str, int x, int y, int speedX, int speedY, int speedRad):QWidget(parent),img(str), speedX(speedX), speedY(speedY), speedRad(speedRad)
{
    setFixedSize(QSize(img.width(),img.height()));
    move(x,y);
    INTIME(updateLocation);
}

GameObject::~GameObject()
{

}

int GameObject::getX()
{
    return x();
}

int GameObject::getY()
{
    return y();
}

int GameObject::getWidth()
{
    return width();
}

int GameObject::getHeight()
{
    return height();
}

QPixmap GameObject::getImg()
{
    return img.transformed(matrix,Qt::FastTransformation);
}

void GameObject::setSpeed(int speedx,int speedy,int speedrad)
{
    speedX=speedx;
    speedY=speedy;
    speedRad=speedrad;
    update();
}

bool GameObject::isCollision(GameObject& other)
{
    return rect().intersects(other.rect());
}

void GameObject::updateLocation()
{
    matrix.rotate(speedRad);
    move(x()+speedX,y()+speedY);
    update();
}

//-------------------------------------------------------------------
GamePage::GamePage(QString bg, QWidget *parent,int wid,int heig) : QWidget(parent),background(bg)
{
    resize(wid,heig);
}

GamePage::~GamePage()
{
    for(auto i:button)  delete i.second;
    for(auto i:object)  delete i.second;
}

void GamePage::init()
{

}

void GamePage::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setFont(standard_font);
    painter.drawPixmap(0,0,width(),height(),QPixmap(background));
    for(auto i:button)
    {
        if(i.second->flipped)
        painter.drawPixmap(i.second->x(),i.second->y(),i.second->width(),i.second->height(),i.second->img2);
        else
        painter.drawPixmap(i.second->x(),i.second->y(),i.second->width(),i.second->height(),i.second->img);
        painter.drawText(i.second->x(),i.second->y(),i.second->width(),i.second->height(),Qt::AlignTop | Qt::AlignLeft,i.second->text);
    }
    for(auto i:object)
    {
        painter.drawPixmap(i.second->x(),i.second->y(),i.second->width(),i.second->height(),i.second->getImg());
    }
}



StartPage::StartPage(QString bg, QWidget *parent, int wid, int heig):GamePage(bg, parent, wid, heig)
{
    init();
}

StartPage::~StartPage()
{
    for(auto i:button)  delete i.second;
    for(auto i:object)  delete i.second;
}

void StartPage::init()
{
    button.insert(std::make_pair("Startup_button_main", new GameButton(this,pic(Startup_button_main_1),pic(Startup_button_main_2),"开始游戏",800,400,this,startGame)));
    object.insert(std::make_pair("Cloud_0_cute",new GameObject(this, pic(Cloud_0_cute),0,100,1,0,0)));
}

void StartPage::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setFont(standard_font);
    painter.drawPixmap(50,180,1000,540,QPixmap(background));
    for(auto i:button)
    {
        if(i.second->flipped)
        painter.drawPixmap(i.second->x(),i.second->y(),i.second->width(),i.second->height(),i.second->img2);
        else
        painter.drawPixmap(i.second->x(),i.second->y(),i.second->width(),i.second->height(),i.second->img);
        painter.drawText(i.second->x(),i.second->y(),i.second->width(),i.second->height(),Qt::AlignCenter,i.second->text);
    }
    for(auto i:object)
    {
        painter.drawPixmap(i.second->x(),i.second->y(),i.second->width(),i.second->height(),i.second->getImg());
    }
}

void StartPage::startGame()
{
    qDebug()<<"开始啦！";
}

void StartPage::mapEdit()
{

}

void StartPage::readMe()
{

}

void StartPage::setConfig()
{

}

void StartPage::exit()
{

}

//-------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1280,720);
    this->setWindowIcon(QPixmap(pic(icon)));
    this->setWindowTitle("Strange Adventure");
    page=new StartPage(pic(Startup_leftCastle),this,this->width(),this->height());
    music = new QMediaPlayer;
    music->setVolume(50);
    playlist = new QMediaPlaylist(music);
    playlist->addMedia(QUrl(snd(Audio_bgm_into_the_castle)));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music->setPlaylist(playlist);
    music->play();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete page;
    delete music;
    delete playlist;
}
