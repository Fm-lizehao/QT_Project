#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include "global.h"

class GameButton : public QWidget
{
    Q_OBJECT

public:

    QPixmap img; //按钮图片

    QPixmap img2; //如果鼠标移入会改变图片，这就是变化之后的图片

    state flipped = false; //为真时加载变化后的图片

    QString text; //按钮文本

    mode changeMode; //模式1：两张图片；模式2：移动图片

    GameButton() {}

    GameButton(GamePage *parent, QString pic1, QString pic2, QString text, int x, int y, QObject* receiver, const char* method);

    GameButton(GamePage *parent, QString pic, QString text, int x, int y, QObject* receiver, const char* method);

    ~GameButton() {}

    QPixmap getImg(); //取得应显示的按钮图片

    void paintEvent() = delete;

    void enterEvent(QEvent *event); //鼠标移入函数

    void leaveEvent(QEvent *event);  //鼠标移出函数

    void mouseReleaseEvent(QMouseEvent *e);  //鼠标点击

signals:

    void clicked();

public slots:

};

#endif // GAMEBUTTON_H
