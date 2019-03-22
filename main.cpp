#include <QApplication>
#include "graphicsview.h"
#include "net.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qNet->initialize();

    GraphicsView view;
    view.setBackgroundBrush(QBrush(QColor(Qt::lightGray)));
    view.showMaximized();

    return a.exec();
}
