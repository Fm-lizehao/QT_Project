#include "mainwindow.h"

GamePage::GamePage(MainWindow *parent, int wid, int heig, QString bg, QRect bgarea, QPointF cameraP)
    : QWidget(parent), pageWidth(wid), pageHeight(heig), background(bg), backgroundArea(bgarea), cameraP(cameraP)
{
    resize(windowWidth,windowHeight);
    music = new QMediaPlayer(this);
    music->setVolume(defaultVolume);
    playlist = new QMediaPlaylist(music);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music->setPlaylist(playlist);
    INTIME(updateAll);
    show();
}

void GamePage::updateCamera()
{
    cameraV = {0,0};
    if(player != nullptr)
    {   if(cameraP.x()>0&&player->getCollisionRect().left()<cameraP.x()+200) cameraV.setX(-pushSpeed);
        if(cameraP.x()+windowWidth<pageWidth&&player->getCollisionRect().right()>cameraP.x()+800) cameraV.setX(pushSpeed);
        if(cameraP.y()>0&&player->getCollisionRect().top()<cameraP.y()+50) cameraV.setY(-pushSpeed);
        if(cameraP.y()+windowHeight<pageHeight&&player->getCollisionRect().bottom()>cameraP.y()+420) cameraV.setY(pushSpeed); }
    cameraP += cameraV;
}

void GamePage::updateAll()
{
    updateCamera();
    for (auto i : virtualObjects)
    {   for(auto j : npcs) i.second->checkCollision(j);
        if(player != nullptr) i.second->checkCollision(player); }
    for(auto i : pushables)
    {   for(auto j: npcs) i.second->checkCollision(j);
        if(player != nullptr) i.second->checkCollision(player);
        for(auto j : pushables) {if(i.second==j.second)continue; i.second->checkCollision(j.second); }
        for(auto j : heavyBodies) i.second->checkCollision(j.second);
        i.second->doCollision(); }
    for(auto i : npcs)
    {   for(auto j : virtualObjects) i->checkCollision(j.second);
        for(auto j : npcs) {if(i==j)continue; i->checkCollision(j); }
        if(player != nullptr) {i->checkCollision(player); }
        for(auto j : pushables) i->checkCollision(j.second);
        for(auto j : heavyBodies) i->checkCollision(j.second);
        i->doCollision(); }
    if(player != nullptr)
    {   for(auto j : virtualObjects) player->checkCollision(j.second);
        for(auto j: npcs) player->checkCollision(j);
        for(auto j : pushables) player->checkCollision(j.second);
        for(auto j : heavyBodies) player->checkCollision(j.second);
        player->doCollision(); }
    for(auto i : heavyBodies)
    {   for(auto j: npcs) i.second->checkCollision(j);
        if(player != nullptr) i.second->checkCollision(player);
        for(auto j : pushables) i.second->checkCollision(j.second);
        i.second->doCollision(); }
    for (auto i : virtualObjects)    i.second->selfUpdate();
    for (auto i : pushables)         i.second->selfUpdate();
    for (auto i : npcs)              i->selfUpdate();
    if  (player != nullptr)          player->selfUpdate();
    for (auto i : heavyBodies)       i.second->selfUpdate();
    for (auto i : triggers)          if(!i->triggered&&player->v.y()<=0.0) i->check(player->getCollisionRect());
    update();
}

void GamePage::paintEvent(QPaintEvent *event)
{
    if(img==nullptr&&!topText.empty())
    {   img=new QPixmap(QSize(windowWidth,windowHeight));
        img->fill(QColor(0,0,0,0));
        QPainter painter(img);
        for (auto i : topText)  {painter.setFont(i.font); painter.drawText(i.rect,Qt::AlignCenter|Qt::TextWordWrap,i.str); } }
    QPainter painter(this);
    painter.setFont(standard_font);
    painter.drawPixmap(backgroundArea.translated(-cameraP.toPoint()), QPixmap(background));
    for (auto i : virtualObjects)   painter.drawPixmap(i.second->getRect(), i.second->getImg());
    for (auto i : heavyBodies)      painter.drawPixmap(i.second->getRect(), i.second->getImg());
    for (auto i : pushables)        painter.drawPixmap(i.second->getRect(), i.second->getImg());
    for (auto i : npcs)             painter.drawPixmap(i->getRect(), i->getImg());
    if  (player != nullptr)         painter.drawPixmap(player->getRect(), player->getImg());
    for (auto i : buttons)
    {   painter.drawPixmap(i.second->getRect(), i.second->getImg());
        painter.drawText(i.second->getRect(), Qt::AlignCenter, i.second->getText()); }
    for (auto i : topVirtualObjects)   painter.drawPixmap(i.second->getCollisionRect().toRect(), i.second->getImg());
    if(img) painter.drawPixmap(QPoint(0,0),*img);
    for (auto i : topButtons)
    {   painter.drawPixmap(i.second->getRect(), i.second->getImg());
        painter.drawText(i.second->getRect(), Qt::AlignCenter, i.second->getText()); }
}

StartPage::StartPage(MainWindow *parent, int wid, int heig)
    : GamePage(parent, wid, heig, pic(Startup_leftCastle), {80, 120, 1100, 600})
{
    buttons.insert(make_pair("001:Start", new GameButton(this, {pic(Startup_button_main_1), pic(Startup_button_main_2)}, {"开始游戏"}, {780, 268}, parent, SLOT(startGame()))));
    buttons.insert(make_pair("002:Edit", new GameButton(this, {pic(Startup_button_main_1), pic(Startup_button_main_2)}, {"关卡设计"}, {780, 378}, parent, SLOT(mapEdit()))));
    buttons.insert(make_pair("003:PVZ", new GameButton(this, {pic(Startup_button_main_1), pic(Startup_button_main_2)}, {"奇怪的地方"}, {780, 488}, parent, SLOT(PVZ()))));
    buttons.insert(make_pair("004:Config", new GameButton(this, {pic(Startup_button_main_3)}, {"设置"}, {170, 0}, parent, SLOT(config()))));
    buttons.insert(make_pair("005:Exit", new GameButton(this, {pic(Startup_button_main_3)}, {"退出"}, {20, 0}, parent, SLOT(exit()))));
    virtualObjects.insert(make_pair("001:Cloud", new VirtualObject(this, {pic(Cloud_0_cute)}, {200, 40}, {-0.2, 0}, 0, pageRect(), false)));
    virtualObjects.insert(make_pair("002:Title", new VirtualObject(this, {pic(Startup_title_zh)}, {744, 168}, {0, 0}, 0, pageRect(), false)));
    virtualObjects.insert(make_pair("003:Bottomline", new VirtualObject(this, {pic(Startup_title_line_both)}, {767, 238}, {0, 0}, 0, pageRect(), false)));
    virtualObjects.insert(make_pair("004:Topline", new VirtualObject(this, {pic(Startup_topsep)}, {640, 78}, {0, 0}, 0, pageRect(), false)));
    virtualObjects.insert(make_pair("005:Jp-of", new VirtualObject(this, {pic(Startup_title_jpof)}, {856, 164}, {0, 0}, 0.2, pageRect(), false)));
    playlist->addMedia(QUrl(snd(Audio_bgm_into_the_castle))); music->play();
}

