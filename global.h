#include <cmath>
#include <map>
#include <utility>
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QFont>
#include <QPaintEvent>
#include <QPainter>
#include <QtMultimedia/QMediaPlayer>
#include <QMediaPlaylist>

class GameButton;
class GameObject;
class IluusoryObject;
class RealObject;
class LineBarrier;
class Role;
class GamePage;
class StartPage;
class MainWindow;

extern QTimer main_timer;

extern QFont standard_font;

#ifndef INTIME
#define INTIME(x) connect(&main_timer,&QTimer::timeout,this,x,Qt::DirectConnection)
#endif

#ifndef MIN
#define MIN -2147483648
#endif

#ifndef MAX
#define MAX 2147483647
#endif

#ifndef pic
#define pic(x) ":/game_resources/image/"#x".png"
#endif

#ifndef snd
#define snd(x)  "qrc:/game_resources/sound/"#x".mp3"
#endif
