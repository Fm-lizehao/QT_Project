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
    {   if(cameraP.x()>0&&player->getCollisionRect().left()<cameraP.x()+250) cameraV.setX(-pushSpeed);
        if(cameraP.x()+windowWidth<pageWidth&&player->getCollisionRect().right()>cameraP.x()+1030) cameraV.setX(pushSpeed);
        if(cameraP.y()>0&&player->getCollisionRect().top()<cameraP.y()+120) cameraV.setY(-pushSpeed);
        if(cameraP.y()+windowHeight<pageHeight&&player->getCollisionRect().bottom()>cameraP.y()+600) cameraV.setY(pushSpeed); }
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
        for(auto j : heavyBodies) {if(i.second==j.second)continue; i.second->checkCollision(j.second); }
        i.second->doCollision(); }
    for (auto i : virtualObjects)    i.second->selfUpdate();
    for (auto i : pushables)         i.second->selfUpdate();
    for (auto i : npcs)              i->selfUpdate();
    if  (player != nullptr)          player->selfUpdate();
    for (auto i : heavyBodies)       i.second->selfUpdate();
    for (auto i : triggers)          if(!i->triggered) i->check(player->getCollisionRect());
    update();
}

void GamePage::paintEvent(QPaintEvent *event)
{
    if(img==nullptr)
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
    for (auto i : topVirtualObjects)   painter.drawPixmap(i.second->getRect(), i.second->getImg());
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
    playlist->addMedia(QUrl(snd(Audio_bgm_into_the_castle)));
    music->play();
}

PlayPage::PlayPage(MainWindow *parent, int wid, int heig, int Level, int Iq, QString bgm, QString bg, QRect bgarea, QPointF cameraP)
    : GamePage(parent, wid, heig, bg, bgarea, cameraP), level(Level), IQ(Iq)
{
    connect(this,SIGNAL(restarted(int,int)),parent,SLOT(restart(int,int)));
    buttons.insert(make_pair("001:Back", new GameButton(this, {pic(Startup_button_main_3)}, {"返回"}, {20, 0}, parent, SLOT(backMain()))));
    playlist->addMedia(QUrl(bgm));
    music->play();
}

void PlayPage::playerKilled()
{
    for(auto i : topVirtualObjects) delete i.second;
    for(auto i : topButtons) delete i.second;
    topVirtualObjects.clear();
    topText.clear();
    topButtons.clear();
    delete img;
    img = nullptr;
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
    IQ-=50;
    QMediaPlayer * killedMusic = new QMediaPlayer(this);
    killedMusic->setVolume(defaultVolume);
    killedMusic->setMedia(QUrl(snd(Audio_boos)));
    killedMusic->play();
}

void PlayPage::victory()
{
    for(auto i : topVirtualObjects) delete i.second;
    for(auto i : topButtons) delete i.second;
    topVirtualObjects.clear();
    topText.clear();
    topButtons.clear();
    delete img;
    img = nullptr;
    topVirtualObjects.insert(make_pair("001:Victory", new VirtualObject(this, {pic(FailFrame)}, {450,130})));
    topVirtualObjects.insert(make_pair("002:UpLine", new VirtualObject(this, {pic(Fail_number_frame_up)}, {561,255})));
    topVirtualObjects.insert(make_pair("003:Downline", new VirtualObject(this, {pic(Fail_number_frame_down)}, {561,340})));
    topVirtualObjects.insert(make_pair("004:Emoji", new VirtualObject(this, {pic(Emoji_hero_6)}, {603,110})));
    topText.push_back({QRect(600,220,70,30),QFont("Felix Titling", 15, QFont::Bold, false),QString("IQ")});
    topText.push_back({QRect(560,255,150,100),QFont("Bahnschrift SemiBold Condensed", 36, QFont::Bold, false),QString::number(IQ)});
    topText.push_back({QRect(500,350,266,30),QFont("幼圆", 8, QFont::Bold, false),QString("国际砖家组织权威认证")});
    topText.push_back({QRect(490,366,166,50),QFont("幼圆", 10, QFont::Bold, false),QString("后人有诗赞曰：")});
    topText.push_back({QRect(500,383,266,150),QFont("幼圆", 12, QFont::Bold, false),comment[4]});
    topButtons.insert(make_pair("001:Restart",new GameButton(this,{pic(Startup_button_main_3)}, {"继续!"}, {570,515}, this, SLOT(restart()))));
    QMediaPlayer * victoryMusic = new QMediaPlayer(this);
    victoryMusic->setVolume(defaultVolume);
    victoryMusic->setMedia(QUrl(snd(Audio_congratulations)));
    victoryMusic->play();
}

PlayPage1::PlayPage1(MainWindow *parent, int wid, int heig, int Iq)
    : PlayPage(parent, wid, heig, 1, Iq, snd(Audio_bgm_aquatic_circus))
{
    player = new Player(this,QPoint(100,100));
    triggers.push_back(new Trigger(this,pageRect(),SLOT(victory())));
}

EditPage::EditPage(MainWindow *parent, int wid, int heig)
    :GamePage(parent, wid, heig, pic(MapEdit), {0, 0, 1280, 720})
{
    buttons.insert(make_pair("001:Brick",new GameButton(this, {pic(Brick)}, {""}, {62, 100}, this, SLOT(clicked(QMouseEvent*,GameButton*)))));
    buttons.insert(make_pair("008:Eraser",new GameButton(this, {pic(StagePlant_slime_shovel_1)}, {""}, {175, 575}, this, SLOT(clicked(QMouseEvent*,GameButton*)))));
    buttons.insert(make_pair("009:Finish",new GameButton(this, {pic(EndEdit)}, {""}, {1055, 608}, this, SLOT(valuate()))));
    buttons.insert(make_pair("010:Back", new GameButton(this, {pic(Startup_button_main_3)}, {"返回"}, {20, 0}, parent, SLOT(backMain()))));
    playlist->addMedia(QUrl(snd(Audio_bgm_air_ducts)));
    music->play();
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
        {   char temp[10]={}; sprintf(temp,"%d",virtualObjects.size());
            virtualObjects.insert(make_pair(temp, new VirtualObject(this,{current->source[0]},QPoint(event->x()-current->width()/2,event->y()-current->height()/2)))); }}
}

void EditPage::mouseReleaseEvent(QMouseEvent *event) {if(event->button()==Qt::LeftButton&&current==buttons["008:Eraser"]) setCursor(QCursor(current->getImg())); }

PVZPage::PVZPage(MainWindow *parent, int wid, int heig)
    : GamePage(parent, wid, heig, pic(StageSimple_block_bottom), {80, 120, 1100, 600})
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
    playlist->addMedia(QUrl(snd(Audio_bgm_strategic_war)));
    music->play();  //接着奏乐
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
                buttons.insert(make_pair(strEne[i],btnEne[i])); } } }
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
                virtualObjects.insert(make_pair(strEne[i],picEne[i])); } } }
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
    this->hide();
    T.stop();
}
void PVZPage::GameLose(){      //游戏失败页面
    this->hide();
    T.stop();
}
