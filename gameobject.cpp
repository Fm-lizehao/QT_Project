#include "gameobject.h"
#include "gamepage.h"

GameObject::GameObject(GamePage *parent, initializer_list<QString> img_str, QPointF p, QPointF v, qreal omega, QRect border, attribute collision, attribute stubborn, attribute grativity, attribute cankill)
    : QWidget(parent), v(v), omega(omega), cameraP(parent->cameraP), cameraV(parent->cameraV), border(border), collision(collision), stubborn(stubborn), grativity(grativity), cankill(cankill)
{
    for (auto i:img_str)
    {
        img.push_back(QPixmap(i));
        if(collisionRectMap.find(i)!=collisionRectMap.end()) collisionRect.push_back(collisionRectMap.find(i)->second);
        else collisionRect.push_back(img.rbegin()->rect());
    }
    resize(img[imgNow].size());
    setLocation(p);
}

void GameObject::checkCollision(GameObject* other)
{
    if(!other->collision) return;
    QRectF rect1 = getCollisionRect();
    QRectF rect2 = other->getCollisionRect();
    if(intersect(rect1, rect2))
    {
        direction tempOrder = 0;
        qreal min = MAX;
        qreal up = rect2.bottom()-rect1.top();
        qreal down = rect1.bottom()-rect2.top();
        qreal left = rect2.right()-rect1.left();
        qreal right = rect1.right()-rect2.left();
        if(up>=0&&up<min) {min = up; tempOrder = UP; }
        if(down>=0&&down<min) {min = down; tempOrder = DOWN; }
        if(left>=0&&left<min) {min = left; tempOrder = LEFT; }
        if(right>=0&&right<min) {min = right; tempOrder = RIGHT; }
        order |= tempOrder;
        switch(tempOrder)
        {
        case UP: upObject = other; break;
        case DOWN: downObject = other; break;
        case LEFT: leftObject = other; break;
        case RIGHT: rightObject = other; break;
        }
    }
}

void GameObject::doCollision()
{
    if((order&UP)>>3&&collision&&!stubborn) bouncedown = true; else {upObject = nullptr; }
    if((order&DOWN)>>2&&collision&&!stubborn) propup = true; else {propup = false; downObject = nullptr; }
    if((order&LEFT)>>1&&collision) propright = true; else {propright = false; leftObject = nullptr; }
    if((order&RIGHT)&&collision) propleft = true; else {propleft = false; rightObject = nullptr; }
    order = NONE;
}

void GameObject::checkBorder()
{
    if (getCollisionRect().left() < border.left() && !propleft && !bounceleft) bounceright = true;
    if (getCollisionRect().right() > border.right() && !propright && !bounceright) bounceleft = true;
    if (getCollisionRect().top() < border.top() && !propup && !bounceup) bouncedown = true;
    if (getCollisionRect().bottom() > border.bottom() && !bouncedown) bounceup = true;
}

void GameObject::checkState()
{
    if(bounceleft&&bounceright)                      { bounceleft = bounceright = false; }
    if(pushleft&&pushright)                          { pushleft = pushright = false; v.setX(0); }
    if(bouncedown)                                   { bounceup = false; }
    if(propup)                                       { bouncedown = false; }
    if(pushleft||propleft)                           { bounceright = false; }
    if(pushright||propright)                         { bounceleft = false; }
}

void GameObject::useState()
{
    a = QPointF(0.0,0.0);
    if(grativity&&!propup&&!bounceup&&!bouncedown)   { a.setY(g); }
    if(bounceup)                                     { if(downObject==nullptr)setUpSpeed(); else v.setY(-bounceSpeed); bounceup = false; }
    if(bouncedown)                                   { setDownSpeed(); bouncedown = false; }
    if(bounceleft)                                   { setLeftSpeed(); bounceleft = false; }
    if(bounceright)                                  { setRightSpeed(); bounceright = false; }
    if(pushleft)                                     { v.setX(-pushSpeed); }
    if(pushright)                                    { v.setX(pushSpeed); }
    if(propup)                                       { p-=QPointF(0,getCollisionRect().bottom()-downObject->getCollisionRect().top()); }
    if(propleft)                                     { p-=QPointF(getCollisionRect().right()-rightObject->getCollisionRect().left(),0); }
    if(propright)                                    { p+=QPointF(leftObject->getCollisionRect().right()-getCollisionRect().left(),0); }
    if(propup&&downObject->v.y()<v.y())              { v.setY(downObject->v.y()); }
    if(propleft&&rightObject->v.x()<v.x())           { v.setX(rightObject->v.x()); }
    if(propright&&leftObject->v.x()>v.x())           { v.setX(leftObject->v.x()); }
}