PlayPage::PlayPage(MainWindow *parent, int wid, int heig, int Level, int Iq, QString bgm, QString bg, QRect bgarea, QPointF cameraP)
    : GamePage(parent, wid, heig, bg, bgarea, cameraP), level(Level), IQ(Iq)
{
    connect(this,SIGNAL(restartSignal(int,int)),parent,SLOT(restart(int,int)));
    connect(this,SIGNAL(nextSignal(int)),parent,SLOT(next(int)));
    buttons.insert(make_pair("001:Back", new GameButton(this, {pic(Startup_button_main_3)}, {"返回"}, {20, 0}, parent, SLOT(backMain()))));
    playlist->addMedia(QUrl(bgm)); music->play();
}

void PlayPage::playerKilled()
{
    if(img) return;
    topVirtualObjects.insert(make_pair("001:Killed", new VirtualObject(this, {pic(FailFrame)}, {450,130})));
    topVirtualObjects.insert(make_pair("002:UpLine", new VirtualObject(this, {pic(Fail_number_frame_up)}, {561,255})));
    topVirtualObjects.insert(make_pair("003:Downline", new VirtualObject(this, {pic(Fail_number_frame_down)}, {561,340})));
    topVirtualObjects.insert(make_pair("004:Emoji", new VirtualObject(this, {pic(Emoji_hero_1)}, {603,110})));
    topText.push_back({QRect(600,220,70,30),QFont("Felix Titling", 15, QFont::Bold, false),QString("IQ")});
    topText.push_back({QRect(560,255,150,100),QFont("Bahnschrift SemiBold Condensed", 36, QFont::Bold, false),QString::number(IQ)});
    topText.push_back({QRect(500,350,266,30),QFont("幼圆", 8, QFont::Bold, false),QString("国际砖家组织权威认证")});
    topText.push_back({QRect(490,366,166,50),QFont("幼圆", 10, QFont::Bold, false),QString("后人有诗赞曰：")});
    topText.push_back({QRect(500,383,266,150),QFont("幼圆", 12, QFont::Bold, false),comment[(250-IQ)/50%4]});
    topButtons.insert(make_pair("001:Restart",new GameButton(this,{pic(Startup_button_main_3)}, {"不服!"}, {570,515}, this, SLOT(restart()))));
    if(IQ/50%2) {MUSIC(Audio_laugh);}
    else {MUSIC(Audio_boos);}
    IQ-=50;
}

void PlayPage::victory()
{
    if(img) return;
    if(player) {player->victory = true; player->v.setX(0); player->pushleft=player->pushright=false; }
    topVirtualObjects.insert(make_pair("001:Victory", new VirtualObject(this, {pic(FailFrame)}, {450,130})));
    topVirtualObjects.insert(make_pair("002:UpLine", new VirtualObject(this, {pic(Fail_number_frame_up)}, {561,255})));
    topVirtualObjects.insert(make_pair("003:Downline", new VirtualObject(this, {pic(Fail_number_frame_down)}, {561,340})));
    topVirtualObjects.insert(make_pair("004:Emoji", new VirtualObject(this, {pic(Emoji_hero_6)}, {603,110})));
    topText.push_back({QRect(600,220,70,30),QFont("Felix Titling", 15, QFont::Bold, false),QString("IQ")});
    topText.push_back({QRect(560,255,150,100),QFont("Bahnschrift SemiBold Condensed", 36, QFont::Bold, false),QString::number(IQ)});
    topText.push_back({QRect(500,350,266,30),QFont("幼圆", 8, QFont::Bold, false),QString("国际砖家组织权威认证")});
    topText.push_back({QRect(490,366,166,50),QFont("幼圆", 10, QFont::Bold, false),QString("后人有诗赞曰：")});
    topText.push_back({QRect(500,383,266,150),QFont("幼圆", 12, QFont::Bold, false),comment[4]});
    topButtons.insert(make_pair("001:Next",new GameButton(this,{pic(Startup_button_main_3)}, {"继续!"}, {570,515}, this, SLOT(next()))));
    MUSIC(Audio_congratulations);
}

