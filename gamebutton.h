#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include "global.h"

class GameButton : public QWidget
{
    Q_OBJECT

private:

    std::vector<QPixmap> img; //按钮图片

    int imgNow = 0; //当前图片序号

    std::vector<QString> text; //按钮文字

    int textNow = 0; //当前文字序号

public:

    GameButton() {}

    GameButton(GamePage *parent, std::initializer_list<QString> img_str, std::initializer_list<QString> text, QPoint point, QObject* receiver, const char* method);

    ~GameButton() {}

    QPixmap getImg() {return img[imgNow]; } //取得应显示的按钮图片

    QString getText() {return text[textNow]; } //取得应显示的文字

    QRect getRect() {return rect().translated(pos()); } //取得应显示的区域

    void paintEvent() = delete;

    void enterEvent(QEvent *event); //鼠标移入函数

    void leaveEvent(QEvent *event);  //鼠标移出函数

    void mouseReleaseEvent(QMouseEvent *e);  //鼠标点击

signals:

    void clicked();

public slots:

};

#endif // GAMEBUTTON_H
