#include "graphicsscene.h"
#include <QDebug>
#include "ui_mainwindow.h"
#include "tile.h"
#include "texture.h"
#include "mainwindow.h"


GraphicsScene::GraphicsScene(QObject *parent, MapView2 *curMap) : QGraphicsScene(parent)
{
    GraphicsScene::parent = parent;
    GraphicsScene::mapInfo = curMap;
}


void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QWidget *q =  mouseEvent->widget()->parentWidget();
    QString name = q->accessibleName();

    if (name.compare("minimap") == 0)
    {
        QGraphicsView *view = this->views()[0];
        view->centerOn(mouseEvent->scenePos());
    }
    else
    {
        Tile *item = (Tile *)this->itemAt(mouseEvent->scenePos(), QTransform());

        Terrain *terrain = mapInfo->getTerrain();
        Terrain::Type type;

        if (curTool == "grass")
            type = Terrain::Grass;
        else if (curTool == "dirt")
            type = Terrain::Dirt;
        else if (curTool == "water")
            type = Terrain::Water;
        else if (curTool == "rock")
            type = Terrain::Rock;
        else if (curTool == "tree")
            type = Terrain::Tree;
        else if (curTool == "wall")
            type = Terrain::Wall;
        else
        {
            QGraphicsScene::mousePressEvent(mouseEvent);
            return;
        }

        QImage imageDx = *terrain->getImageTile(type);
        QPixmap pixmap = QPixmap::fromImage(imageDx);
        Tile * pixItem = new Tile(type, pixmap);

        int x = item->scenePos().x();
        int y = item->scenePos().y();
        pixItem->setPos(x, y);
        addItem(pixItem);

        emit changedLayout(x, y, type);
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    //((QMainWindow *)parent)->statusBar()->showMessage(QString::number(event->scenePos().x()) + ", " + QString::number(event->scenePos().y()), 500);
}

