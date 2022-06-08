#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include "global.h"

class GamePage : public QWidget
{
		Q_OBJECT

	public:

		QPixmap background; //背景图

		QRect backgroundArea; //背景图区域

		std::map<QString, GameButton*> buttons; //页面中的按钮

		std::map<QString, VirtualObject*> virtualObjects; //页面中不碰撞的物体

		std::map<QString, HeavyBody*> heavyBodies; //页面中碰撞不改变运动状态的物体

		std::map<QString, Pushable*> pushables; //页面中碰撞会改变运动状态的物体

		std::vector<Role*> roles; //页面中的npc角色

		Player* player = nullptr; //主角

		float cameraSpeedX = 0, cameraSpeedY = 0; //相机速度

		float cameraX = 0, cameraY = 0; //相机左上角位置

		explicit GamePage(QString bg, QRect bgarea, float camerax = 0, float cameray = 0, MainWindow *parent = nullptr, int wid = 1280, int heig = 720);

		virtual ~GamePage();

		void paintEvent(QPaintEvent *event);

	signals:

	public slots:

		void updateAll(); //更新所有物体的速度和位置并刷新页面

};

class StartPage : public GamePage
{
		Q_OBJECT

	public:

		explicit StartPage(MainWindow *parent = nullptr, int wid = 1280, int heig = 720);

		~StartPage() {}

	signals:

	public slots:

}; //开始页面

#endif // GAMEPAGE_H
