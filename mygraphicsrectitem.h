#ifndef MYGRAPHICSRECTITEM_H
#define MYGRAPHICSRECTITEM_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include <QVariant>
#include <QDebug>
#include <QKeyEvent>
#include "cornergrabber.h"

class MyGraphicsRectItem :  public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit MyGraphicsRectItem(const QRectF & rect, QGraphicsItem * parent = nullptr);
    int checkCornerGrabbers();
    void setCornerPositions();
    bool grabbersAreCreated();
    void createGrabbers();

signals:
    void hover_enter();
    void hover_leave();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    CornerGrabber* _bottomLeft_corner;
    CornerGrabber* _topLeft_corner;
    CornerGrabber* _topRight_corner;
    CornerGrabber* _bottomRight_corner;

    bool _grabbers_created;
};

#endif
