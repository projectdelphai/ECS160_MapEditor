#include "graphicsscene.h"
#include <QDebug>
#include "ui_mainwindow.h"
#include "tile.h"
#include "texture.h"
#include "mainwindow.h"


GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent)
{
    GraphicsScene::parent = parent;
}


void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Tile *item = (Tile *)this->itemAt(mouseEvent->scenePos(), QTransform());

    Texture *texture = new Texture(":/data/img/Terrain.png");
    Texture::Type type;

    if (curTool == "grass")
        type = Texture::Grass;
    else if (curTool == "water")
        type = Texture::Water;
    else if (curTool == "dirt")
        type = Texture::Dirt;
    else
    {
        QGraphicsScene::mousePressEvent(mouseEvent);
        return;
    }

    QImage imageDx = texture->getImageTile(type);
    QPixmap pixmap = QPixmap::fromImage(imageDx);
    Tile * pixItem = new Tile(type, pixmap);

    int x = item->scenePos().x();
    int y = item->scenePos().y();
    pixItem->setPos(x, y);
    addItem(pixItem);

    emit changedLayout(x, y, type);

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    //((QMainWindow *)parent)->statusBar()->showMessage(QString::number(event->scenePos().x()) + ", " + QString::number(event->scenePos().y()), 500);
}

