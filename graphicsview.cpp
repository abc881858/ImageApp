#include "graphicsview.h"
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>

GraphicsView::GraphicsView(GraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent), step1(false), step2(false), step3(false), _scene(scene)
{
    m_zoomDelta = 0.1;

    setMouseTracking(true);

    dialog = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout;
    edit = new QLineEdit;
    layout->addWidget(edit);
    QPushButton *ok = new QPushButton("OK");
    connect(ok,&QPushButton::clicked,[=](){dialog->hide();edit->clear();});
    QPushButton *cancle = new QPushButton("Cancel");
    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(ok);
    layout2->addWidget(cancle);
    layout->addLayout(layout2);
    layout->addWidget(new QListWidget);
    dialog->setLayout(layout);
    dialog->setFixedSize(200,220);
    dialog->hide();
}

void GraphicsView::zoom(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.25 || factor > 3)
        return;
    scale(scaleFactor, scaleFactor);
}

void GraphicsView::original()
{
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    QMatrix q;
    q.setMatrix(1,matrix().m12(),matrix().m21(),1,matrix().dx(),matrix().dy());
    setMatrix(q,false);
}

void GraphicsView::wheelEvent(QWheelEvent *e)
{
    if(e->modifiers()!=Qt::ControlModifier)
        return;
    QPoint scrollAmount = e->angleDelta();
    scrollAmount.y() > 0 ? zoom(1 + m_zoomDelta) : zoom(1 - m_zoomDelta);
}

void GraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_V)
    {
        _scene->current->changeVisiable();
    }
    if(event->key() == Qt::Key_X)
    {
        _scene->current->changePixmap();
    }
    if(event->key() == Qt::Key_Z)
    {
        _scene->current->line->moveBy(-2,0);
    }
    if(event->key() == Qt::Key_C)
    {
        _scene->current->line->moveBy(2,0);
    }
    else if(event->key()==Qt::Key_F11)
    {
        if(isMaximized())
        {
            showFullScreen();
        }
        else if(isFullScreen())
        {
            showMaximized();
        }
    }
    QGraphicsView::keyReleaseEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(step1)
    {
        setCursor(Qt::CrossCursor);
        _scene->showTwoLine(mapToScene(event->pos()));
    }
    if(step2)
    {
        qreal x = _scene->current->rect().x();
        qreal y = _scene->current->rect().y();
        qreal nx = mapToScene(event->pos()).x();
        qreal ny = mapToScene(event->pos()).y();
        qreal w = nx - x;
        qreal h = ny - y;
        _scene->current->setRect(x, y, w, h);
        step3 = true;
    }
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(step1)
    {
        _scene->hideTwoLine(mapToScene(event->pos()));
        step1 = false;
        step2 = true;
    }
    if(step3)
    {
        step2 = false;
        step3 = false;
        setCursor(Qt::ArrowCursor);

        dialog->move(mapToScene(event->pos()).x(),mapToScene(event->pos()).y());
        dialog->show();
        _scene->current->createGrabbers();
    }
    QGraphicsView::mousePressEvent(event);
}
