#include "gamepage.h"

#include "gamebutton.h"

#include "gameobject.h"

GamePage::GamePage(QString bg, QRect bgArea, QWidget *parent, int wid, int heig)
    : QWidget(parent), background(bg), backgroundArea(bgArea)
{
    resize(wid, heig);
    INTIME(updateAll);
}

void GamePage::updateAll()
{
    for(auto i : objects)
    {
        i.second->updateLocation();
    }
    update();
}

void GamePage::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setFont(standard_font);
    painter.drawPixmap(backgroundArea, QPixmap(background));
    for (auto i : buttons)
    {
        painter.drawPixmap(i.second->x(), i.second->y(), i.second->width(), i.second->height(), i.second->getImg());
        painter.drawText(i.second->x(), i.second->y(), i.second->width(), i.second->height(), Qt::AlignCenter, i.second->text);
    }
    for (auto i : objects)
    {
        painter.drawPixmap(i.second->x(), i.second->y(), i.second->width(), i.second->height(), i.second->getImg());
    }
}



StartPage::StartPage(QWidget *parent, int wid, int heig)
    : GamePage(pic(Startup_leftCastle), QRect(80, 120, 1100, 600), parent, wid, heig)
{
    buttons.insert(std::make_pair("001:Start", new GameButton(this, pic(Startup_button_main_1), pic(Startup_button_main_2), "开始游戏", 780, 268, parent, SLOT(startGame()))));
    buttons.insert(std::make_pair("002:Edit", new GameButton(this, pic(Startup_button_main_1), pic(Startup_button_main_2), "关卡设计", 780, 378, parent, SLOT(mapEdit()))));
    buttons.insert(std::make_pair("003:Info", new GameButton(this, pic(Startup_button_main_1), pic(Startup_button_main_2), "操作说明", 780, 488, parent, SLOT(readMe()))));
    buttons.insert(std::make_pair("004:Config", new GameButton(this, pic(Startup_button_main_3), "设置", 170, 0, parent, SLOT(config()))));
    buttons.insert(std::make_pair("005:Exit", new GameButton(this, pic(Startup_button_main_3), "退出", 20, 0, parent, SLOT(exit()))));
    objects.insert(std::make_pair("001:Cloud", new VirtualObject(this, pic(Cloud_0_cute), 200, 40, -1, 0, 0, 0, this->width(), 0, this->height(), true)));
    objects.insert(std::make_pair("002:Title", new VirtualObject(this, pic(Startup_title_zh), 744, 168, 0, 0, 0, 0, this->width(), 0, this->height(), false)));
    objects.insert(std::make_pair("003:Bottomline", new VirtualObject(this, pic(Startup_title_line_both), 767, 238, 0, 0, 0, 0, this->width(), 0, this->height(), false)));
    objects.insert(std::make_pair("004:Topline", new VirtualObject(this, pic(Startup_topsep), 640, 78, 0, 0, 0, 0, this->width(), 0, this->height(), false)));
    objects.insert(std::make_pair("005:Jp-of", new VirtualObject(this, pic(Startup_title_jpof), 856, 164, 0, 0, 1, 0, this->width(), 0, this->height(), false)));
}
