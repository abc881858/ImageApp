#include "graphicsview.h"
#include <QKeyEvent>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QFormLayout>

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent), step1(false), step2(false), step3(false)
{
    scene = new GraphicsScene;
    scene->setSceneRect(0,0,2000,1200);
    setScene(scene);

    setMouseTracking(true);

    dialog = new QDialog(this);

    nameLabel = new QLabel("name");
    nameEdit = new QComboBox;
    nameEdit->addItem("");
    nameEdit->addItem("Pedestrian");
    nameEdit->addItem("Cyclist");
    nameEdit->addItem("Car");
    nameEdit->addItem("Truck");
    occludedLabel = new QLabel("occluded");
    occludedEdit = new QLineEdit;
    truncatedLabel = new QLabel("truncated");
    truncatedEdit = new QLineEdit;
    ignoreLabel = new QLabel("ignore");
    ignoreEdit = new QLineEdit;
    difficultLabel = new QLabel("difficult");
    difficultEdit = new QLineEdit;

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(nameLabel, nameEdit);
    formLayout->addRow(occludedLabel, occludedEdit);
    formLayout->addRow(truncatedLabel, truncatedEdit);
    formLayout->addRow(ignoreLabel, ignoreEdit);
    formLayout->addRow(difficultLabel, difficultEdit);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(formLayout);
    QPushButton *ok = new QPushButton("OK");
    connect(ok,&QPushButton::clicked,[=](){
        scene->current->setData(Qt::UserRole+1, nameEdit->currentText());
        scene->current->setData(Qt::UserRole+2, occludedEdit->text());
        scene->current->setData(Qt::UserRole+3, truncatedEdit->text());
        scene->current->setData(Qt::UserRole+4, ignoreEdit->text());
        scene->current->setData(Qt::UserRole+5, difficultEdit->text());
        dialog->hide();
        nameEdit->setCurrentText("");
        occludedEdit->clear();
        truncatedEdit->clear();
        ignoreEdit->clear();
        difficultEdit->clear();
    });
    QPushButton *cancle = new QPushButton("Cancel");
    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(ok);
    layout2->addWidget(cancle);
    layout->addLayout(layout2);
    dialog->setLayout(layout);
    dialog->setFixedSize(200,200);
    dialog->hide();
}

void GraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_F)
    {
        if(!scene->pixmap.isNull())
        {
            return;
        }
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/wu", tr("Images (*.png *.xpm *.jpg)"));
        scene->addImage(fileName);
        centerOn(0,0);
    }
    else if(event->key()==Qt::Key_D)
    {
        //delete
        for(MyGraphicsRectItem* item:scene->groupItems)
        {
            if(item==scene->current)
            {
                scene->groupItems.removeOne(item);
                scene->current->deleteLater();
                return;
            }
        }
    }
    else if(event->key()==Qt::Key_W)
    {
        //query and modify
        nameEdit->setCurrentText(scene->current->data(Qt::UserRole+1).toString());
        occludedEdit->setText(QString::number(scene->current->data(Qt::UserRole+2).toInt()));
        truncatedEdit->setText(QString::number(scene->current->data(Qt::UserRole+3).toInt()));
        ignoreEdit->setText(QString::number(scene->current->data(Qt::UserRole+4).toInt()));
        difficultEdit->setText(QString::number(scene->current->data(Qt::UserRole+5).toInt()));
        dialog->move(mapFromScene(scene->current->rect().topLeft()-QPointF(20,20)));
        dialog->show();
    }
    else if(event->key()==Qt::Key_A)
    {
        //add
        if(scene->pixmap.isNull())
        {
            return;
        }
        if(scene->pixmapItem==nullptr)
        {
            return;
        }
        step1 = true;
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
    if(scene->pixmap.isNull())
    {
        return;
    }
    if(step1)
    {
        setCursor(Qt::CrossCursor);
        scene->showTwoLine(mapToScene(event->pos()));
    }
    if(step2)
    {
        qreal x = scene->current->rect().x();
        qreal y = scene->current->rect().y();
        qreal nx = mapToScene(event->pos()).x();
        qreal ny = mapToScene(event->pos()).y();
        qreal w = nx - x;
        qreal h = ny - y;
        scene->current->setRect(x, y, w, h);
        step3 = true;
    }
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(scene->pixmap.isNull())
    {
        return;
    }
    if(step1)
    {
        scene->hideTwoLine(mapToScene(event->pos()));
        step1 = false;
        step2 = true;
    }
    if(step3)
    {
        step2 = false;
        step3 = false;
        setCursor(Qt::ArrowCursor);

        dialog->move(mapToScene(event->pos()).toPoint());
        dialog->show();
        scene->current->createGrabbers();
    }
    QGraphicsView::mousePressEvent(event);
}
