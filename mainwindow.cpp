#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    connect(this, SIGNAL(quitSignal()), qApp, SLOT(quit()));
    ui->setupUi(this);
    setFixedSize(windowWidth, windowHeight);
    setWindowIcon(QPixmap(pic(icon)));
    setWindowTitle("正常的大冒险");
    page = new StartPage(this, this->width(), this->height());
}
void MainWindow::backMain()
{
    page->deleteLater();
    page = new StartPage(this, this->width(), this->height());
}
void MainWindow::restart(int Level, int Iq)
{
    switch(Level)
    {
    case 1: page->deleteLater(); page = new PlayPage1(this, Iq); break;
    case 2: page->deleteLater(); page = new PlayPage2(this, Iq); break;
    case 3: page->deleteLater(); page = new PlayPage3(this, Iq); break;
    case 4: page->deleteLater(); page = new PVZPage(this, Iq); break;
    case 5: page->deleteLater(); page = new EditPage(this, Iq); break;
    }
}
void MainWindow::next(int Level)
{
    switch(Level)
    {
    case 2:page->deleteLater(); page = new PlayPage2(this); break;
    case 3:page->deleteLater(); page = new PlayPage3(this); break;
    case 4:page->deleteLater(); page = new PVZPage(this); break;
    case 5:page->deleteLater(); page = new EditPage(this); break;
    case 6:page->deleteLater(); page = new PlayPage2(this); break;
    }
}
void MainWindow::startGame()
{
    page->deleteLater();
    page = new PlayPage1(this);
}
void MainWindow::mapEdit()
{
    page->deleteLater();
    page = new EditPage(this);
}
void MainWindow::PVZ()
{
    page->deleteLater();
    page = new PVZPage(this);
}
void MainWindow::config()
{
    page->deleteLater();

}
void MainWindow::exit()
{
    if (!(QMessageBox::question(this, tr("退出游戏"), tr("     你真的要退出吗?    (盯) "), tr(" 啊~可耻地逃了T__T "), tr(" 人家点错了>﹏< ")))) quitSignal();
}
