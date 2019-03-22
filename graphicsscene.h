#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "mygraphicsrectitem.h"

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(QObject *parent = nullptr);
    void addImage(QString fileName);

    QPixmap pixmap;
    QGraphicsPixmapItem *pixmapItem;
    QGraphicsLineItem *line1;
    QGraphicsLineItem *line2;

    void showTwoLine(QPointF p);
    void hideTwoLine(QPointF p);

    MyGraphicsRectItem *current;
    bool isPressed;

signals:
    void resizePixmap();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
};

#endif // GRAPHICSSCENE_H