PlayPage1::PlayPage1(MainWindow *parent, int Iq)
    : PlayPage(parent, 3000, 1000, 1, Iq, snd(Audio_bgm_aquatic_circus), "", {0,0,3000,1000},{0,280})
{
    player = new Player(this,QPoint(200,580));
    npcs.push_back(new NPC(this,slimeImg,{1377,780}));
    triggers.push_back(new Trigger(this,{2870,830,14,50},SLOT(victory())));
    triggers.push_back(new Trigger(this,{512,498,46,1},SLOT(brickFall())));
    triggers.push_back(new Trigger(this,{641,498,46,1},SLOT(newBrick1())));
    triggers.push_back(new Trigger(this,{1389,703,46,1},SLOT(newBoard1())));
    triggers.push_back(new Trigger(this,{266,703,46,1},SLOT(newSlime1())));
    triggers.push_back(new Trigger(this,{464,703,46,1},SLOT(newSlime2())));
    triggers.push_back(new Trigger(this,{560,703,46,1},SLOT(empty())));
    triggers.push_back(new Trigger(this,{1189,703,46,1},SLOT(slimeActivate())));
    triggers.push_back(new Trigger(this,{2000,0,1,880},SLOT(kingActivate())));
    triggers.push_back(new Trigger(this,{2200,0,1,880},SLOT(kingNormal())));
    triggers.push_back(new Trigger(this,{2680,0,1,880},SLOT(kingKill())));
    virtualObjects.insert(make_pair("001:Hill",new VirtualObject(this,{pic(Hill_1)},{450,700})));
    virtualObjects.insert(make_pair("002:Hill",new VirtualObject(this,{pic(Hill_2)},{1080,763})));
    virtualObjects.insert(make_pair("003:Cloud",new VirtualObject(this,{pic(Cloud_0),pic(Cloud_0_bad)},{730,380},{0.0,0.0},0.0,noBorder,false,true)));
    virtualObjects.insert(make_pair("004:Cloud",new VirtualObject(this,{pic(Cloud_2)},{365,390},{0.05,0},0,{330,0,370,1000})));
    virtualObjects.insert(make_pair("005:Grass",new VirtualObject(this,{pic(Grass_2)},{40,852})));
    virtualObjects.insert(make_pair("006:Grass",new VirtualObject(this,{pic(Grass_1)},{720,852})));
    virtualObjects.insert(make_pair("007:Grass",new VirtualObject(this,{pic(Grass_2)},{630,852})));
    virtualObjects.insert(make_pair("008:Saw",new VirtualObject(this,{pic(Saw_252_invisible),pic(Saw_252)},{630,859},{0.0,0.0},0.0,noBorder,false,true)));
    virtualObjects.insert(make_pair("009:Castle",new VirtualObject(this,{pic(Castle_2)},{2800,724})));
    virtualObjects.insert(make_pair("010:HelloBoard",new VirtualObject(this,{pic(HelloBoard_2)},{1405,703})));
    virtualObjects.insert(make_pair("011:Cloud",new VirtualObject(this,{pic(Cloud_3_cute)},{1200,390})));
    virtualObjects.insert(make_pair("012:HelloBoard",new VirtualObject(this,{pic(HelloBoard_3)},{100,390})));
    virtualObjects.insert(make_pair("013:Cloud",new VirtualObject(this,{pic(Cloud_0_cute)},{1900,390},{0.05,0},0,{1830,0,600,1000})));
    virtualObjects.insert(make_pair("014:Fence",new VirtualObject(this,{pic(Fence)},{1970,810})));
    virtualObjects.insert(make_pair("015:Cloud",new VirtualObject(this,{pic(Cloud_2)},{2550,395})));
    heavyBodies.insert(make_pair("001:Ground",new HeavyBody(this,{pic(Grass_ground)},{0,880})));
    heavyBodies.insert(make_pair("002:Ground",new HeavyBody(this,{pic(Grass_ground)},{200,880})));
    heavyBodies.insert(make_pair("003:Ground",new HeavyBody(this,{pic(Grass_ground)},{400,880})));
    heavyBodies.insert(make_pair("004:Ground",new HeavyBody(this,{pic(Grass_ground)},{600,880})));
    heavyBodies.insert(make_pair("005:Ground",new HeavyBody(this,{pic(Grass_ground)},{800,880})));
    heavyBodies.insert(make_pair("006:Ground",new HeavyBody(this,{pic(Grass_ground)},{1000,880})));
    heavyBodies.insert(make_pair("007:Ground",new HeavyBody(this,{pic(Grass_ground)},{1200,880})));
    heavyBodies.insert(make_pair("008:Groundright",new HeavyBody(this,{pic(Grass_ground_right)},{1400,880})));
    heavyBodies.insert(make_pair("009:Groundleft",new HeavyBody(this,{pic(Grass_ground_left)},{1770,880})));
    heavyBodies.insert(make_pair("010:Ground",new HeavyBody(this,{pic(Grass_ground)},{1800,880})));
    heavyBodies.insert(make_pair("011:Ground",new HeavyBody(this,{pic(Grass_ground)},{2000,880})));
    heavyBodies.insert(make_pair("012:Ground",new HeavyBody(this,{pic(Grass_ground)},{2200,880})));
    heavyBodies.insert(make_pair("013:Ground",new HeavyBody(this,{pic(Grass_ground)},{2400,880})));
    heavyBodies.insert(make_pair("014:Ground",new HeavyBody(this,{pic(Grass_ground)},{2600,880})));
    heavyBodies.insert(make_pair("015:Ground",new HeavyBody(this,{pic(Grass_ground)},{2800,880})));
    heavyBodies.insert(make_pair("016:Pipe",new HeavyBody(this,{pic(Pipe)},{870,676})));
    heavyBodies.insert(make_pair("017:Brick",new HeavyBody(this,{pic(BrickUnknown),pic(UnknownBrickOver)},{265,655})));
    heavyBodies.insert(make_pair("018:Brick",new HeavyBody(this,{pic(Brick)},{415,655})));
    heavyBodies.insert(make_pair("019:Brick",new HeavyBody(this,{pic(BrickUnknown),pic(UnknownBrickOver)},{463,655})));
    heavyBodies.insert(make_pair("020:Brick",new HeavyBody(this,{pic(Brick)},{511,655})));
    heavyBodies.insert(make_pair("021:Brick",new HeavyBody(this,{pic(BrickUnknown),pic(UnknownBrickOver)},{559,655})));
    heavyBodies.insert(make_pair("022:Brick",new HeavyBody(this,{pic(Brick)},{607,655})));
    heavyBodies.insert(make_pair("023:Brick",new HeavyBody(this,{pic(BrickUnknown),pic(UnknownBrickOver)},{511,450})));
    heavyBodies.insert(make_pair("024:Brick",new HeavyBody(this,{pic(BrickUnknown),pic(UnknownBrickOver)},{1388,655})));
    heavyBodies.insert(make_pair("025:Brick",new HeavyBody(this,{pic(BrickUnknown),pic(UnknownBrickOver)},{1188,655})));
}

