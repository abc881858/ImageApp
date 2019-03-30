#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include "graphicsscene.h"
#include <QDialog>
#include <QLineEdit>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(GraphicsScene *scene, QWidget *parent = Q_NULLPTR);

    void zoom(qreal scaleFactor);
    void original();
    bool step1;
    bool step2;
    bool step3;

    QDialog *dialog;
    QLineEdit *edit;

protected:
    void keyReleaseEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *e);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    qreal m_zoomDelta;
    GraphicsScene *_scene;

};

#endif // GRAPHICSVIEW_H
