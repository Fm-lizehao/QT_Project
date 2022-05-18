#include "mainwindow.h"

#include "gamepage.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    connect(this,SIGNAL(quitSignal()),qApp,SLOT(quit()));
	ui->setupUi(this);
	setFixedSize(1280, 720);
	setWindowIcon(QPixmap(pic(icon)));
    setWindowTitle("正常的大冒险");
    page = new StartPage(pic(Startup_leftCastle), this, this->width(), this->height());
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
    qDebug()<<"startGame()";
}

void MainWindow::mapEdit()
{
    page->deleteLater();
    qDebug()<<"mapEdit()";
}

void MainWindow::readMe()
{
    page->deleteLater();
    qDebug()<<"readMe()";
}

void MainWindow::config()
{
    page->deleteLater();
    qDebug()<<"config()";
}

void MainWindow::exit()
{
    if(!(QMessageBox::question(this,tr("退出游戏"),tr("     你真的要退出吗?    (盯) "),tr(" 啊~可耻地润了~T__T "),tr(" 人家点错惹>﹏< "))))
    {
        quitSignal();
    }
}
