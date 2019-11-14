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
    bool step1;
    bool step2;
    bool step3;

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
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QStringList m_imgList;
    int m_index{0};
    QDir dir;
};

#endif // GRAPHICSVIEW_H
