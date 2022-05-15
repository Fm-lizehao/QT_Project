#include "global.h"

#include "mainwindow.h"

#include "gamepage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1280,720);
    this->setWindowIcon(QPixmap(pic(icon)));
    this->setWindowTitle("Strange Adventure");
    page=new StartPage(pic(Startup_leftCastle),this,this->width(),this->height());
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
    delete page;
    delete music;
    delete playlist;
}

void MainWindow::startGame()
{
    qDebug()<<"开始啦！";
}

void MainWindow::mapEdit()
{

}

void MainWindow::readMe()
{

}

void MainWindow::setConfig()
{

}

void MainWindow::exit()
{

}
