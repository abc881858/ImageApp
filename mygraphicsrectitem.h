#ifndef MYGRAPHICSRECTITEM_H
#define MYGRAPHICSRECTITEM_H

#include <QObject>
#include <QGraphicsRectItem>
#include "cornergrabber.h"

class QGraphicsSceneMouseEvent;
class QPointF;
class QColor;

class MyGraphicsRectItem :  public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit MyGraphicsRectItem(const QRectF & rect, QGraphicsItem * parent = 0);
    int checkCornerGrabbers();
    void setCornerPositions();
    bool grabbersAreCreated();
    void createGrabbers();
    void deleteGrabbers();

    void setLinePosition();

    QGraphicsLineItem *line;
    QGraphicsPixmapItem *mask;

    bool side;
    bool visi;
    void changePixmap();
    void changeVisiable();
signals:
    void hover_enter();
    void hover_leave();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

//    void keyPressEvent(QKeyEvent *event);
private:
    CornerGrabber* _bottomLeft_corner;
    CornerGrabber* _topLeft_corner;
    CornerGrabber* _topRight_corner;
    CornerGrabber* _bottomRight_corner;

    bool _grabbers_created;
};

#endif
