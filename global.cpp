#include "global.h"

QTimer main_timer;

const QFont standard_font("幼圆", 15, QFont::Bold, false);

const QRect noBorder = {QPoint(MIN,MIN),QPoint(MAX,MAX)};

const std::map<QString, QRect> collisionRectMap
    ={

     }; //此处插入需要限制碰撞区域的图片的<QString, QRect>

const std::initializer_list<QString> playerImg
    ={
        pic(Player_stand_right), //1
        pic(Player_stand_left),  //2
        pic(Player_walk1_right), //3
        pic(Player_walk1_left),  //4
        pic(Player_walk2_right), //5
        pic(Player_walk2_left),  //6
        pic(Player_jump_right),  //7
        pic(Player_jump_left),   //8
        pic(Player_fly1_right),  //9
        pic(Player_fly1_left),   //10
        pic(Player_fly2_right),  //11
        pic(Player_fly2_left),   //12
        pic(Player_cry1_right),  //13
        pic(Player_cry1_left),   //14
        pic(Player_cry2_right),  //15
        pic(Player_cry2_left),   //16
        pic(Player_cry3_right),  //17
        pic(Player_cry3_left)    //18
    };
