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
    for(auto i : pushables)
    {
        for(auto j: npcs) i.second->checkCollision(j);
        if(player != nullptr) i.second->checkCollision(player);
        for(auto j : pushables) {if(i.second==j.second)continue; i.second->checkCollision(j.second); }
        for(auto j : heavyBodies) i.second->checkCollision(j.second);
        i.second->doCollision();
    }
    for(auto i : npcs)
    {
        for(auto j : virtualObjects) i->checkCollision(j.second);
        for(auto j : npcs) {if(i==j)continue; i->checkCollision(j); }
        if(player != nullptr) {i->checkCollision(player); }
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
    for(auto i : heavyBodies)
    {
        for(auto j: npcs) i.second->checkCollision(j);
        if(player != nullptr) i.second->checkCollision(player);
        for(auto j : pushables) i.second->checkCollision(j.second);
        for(auto j : heavyBodies) {if(i.second==j.second)continue; i.second->checkCollision(j.second); }
        i.second->doCollision();
    }
    for (auto i : virtualObjects)    i.second->selfUpdate();
    for (auto i : pushables)         i.second->selfUpdate();
    for (auto i : npcs)              i->selfUpdate();
    if  (player != nullptr)          player->selfUpdate();
    for (auto i : heavyBodies)       i.second->selfUpdate();
    update();
}

void GamePage::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setFont(standard_font);
    painter.drawPixmap(backgroundArea.translated(-cameraP.toPoint()), QPixmap(background));
    for (auto i : virtualObjects)   painter.drawPixmap(i.second->getRect(), i.second->getImg());
    for (auto i : heavyBodies)      painter.drawPixmap(i.second->getRect(), i.second->getImg());
    for (auto i : pushables)        painter.drawPixmap(i.second->getRect(), i.second->getImg());
    for (auto i : npcs)             painter.drawPixmap(i->getRect(), i->getImg());
    if  (player != nullptr)         painter.drawPixmap(player->getRect(), player->getImg());
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
    buttons.insert(make_pair("003:PVZ", new GameButton(this, {pic(Startup_button_main_1), pic(Startup_button_main_2)}, {"奇怪的地方"}, {780, 488}, parent, SLOT(PVZ()))));
    buttons.insert(make_pair("004:Config", new GameButton(this, {pic(Startup_button_main_3)}, {"设置"}, {170, 0}, parent, SLOT(config()))));
    buttons.insert(make_pair("005:Exit", new GameButton(this, {pic(Startup_button_main_3)}, {"退出"}, {20, 0}, parent, SLOT(exit()))));
    virtualObjects.insert(make_pair("001:Cloud", new VirtualObject(this, {pic(Cloud_0_cute)}, {200, 40}, {-0.2, 0}, 0, pageRect(), false)));
    virtualObjects.insert(make_pair("002:Title", new VirtualObject(this, {pic(Startup_title_zh)}, {744, 168}, {0, 0}, 0, pageRect(), false)));
    virtualObjects.insert(make_pair("003:Bottomline", new VirtualObject(this, {pic(Startup_title_line_both)}, {767, 238}, {0, 0}, 0, pageRect(), false)));
    virtualObjects.insert(make_pair("004:Topline", new VirtualObject(this, {pic(Startup_topsep)}, {640, 78}, {0, 0}, 0, pageRect(), false)));
    virtualObjects.insert(make_pair("005:Jp-of", new VirtualObject(this, {pic(Startup_title_jpof)}, {856, 164}, {0, 0}, 0.2, pageRect(), false)));
}

