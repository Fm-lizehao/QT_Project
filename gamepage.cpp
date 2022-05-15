#include "gamepage.h"

#include "gamebutton.h"

#include "gameobject.h"

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
    button.insert(std::make_pair("001:Start", new GameButton(this,pic(Startup_button_main_1),pic(Startup_button_main_2),"开始游戏",800,400,(QObject*)parent(),SLOT(startGame()))));
    object.insert(std::make_pair("001:Cloud",new IllusoryObject(this, pic(Cloud_0_cute),0,100,1,0,0,0,this->width(),0,this->height(),true)));
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
