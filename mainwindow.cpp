#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QtOpenGL>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new GraphicsScene;
    scene->setSceneRect(0,0,4000,4000);

    view = new GraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setCacheMode(QGraphicsView::CacheNone);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    view->setBackgroundBrush(QBrush(QColor(Qt::lightGray)));
//    view->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));

    auto vLayout = new QVBoxLayout;
    vLayout->addWidget(view);
    vLayout->setMargin(0);
    ui->drawWidget->setLayout(vLayout);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_clicked()
{
    if(!scene->pixmap.isNull())
    {
        return;
    }
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/wu", tr("Images (*.png *.xpm *.jpg)"));
    scene->addImage(fileName);
    view->centerOn(0,0);
}

void MainWindow::on_dirButton_clicked()
{

}

void MainWindow::on_previousButton_clicked()
{

}

void MainWindow::on_nextButton_clicked()
{

}

void MainWindow::on_saveButton_clicked()
{

}

void MainWindow::on_createButton_clicked()
{
    if(scene->pixmapItem != nullptr)
    {
        view->step1 = true;
    }
    if(scene->current != nullptr)
    {
        if(scene->current->grabbersAreCreated())
        {
            if(scene->current->checkCornerGrabbers() != -1)
            {
                scene->isPressed = true;
            }
        }
    }
}

void MainWindow::on_copyButton_clicked()
{

}

void MainWindow::on_deleteButton_clicked()
{

}

void MainWindow::on_zoominButton_clicked()
{
    view->zoom(1.1);
    view->centerOn(scene->pixmapItem);
}

void MainWindow::on_restoreButton_clicked()
{
    view->original();
    view->centerOn(scene->pixmapItem);
}

void MainWindow::on_zoomoutButton_clicked()
{
    view->zoom(0.9);
    view->centerOn(scene->pixmapItem);
}

void MainWindow::on_fitwindowButton_clicked()
{

}

void MainWindow::on_fitwidthButton_clicked()
{

}
