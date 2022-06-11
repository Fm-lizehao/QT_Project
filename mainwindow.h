#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "global.h"

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    Ui::MainWindow *ui;

public:

    GamePage *page = NULL; //窗口对应的页面

    QMediaPlayer * music = NULL; //音乐播放器

    QMediaPlaylist * playlist = NULL; //播放列表

    MainWindow(QWidget *parent = 0);

    ~MainWindow();

signals:

    void quitSignal(); //退出应用程序信号

public slots:

    void startGame(); //开始游戏

    void mapEdit(); //地图编辑

    void readMe(); //游戏说明

    void config(); //游戏设置

    void exit(); //退出游戏

};

#endif // MAINWINDOW_H
