#include "mainwindow.h"

GameObject::GameObject(GamePage *parent, initializer_list<QString> img_str, QPointF p, QPointF v, qreal omega, QRect border, attribute collision, attribute stubborn, attribute grativity, attribute cankill)
    : QWidget(parent), source(img_str), v(v), omega(omega), cameraP(parent->cameraP), cameraV(parent->cameraV), border(border), collision(collision), stubborn(stubborn), grativity(grativity), cankill(cankill)
{
    for (auto i:img_str)
    {   img.push_back(QPixmap(i));
        if(collisionRectMap.find(i)!=collisionRectMap.end()) collisionRect.push_back(collisionRectMap.find(i)->second);
        else collisionRect.push_back(img.rbegin()->rect()); }
    resize(img[imgNow].size());
    setLocation(p);
}

void GameObject::checkCollision(GameObject* other)
{
    QRectF rect1 = getCollisionRect();
    QRectF rect2 = other->getCollisionRect();
    if(!other->collision||!intersect(rect1, rect2)) return;
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
    {case UP: upObject = other; break;
     case DOWN: downObject = other; break;
     case LEFT: leftObject = other; break;
     case RIGHT: rightObject = other; break; }
}

void GameObject::doCollision()
{
    if((order&UP)>>3&&collision) bouncedown = true; else {upObject = nullptr; }
    if((order&DOWN)>>2&&collision) propup = true; else {propup = false; downObject = nullptr; }
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
    if(propup&&getCollisionRect().bottom()>downObject->getCollisionRect().top())
                                                     { p-=QPointF(0,getCollisionRect().bottom()-downObject->getCollisionRect().top()); }
    if(propleft&&getCollisionRect().right()>rightObject->getCollisionRect().left())
                                                     { p-=QPointF(getCollisionRect().right()-rightObject->getCollisionRect().left(),0); }
    if(propright&&leftObject->getCollisionRect().right()>getCollisionRect().left())
                                                     { p+=QPointF(leftObject->getCollisionRect().right()-getCollisionRect().left(),0); }
    if(propup&&!stubborn&&downObject->v.y()<v.y())   { v.setY(downObject->v.y()); }
    if(propleft&&!stubborn&&rightObject->v.x()<v.x()){ v.setX(rightObject->v.x()); }
    if(propright&&!stubborn&&leftObject->v.x()>v.x()){ v.setX(leftObject->v.x()); }
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
    this->checkBorder(); this->checkState(); this->useState(); this->updateSpeed(); this->updateLocation();
}

void VirtualObject::useState()
{
    GameObject::useState();
    if(breakin&&getImgNumNow()!=getImgNumTotal()-1)  { setImg(getImgNumTotal()-1); v = a = {0,0}; }
}

void HeavyBody::doCollision()
{
    if((order&UP)>>3) weighdown = true; else {weighdown = false; upObject = nullptr; }
    if((order&DOWN)>>2) butted = true; else {downObject = nullptr; }
    if((order&LEFT)>>1) propright = true; else {propright = false; leftObject = nullptr; }
    if(order&RIGHT) propleft = true; else {propleft = false; rightObject = nullptr; }
    order = NONE;
}

void HeavyBody::useState()
{
    GameObject::useState();
    if(!butted&&weighdown&&getImgNumTotal()>=3)      { setImg(getImgNumTotal()-2); }
    else if(!butted&&getImgNumNow()!=0)              { setImg(0); }
    if(butted&&getImgNumNow()!=getImgNumTotal()-1)   { setImg(getImgNumTotal()-1); }
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
    GameObject::checkState();
    if(weighdown)                                    { bounceup = false; }
}

void Pushable::useState()
{
    v.setX(0.0);
    if(weighdown)                                    { setImg(getImgNumTotal()-1); setDownSpeed(); }
    else if(getImgNumNow()!=0)                       { setImg(0); }
    GameObject::useState();
}

void Role::checkCollision(GameObject* other)
{
    if(other->cankill&&intersect(getCollisionRect(),other->getCollisionRect())) killed = true;
    else GameObject::checkCollision(other);
}

void Role::updateSpeed()
{
    GameObject::updateSpeed();
    if(getCollisionRect().left()<0&&v.x()<0) v.setX(0);
    if(getCollisionRect().right()>((GamePage*)parent())->pageWidth&&v.x()>0) v.setX(0);
    if(getCollisionRect().top()<0&&v.y()<0) v.setY(0);
    if(getCollisionRect().top()>((GamePage*)parent())->pageHeight) killed = true;
}

void NPC::checkCollision(GameObject* other)
{
    if(other==((GamePage*)parent())->player&&cankill&&intersect(getCollisionRect(),other->getCollisionRect())) victory = true;
    else Role::checkCollision(other);
}

void NPC::useState()
{
    setImg(leftOrRight());
    if(victory)                                      { v.setX(0); if(getImgNumTotal()>=4) setImg(getImgNumTotal()-4+leftOrRight()); if(downObject!=nullptr) v.setY(-bounceSpeed/1.7); }
    if(killed)                                       { v.setX(0); if(getImgNumTotal()>=2) setImg(getImgNumTotal()-2+leftOrRight()); cankill = false; stubborn = true; victory = false; }
    GameObject::useState();
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) return;
    switch(event->key())
    {case Qt::Key_A: case Qt::Key_Left: pushright = false; if(!killed) pushleft = true; break;
     case Qt::Key_D: case Qt::Key_Right: pushleft = false; if(!killed) pushright = true; break;
     case Qt::Key_W: case Qt::Key_Up: case Qt::Key_Space: if(!killed&&(propup||flying)) bounceup = true; break; }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) return;
    switch(event->key())
    {case Qt::Key_A: case Qt::Key_Left: pushleft = false; if(!pushright) v.setX(leftObject==nullptr?0:leftObject->v.x()); break;
     case Qt::Key_D: case Qt::Key_Right: pushright = false; if(!pushleft) v.setX(rightObject==nullptr?0:rightObject->v.x()); break; }
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
    if(timer.isActive()&&(getImgNumNow()==2+leftOrRight()||getImgNumNow()==4+leftOrRight())&&!propleft&&!propright) return;
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

void Player::checkState()
{
    GameObject::checkState();
    if(propleft&&!rightObject->stubborn&&pushright)  { propleft = false; rightObject = nullptr; }
    if(propright&&!leftObject->stubborn&&pushleft)   { propright = false; leftObject = nullptr; }
}

void Player::useState()
{
    if(killed)                                       { v.setX(0); stubborn = true; pushleft = pushright = false; }
    if(bounceup)                                     { if(!flying) jumping = true; v.setY(-bounceSpeed); bounceup = false; }
    if(propup&&downObject->v.y()<v.y())              { v.setY(downObject->v.y()); jumping = flying = false; }
    GameObject::useState();
}

void Player::updateSpeed()
{
    Role::updateSpeed();
    if(killed) cry();
    else if(flying) fly();
    else if(jumping) jump();
    else if(propup&&(pushleft||pushright)) walk();
    else stand();
}

void Player::changeImg()
{
    setImg(flip[getImgNumNow()]);
    if(getImgNumNow()==14||getImgNumNow()==15) ((PlayPage*)parent())->playerKilled();
}
