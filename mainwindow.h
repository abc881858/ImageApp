#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphicsview.h"
#include "graphicsscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openButton_clicked();

    void on_dirButton_clicked();

    void on_previousButton_clicked();

    void on_nextButton_clicked();

    void on_saveButton_clicked();

    void on_createButton_clicked();

    void on_copyButton_clicked();

    void on_deleteButton_clicked();

    void on_zoominButton_clicked();

    void on_restoreButton_clicked();

    void on_zoomoutButton_clicked();

    void on_fitwindowButton_clicked();

    void on_fitwidthButton_clicked();

private:
    Ui::MainWindow *ui;
    GraphicsScene *scene;
    GraphicsView *view;
};

#endif // MAINWINDOW_H
