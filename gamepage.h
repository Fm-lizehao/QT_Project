#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include "global.h"

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

#endif // GAMEPAGE_H