PlayPage2::PlayPage2(MainWindow *parent, int Iq)
    : PlayPage(parent, windowWidth, windowHeight, 2, Iq, snd(Audio_bgm_the_survival))
{
    player = new Player(this,QPoint(1080,600));
    triggers.push_back(new Trigger(this,{530,429,48,1},SLOT(brickFall_010())));
    triggers.push_back(new Trigger(this,{480,429,48,1},SLOT(brickFall_017())));
    triggers.push_back(new Trigger(this,{400,549,48,1},SLOT(brickFall_011())));
    triggers.push_back(new Trigger(this,{1080,20,200,200},SLOT(victory())));
    triggers.push_back(new Trigger(this,{850,100,100,50},SLOT(newSaw())));
    virtualObjects.insert(make_pair("200:Saw",new VirtualObject(this,{pic(Saw2),pic(Saw2)},{880,480},{0.0,0.0},0.0,noBorder,false,true)));
    virtualObjects.insert(make_pair("201:Cloud",new VirtualObject(this,{pic(Cloud_0),pic(Cloud_0_bad)},{100,110},{0.0,0.0},0.0,noBorder,false,true)));
    virtualObjects.insert(make_pair("202:Cloud",new VirtualObject(this,{pic(Cloud_2)},{300,400})));
    virtualObjects.insert(make_pair("203:Cloud",new VirtualObject(this,{pic(Cloud_0)},{1050,450})));
    virtualObjects.insert(make_pair("300:Castle",new VirtualObject(this,{pic(Castle_2)},{1080,20})));
    virtualObjects.insert(make_pair("400:Slime", new VirtualObject(this, {pic(Slime_idle_left)},{700,112},{-0.08,0},0.0,QRect(600,112,400,400),false,true)));
    heavyBodies.insert(make_pair("001:Brick",new HeavyBody(this,{pic(Brick)},{1050,620})));
    heavyBodies.insert(make_pair("002:Brick",new HeavyBody(this,{pic(Brick)},{1100,620})));
    heavyBodies.insert(make_pair("003:Brick",new HeavyBody(this,{pic(Brick)},{1150,620})));
    heavyBodies.insert(make_pair("004:Brick",new HeavyBody(this,{pic(Brick)},{980,600})));
    heavyBodies.insert(make_pair("005:Brick",new HeavyBody(this,{pic(Brick)},{930,600})));
    heavyBodies.insert(make_pair("006:Brick",new HeavyBody(this,{pic(Brick)},{870,500})));
    heavyBodies.insert(make_pair("007:Brick",new HeavyBody(this,{pic(Brick)},{700,500})));
    heavyBodies.insert(make_pair("008:Brick",new HeavyBody(this,{pic(Brick)},{650,500})));
    heavyBodies.insert(make_pair("010:Brick",new HeavyBody(this,{pic(UnknownBrickOver_broken)},{530,430})));
    heavyBodies.insert(make_pair("011:Brick",new HeavyBody(this,{pic(UnknownBrickOver)},{400,550})));
    heavyBodies.insert(make_pair("012:Brick",new HeavyBody(this,{pic(Brick)},{310,600})));
    heavyBodies.insert(make_pair("013:Brick",new HeavyBody(this,{pic(Brick)},{200,520})));
    heavyBodies.insert(make_pair("014:Brick",new HeavyBody(this,{pic(Brick)},{80,500})));
    heavyBodies.insert(make_pair("015:Brick",new HeavyBody(this,{pic(Brick)},{120,430})));
    heavyBodies.insert(make_pair("016:Brick",new HeavyBody(this,{pic(Brick)},{580,430})));
    heavyBodies.insert(make_pair("017:Brick",new HeavyBody(this,{pic(UnknownBrickOver)},{480,430})));
    heavyBodies.insert(make_pair("018:Brick",new HeavyBody(this,{pic(Brick)},{220,300})));
    heavyBodies.insert(make_pair("019:Brick",new HeavyBody(this,{pic(Brick)},{270,300})));
    heavyBodies.insert(make_pair("020:Brick",new HeavyBody(this,{pic(Brick)},{400,80})));
    heavyBodies.insert(make_pair("021:Brick",new HeavyBody(this,{pic(Brick)},{600,150})));
    heavyBodies.insert(make_pair("022:Brick",new HeavyBody(this,{pic(Brick)},{650,150})));
    heavyBodies.insert(make_pair("023:Brick",new HeavyBody(this,{pic(Brick)},{700,150})));
    heavyBodies.insert(make_pair("024:Brick",new HeavyBody(this,{pic(Brick)},{750,150})));
    heavyBodies.insert(make_pair("025:Brick",new HeavyBody(this,{pic(Brick)},{800,150})));
    heavyBodies.insert(make_pair("026:Brick",new HeavyBody(this,{pic(Brick)},{530,150})));
    heavyBodies.insert(make_pair("027:Brick",new HeavyBody(this,{pic(Brick)},{850,150})));
    heavyBodies.insert(make_pair("028:Brick",new HeavyBody(this,{pic(Brick)},{900,150})));
    heavyBodies.insert(make_pair("029:Brick",new HeavyBody(this,{pic(Brick)},{950,150})));
    heavyBodies.insert(make_pair("030:Brick",new HeavyBody(this,{pic(Brick)},{1080,178})));
    heavyBodies.insert(make_pair("031:Brick",new HeavyBody(this,{pic(Brick)},{1130,178})));
    heavyBodies.insert(make_pair("032:Brick",new HeavyBody(this,{pic(Brick)},{1180,178})));
    heavyBodies.insert(make_pair("033:Brick",new HeavyBody(this,{pic(Brick)},{1030,178})));
    heavyBodies.insert(make_pair("034:Brick",new HeavyBody(this,{pic(Brick)},{1230,178})));
    ifstream inFile; inFile.open("Usermap.txt");
    char temp[200]; int tempx,tempy;
    while(inFile>>tempx>>tempy>>temp)
    {
        QString string_temp = QString::number(tempx,10);
        QString string_temp2(temp);
        if(temp[25]=='w'&&temp[26]=='2') virtualObjects.insert(make_pair(string_temp,new VirtualObject(this,{string_temp2},{tempx,tempy},{0.0,0.0},0.0,noBorder,false,true)));
        else if(temp[23]=='S'&&temp[24]=='l') virtualObjects.insert(make_pair(string_temp,new VirtualObject(this,{string_temp2},{tempx,tempy},{0.0,0.0},0.0,noBorder,false,true)));
        else if(temp[25]=='w'&&temp[26]=='_')
        {   if(temp[33]=='t') virtualObjects.insert(make_pair(string_temp,new VirtualObject(this,{string_temp2},{tempx,tempy},{0.0,0.2},0.0,pageRect(),false,true)));
            else virtualObjects.insert(make_pair(string_temp,new VirtualObject(this,{string_temp2},{tempx,tempy},{0.3,0.0},0.0,pageRect(),false,true))); }
        else if(temp[23]=='F') virtualObjects.insert(make_pair(string_temp,new VirtualObject(this,{string_temp2},{tempx,tempy},{0.25,0.0},0.0,pageRect(),false,true)));
        else heavyBodies.insert(make_pair(string_temp,new HeavyBody(this,{string_temp2},{tempx,tempy}))); }
    inFile.close();
}