PlayPage::PlayPage(MainWindow *parent, int wid, int heig)
    : GamePage(parent, wid, heig, pic(Startup_leftCastle), {80, 120, 1100, 600})
{
    virtualObjects.insert(make_pair("001:Cloud", new VirtualObject(this, {pic(Cloud_0_cute),pic(Cloud_0_bad)}, {200, 80}, {-0.2, 0}, 0, pageRect(), false, true)));
    heavyBodies.insert(make_pair("001:Object", new HeavyBody(this, {pic(Float_144)}, {0,400}, {0,0}, 0, pageRect())));
    heavyBodies.insert(make_pair("002:Object", new HeavyBody(this, {pic(Float_144)}, {150,400}, {0,0}, 0, pageRect())));
    heavyBodies.insert(make_pair("003:Object", new HeavyBody(this, {pic(Float_144)}, {300,400}, {0,0}, 0, pageRect())));
    heavyBodies.insert(make_pair("004:Object", new HeavyBody(this, {pic(Float_144)}, {450,400}, {0,0}, 0, pageRect())));
    heavyBodies.insert(make_pair("005:Object", new HeavyBody(this, {pic(Float_144)}, {600,400}, {0,0}, 0, pageRect())));
    heavyBodies.insert(make_pair("006:Object", new HeavyBody(this, {pic(Float_144)}, {750,400}, {0,0}, 0, pageRect())));
    heavyBodies.insert(make_pair("007:Object", new HeavyBody(this, {pic(Float_144)}, {900,400}, {0,0}, 0, pageRect())));
    heavyBodies.insert(make_pair("008:Object", new HeavyBody(this, {pic(Float_144)}, {1050,400}, {0,0}, 0, pageRect())));
    pushables.insert(make_pair("001:Block", new Pushable(this, {pic(BrickUnknown)}, {500,80})));
    npcs.push_back(new NPC(this,slimeImg,{800,100},{-0.2,0}));
    player = new Player(this,{100,100});
}

EditPage::EditPage(MainWindow *parent, int wid, int heig)
    :GamePage(parent, wid, heig, pic(MapEdit), {0, 0, 1280, 720})
{
    buttons.insert(make_pair("001:Brick",new GameButton(this, {pic(Brick)}, {""}, {62, 100}, this, SLOT(clicked(GameButton*)))));
    buttons.insert(make_pair("008:Eraser",new GameButton(this, {pic(StagePlant_slime_shovel_1)}, {""}, {175, 575}, this, SLOT(clicked(GameButton*)))));
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
        {   char temp[10]={}; sprintf(temp,"%d",virtualObjects.size());
            virtualObjects.insert(make_pair(temp, new VirtualObject(this,{current->source[0]},QPointF(event->x()-current->width()/2,event->y()-current->height()/2)))); }}
}

void EditPage::mouseReleaseEvent(QMouseEvent *event) {if(current==buttons["008:Eraser"]) setCursor(QCursor(current->getImg())); }