void GameObject::updateSpeed() {v.setX(v.x()+a.x()); v.setY(v.y()+a.y()); }

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
    this->checkBorder();
    this->checkState();
    this->useState();
    this->updateSpeed();
    this->updateLocation();
}

void HeavyBody::doCollision()
{
    if((order&UP)>>3) weighdown = true; else {weighdown = false; upObject = nullptr; }
    if((order&DOWN)>>2) butted = true; else {downObject = nullptr; }
    if((order&LEFT)>>1) propright = true; else {propright = false; leftObject = nullptr; }
    if(order&RIGHT) propleft = true; else {propleft = false; rightObject = nullptr; }
    order = NONE;
}

void HeavyBody::checkState()
{
    if(bounceleft&&bounceright)                      { bounceleft = bounceright = false; }
    if(bouncedown)                                   { bounceup = false; }
    if(propup)                                       { bouncedown = false; }
}

void HeavyBody::useState()
{
    a = QPointF(0.0,0.0);
    if(grativity&&!propup&&!bounceup&&!bouncedown)   { a.setY(g); }
    if(bounceup)                                     { setUpSpeed(); bounceup = false; }
    if(bouncedown)                                   { setDownSpeed(); bouncedown = false; }
    if(bounceleft)                                   { setLeftSpeed(); bounceleft = false; }
    if(bounceright)                                  { setRightSpeed(); bounceright = false; }
}

void Pushable::doCollision()
{
    if((order&UP)>>3) weighdown = true; else {weighdown = false; upObject = nullptr; }
    if((order&DOWN)>>2) propup = true; else {propup = false; downObject = nullptr; }
    if((order&LEFT)>>1) propright = true; else {propright = false; leftObject = nullptr; }
    if(order&RIGHT) propleft = true; else {propleft = false; rightObject = nullptr; }
    order = NONE;
}

void Pushable::checkState()
{
    if(bounceleft&&bounceright)                      { bounceleft = bounceright = false; }
    if(bouncedown)                                   { bounceup = false; }
    if(propup)                                       { bouncedown = false; }
    if(propleft)                                     { bounceright = false; }
    if(propright)                                    { bounceleft = false; }
}

void Pushable::useState()
{
    a = QPointF(0.0,0.0);
    if(grativity&&!propup&&!bounceup&&!bouncedown)   { a.setY(g); }
    if(bounceup)                                     { if(downObject==nullptr)setUpSpeed(); else v.setY(-bounceSpeed); bounceup = false; }
    if(bouncedown)                                   { setDownSpeed(); bouncedown = false; }
    if(bounceleft)                                   { setLeftSpeed(); bounceleft = false; }
    if(bounceright)                                  { setRightSpeed(); bounceright = false; }
    if(propup)                                       { p-=QPointF(0,getCollisionRect().bottom()-downObject->getCollisionRect().top()); }
    if(propleft)                                     { p-=QPointF(getCollisionRect().right()-rightObject->getCollisionRect().left(),0); }
    if(propright)                                    { p+=QPointF(leftObject->getCollisionRect().right()-getCollisionRect().left(),0); }
    if(propup&&downObject->v.y()<v.y())              { v.setY(downObject->v.y()); }
    if(propleft&&rightObject->v.x()<v.x())           { v.setX(rightObject->v.x()); }
    if(propright&&leftObject->v.x()>v.x())           { v.setX(leftObject->v.x()); }
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) return;
    switch(event->key())
    {
    case Qt::Key_A: case Qt::Key_Left:
        pushright = false;
        pushleft = true;
        break;
    case Qt::Key_D: case Qt::Key_Right:
        pushleft = false;
        pushright = true;
        break;
    case Qt::Key_W: case Qt::Key_Up: case Qt::Key_Space:
        if(propup||flying) bounceup = true;
        break;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) return;
    switch(event->key())
    {
    case Qt::Key_A: case Qt::Key_Left:
        pushleft = false;
        if(pushright) break;
        if(leftObject == nullptr) v.setX(0);
        else v.setX(leftObject->v.x());
        break;
    case Qt::Key_D: case Qt::Key_Right:
        pushright = false;
        if(pushleft) break;
        if(rightObject == nullptr) v.setX(0);
        else v.setX(rightObject->v.x());
        break;
    }
}

