#include "mygraphicsrectitem.h"

#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include <QVariant>
#include <QDebug>
#include <QKeyEvent>

MyGraphicsRectItem::MyGraphicsRectItem(const QRectF & rect, QGraphicsItem * parent)
    : QGraphicsRectItem(rect, parent)
{
//    setFlag(QGraphicsItem::ItemIsSelectable);
//    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
//    setFlag(QGraphicsItem::ItemIsFocusable);

    setPen(QPen(QBrush(QColor(Qt::green)),3));

    _grabbers_created = false;
}

void MyGraphicsRectItem::deleteGrabbers()
{
    _bottomLeft_corner->setParentItem(NULL);
    _topLeft_corner->setParentItem(NULL);
    _topRight_corner->setParentItem(NULL);
    _bottomRight_corner->setParentItem(NULL);

    delete _bottomLeft_corner;
    delete _topLeft_corner;
    delete _topRight_corner;
    delete _bottomRight_corner;
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

//void MyGraphicsRectItem::keyPressEvent(QKeyEvent *event)
//{

//    return QGraphicsItem::keyPressEvent(event);
//}

void MyGraphicsRectItem::setCornerPositions()
{
    QRectF rect = this->rect();

    _bottomLeft_corner->setPos(rect.bottomLeft().x()-6, rect.bottomLeft().y() - _bottomLeft_corner->getHeight()+6);
    _topLeft_corner->setPos(rect.topLeft().x()-6, rect.topLeft().y()-6);
    _topRight_corner->setPos(rect.topRight().x()+6 - _topRight_corner->getWidth(), rect.topRight().y()-6);
    _bottomRight_corner->setPos(rect.bottomRight().x()+6 - _bottomRight_corner->getWidth(), rect.bottomRight().y()+6 - _bottomRight_corner->getHeight());
}

void MyGraphicsRectItem::setLinePosition()
{
    line->setLine(rect().x()+rect().width()/2,rect().y(),rect().bottomLeft().x()+rect().width()/2,rect().bottomLeft().y());
    mask->setPos(line->line().p1().x()-10,line->line().p1().y()+rect().height()/2-10);
}

void MyGraphicsRectItem::createGrabbers()
{
    if(!grabbersAreCreated())
    {
        _bottomLeft_corner = new CornerGrabber(this);
        _topLeft_corner = new CornerGrabber(this);
        _topRight_corner = new CornerGrabber(this);
        _bottomRight_corner = new CornerGrabber(this);

        line = new QGraphicsLineItem(this);
        line->setLine(rect().x()+rect().width()/2,rect().y(),rect().bottomLeft().x()+rect().width()/2,rect().bottomLeft().y());
        line->setPen(QPen(QBrush(QColor(Qt::green)),3));

        mask = new QGraphicsPixmapItem(line);
        mask->setPos(line->line().p1().x()-10,line->line().p1().y()+rect().height()/2-10);
        mask->setPixmap(QPixmap(":/left"));
        side = true;

        line->hide();
        visi = false;

        _grabbers_created = true;
        setCornerPositions();
    }
}

void MyGraphicsRectItem::changePixmap()
{
    if(side)
    {
        mask->setPixmap(QPixmap(":/right"));
        side = false;
    }
    else
    {
        mask->setPixmap(QPixmap(":/left"));
        side = true;
    }
}

void MyGraphicsRectItem::changeVisiable()
{
    if(visi)
    {
        line->hide();
        visi = false;
    }
    else
    {
        line->show();
        visi = true;
    }
}

int MyGraphicsRectItem::checkCornerGrabbers()
{
    // we return the first active found. Hopefully we never have two at the same time.
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
