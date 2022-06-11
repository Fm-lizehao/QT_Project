#ifndef GLOBAL_H
#define GLOBAL_H

#include <map>
#include <vector>
#include <utility>
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include <QTimer>
#include <QFont>
#include <QPaintEvent>
#include <QPainter>
#include <QtMultimedia/QMediaPlayer>
#include <QMediaPlaylist>

#define INTIME(x) connect(&main_timer,SIGNAL(timeout()),this,SLOT(x()),Qt::DirectConnection) //每秒将一个函数触发60次
#define MIN -2147483648                              //MIN宏
#define MAX 2147483647                               //MAX宏
#define windowWidth 1280                             //窗口宽度
#define windowHeight 720                             //窗口高度
#define pic(x) ":/game_resources/image/"#x".png"     //图片位置宏
#define snd(x)  "qrc:/game_resources/sound/"#x".mp3" //声音位置宏
#define pushSpeed 0.5                                //推动标准速度
#define g 0.008                                      //重力加速度

typedef bool state;
typedef bool attribute;
typedef int mode;

class GameButton;
class GameObject;
class VirtualObject;
class HeavyBody;
class Pushable;
class Role;
class Player;
class GamePage;
class StartPage;
class MainWindow;

extern QTimer main_timer;
extern const QFont standard_font;
extern const QRect noBorder;
extern const std::map<QString, QRect> collisionRectMap;
extern const std::initializer_list<QString> playerImg;
extern const int flip[18];

#endif // GLOBAL_H
