#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include "graphicsscene.h"
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QDir>
#include <QComboBox>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget *parent = nullptr);
    GraphicsScene *scene;

    QString openJsonName;

    QDialog *dialog;
    QLabel *nameLabel;
    QComboBox *nameEdit;
    QLabel *occludedLabel;
    QLineEdit *occludedEdit;
    QLabel *truncatedLabel;
    QLineEdit *truncatedEdit;
    QLabel *ignoreLabel;
    QLineEdit *ignoreEdit;
    QLabel *difficultLabel;
    QLineEdit *difficultEdit;

protected:
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

};

#endif // GRAPHICSVIEW_H