PVZPage::PVZPage(MainWindow *parent, int wid, int heig)
    : GamePage(parent, wid, heig)
{
    static char str[100];
    btn1 = new GameButton(this, {pic(StagePlant_btn_flower)}, {""}, {100, 568}, this, SLOT(empty()));
    connect(btn1,&GameButton::clicked,this,[=](){selectplt(1);});
    buttons.insert(make_pair("001:Plant", btn1));
    btn2 = new GameButton(this, {pic(StagePlant_btn_gun)}, {""}, {200, 568}, this, SLOT(empty()));
    connect(btn2,&GameButton::clicked,this,[=](){selectplt(2);});
    buttons.insert(make_pair("002:Gun", btn2));
    btn3 = new GameButton(this, {pic(StagePlant_btn_shovel)}, {""}, {300,568}, this, SLOT(empty()));
    connect(btn3,&GameButton::clicked,this,[=](){selectplt(3);});
    buttons.insert(make_pair("003:Shovel", btn3));
    coins=100;
    sprintf(str,"金钱：%d",coins);
    btn4 = new GameButton(this,{pic(Startup_button_main_1)},{QString(str)},{500,20},this,SLOT(empty()));
    buttons.insert(make_pair("004:Coins", btn4));
    virtualObjects.insert(make_pair("001:Box", new VirtualObject(this, {pic(Box_1)}, {150, 300})));
    virtualObjects.insert(make_pair("003:Pig", new VirtualObject(this, {pic(StagePlant_pig)}, {900, 568})));
    virtualObjects.insert(make_pair("004:Line2", new VirtualObject(this, {pic(Line)}, {80, 521})));
    virtualObjects.insert(make_pair("005:Line3", new VirtualObject(this, {pic(Line)}, {80, 170})));
    virtualObjects.insert(make_pair("006:Taizi", new VirtualObject(this, {pic(Base)}, {137, 358})));
    virtualObjects.insert(make_pair("007:Chazi1", new VirtualObject(this, {pic(Base)}, {259, 247})));
    virtualObjects.insert(make_pair("007:Chazi2", new VirtualObject(this, {pic(Base)}, {259, 347})));
    virtualObjects.insert(make_pair("007:Chazi3", new VirtualObject(this, {pic(Base)}, {259, 447})));
    is_selected=0;
    Time=0;
    ec=0;bc=0;
    Killed=0;
    T.setInterval(10);
    for (int i=0;i<3;i++) EnemyPer[i]=i;
    random_shuffle(EnemyPer,EnemyPer+3);
    connect(&T,&QTimer::timeout,this,[=](){Timeout();});
    for (int i=0;i<3;i++){
        for (int j=0;j<6;j++){
            int x=300+j*100;
            int y=200+i*100;
            A[i][j]=0;
            sprintf(str,"%d%d:Slot",i,j);
            s[i][j]=QString(str);
            B[i][j]=new GameButton(this, {pic(StagePlant_shadow), pic(StagePlant_shadow_pressed)}, {""}, {x, y}, this, SLOT(empty()));
            connect(B[i][j],&GameButton::clicked,this,[=](){selectpos(i,j);});
            B[i][j]->hide();
            sprintf(str,"002_%d%d:Line",i,j);
            virtualObjects.insert(make_pair(QString(str), new VirtualObject(this, {pic(Line1)}, {x+3, y+85})));
        }
    }
    for (int i=0;i<3;i++){
        Fc[i]=0;
        Fx[i]=250;
        Fy[i]=225+i*100;
        sprintf(str,"%d:Fish",i);
        Fs[i]=QString(str);
        F[i]=new VirtualObject(this,{pic(Fish_1)},{Fx[i],Fy[i]});
        virtualObjects.insert(make_pair(Fs[i],F[i]));
    }
    T.start();
}
void PVZPage::empty(){

}
void PVZPage::UpdateCoins(){
    static char str[100];
    btn4->hide();
    buttons.erase("004:Coins");
    delete btn4;
    sprintf(str,"金钱：%d",coins);
    btn4 = new GameButton(this,{pic(Startup_button_main_1)},{QString(str)},{500,20},this,SLOT(empty()));
    buttons.insert(make_pair("004:Coins", btn4));
}

void PVZPage::swap(){
    if (is_selected){
        if (type<=2){
            for (int i=0;i<3;i++){
                for (int j=0;j<6;j++) if (!A[i][j]){
                    B[i][j]->show();
                    buttons.insert(make_pair(s[i][j],B[i][j]));
                }
            }
        } else{
            for (int i=0;i<3;i++){
                for (int j=0;j<6;j++) if (A[i][j]){
                    C[i][j]->hide();
                    virtualObjects.erase(s[i][j]);
                    B[i][j]->show();
                    buttons.insert(make_pair(s[i][j],B[i][j]));
                }
            }
            for (int i=0;i<ec;i++) if (hp[i]>0){
                e[i]->hide();
                virtualObjects.erase(es[i]);
                eb[i]->show();
                buttons.insert(make_pair(es[i],eb[i]));
            }
        }
    } else{
        if (type<=2){
            for (int i=0;i<3;i++){
                for (int j=0;j<6;j++) if (!A[i][j]){
                    B[i][j]->hide();
                    buttons.erase(s[i][j]);
                }
            }
        }
        if (type==3){
            for (int i=0;i<3;i++){
                for (int j=0;j<6;j++) if (A[i][j]){
                    B[i][j]->hide();
                    buttons.erase(s[i][j]);
                    C[i][j]->show();
                    virtualObjects.insert(make_pair(s[i][j],C[i][j]));
                }
            }
            for (int i=0;i<ec;i++) if (hp[i]>0){
                eb[i]->hide();
                buttons.erase(es[i]);
                delete e[i];
                e[i]=new VirtualObject(this,{EnemyStr[i]},{ex[i],ey[i]});
                virtualObjects.insert(make_pair(es[i],e[i]));
            }
        }
    }
}
void PVZPage::selectplt(int t){
    if (!is_selected){
        if (t==1){
            if (coins>=30){
                type=1;
                is_selected=1;
                swap();
            }
        } else if (t==2){
            if (coins>=50){
                type=2;
                is_selected=1;
                swap();
            }
        } else{
            type=3;
            is_selected=1;
            swap();
        }
    } else{
        is_selected=0;
        swap();
    }
}
void PVZPage::selectpos(int i,int j){
    int x=300+j*100;
    int y=200+i*100;
    if (type<=2){
        A[i][j]=type;
        StartTime[i][j]=Time;
        C[i][j]=new VirtualObject(this,{type==1?pic(StagePlant_flower):pic(StagePlant_gun_1)},{x,y});
        virtualObjects.insert(make_pair(s[i][j],C[i][j]));
        B[i][j]->hide();
        buttons.erase(s[i][j]);
        coins-=type==1?30:50;
        is_selected=0;
        swap();
        UpdateCoins();
    } else{
        A[i][j]=0;
        B[i][j]->hide();
        buttons.erase(s[i][j]);
        is_selected=0;
        swap();
    }
}

