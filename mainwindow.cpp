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
    case 1:
        page->deleteLater();
        page = new PlayPage1(this, this->width(), this->height(), Iq);
        break;
    }
}

void MainWindow::startGame()
{
    page->deleteLater();
    page = new PlayPage1(this, this->width(), this->height());
}

void MainWindow::mapEdit()
{
    page->deleteLater();
    page = new EditPage(this, this->width(), this->height());
}

void MainWindow::PVZ()
{
    page->deleteLater();
    page = new PVZPage(this, this->width(), this->height());
}

void MainWindow::config()
{
    page->deleteLater();

}

void MainWindow::exit()
{
    if (!(QMessageBox::question(this, tr("退出游戏"), tr("     你真的要退出吗?    (盯) "), tr(" 啊~可耻地逃了T__T "), tr(" 人家点错了>﹏< ")))) quitSignal();
}
