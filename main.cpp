#include <QApplication>
#include "graphicsview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphicsView view;
    view.setBackgroundBrush(QBrush(QColor(Qt::lightGray)));
    view.showMaximized();

    return a.exec();
}
