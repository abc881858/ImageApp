#ifndef CORNERGRABBER_H
#define CORNERGRABBER_H

#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include <QColor>
#include <QPainter>
#include <QPen>
#include <QPointF>

class CornerGrabber : public QGraphicsItem
{
public:
    explicit CornerGrabber(QGraphicsItem *parent = 0);
    qreal getHeight();
    qreal getWidth();
    bool isActive();

    enum {bottomLeft, topLeft, topRight, bottomRight};

private:
    virtual QRectF boundingRect() const;
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );
    virtual void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );

    QColor _outterborderColor;
    QPen _outterborderPen;

    qreal   _width;
    qreal   _height;

    bool _is_active;
};

#endif // CORNERGRABBER_H
