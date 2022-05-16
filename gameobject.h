#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "global.h"

class GameObject : public QWidget
{
		Q_OBJECT

	private:

		QPixmap img;

	public:

		QMatrix matrix;

		int speedX, speedY, speedRad;

		int xLower, xUpper, yLower, yUpper;

        bool inCollision;   //是否参与碰撞

		bool isStubborn;   //能不能被撞得动

		GameObject() {}

        GameObject(QWidget *parent, QString str, int x, int y, int speedX = 0, int speedY = 0, int speedRad = 0, int xLower = MIN, int xUpper = MAX, int yLower = MIN, int yUpper = MAX, bool inCollision=true, bool stubborn = true);

		~GameObject();

		int getX();

		int getY();

		int getWidth();

		int getHeight();

		QPixmap getImg();

		void setSpeed(int speedx, int speedy, int speedRad);

		void setReverseSpeed();

		void checkOutBorder();

		bool isCollision(GameObject& other);

	signals:

	public slots:

		void updateLocation();

};


class LineBarrier : public GameObject
{
		Q_OBJECT
};


class Role : public GameObject
{
		Q_OBJECT
};

#endif // GAMEOBJECT_H