void Player::stand()
{
    if(timer.isActive()&&getImgNumNow()==leftOrRight()) return;
    timer.stop();
    setImg(leftOrRight());
    timer.setInterval(250);
    timer.start();
}

void Player::walk()
{
    if(timer.isActive()&&(getImgNumNow()==2+leftOrRight()||getImgNumNow()==4+leftOrRight())) return;
    timer.stop();
    setImg(2+leftOrRight());
    if(propleft||propright) return;
    timer.setInterval(250);
    timer.start();
}

void Player::jump()
{
    if(timer.isActive()&&getImgNumNow()==6+leftOrRight()) return;
    timer.stop();
    setImg(6+leftOrRight());
    timer.setInterval(250);
    timer.start();
}

void Player::fly()
{
    if(timer.isActive()&&getImgNumNow()==8+2*(v.y()<-bounceSpeed/3)+leftOrRight()) return;
    timer.stop();
    setImg(8+2*(v.y()<-bounceSpeed/3)+leftOrRight());
    timer.setInterval(250);
    timer.start();
}

void Player::cry()
{
    if(timer.isActive()&&getImgNumNow()>=12&&getImgNumNow()%2==leftOrRight()) return;
    timer.stop();
    setImg(12+leftOrRight());
    timer.setInterval(800);
    timer.start();
}

void Player::useState()
{
    a = QPointF(0.0,0.0);
    if(grativity&&!propup&&!bounceup&&!bouncedown)   { a.setY(g); }
    if(killed)                                       { v.setX(0); }
    if(!killed&&bounceup)                            { if(!flying) jumping = true; v.setY(-bounceSpeed); bounceup = false; }
    if(bouncedown)                                   { setDownSpeed(); bouncedown = false; }
    if(!killed&&pushleft)                            { v.setX(-pushSpeed); }
    if(!killed&&pushright)                           { v.setX(pushSpeed); }
    if(propup)                                       { p-=QPointF(0,getCollisionRect().bottom()-downObject->getCollisionRect().top()); }
    if(propleft)                                     { p-=QPointF(getCollisionRect().right()-rightObject->getCollisionRect().left(),0); }
    if(propright)                                    { p+=QPointF(leftObject->getCollisionRect().right()-getCollisionRect().left(),0); }
    if(propup&&downObject->v.y()<v.y())              { v.setY(downObject->v.y()); jumping = flying = false; }
    if(propleft&&rightObject->v.x()<v.x())           { v.setX(rightObject->v.x()); }
    if(propright&&leftObject->v.x()>v.x())           { v.setX(leftObject->v.x()); }
}

void Player::updateSpeed()
{
    v.setX(v.x()+a.x());
    v.setY(v.y()+a.y());
    if(getCollisionRect().left()<0&&v.x()<0) v.setX(0);
    if(getCollisionRect().right()>((GamePage*)parent())->pageWidth&&v.x()>0) v.setX(0);
    if(getCollisionRect().top()<0&&v.y()<0) v.setY(0);
    if(getCollisionRect().top()>((GamePage*)parent())->pageHeight) killed = true;
    if(killed) cry();
    else if(flying) fly();
    else if(jumping) jump();
    else if(propup&&(pushleft||pushright)) walk();
    else stand();
}
