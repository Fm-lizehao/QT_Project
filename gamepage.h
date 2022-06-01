#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include "global.h"

class GamePage : public QWidget
{
    Q_OBJECT

public:

    QPixmap background;

    QRect backgroundArea;

    std::map<QString, GameButton*> buttons;

    std::map<QString, GameObject*> objects;

    explicit GamePage(QString bg, QRect bgArea, QWidget *parent = nullptr, int wid = 1280, int heig = 720);

    virtual ~GamePage(){}

    void paintEvent(QPaintEvent *event);

signals:

public slots:

};

class StartPage : public GamePage
{
    Q_OBJECT

public:

    explicit StartPage(QWidget *parent = nullptr, int wid = 1280, int heig = 720);

    ~StartPage(){}

signals:

public slots:

};

#endif // GAMEPAGE_H