void PVZPage::SelectEnemy(int i){
    hp[i]=0;
    eb[i]->hide();
    buttons.erase(es[i]);
    delete eb[i];
    coins+=10;
    UpdateCoins();
    is_selected=0;
    swap();
    Killed++;
    if (Killed == N_Enemy){
        GameWin();
        return;
    }
    if (Killed == N_Last){
        int tmp=EnemyGainTime[N_Last]-Time-300;
        for (int k=N_Last;k<N_Enemy;k++){
            EnemyGainTime[k]-=tmp;
        }
    }
}

void PVZPage::Timeout(){
    static char str[100];
    if (is_selected) return;
    Time++;
    if (ec<N_Enemy && Time==EnemyGainTime[ec]){
        ex[ec]=1000;
        ey[ec]=200+EnemyPer[EnemyRow[ec]]*100+5;
        hp[ec]=EnemyHp[EnemyType[ec]];
        if (EnemyType[ec]==0){
            EnemyStr[ec]=pic(StagePlant_slime_angry_3);
        } else if (EnemyType[ec]==1){
            EnemyStr[ec]=pic(StagePlant_slime_angry_1);
        } else if (EnemyType[ec]==2){
            EnemyStr[ec]=pic(StagePlant_slime_angry_2);
        }
        e[ec]=new VirtualObject(this,{EnemyStr[ec]},{ex[ec],ey[ec]});
        sprintf(str,"%d:enemy",ec);
        es[ec]=QString(str);
        virtualObjects.insert(make_pair(es[ec],e[ec]));
        eb[ec]=new GameButton(this,{pic(Startup_button_main_1)},{""},{ex[ec],ey[ec]},this,SLOT(empty()));
        connect(eb[ec],&GameButton::clicked, this, [=](){SelectEnemy(ec);});
        eb[ec]->hide();
        ec++;
    }
    for (int i=0;i<3;i++){
        for (int j=0;j<6;j++){
            if (A[i][j]==1&&(Time-StartTime[i][j])%CoinGainTime==0){
                coins+=10;
                UpdateCoins();
            }
            if (A[i][j]==2&&(Time-StartTime[i][j])%BulletGainTime==0){
                int x=300+j*100+100;
                int y=200+i*100;
                bx[bc]=x+10;
                by[bc]=y;
                b[bc]=new VirtualObject(this,{pic(Toggle_bk)},{bx[bc],by[bc]});
                sprintf(str,"%d:bullet",bc);
                bs[bc]=QString(str);
                virtualObjects.insert(make_pair(bs[bc],b[bc]));
                bc++;

                x=300+j*100;
                y=200+i*100;
                C[i][j]->hide();
                virtualObjects.erase(s[i][j]);
                delete C[i][j];
                C[i][j]=new VirtualObject(this,{pic(StagePlant_gun_2)},{x,y});
                virtualObjects.insert(make_pair(s[i][j],C[i][j]));
            }
            if (A[i][j]==2&&(Time-StartTime[i][j])%BulletGainTime==100){
                int x=300+j*100;
                int y=200+i*100;
                C[i][j]->hide();
                virtualObjects.erase(s[i][j]);
                delete C[i][j];
                C[i][j]=new VirtualObject(this,{pic(StagePlant_gun_1)},{x,y});
                virtualObjects.insert(make_pair(s[i][j],C[i][j]));
            }
        }
    }
    if (Time%BulletFlyTime==0){
        for (int i=0;i<bc;i++)
            if (b[i]){
                b[i]->hide();
                virtualObjects.erase(bs[i]);
                delete b[i];
                bx[i]+=2;
                b[i]=new VirtualObject(this,{pic(Toggle_bk)},{bx[i],by[i]});
                virtualObjects.insert(make_pair(bs[i],b[i]));
            }
    }
    if (Time%FishTime==0){
        for (int i=0;i<3;i++)
            if (Fc[i]==1){
                F[i]->hide();
                virtualObjects.erase(Fs[i]);
                delete F[i];
                Fx[i]+=2;
                if (Fx[i]>1000){
                    Fc[i]=2;
                } else{
                    F[i]=new VirtualObject(this,{Fx[i]%100>50?pic(Fish_1):pic(Fish_2)},{Fx[i],Fy[i]});
                    virtualObjects.insert(make_pair(Fs[i],F[i]));
                }
            }
    }
    if (Time%EnemyTime==0){
        for (int i=0;i<ec;i++)
            if (hp[i]>0){
                e[i]->hide();
                virtualObjects.erase(es[i]);
                delete e[i];
                delete eb[i];
                ex[i]--;
                e[i]=new VirtualObject(this,{EnemyStr[i]},{ex[i],ey[i]});
                virtualObjects.insert(make_pair(es[i],e[i]));
                eb[i]=new GameButton(this,{EnemyStr[i]},{""},{ex[i],ey[i]},this,SLOT(empty()));
                connect(eb[i],&GameButton::clicked, this, [=](){SelectEnemy(i);});
            }
    }
    for (int i=0;i<ec;i++)
        if (hp[i]>0){
            int u=EnemyPer[EnemyRow[i]];
            if (ex[i]<300){
                if (Fc[u]==0){
                    Fc[u]=1;
                } else if (Fc[u]==2){
                    GameLose();
                    return;
                }
            }
            for (int j=0;j<6;j++){
                if (A[u][j]&&ex[i]>300+j*100&&ex[i]<300+j*100+85){
                    A[u][j]=0;
                    C[u][j]->hide();
                    virtualObjects.erase(s[u][j]);
                }
            }
            if (Fc[u]==1&&ex[i]<=Fx[u]+20){
                hp[i]=-1;
                e[i]->hide();
                virtualObjects.erase(es[i]);
                delete e[i];
                coins+=10;
                UpdateCoins();
                Killed++;
                if (Killed == N_Enemy){
                    GameWin();
                    return;
                }
                if (Killed == N_Last){
                    int tmp=EnemyGainTime[N_Last]-Time-300;
                    for (int k=N_Last;k<N_Enemy;k++){
                        EnemyGainTime[k]-=tmp;
                    }
                }
            }
        }
    for (int i=0;i<ec;i++)
        if (hp[i]>0){
            for (int j=0;j<bc;j++)
                if (b[j]){
                    if (ey[i]==by[j]+5&&bx[j]+5>ex[i]){
                        b[j]->hide();
                        virtualObjects.erase(bs[j]);
                        delete b[j];
                        b[j]=NULL;
                        hp[i]-=20;
                        if (hp[i]<=0){
                            e[i]->hide();
                            virtualObjects.erase(es[i]);
                            delete e[i];
                            coins+=10;
                            UpdateCoins();
                            Killed++;
                            if (Killed == N_Enemy){
                                GameWin();
                                return;
                            }
                            if (Killed == N_Last){
                                int tmp=EnemyGainTime[N_Last]-Time-300;
                                for (int k=N_Last;k<N_Enemy;k++){
                                    EnemyGainTime[k]-=tmp;
                                }
                            }
                            break;
                        }
                    }
                }
        }
}

void PVZPage::GameWin(){
    this->hide();
    T.stop();
}
void PVZPage::GameLose(){
    this->hide();
    T.stop();
}
