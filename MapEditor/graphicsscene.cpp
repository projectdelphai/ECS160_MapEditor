#include "graphicsscene.h"
#include <QDebug>
#include "ui_mainwindow.h"


GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent)
{
    GraphicsScene::parent = parent;
}


void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsView *view = this->views()[0];
    view->centerOn(mouseEvent->scenePos());
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    ((QMainWindow *)parent)->statusBar()->showMessage(QString::number(event->scenePos().x()) + ", " + QString::number(event->scenePos().y()), 500);
}