PlayPage3::PlayPage3(MainWindow *parent, int Iq)
    : PlayPage(parent, MAX, windowHeight, 3, Iq, snd(Audio_bgm_cactus_land), "", {0,0,MAX,windowHeight},{1280,0})
{
    player = new Player(this,QPoint(1500,380));
    triggers.push_back(new Trigger(this,{70,550,14,50},SLOT(victory())));
    triggers.push_back(new Trigger(this,{1170,0,1,720},SLOT(board())));
    triggers.push_back(new Trigger(this,{1650,575,43,21},SLOT(fly())));
    triggers.push_back(new Trigger(this,{800,0,400,720},SLOT(fish())));
    buttons.insert(make_pair("010:Process", new GameButton(this, {pic(Startup_button_main_3)}, {"0%"}, {550,0}, this, SLOT(empty()))));
    virtualObjects.insert(make_pair("001:Board",new VirtualObject(this,{pic(HelloBoard_5),pic(HelloBoard_6)},{1350,100})));
    virtualObjects.insert(make_pair("002:Wing",new VirtualObject(this,{pic(Wing),""},{1650,575})));
    virtualObjects.insert(make_pair("003:Fence",new VirtualObject(this,{pic(Fence)},{1360,530})));
    virtualObjects.insert(make_pair("004:Fence",new VirtualObject(this,{pic(Fence)},{300,530})));
    virtualObjects.insert(make_pair("005:Tree",new VirtualObject(this,{pic(Tree_1)},{760,505})));
    virtualObjects.insert(make_pair("201:Cloud",new VirtualObject(this,{pic(Cloud_0),pic(Cloud_0_bad)},{220,110},{0.0,0.0},0.0,noBorder,false,true)));
    virtualObjects.insert(make_pair("202:Cloud",new VirtualObject(this,{pic(Cloud_2)},{550,110})));
    virtualObjects.insert(make_pair("203:Cloud",new VirtualObject(this,{pic(Cloud_0)},{1050,110})));
    virtualObjects.insert(make_pair("300:Castle",new VirtualObject(this,{pic(Castle_2)},{0,444})));
    heavyBodies.insert(make_pair("001:Ground",new HeavyBody(this,{pic(Grass_ground)},{0,600})));
    heavyBodies.insert(make_pair("002:Ground",new HeavyBody(this,{pic(Grass_ground)},{200,600})));
    heavyBodies.insert(make_pair("003:Ground",new HeavyBody(this,{pic(Grass_ground)},{400,600})));
    heavyBodies.insert(make_pair("004:Ground",new HeavyBody(this,{pic(Grass_ground)},{600,600})));
    heavyBodies.insert(make_pair("005:Groundright",new HeavyBody(this,{pic(Grass_ground_right)},{800,600})));
    heavyBodies.insert(make_pair("006:Groundleft",new HeavyBody(this,{pic(Grass_ground_left)},{1170,600})));
    heavyBodies.insert(make_pair("007:Ground",new HeavyBody(this,{pic(Grass_ground)},{1200,600})));
    heavyBodies.insert(make_pair("008:Ground",new HeavyBody(this,{pic(Grass_ground)},{1400,600})));
    heavyBodies.insert(make_pair("009:Ground",new HeavyBody(this,{pic(Grass_ground)},{1600,600})));
    heavyBodies.insert(make_pair("010:Ground",new HeavyBody(this,{pic(Grass_ground)},{1800,600})));
    heavyBodies.insert(make_pair("011:Ground",new HeavyBody(this,{pic(Grass_ground)},{2000,600})));
    heavyBodies.insert(make_pair("012:Ground",new HeavyBody(this,{pic(Grass_ground)},{2200,600})));
    heavyBodies.insert(make_pair("013:Ground",new HeavyBody(this,{pic(Grass_ground)},{2400,600})));
    heavyBodies.insert(make_pair("014:Ground",new HeavyBody(this,{pic(Grass_ground)},{2600,600})));
    heavyBodies.insert(make_pair("000:Pipe0",new HeavyBody(this,{pic(PipeBad)},{1800,-200},{0,0},0,noBorder,false,true)));
    heavyBodies.insert(make_pair("000:Pipe1",new HeavyBody(this,{pic(PipeBad_up)},{1800,500},{0,0},0,noBorder,false,true)));
    triggers.push_back(new Trigger(this,{1800,0,135,720},SLOT(insert())));
    heavyBodies.insert(make_pair("000:Pipe2",new HeavyBody(this,{pic(PipeBad)},{2000,-230},{0,0},0,noBorder,false,true)));
    heavyBodies.insert(make_pair("000:Pipe3",new HeavyBody(this,{pic(PipeBad_up)},{2000,470},{0,0},0,noBorder,false,true)));
    triggers.push_back(new Trigger(this,{2000,0,135,720},SLOT(insert())));
    heavyBodies.insert(make_pair("000:Pipe4",new HeavyBody(this,{pic(PipeBad)},{2200,-180},{0,0},0,noBorder,false,true)));
    heavyBodies.insert(make_pair("000:Pipe5",new HeavyBody(this,{pic(PipeBad_up)},{2200,520},{0,0},0,noBorder,false,true)));
    triggers.push_back(new Trigger(this,{2200,0,135,720},SLOT(insert())));
    heavyBodies.insert(make_pair("000:Pipe6",new HeavyBody(this,{pic(PipeBad)},{2400,-190},{0,0},0,noBorder,false,true)));
    heavyBodies.insert(make_pair("000:Pipe7",new HeavyBody(this,{pic(PipeBad_up)},{2400,510},{0,0},0,noBorder,false,true)));
    triggers.push_back(new Trigger(this,{2400,0,135,720},SLOT(insert())));
    heavyBodies.insert(make_pair("000:Pipe8",new HeavyBody(this,{pic(PipeBad)},{2600,-200},{0,0},0,noBorder,false,true)));
    heavyBodies.insert(make_pair("000:Pipe9",new HeavyBody(this,{pic(PipeBad_up)},{2600,500},{0,0},0,noBorder,false,true)));
    triggers.push_back(new Trigger(this,{2600,0,135,720},SLOT(insert())));
}

