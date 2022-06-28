#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "gamepage.h"
#include "ui_mainwindow.h"
#include "global.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
public:
    GamePage *page = NULL; //当前页面
    MainWindow(QWidget *parent = 0);
    ~MainWindow() {delete ui; }
signals:
    void quitSignal(); //退出应用程序信号
public slots:
    void backMain(); //返回主界面
    void restart(int Level,int Iq); //关卡重新来过
    void startGame(); //开始游戏
    void mapEdit(); //地图编辑
    void PVZ(); //PVZ
    void config(); //游戏设置
    void exit(); //退出游戏
};
#endif // MAINWINDOW_H
