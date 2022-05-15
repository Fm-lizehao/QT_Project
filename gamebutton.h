#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include "global.h"

class GameButton : public QWidget
{
    Q_OBJECT

public:

    QPixmap img;

    QPixmap img2;//change

    bool flipped = false;

    QString text;

    GameButton(){}

    GameButton(QWidget *parent, QString pic1,QString pic2,QString text,int x,int y,QObject* receiver,const char* method);

    GameButton(QWidget *parent, QString pic,QString text,int x,int y,QObject* receiver, const char* method);

    ~GameButton();

    void enterEvent(QEvent *event); //鼠标移入函数

    void leaveEvent(QEvent *event);  //鼠标移出函数

    void mouseReleaseEvent(QMouseEvent *e);  //鼠标点击

signals:

    void clicked();

public slots:

};

#endif // GAMEBUTTON_H
