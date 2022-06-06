#include "gameobject.h"
#include "gamepage.h"

GameObject::GameObject(GamePage *parent, QString str, float realX, float realY, float realSpeedX, float realSpeedY, float realSpeedRad, int xLower, int xUpper, int yLower, int yUpper, attribute collision, attribute stubborn, attribute grativity, int collisionx, int collisiony, int collisionwidth, int collisionheight)
    : QWidget(parent), img(str), realSpeedX(realSpeedX), realSpeedY(realSpeedY), realSpeedRad(realSpeedRad), cameraSpeedX(parent->cameraSpeedX), cameraSpeedY(parent->cameraSpeedY), realX(realX), realY(realY), cameraX(parent->cameraX), cameraY(parent->cameraY), xLower(xLower), xUpper(xUpper), yLower(yLower), yUpper(yUpper), collision(collision), stubborn(stubborn), grativity(grativity), collisionX(collisionx), collisionY(collisiony), collisionWidth(collisionwidth), collisionHeight(collisionheight)
{
    setFixedSize(QSize(img.width(), img.height()));
    move(realX - cameraX, realY - cameraY);
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

FloatRect GameObject::getCollisionRect()
{
    return FloatRect(realX + collisionX, realY + collisionY, collisionWidth, collisionHeight);
}

void GameObject::setLocation(float x,float y)        { realX = x; realY = y; move(realX - cameraX, realY - cameraY); }
void GameObject::setX(float x)                       { realX = x; move(realX - cameraX, y()); }
void GameObject::setY(float y)                       { realY = y; move(x(), realY - cameraY); }
void GameObject::setSpeed(float x,float y,float rad) { realSpeedX = x; realSpeedY = y; realSpeedRad = rad; }
void GameObject::setXSpeed(float x)                  { realSpeedX = x; }
void GameObject::setYSpeed(float y)                  { realSpeedY = y; }
void GameObject::setRadSpeed(float rad)              { realSpeedRad = rad; }
void GameObject::setReverseSpeed()                   { realSpeedX = -realSpeedX; realSpeedY = -realSpeedY; }
void GameObject::setXReverseSpeed()                  { realSpeedX = -realSpeedX; }
void GameObject::setYReverseSpeed()                  { realSpeedY = -realSpeedY; }
void GameObject::setLeftSpeed()                      { realSpeedX = -std::abs(realSpeedX); }
void GameObject::setRightSpeed()                     { realSpeedX = std::abs(realSpeedX); }
void GameObject::setUpSpeed()                        { realSpeedY = -std::abs(realSpeedY); }
void GameObject::setDownSpeed()                      { realSpeedY = std::abs(realSpeedY); }
//state GameObject::collisionWith(GameObject& other) { return getCollisionRect().intersects(other.getCollisionRect()); }

void GameObject::checkBorder()
{
    if (realX + collisionX < xLower && !propleft && !bounceleft)
    {
        pushleft = false;
        if(realSpeedX == 0.0) realSpeedX = pushSpeed;
        else bounceright = true;
    }
    if (realX + collisionX + collisionWidth > xUpper && !propright && !bounceright)
    {
        pushright = false;
        if(realSpeedX == 0.0) realSpeedX = -pushSpeed;
        else bounceleft = true;
    }
    if (realY + collisionY < yLower && !propup && !bounceup)
    {
        if(realSpeedY == 0.0) realSpeedY = pushSpeed;
        else bouncedown = true;
    }
    if (realY + collisionY + collisionHeight > yUpper && !bouncedown)
    {
        if(realSpeedY == 0.0) realSpeedY = -pushSpeed;
        else bounceup = true; //bounceup: 对脚下物体相对速度为零则跳跃，对脚下物体有正相对速度时则反弹
    }
}

void GameObject::checkState()
{
    if(downObject==nullptr)                          { propup = false; }
    if(leftObject==nullptr)                          { propright = false; }
    if(rightObject==nullptr)                         { propleft = false; }
    if(bouncedown)                                   { bounceup = false; }
    if(bounceup)                                     { propup = false;downObject = nullptr; }
    if(propup)                                       { bouncedown = false; }
    if(bounceleft&&bounceright)                      { bounceleft = bounceright = false; }
    if(pushleft&&pushright)                          { pushleft = pushright = false; }
    if(pushleft||propleft)                           { bounceright = false; }
    if(pushright||propright)                         { bounceleft = false; }
    if(bounceleft||(pushleft&&!propright))           { propleft = false; rightObject = nullptr; }
    if(bounceright||(pushright&&!propleft))          { propright = false; leftObject = nullptr; }
}

void GameObject::useState()
{
    aX = aY = 0;
    if(grativity&&!propup)                           { aY = g; }
    if(bounceup)                                     { if(downObject!=nullptr&&realSpeedY==downObject->realSpeedY)setYSpeed(-1);else setUpSpeed();bounceup = false; }
    if(bouncedown)                                   { setDownSpeed(); bouncedown = false; }
    if(bounceleft)                                   { setLeftSpeed(); bounceleft = false; }
    if(bounceright)                                  { setRightSpeed(); bounceright = false; }
    if(pushleft)                                     { setXSpeed(-pushSpeed); }
    if(pushright)                                    { setXSpeed(pushSpeed); }
    if(propup)                                       { setYSpeed(downObject->realSpeedY); }
    if(propleft&&rightObject->realSpeedX<realSpeedX) { setXSpeed(rightObject->realSpeedX); }
    if(propright&&leftObject->realSpeedX>realSpeedX) { setXSpeed(leftObject->realSpeedX); }
}

void GameObject::updateSpeed() { realSpeedX += aX; realSpeedY += aY; }

void GameObject::updateLocation()
{
    matrix.translate(img.width() / 2.0, img.height() / 2.0);
    matrix.rotate(realSpeedRad);
    matrix.translate(-img.width() / 2.0, -img.height() / 2.0);
    realX += realSpeedX;
    realY += realSpeedY;
    cameraX += cameraSpeedX;
    cameraY += cameraSpeedY;
    move(realX - cameraX, realY - cameraY);
}

void GameObject::selfUpdate()
{
    checkBorder();
    checkState();
    useState();
    updateSpeed();
    updateLocation();
}