void PlayPage3::insert()
{
    int x=triggers[triggers.size()-1]->rect.left()+200, y = rand()%70;
    char str[20] = {};
    sprintf(str,"%03d:Ground",x/200+1);
    heavyBodies.insert(make_pair(str,new HeavyBody(this,{pic(Grass_ground)},{x,600})));
    sprintf(str,"000:Pipe%d",(x-1800)/100);
    heavyBodies.insert(make_pair(QString(str),new HeavyBody(this,{pic(PipeBad)},{x,-230+y},{0,0},0,noBorder,false,true)));
    sprintf(str,"000:Pipe%d",(x-1800)/100+1);
    heavyBodies.insert(make_pair(QString(str),new HeavyBody(this,{pic(PipeBad_up)},{x,440+y},{0,0},0,noBorder,false,true)));
    triggers.push_back(new Trigger(this,{x,0,135,720},SLOT(insert())));
    sprintf(str,"%d%%",(x-1800)/20-50);
    buttons["010:Process"]->text[0]=QString(str);
}

EditPage::EditPage(MainWindow *parent, int Iq, int wid, int heig)
    :PlayPage(parent, wid, heig, 5, Iq, snd(Audio_bgm_air_ducts), pic(MapEdit2), {0, 0, 1280, 720})//最后这里把mapedit2替换掉
{
    buttons.insert(make_pair("001:Brick",new GameButton(this, {pic(Brick)}, {""}, {62, 100}, this, SLOT(clicked(QMouseEvent*,GameButton*)))));
    buttons.insert(make_pair("002:Slime",new GameButton(this, {pic(Slime_idle_left)}, {""}, {215, 100}, this, SLOT(clicked(QMouseEvent*,GameButton*)))));
    buttons.insert(make_pair("003:Brick2",new GameButton(this, {pic(UnknownBrickOver)}, {""}, {62, 235}, this, SLOT(clicked(QMouseEvent*,GameButton*)))));
    buttons.insert(make_pair("004:Saw",new GameButton(this, {pic(Saw2)}, {""}, {220, 245}, this, SLOT(clicked(QMouseEvent*,GameButton*)))));
    buttons.insert(make_pair("005:Saw2",new GameButton(this, {pic(Saw_48x12_left)}, {""}, {70, 450}, this, SLOT(clicked(QMouseEvent*,GameButton*)))));
    buttons.insert(make_pair("006:Saw3",new GameButton(this, {pic(Saw_48x12_top)}, {""}, {215, 460}, this, SLOT(clicked(QMouseEvent*,GameButton*)))));
    buttons.insert(make_pair("007:Fish",new GameButton(this, {pic(Fish_1)}, {""}, {65, 585}, this, SLOT(clicked(QMouseEvent*,GameButton*)))));
    buttons.insert(make_pair("008:Eraser",new GameButton(this, {pic(StagePlant_slime_shovel_1)}, {""}, {175, 575}, this, SLOT(clicked(QMouseEvent*,GameButton*)))));
    buttons.insert(make_pair("009:Finish",new GameButton(this, {pic(EndEdit)}, {""}, {1055, 608}, this, SLOT(valuate()))));
}

void EditPage::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::RightButton)
    {   setCursor(Qt::ArrowCursor);
        current = nullptr; }
    else if(event->button()==Qt::LeftButton&&event->x()>=330&&current!=nullptr)
    {   if(current==buttons["008:Eraser"])
        {   setCursor(QCursor(QPixmap(pic(StagePlant_slime_shovel_2))));
            erase(event->pos()); }
        else
        {   tot++; int tmp=0;
            if(current==buttons["001:Brick"]) tmp=1;
            char temp[10]={}; sprintf(temp,"%d%d",tmp,tot);
            virtualObjects.insert(make_pair(temp, new VirtualObject(this,{current->source[0]},QPoint(event->x()-current->width()/2,event->y()-current->height()/2)))); }}
}

void EditPage::mouseReleaseEvent(QMouseEvent *event) {if(event->button()==Qt::LeftButton&&current==buttons["008:Eraser"]) setCursor(QCursor(current->getImg())); }

