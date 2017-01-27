#include "graphicsscene.h"
#include <QDebug>
#include "ui_mainwindow.h"


GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent)
{
}


void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsView *view = this->views()[0];
    view->centerOn(mouseEvent->scenePos());
    QGraphicsScene::mousePressEvent(mouseEvent);
}

