#include "mygraphicsrectitem.h"

MyGraphicsRectItem::MyGraphicsRectItem(const QRectF & rect, QGraphicsItem * parent)
    : QGraphicsRectItem(rect, parent)
{
    setAcceptHoverEvents(true);
    setPen(QPen(QBrush(QColor(Qt::green)),3));
    _grabbers_created = false;
}

void MyGraphicsRectItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit hover_enter();
    return QGraphicsRectItem::hoverEnterEvent(event);
}

void MyGraphicsRectItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit hover_leave();
    return QGraphicsRectItem::hoverLeaveEvent(event);
}

bool MyGraphicsRectItem::grabbersAreCreated()
{
    return _grabbers_created;
}

void MyGraphicsRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    return QGraphicsItem::mousePressEvent(event);
}

void MyGraphicsRectItem::setCornerPositions()
{
    QRectF rect = this->rect();

    _bottomLeft_corner->setPos(rect.bottomLeft().x()-6, rect.bottomLeft().y() - _bottomLeft_corner->getHeight()+6);
    _topLeft_corner->setPos(rect.topLeft().x()-6, rect.topLeft().y()-6);
    _topRight_corner->setPos(rect.topRight().x()+6 - _topRight_corner->getWidth(), rect.topRight().y()-6);
    _bottomRight_corner->setPos(rect.bottomRight().x()+6 - _bottomRight_corner->getWidth(), rect.bottomRight().y()+6 - _bottomRight_corner->getHeight());
}

void MyGraphicsRectItem::createGrabbers()
{
    if(!grabbersAreCreated())
    {
        _bottomLeft_corner = new CornerGrabber(this);
        _topLeft_corner = new CornerGrabber(this);
        _topRight_corner = new CornerGrabber(this);
        _bottomRight_corner = new CornerGrabber(this);
        _grabbers_created = true;
        setCornerPositions();
    }
}

int MyGraphicsRectItem::checkCornerGrabbers()
{
    if(_bottomLeft_corner->isActive())
        return CornerGrabber::bottomLeft;
    else if(_topLeft_corner->isActive())
        return CornerGrabber::topLeft;
    else if (_topRight_corner->isActive())
        return CornerGrabber::topRight;
    else if( _bottomRight_corner->isActive())
        return CornerGrabber::bottomRight;
    else
        return -1;
}