PVZPage::PVZPage(MainWindow *parent, int Iq, int wid, int heig)
    : PlayPage(parent, wid, heig, 4, Iq, snd(Audio_bgm_strategic_war), pic(StageSimple_block_bottom), {80, 120, 1100, 600})
{
    static char str[100];
    buttons.insert(make_pair("001:Flower", new GameButton(this, {pic(StagePlant_btn_flower)}, {""}, {100, 568}, this, SLOT(selectplt(QMouseEvent*,GameButton*)))));
    buttons.insert(make_pair("002:Gun", new GameButton(this, {pic(StagePlant_btn_gun)}, {""}, {200, 568}, this, SLOT(selectplt(QMouseEvent*,GameButton*)))));
    buttons.insert(make_pair("003:Shovel", new GameButton(this, {pic(StagePlant_btn_shovel)}, {""}, {300, 568}, this, SLOT(selectplt(QMouseEvent*,GameButton*)))));
    sprintf(str,"金钱：%d",Coins);
    buttons.insert(make_pair("004:Coins", new GameButton(this,{pic(Startup_button_main_1)},{QString(str)},{500,20},this,SLOT(empty()))));
    virtualObjects.insert(make_pair("001:Box", new VirtualObject(this, {pic(Box_1)}, {150, 300})));
    virtualObjects.insert(make_pair("002:Pig", new VirtualObject(this, {pic(StagePlant_pig)}, {900, 568})));
    virtualObjects.insert(make_pair("003:Line", new VirtualObject(this, {pic(Line)}, {80, 521})));
    virtualObjects.insert(make_pair("004:Line", new VirtualObject(this, {pic(Line)}, {80, 170})));
    virtualObjects.insert(make_pair("005:Base", new VirtualObject(this, {pic(Base)}, {126, 357})));
    virtualObjects.insert(make_pair("006:Fork", new VirtualObject(this, {pic(Fork)}, {268, 250})));
    virtualObjects.insert(make_pair("007:Fork", new VirtualObject(this, {pic(Fork)}, {268, 350})));
    virtualObjects.insert(make_pair("008:Fork", new VirtualObject(this, {pic(Fork)}, {268, 450})));
    random_shuffle(EnemyPer,EnemyPer+3); //将敌人所在行随机打乱
    T.setInterval(10);
    connect(&T,&QTimer::timeout,this,[=](){Timeout();}); //设置计时器
    for (int i=0;i<3;i++)  //生成植物框
        for (int j=0;j<6;j++){
            sprintf(str,"%d%d:Slot",i,j);
            strPlt[i][j]=QString(str);
            btnPlt[i][j]=new GameButton(this, {pic(StagePlant_shadow), pic(StagePlant_shadow_pressed)}, {""}, {300+j*100, 200+i*100}, this, SLOT(empty()));
            connect(btnPlt[i][j],&GameButton::clicked,this,[=](){selectpos(i,j);});
            btnPlt[i][j]->hide();
            sprintf(str,"002_%d%d:Line",i,j);
            virtualObjects.insert(make_pair(QString(str), new VirtualObject(this, {pic(Line1)}, {303+j*100, 285+i*100}))); } //显示植物框底下的横线
    for (int i=0;i<3;i++){  //生成鱼
        picFish[i]=new VirtualObject(this,{pic(Fish_1)},{xFish[i],yFish[i]});
        virtualObjects.insert(make_pair(strFish[i],picFish[i])); }
    T.start();  //计时器开始
}
void PVZPage::UpdateCoins(){   //更新硬币情况
    static char str[100];
    sprintf(str,"金钱：%d",Coins);
    buttons["004:Coins"]->text[0]=QString(str);
}
void PVZPage::swap(){  //切换选中状态后，重新生成3*6的植物区
    if (isSelected)    //选定了植物/铲子，进入放置状态
    {   if (Type<=2){
            for (int i=0;i<3;i++)
                for (int j=0;j<6;j++)
                    if (!Plant[i][j]) {btnPlt[i][j]->show(); buttons.insert(make_pair(strPlt[i][j],btnPlt[i][j])); } }
        else {for (int i=0;i<3;i++)
                for (int j=0;j<6;j++)
                    if (Plant[i][j]){
                    picPlt[i][j]->hide();
                    virtualObjects.erase(strPlt[i][j]);
                    btnPlt[i][j]->show();
                    buttons.insert(make_pair(strPlt[i][j],btnPlt[i][j])); }
            for (int i=0;i<cntEne;i++)
                if (Hp[i]>0){
                picEne[i]->hide();
                virtualObjects.erase(strEne[i]);
                btnEne[i]->show();
                buttons.insert(make_pair(strEne[i],btnEne[i])); }
        setCursor(QCursor(QPixmap(pic(StagePlant_slime_shovel_1)))); } }
    else     //使用了植物/铲子，回归正常状态
    {   if (Type<=2)
            for (int i=0;i<3;i++)
                for (int j=0;j<6;j++)
                    if (!Plant[i][j]){
                    btnPlt[i][j]->hide();
                    buttons.erase(strPlt[i][j]); }
        if (Type==3){
            for (int i=0;i<3;i++)
                for (int j=0;j<6;j++)
                    if (Plant[i][j]){
                    btnPlt[i][j]->hide();
                    buttons.erase(strPlt[i][j]);
                    picPlt[i][j]->show();
                    virtualObjects.insert(make_pair(strPlt[i][j],picPlt[i][j])); }
            for (int i=0;i<cntEne;i++)
                if (Hp[i]>0){
                btnEne[i]->hide();
                buttons.erase(strEne[i]);
                delete picEne[i];
                picEne[i]=new VirtualObject(this,{EnemyStr[i]},{xEne[i],yEne[i]});
                virtualObjects.insert(make_pair(strEne[i],picEne[i])); } }
        setCursor(Qt::ArrowCursor); }
}
void PVZPage::selectplt(QMouseEvent* event,GameButton* btn){
    if (!isSelected){
        if (btn==buttons["001:Flower"]&&Coins>=30) {Type=1; isSelected=1; swap(); }
        else if(btn==buttons["002:Gun"]&&Coins>=50){Type=2; isSelected=1; swap(); }
        else if(btn==buttons["003:Shovel"])        {Type=3; isSelected=1; swap(); } }
    else {isSelected=0; swap(); }
}
void PVZPage::selectpos(int i,int j){  //植物区(i,j)按钮被按下
    int x=300+j*100;
    int y=200+i*100;
    if (Type<=2){  //种下植物
        Plant[i][j]=Type;
        StartTime[i][j]=Time;
        picPlt[i][j]=new VirtualObject(this,{Type==1?pic(StagePlant_flower):pic(StagePlant_gun_1)},{x,y});
        virtualObjects.insert(make_pair(strPlt[i][j],picPlt[i][j]));
        btnPlt[i][j]->hide();
        buttons.erase(strPlt[i][j]);
        Coins-=Type==1?30:50;
        isSelected=0;
        swap();
        UpdateCoins(); }
    else { Plant[i][j]=0; btnPlt[i][j]->hide(); buttons.erase(strPlt[i][j]); isSelected=0; swap(); } //铲掉该位置的植物
}

void PVZPage::SelectEnemy(int i){   //敌人按钮被按下（铲掉）
    Hp[i]=0;
    btnEne[i]->hide();
    buttons.erase(strEne[i]);
    delete btnEne[i];
    Coins+=10;
    UpdateCoins();
    isSelected=0;
    swap();
    numKill++;
    if (numKill == N_Enemy) {GameWin(); return; }
    if(numKill == N_Last) {int tmp=EnemyGainTime[N_Last]-Time-300; for(int k=N_Last;k<N_Enemy;k++) EnemyGainTime[k]-=tmp; }
}

