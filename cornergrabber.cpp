#include "cornergrabber.h"

CornerGrabber::CornerGrabber(QGraphicsItem *parent) :
    QGraphicsItem(parent),
    _outterborderColor(Qt::green),
    _outterborderPen(),
    _width(10),
    _height(10),
    _is_active(false)
{
    setParentItem(parent);

    _outterborderPen.setWidth(2);
    _outterborderPen.setColor(_outterborderColor);

    setAcceptHoverEvents(true);
}

qreal CornerGrabber::getHeight()
{
    return _height;
}

qreal CornerGrabber::getWidth()
{
    return _width;
}

bool CornerGrabber::isActive()
{
    return _is_active;
}

void CornerGrabber::hoverLeaveEvent ( QGraphicsSceneHoverEvent * )
{
    _outterborderColor = Qt::green;
    _is_active = false;
    update(0,0,_width,_height);
}

void CornerGrabber::hoverEnterEvent ( QGraphicsSceneHoverEvent * )
{
    _outterborderColor = Qt::red;
    _is_active = true;
    update(0,0,_width,_height);
}

QRectF CornerGrabber::boundingRect() const
{
    return QRectF(0,0,_width,_height);
}

void CornerGrabber::paint (QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    _outterborderPen.setCapStyle(Qt::SquareCap);
    _outterborderPen.setStyle(Qt::SolidLine);
    painter->setPen(_outterborderPen);

    QPointF topLeft (0, 0);
    QPointF bottomRight ( _width, _height);

    QRectF rect (topLeft, bottomRight);
    QBrush brush (Qt::SolidPattern);
    brush.setColor (_outterborderColor);
    painter->fillRect(rect,brush);

}
