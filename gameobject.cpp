#include "gameobject.h"
#include "gamepage.h"

GameObject::GameObject(GamePage *parent, QString str, int x, int y, int speedX, int speedY, int speedRad, int xLower, int xUpper, int yLower, int yUpper, attribute collision, attribute stubborn, attribute grativity, int collisionx, int collisiony, int collisionwidth, int collisionheight)
    : QWidget(parent), img(str), speedX(speedX), speedY(speedY), speedRad(speedRad), cameraSpeedX(parent->cameraSpeedX), cameraSpeedY(parent->cameraSpeedY), xLower(xLower), xUpper(xUpper), yLower(yLower), yUpper(yUpper), collision(collision), stubborn(stubborn), grativity(grativity), collisionX(collisionx), collisionY(collisiony), collisionWidth(collisionwidth), collisionHeight(collisionheight)
{
    setFixedSize(QSize(img.width(), img.height()));
    move(x, y);
    if (collisionWidth == -1) collisionWidth = img.width();
    if (collisionHeight == -1) collisionHeight = img.height();
}

QPixmap GameObject::getImg()
{
    QRect rect(0, 0, img.width(), img.height());
    auto retImg = img.transformed(matrix, Qt::SmoothTransformation);
    rect.moveCenter(retImg.rect().center());
    return retImg.copy(rect);
}

QRect GameObject::getCollisionRect()
{
    return QRect(x() + collisionX, y() + collisionY, collisionWidth, collisionHeight);
}

void GameObject::setLocation(int x, int y)         { move(x,y); }
void GameObject::setX(int x)                       { move(x,y()); }
void GameObject::setY(int y)                       { move(x(),y); }
void GameObject::setSpeed(int x, int y, int rad)   { speedX = x; speedY = y; speedRad = rad; }
void GameObject::setXSpeed(int x)                  { speedX = x; }
void GameObject::setYSpeed(int y)                  { speedY = y; }
void GameObject::setRadSpeed(int rad)              { speedRad = rad; }
void GameObject::setReverseSpeed()                 { speedX = -speedX; speedY = -speedY; }
void GameObject::setXReverseSpeed()                { speedX = -speedX; }
void GameObject::setYReverseSpeed()                { speedY = -speedY; }
void GameObject::setLeftSpeed()                    { speedX = -abs(speedX); }
void GameObject::setRightSpeed()                   { speedX = abs(speedX); }
void GameObject::setUpSpeed()                      { speedY = -abs(speedY); }
void GameObject::setDownSpeed()                    { speedY = abs(speedY); }
state GameObject::collisionWith(GameObject& other) { return getCollisionRect().intersects(other.getCollisionRect()); }

void GameObject::checkBorder()
{
    if (x() + collisionX < xLower && !propleft && !bounceleft)
    {
        pushleft = false;
        if(speedX == 0) speedX = pushSpeed;
        else bounceright = true;
    }
    if (x() + collisionX + collisionWidth > xUpper && !propright && !bounceright)
    {
        pushright = false;
        if(speedX == 0) speedX = -pushSpeed;
        else bounceleft = true;
    }
    if (y() + collisionY < yLower && !propup && !bounceup)
    {
        if(speedY == 0) speedY = pushSpeed;
        else bouncedown = true;
    }
    if (y() + collisionY + collisionHeight > yUpper && !bouncedown)
    {
        if(speedY == 0) speedY = -pushSpeed;
        else bounceup = true; //bounceup: 对地面相对速度为零则跳跃，对地面有正相对速度时则反弹
    }
}

void GameObject::checkState()
{
    if(downObject==nullptr)                        { propup = false; }
    if(leftObject==nullptr)                        { propright = false; }
    if(rightObject==nullptr)                       { propleft = false; }
    if(!propup||bouncedown)                        { bounceup = false; }
    if(bounceup)                                   { propup = false;downObject = nullptr; }
    if(propup)                                     { bouncedown = false; }
    if(bounceleft&&bounceright)                    { bounceleft = bounceright = false; }
    if(pushleft&&pushright)                        { pushleft = pushright = false; }
    if(pushleft||propleft)                         { bounceright = false; }
    if(pushright||propright)                       { bounceleft = false; }
    if(bounceleft||(pushleft&&!propright))         { propleft = false; rightObject = nullptr; }
    if(bounceright||(pushright&&!propleft))        { propright = false; leftObject = nullptr; }
}

void GameObject::useState()
{
    aX = aY = 0;
    if(grativity&&!propup)                         { aY = g; }
    if(bounceup)                                   { setYSpeed(-3); bounceup = false; }
    if(bouncedown)                                 { setDownSpeed(); bouncedown = false; }
    if(bounceleft)                                 { setLeftSpeed(); bounceleft = false; }
    if(bounceright)                                { setRightSpeed(); bounceright = false; }
    if(pushleft)                                   { setXSpeed(-pushSpeed); }
    if(pushright)                                  { setXSpeed(pushSpeed); }
    if(propup)                                     { setYSpeed(downObject->speedY); }
    if(propleft&&rightObject->speedX<speedX)       { setXSpeed(rightObject->speedX); }
    if(propright&&leftObject->speedX>speedX)       { setXSpeed(leftObject->speedX); }
}

void GameObject::updateSpeed() { speedX += aX; speedY += aY; }

void GameObject::updateLocation()
{
    matrix.translate(img.width() / 2.0, img.height() / 2.0);
    matrix.rotate(speedRad);
    matrix.translate(-img.width() / 2.0, -img.height() / 2.0);
    move(x() + speedX + cameraSpeedX, y() + speedY + cameraSpeedY);
}

void GameObject::selfUpdate()
{
    checkBorder();
    checkState();
    useState();
    updateSpeed();
    updateLocation();
}
