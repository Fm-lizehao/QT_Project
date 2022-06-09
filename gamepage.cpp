#include "gamebutton.h"
#include "gameobject.h"
#include "gamepage.h"
#include "mainwindow.h"

GamePage::GamePage(QString bg, QRect bgarea, QPointF cameraP, MainWindow *parent, int wid, int heig)
    : QWidget(parent), background(bg), backgroundArea(bgarea), cameraP(cameraP)
{
    resize(wid, heig);
    INTIME(updateAll);
}

GamePage::~GamePage()
{
    delete player;
}

void GamePage::updateAll()
{
    for (auto i : virtualObjects)    i.second->selfUpdate();
    for (auto i : roles)             i->selfUpdate();
    if  (player != nullptr)          player->selfUpdate();
    for (auto i : pushables)         i.second->selfUpdate();
    for (auto i : heavyBodies)       i.second->selfUpdate();
    update();
}

void GamePage::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setFont(standard_font);
    painter.drawPixmap(backgroundArea, QPixmap(background));
    for (auto i : virtualObjects)   painter.drawPixmap(i.second->getRect(), i.second->getImg());
    for (auto i : roles)            painter.drawPixmap(i->getRect(), i->getImg());
    if  (player != nullptr)         painter.drawPixmap(player->getRect(), player->getImg());
    for (auto i : pushables)        painter.drawPixmap(i.second->getRect(), i.second->getImg());
    for (auto i : heavyBodies)      painter.drawPixmap(i.second->getRect(), i.second->getImg());
    for (auto i : buttons)
    {
        painter.drawPixmap(i.second->getRect(), i.second->getImg());
        painter.drawText(i.second->getRect(), Qt::AlignCenter, i.second->getText());
    }
}

StartPage::StartPage(MainWindow *parent, int wid, int heig)
    : GamePage(pic(Startup_leftCastle), {80, 120, 1100, 600}, {0, 0}, parent, wid, heig)
{
    buttons.insert(std::make_pair("001:Start", new GameButton(this, {pic(Startup_button_main_1), pic(Startup_button_main_2)}, {"开始游戏"}, {780, 268}, parent, SLOT(startGame()))));
    buttons.insert(std::make_pair("002:Edit", new GameButton(this, {pic(Startup_button_main_1), pic(Startup_button_main_2)}, {"关卡设计"}, {780, 378}, parent, SLOT(mapEdit()))));
    buttons.insert(std::make_pair("003:Info", new GameButton(this, {pic(Startup_button_main_1), pic(Startup_button_main_2)}, {"操作说明"}, {780, 488}, parent, SLOT(readMe()))));
    buttons.insert(std::make_pair("004:Config", new GameButton(this, {pic(Startup_button_main_3)}, {"设置"}, {170, 0}, parent, SLOT(config()))));
    buttons.insert(std::make_pair("005:Exit", new GameButton(this, {pic(Startup_button_main_3)}, {"退出"}, {20, 0}, parent, SLOT(exit()))));
    virtualObjects.insert(std::make_pair("001:Cloud", new VirtualObject(this, {pic(Cloud_0_cute)}, {200, 40}, {-0.2, 0}, 0, rect(), true)));
    virtualObjects.insert(std::make_pair("002:Title", new VirtualObject(this, {pic(Startup_title_zh)}, {744, 168}, {0, 0}, 0, rect(), false)));
    virtualObjects.insert(std::make_pair("003:Bottomline", new VirtualObject(this, {pic(Startup_title_line_both)}, {767, 238}, {0, 0}, 0, rect(), false)));
    virtualObjects.insert(std::make_pair("004:Topline", new VirtualObject(this, {pic(Startup_topsep)}, {640, 78}, {0, 0}, 0, rect(), false)));
    virtualObjects.insert(std::make_pair("005:Jp-of", new VirtualObject(this, {pic(Startup_title_jpof)}, {856, 164}, {0, 0}, 0.2, rect(), false)));
}
