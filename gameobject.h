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

        bool grativity;   //是否受重力下落

		GameObject() {}

        GameObject(QWidget *parent, QString str, int x, int y, int speedX = 0, int speedY = 0, int speedRad = 0, int xLower = MIN, int xUpper = MAX, int yLower = MIN, int yUpper = MAX, bool inCollision=true, bool stubborn = true, bool grativity = false);

        virtual ~GameObject();

		int getX();

		int getY();

		int getWidth();

		int getHeight();

		QPixmap getImg();

		void setSpeed(int speedx, int speedy, int speedRad);

		void setReverseSpeed();

        void setXReverseSpeed();

        void setYReverseSpeed();

		void checkOutBorder();

		bool isCollision(GameObject& other);

	signals:

	public slots:

		void updateLocation();

};

class VirtualObject : public GameObject
{
        Q_OBJECT

    public:

        VirtualObject(QWidget *parent, QString str, int x, int y, int speedX = 0, int speedY = 0, int speedRad = 0, int xLower = MIN, int xUpper = MAX, int yLower = MIN, int yUpper = MAX, bool grativity = false);

        ~VirtualObject();

};

class HeavyBody : public GameObject
{
        Q_OBJECT

    public:

        HeavyBody(QWidget *parent, QString str, int x, int y, int speedX = 0, int speedY = 0, int speedRad = 0, int xLower = MIN, int xUpper = MAX, int yLower = MIN, int yUpper = MAX, bool grativity = false);

        ~HeavyBody();

};

class Pushable : public GameObject
{
        Q_OBJECT

    public:

        Pushable(QWidget *parent, QString str, int x, int y, int speedX = 0, int speedY = 0, int speedRad = 0, int xLower = MIN, int xUpper = MAX, int yLower = MIN, int yUpper = MAX, bool grativity = false);

        ~Pushable();

};

class Role : public GameObject
{
		Q_OBJECT
};

class LineBarrier : public GameObject
{
        Q_OBJECT
};

#endif // GAMEOBJECT_H
