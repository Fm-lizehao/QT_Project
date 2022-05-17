#include "gamepage.h"

#include "gamebutton.h"

#include "gameobject.h"

GamePage::GamePage(QString bg, QWidget *parent, int wid, int heig) : QWidget(parent), background(bg)
{
	resize(wid, heig);
}

GamePage::~GamePage()
{

}

void GamePage::init()
{

}

void GamePage::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setFont(standard_font);
	painter.drawPixmap(0, 0, width(), height(), QPixmap(background));
	for (auto i : button)
	{
		if (i.second->flipped)
			painter.drawPixmap(i.second->x(), i.second->y(), i.second->width(), i.second->height(), i.second->img2);
		else painter.drawPixmap(i.second->x(), i.second->y(), i.second->width(), i.second->height(), i.second->img);
		painter.drawText(i.second->x(), i.second->y(), i.second->width(), i.second->height(), Qt::AlignTop | Qt::AlignLeft, i.second->text);
	}
	for (auto i : object)
	{
		painter.drawPixmap(i.second->x(), i.second->y(), i.second->width(), i.second->height(), i.second->getImg());
	}
}



StartPage::StartPage(QString bg, QWidget *parent, int wid, int heig): GamePage(bg, parent, wid, heig)
{
	init();
}

StartPage::~StartPage()
{

}

void StartPage::init()
{
    button.insert(std::make_pair("001:Start", new GameButton(this, pic(Startup_button_main_1), pic(Startup_button_main_2), "开始游戏", 780, 268, (QObject*)parent(), SLOT(startGame()))));
    button.insert(std::make_pair("002:Edit", new GameButton(this, pic(Startup_button_main_1), pic(Startup_button_main_2), "关卡设计", 780, 378, (QObject*)parent(), SLOT(mapEdit()))));
    button.insert(std::make_pair("003:Info", new GameButton(this, pic(Startup_button_main_1), pic(Startup_button_main_2), "操作说明", 780, 488, (QObject*)parent(), SLOT(readMe()))));
    button.insert(std::make_pair("004:Config", new GameButton(this, pic(Startup_button_main_3), "设置", 170, 0, (QObject*)parent(), SLOT(config()))));
    button.insert(std::make_pair("005:Exit", new GameButton(this, pic(Startup_button_main_3), "退出", 20, 0, (QObject*)parent(), SLOT(exit()))));
    object.insert(std::make_pair("001:Cloud", new VirtualObject(this, pic(Cloud_0_cute), 200, 40, -1, 0, 0, 0, this->width(), 0, this->height(), true)));
    object.insert(std::make_pair("002:Title", new VirtualObject(this, pic(Startup_title_zh), 744, 168, 0, 0, 0, 0, this->width(), 0, this->height(), false)));
    object.insert(std::make_pair("003:Bottomline", new VirtualObject(this, pic(Startup_title_line_both), 767, 238, 0, 0, 0, 0, this->width(), 0, this->height(), false)));
    object.insert(std::make_pair("004:Topline", new VirtualObject(this, pic(Startup_topsep), 640, 78, 0, 0, 0, 0, this->width(), 0, this->height(), false)));
    object.insert(std::make_pair("005:Jp-of", new VirtualObject(this, pic(Startup_title_jpof), 856, 164, 0, 0, 1, 0, this->width(), 0, this->height(), false)));
}

void StartPage::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setFont(standard_font);
    painter.drawPixmap(80, 120, 1100, 600, QPixmap(background));
	for (auto i : button)
	{
		if (i.second->flipped)
			painter.drawPixmap(i.second->x(), i.second->y(), i.second->width(), i.second->height(), i.second->img2);
		else
			painter.drawPixmap(i.second->x(), i.second->y(), i.second->width(), i.second->height(), i.second->img);
		painter.drawText(i.second->x(), i.second->y(), i.second->width(), i.second->height(), Qt::AlignCenter, i.second->text);
	}
	for (auto i : object)
	{
		painter.drawPixmap(i.second->x(), i.second->y(), i.second->width(), i.second->height(), i.second->getImg());
	}
}
