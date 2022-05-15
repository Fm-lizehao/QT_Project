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

		explicit MainWindow(QWidget *parent = 0);

		~MainWindow();

	signals:

	public slots:

		void startGame();

		void mapEdit();

		void readMe();

		void setConfig();

		void exit();

};

#endif // MAINWINDOW_H
