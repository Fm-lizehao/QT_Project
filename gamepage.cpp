#include "gamebutton.h"
#include "gameobject.h"
#include "gamepage.h"
#include "mainwindow.h"

GamePage::GamePage(MainWindow *parent, int wid, int heig, QString bg, QRect bgarea, QPointF cameraP)
    : QWidget(parent), pageWidth(wid), pageHeight(heig), background(bg), backgroundArea(bgarea), cameraP(cameraP)
{
    resize(windowWidth,windowHeight);
    INTIME(updateAll);
}

GamePage::~GamePage()
{
    delete player;
}

void GamePage::updateCamera()
{
    cameraV = {0,0};
    if(player != nullptr)
    {
        if(cameraP.x()>0&&player->getCollisionRect().left()<cameraP.x()+250) cameraV.setX(-pushSpeed);
        if(cameraP.x()+windowWidth<pageWidth&&player->getCollisionRect().right()>cameraP.x()+1030) cameraV.setX(pushSpeed);
        if(cameraP.y()>0&&player->getCollisionRect().top()<cameraP.y()+120) cameraV.setY(-pushSpeed);
        if(cameraP.y()+windowHeight<pageHeight&&player->getCollisionRect().bottom()>cameraP.y()+600) cameraV.setY(pushSpeed);
    }
    cameraP += cameraV;
}

void GamePage::updateAll()
{
    updateCamera();
    for (auto i : virtualObjects)
    {
        for(auto j : npcs) i.second->checkCollision(j);
        if(player != nullptr) i.second->checkCollision(player);
    }
    for(auto i : npcs)
    {
        for(auto j : virtualObjects) i->checkCollision(j.second);
        for(auto j : npcs) {if(i==j)continue; i->checkCollision(j); }
        if(player != nullptr) {i->checkCollision(player); if(i->cankill&&(i->upObject==player||i->downObject==player||i->leftObject==player||i->rightObject==player)) i->victory=true; }
        for(auto j : pushables) i->checkCollision(j.second);
        for(auto j : heavyBodies) i->checkCollision(j.second);
        i->doCollision();
    }
    if(player != nullptr)
    {
        for(auto j : virtualObjects) player->checkCollision(j.second);
        for(auto j: npcs) player->checkCollision(j);
        for(auto j : pushables) player->checkCollision(j.second);
        for(auto j : heavyBodies) player->checkCollision(j.second);
        player->doCollision();
    }
    for(auto i : pushables)
    {
        for(auto j: npcs) i.second->checkCollision(j);
        if(player != nullptr) i.second->checkCollision(player);
        for(auto j : pushables) {if(i.second==j.second)continue; i.second->checkCollision(j.second); }
        for(auto j : heavyBodies) i.second->checkCollision(j.second);
        i.second->doCollision();
    }
    for(auto i : heavyBodies)
    {
        for(auto j: npcs) i.second->checkCollision(j);
        if(player != nullptr) i.second->checkCollision(player);
        for(auto j : pushables) i.second->checkCollision(j.second);
        for(auto j : heavyBodies) {if(i.second==j.second)continue; i.second->checkCollision(j.second); }
        i.second->doCollision();
    }
    for (auto i : virtualObjects)    i.second->selfUpdate();
    for (auto i : npcs)              i->selfUpdate();
    if  (player != nullptr)          player->selfUpdate();
    for (auto i : pushables)         i.second->selfUpdate();
    for (auto i : heavyBodies)       i.second->selfUpdate();
    update();
}

void GamePage::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setFont(standard_font);
    painter.drawPixmap(backgroundArea.translated(-cameraP.toPoint()), QPixmap(background));
    for (auto i : virtualObjects)   painter.drawPixmap(i.second->getRect(), i.second->getImg());
    for (auto i : npcs)             painter.drawPixmap(i->getRect(), i->getImg());
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
    : GamePage(parent, wid, heig, pic(Startup_leftCastle), {80, 120, 1100, 600})
{
    buttons.insert(make_pair("001:Start", new GameButton(this, {pic(Startup_button_main_1), pic(Startup_button_main_2)}, {"开始游戏"}, {780, 268}, parent, SLOT(startGame()))));
    buttons.insert(make_pair("002:Edit", new GameButton(this, {pic(Startup_button_main_1), pic(Startup_button_main_2)}, {"关卡设计"}, {780, 378}, parent, SLOT(mapEdit()))));
    buttons.insert(make_pair("003:Info", new GameButton(this, {pic(Startup_button_main_1), pic(Startup_button_main_2)}, {"操作说明"}, {780, 488}, parent, SLOT(readMe()))));
    buttons.insert(make_pair("004:Config", new GameButton(this, {pic(Startup_button_main_3)}, {"设置"}, {170, 0}, parent, SLOT(config()))));
    buttons.insert(make_pair("005:Exit", new GameButton(this, {pic(Startup_button_main_3)}, {"退出"}, {20, 0}, parent, SLOT(exit()))));
    virtualObjects.insert(make_pair("001:Cloud", new VirtualObject(this, {pic(Cloud_0_cute)}, {200, 40}, {-0.2, 0}, 0, PageRect(), false)));
    virtualObjects.insert(make_pair("002:Title", new VirtualObject(this, {pic(Startup_title_zh)}, {744, 168}, {0, 0}, 0, PageRect(), false)));
    virtualObjects.insert(make_pair("003:Bottomline", new VirtualObject(this, {pic(Startup_title_line_both)}, {767, 238}, {0, 0}, 0, PageRect(), false)));
    virtualObjects.insert(make_pair("004:Topline", new VirtualObject(this, {pic(Startup_topsep)}, {640, 78}, {0, 0}, 0, PageRect(), false)));
    virtualObjects.insert(make_pair("005:Jp-of", new VirtualObject(this, {pic(Startup_title_jpof)}, {856, 164}, {0, 0}, 0.2, PageRect(), false)));
}

PlayPage::PlayPage(MainWindow *parent, int wid, int heig)
    : GamePage(parent, wid, heig, pic(Startup_leftCastle), {80, 120, 1100, 600})
{
    virtualObjects.insert(make_pair("001:Cloud", new VirtualObject(this, {pic(Cloud_0_cute)}, {200, 80}, {-0.2, 0}, 0, PageRect(), false, true)));
    heavyBodies.insert(make_pair("001:Object", new HeavyBody(this, {pic(Float_144)}, {0,400}, {0,0}, 0, PageRect())));
    heavyBodies.insert(make_pair("002:Object", new HeavyBody(this, {pic(Float_144)}, {150,400}, {0,0}, 0, PageRect())));
    heavyBodies.insert(make_pair("003:Object", new HeavyBody(this, {pic(Float_144)}, {300,400}, {0,0}, 0, PageRect())));
    heavyBodies.insert(make_pair("004:Object", new HeavyBody(this, {pic(Float_144)}, {450,400}, {0,0}, 0, PageRect())));
    heavyBodies.insert(make_pair("005:Object", new HeavyBody(this, {pic(Float_144)}, {600,400}, {0,0}, 0, PageRect())));
    heavyBodies.insert(make_pair("006:Object", new HeavyBody(this, {pic(Float_144)}, {750,400}, {0,0}, 0, PageRect())));
    heavyBodies.insert(make_pair("007:Object", new HeavyBody(this, {pic(Float_144)}, {900,400}, {0,0}, 0, PageRect())));
    heavyBodies.insert(make_pair("008:Object", new HeavyBody(this, {pic(Float_144)}, {1050,400}, {0,0}, 0, PageRect())));
    player = new Player(this,{100,100});
}
