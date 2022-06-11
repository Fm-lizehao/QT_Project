#include "global.h"

QTimer main_timer;

const QFont standard_font("幼圆", 15, QFont::Bold, false);

const QRect noBorder = {QPoint(MIN,MIN),QPoint(MAX,MAX)};

const std::map<QString, QRect> collisionRectMap
    ={

     }; //此处插入需要限制碰撞区域的图片的<QString, QRect>

const std::initializer_list<QString> playerImg
    ={
        pic(Player_stand_right), //0
        pic(Player_stand_left),  //1
        pic(Player_walk1_right), //2
        pic(Player_walk1_left),  //3
        pic(Player_walk2_right), //4
        pic(Player_walk2_left),  //5
        pic(Player_jump_right),  //6
        pic(Player_jump_left),   //7
        pic(Player_fly1_right),  //8
        pic(Player_fly1_left),   //9
        pic(Player_fly2_right),  //10
        pic(Player_fly2_left),   //11
        pic(Player_cry1_right),  //12
        pic(Player_cry1_left),   //13
        pic(Player_cry2_right),  //14
        pic(Player_cry2_left),   //15
        pic(Player_cry3_right),  //16
        pic(Player_cry3_left)    //17
    };

const int flip[18] = {0,1,4,5,2,3,6,7,8,9,10,11,14,15,16,17,16,17};
