#ifndef GLOBAL_H
#define GLOBAL_H
#include <cstring>
#include <ctime>
#include <fstream>
#include <map>
#include <vector>
#include <utility>
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include <QTimer>
#include <QFont>
#include <QTextItem>
#include <QPaintEvent>
#include <QPainter>
#include <QtMultimedia/QMediaPlayer>
#include <QMediaPlaylist>
using namespace std;
#define INTIME(x) connect(&main_timer,SIGNAL(timeout()),this,SLOT(x()),Qt::DirectConnection) //每秒将一个函数触发60次
#define MIN -2147483648                              //MIN宏
#define MAX 2147483647                               //MAX宏
#define NONE   0                                     //方位码   char:
#define UP     8                                     //方位码  |0|0|0|0|上|下|左|右|
#define DOWN   4                                     //方位码
#define LEFT   2                                     //方位码
#define RIGHT  1                                     //方位码
#define windowWidth 1280                             //窗口宽度
#define windowHeight 720                             //窗口高度
#define defaultVolume 50                             //默认音量
#define pic(x) ":/game_resources/image/"#x".png"     //图片位置宏
#define snd(x)  "qrc:/game_resources/sound/"#x".mp3" //声音位置宏
#define pushSpeed 0.3                                //推动标准速度
#define bounceSpeed 1.2                              //弹跳标准速度
#define g 0.003                                      //重力加速度
typedef bool state;
typedef bool attribute;
typedef int mode;
typedef char direction;
typedef struct{QRect rect;QFont font;QString str;} TextItem;
class GameButton;
class GameObject;
class VirtualObject;
class HeavyBody;
class Pushable;
class Role;
class NPC;
class Player;
class Trigger;
class GamePage;
class StartPage;
class MainWindow;
extern QTimer main_timer;
extern const QFont standard_font;
extern const QRect noBorder;
extern const map<QString, QRect> collisionRectMap;
extern const initializer_list<QString> playerImg;
extern const initializer_list<QString> slimeImg;
extern const int flip[18];
bool intersect(QRectF rect1, QRectF rect2);
#endif // GLOBAL_H
