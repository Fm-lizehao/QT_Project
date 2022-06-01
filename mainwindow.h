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

    GamePage *page = NULL;

    QMediaPlayer * music = NULL;

    QMediaPlaylist * playlist = NULL;

    MainWindow(QWidget *parent = 0);

    ~MainWindow();

signals:

    void quitSignal();

public slots:

    void startGame();

    void mapEdit();

    void readMe();

    void config();

    void exit();

};

#endif // MAINWINDOW_H
