#include "gameobject.h"
#include "gamepage.h"

GameObject::GameObject(GamePage *parent, std::initializer_list<QString> str, QPointF p, QPointF v, qreal omega, QRect border, attribute collision, attribute stubborn, attribute grativity)
    : QWidget(parent), p(p), v(v), omega(omega), cameraP(parent->cameraP), cameraV(parent->cameraV), border(border), collision(collision), stubborn(stubborn), grativity(grativity)
{
    for (auto i:str)
    {
        img.push_back(QPixmap(i));
        if(collisionRectMap.find(i)!=collisionRectMap.end()) collisionRect.push_back(collisionRectMap[i]);
        else collisionRect.push_back(img.rbegin()->rect());
    }
    resize(img[imgNow].size());
    move((p-cameraP).toPoint());
}

void GameObject::checkBorder()
{
    if (getCollisionRect().left() < border.left() && !propleft && !bounceleft)
    {
        pushleft = false;
        if(v.x() == 0.0) v.setX(pushSpeed);
        else bounceright = true;
    }
    if (getCollisionRect().right() > border.right() && !propright && !bounceright)
    {
        pushright = false;
        if(v.x() == 0.0) v.setX(-pushSpeed);
        else bounceleft = true;
    }
    if (getCollisionRect().top() < border.top() && !propup && !bounceup)
    {
        if(v.y() == 0.0) v.setY(pushSpeed);
        else bouncedown = true;
    }
    if (getCollisionRect().bottom() > border.bottom() && !bouncedown)
    {
        if(v.y() == 0.0) v.setY(-pushSpeed);
        else bounceup = true;
    }
}

void GameObject::checkState()
{
    if(downObject==nullptr)                          { propup = false; }
    if(leftObject==nullptr)                          { propright = false; }
    if(rightObject==nullptr)                         { propleft = false; }
    if(bouncedown)                                   { bounceup = false; }
    if(bounceup)                                     { propup = false; }
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
    a = QPointF(0.0,0.0);
    if(grativity&&!propup)                           { a.setY(g); }
    if(bounceup)                                     { if(downObject!=nullptr&&v.y()==downObject->v.y())v.setY(-1);else setUpSpeed();downObject=nullptr; }
    if(bouncedown)                                   { setDownSpeed(); }
    if(bounceleft)                                   { setLeftSpeed(); }
    if(bounceright)                                  { setRightSpeed(); }
    if(pushleft)                                     { v.setX(-pushSpeed); }
    if(pushright)                                    { v.setX(pushSpeed); }
    if(propup)                                       { v.setY(downObject->v.y()); }
    if(propleft&&rightObject->v.x()<v.x())           { v.setX(rightObject->v.x()); }
    if(propright&&leftObject->v.x()>v.x())           { v.setX(leftObject->v.x()); }
}

void GameObject::updateSpeed()
{
    if(!bounceleft&&!bounceright)v.setX(v.x()+a.x());
    if(!bounceup&&!bouncedown)v.setY(v.y()+a.y());
    bounceup = bouncedown = bounceleft = bounceright = false;
}

void GameObject::updateLocation()
{
    matrix.translate(width() / 2.0, height() / 2.0);
    matrix.rotate(omega);
    matrix.translate(-width() / 2.0, -height() / 2.0);
    p+=v;
    move((p-cameraP).toPoint());
}

void GameObject::selfUpdate()
{
    checkBorder();
    checkState();
    useState();
    updateSpeed();
    updateLocation();
}
