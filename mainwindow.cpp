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
    music = new QMediaPlayer;
    music->setVolume(50);
    playlist = new QMediaPlaylist(music);
    playlist->addMedia(QUrl(snd(Audio_bgm_into_the_castle)));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music->setPlaylist(playlist);
    music->play();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete music;
}

void MainWindow::startGame()
{
    page->deleteLater();
    page = new PlayPage(this, this->width(), this->height());
    page->show();
}

void MainWindow::mapEdit()
{
    page->deleteLater();
    page = new EditPage(this, this->width(), this->height());
    page->show();
}

void MainWindow::PVZ()
{
    page->deleteLater();
    page = new PVZPage(this, this->width(), this->height());
    page->show();
}

void MainWindow::config()
{
    page->deleteLater();

    page->show();
}

void MainWindow::exit()
{
    if (!(QMessageBox::question(this, tr("退出游戏"), tr("     你真的要退出吗?    (盯) "), tr(" 啊~可耻地逃了T__T "), tr(" 人家点错了>﹏< "))))
    {
        quitSignal();
    }
}
