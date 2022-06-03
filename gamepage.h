#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include "global.h"

class GamePage : public QWidget
{
    Q_OBJECT

public:

    QPixmap background; //背景图

    QRect backgroundArea; //背景图区域

    std::map<QString, GameButton*> buttons; //页面按钮

    std::map<QString, GameObject*> objects; //页面物体

    std::vector<Role*> roles; //页面角色，第一个是主角

    explicit GamePage(QString bg, QRect bgArea, QWidget *parent = nullptr, int wid = 1280, int heig = 720);

    virtual ~GamePage(){}

    void paintEvent(QPaintEvent *event);

signals:

public slots:

    void updateAll(); //更新所有物体的速度和位置并刷新页面

};

class StartPage : public GamePage
{
    Q_OBJECT

public:

    explicit StartPage(QWidget *parent = nullptr, int wid = 1280, int heig = 720);

    ~StartPage(){}

signals:

public slots:

}; //开始页面

#endif // GAMEPAGE_H