void PVZPage::Timeout(){
    //计时器发射了一期信号
    static char str[100];
    if (isSelected) return;    //当前处于选中状态，无视该信号
    Time++;
    if (cntEne<N_Enemy && Time==EnemyGainTime[cntEne]){     //到达该生成敌人的时间，生成敌人
        xEne[cntEne]=1000;
        yEne[cntEne]=200+EnemyPer[EnemyRow[cntEne]]*100+5;
        Hp[cntEne]=EnemyHp[EnemyType[cntEne]];
        if (EnemyType[cntEne]==0) EnemyStr[cntEne]=pic(StagePlant_slime_angry_3);
        else if (EnemyType[cntEne]==1) EnemyStr[cntEne]=pic(StagePlant_slime_angry_1);
        else if (EnemyType[cntEne]==2) EnemyStr[cntEne]=pic(StagePlant_slime_angry_2);
        picEne[cntEne]=new VirtualObject(this,{EnemyStr[cntEne]},{xEne[cntEne],yEne[cntEne]});
        sprintf(str,"%d:enemy",cntEne);
        strEne[cntEne]=QString(str);
        virtualObjects.insert(make_pair(strEne[cntEne],picEne[cntEne]));
        btnEne[cntEne]=new GameButton(this,{pic(Startup_button_main_1)},{""},{xEne[cntEne],yEne[cntEne]},this,SLOT(empty()));
        connect(btnEne[cntEne],&GameButton::clicked, this, [=](){SelectEnemy(cntEne);});
        btnEne[cntEne]->hide();
        cntEne++; }
    for (int i=0;i<3;i++)
        for (int j=0;j<6;j++){
            if (Plant[i][j]==1&&(Time-StartTime[i][j])%CoinGainTime==0) {Coins+=10; UpdateCoins(); } //到达该产出金币的时间
            if (Plant[i][j]==2&&(Time-StartTime[i][j])%BulletGainTime==0){  //到达该生产子弹的时间
                xBul[cntBul]=410+j*100+110;
                yBul[cntBul]=200+i*100;
                picBul[cntBul]=new VirtualObject(this,{pic(Toggle_bk)},{xBul[cntBul],yBul[cntBul]});
                sprintf(str,"%d:bullet",cntBul);
                strBul[cntBul]=QString(str);
                virtualObjects.insert(make_pair(strBul[cntBul],picBul[cntBul]));
                cntBul++;

                picPlt[i][j]->hide();
                virtualObjects.erase(strPlt[i][j]);
                delete picPlt[i][j];
                picPlt[i][j]=new VirtualObject(this,{pic(StagePlant_gun_2)},{300+j*100,200+i*100});  //产完子弹后改变射手图片
                virtualObjects.insert(make_pair(strPlt[i][j],picPlt[i][j])); }
            if (Plant[i][j]==2&&(Time-StartTime[i][j])%BulletGainTime==100){    //将射手图片改回去
                picPlt[i][j]->hide();
                virtualObjects.erase(strPlt[i][j]);
                delete picPlt[i][j];
                picPlt[i][j]=new VirtualObject(this,{pic(StagePlant_gun_1)},{300+j*100,200+i*100});
                virtualObjects.insert(make_pair(strPlt[i][j],picPlt[i][j])); } }
    if (Time%BulletFlyTime==0)      //到达子弹该飞行的时间
        for (int i=0;i<cntBul;i++)
            if (picBul[i]){
                picBul[i]->hide();
                virtualObjects.erase(strBul[i]);
                delete picBul[i];
                xBul[i]+=2;
                picBul[i]=new VirtualObject(this,{pic(Toggle_bk)},{xBul[i],yBul[i]});
                virtualObjects.insert(make_pair(strBul[i],picBul[i])); }
    if (Time%FishTime==0)           //到达鱼该前进的时间
        for (int i=0;i<3;i++)
            if (cFish[i]==1){
                picFish[i]->hide();
                virtualObjects.erase(strFish[i]);
                delete picFish[i];
                xFish[i]+=2;
                if (xFish[i]>1000) cFish[i]=2;
                else{picFish[i]=new VirtualObject(this,{xFish[i]%100>50?pic(Fish_1):pic(Fish_2)},{xFish[i],yFish[i]});  //根据鱼的位置切换图片
                     virtualObjects.insert(make_pair(strFish[i],picFish[i])); } }
    if (Time%EnemyTime==0)          //到达敌人该前进的时间
        for (int i=0;i<cntEne;i++)
            if (Hp[i]>0){
                picEne[i]->hide();
                virtualObjects.erase(strEne[i]);
                delete picEne[i];
                delete btnEne[i];
                xEne[i]--;
                picEne[i]=new VirtualObject(this,{EnemyStr[i]},{xEne[i],yEne[i]});
                virtualObjects.insert(make_pair(strEne[i],picEne[i]));
                btnEne[i]=new GameButton(this,{EnemyStr[i]},{""},{xEne[i],yEne[i]},this,SLOT(empty()));
                connect(btnEne[i],&GameButton::clicked, this, [=](){SelectEnemy(i);}); }
    for (int i=0;i<cntEne;i++)
        if (Hp[i]>0){
            int u=EnemyPer[EnemyRow[i]];
            if (xEne[i]<300){         //敌人到达边界
                if (cFish[u]==0) cFish[u]=1;     //鱼出发
                else if (cFish[u]==2) {GameLose(); return; }  /*没有鱼了，游戏失败*/ }
            for (int j=0;j<6;j++)
                if (Plant[u][j]&&xEne[i]>300+j*100&&xEne[i]<300+j*100+85){      //敌人和植物碰撞，消灭植物
                    Plant[u][j]=0;
                    picPlt[u][j]->hide();
                    virtualObjects.erase(strPlt[u][j]); }
            if (cFish[u]==1&&xEne[i]<=xFish[u]+20){     //敌人和鱼碰撞，敌人被消灭
                Hp[i]=-1;
                picEne[i]->hide();
                virtualObjects.erase(strEne[i]);
                delete picEne[i];
                Coins+=10;
                UpdateCoins();
                numKill++;
                if (numKill == N_Enemy) {GameWin(); return; }
                if (numKill == N_Last) {int tmp=EnemyGainTime[N_Last]-Time-300; for(int k=N_Last;k<N_Enemy;k++) EnemyGainTime[k]-=tmp; } } }
    for (int i=0;i<cntEne;i++)
        if (Hp[i]>0)
            for (int j=0;j<cntBul;j++)
                if (picBul[j] && yEne[i]==yBul[j]+5 && xBul[j]+5>xEne[i]){   //敌人和子弹碰撞，子弹消失，敌人掉血
                        picBul[j]->hide();
                        virtualObjects.erase(strBul[j]);
                        delete picBul[j];
                        picBul[j]=NULL;
                        Hp[i]-=20;
                        if (Hp[i]<=0){      //敌人死亡
                            picEne[i]->hide();
                            virtualObjects.erase(strEne[i]);
                            delete picEne[i];
                            Coins+=10;
                            UpdateCoins();
                            numKill++;
                            if (numKill == N_Enemy) {GameWin(); return; }
                            if (numKill == N_Last) {int tmp=EnemyGainTime[N_Last]-Time-300; for(int k=N_Last;k<N_Enemy;k++) EnemyGainTime[k]-=tmp; }
                            break; } }
}
void PVZPage::GameWin(){       //游戏胜利页面
    victory();
}
void PVZPage::GameLose(){      //游戏失败页面
    playerKilled();
}
