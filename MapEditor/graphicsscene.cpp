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
    brushing = false;
    peasantTool = new Texture(":/data/img/Peasant.dat",":/data/img/Colors.png");
    peasantTool->paintAll();
    goldmineTool = new Texture(":/data/img/GoldMine.dat",":/data/img/Colors.png");
    townhallTool = new Texture(":/data/img/TownHall.dat",":/data/img/Colors.png");
    townhallTool->paintAll();
}

void GraphicsScene::addToolItem(QGraphicsSceneMouseEvent *mouseEvent)
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
        Texture *asset = 0;

        if (curTool == "Peasant")
        {
            asset = peasantTool;
        }
        else if (curTool == "GoldMine")
        {
            asset = goldmineTool;
        }
        else if (curTool == "TownHall")
        {
            asset = townhallTool;
        }
        else
        {
            QGraphicsScene::mousePressEvent(mouseEvent);
            return;
        }

        QImage imageDx;
        if (!asset)
            imageDx = *terrain->getImageTile(curTool);
        else
        {
            if (curTool == "GoldMine")
                imageDx = asset->imageList[0];
            else
                imageDx = asset->colorPlayerImg[curPlayer][3];
        }

        QPixmap pixmap = QPixmap::fromImage(imageDx);
        Tile * pixItem = new Tile(type, pixmap);

        int x = item->scenePos().x();
        int y = item->scenePos().y();
        pixItem->setPos(x, y);
        addItem(pixItem);

        if (!asset)
            emit changedLayout(x, y, type);
        else
        {
            if (curTool == "GoldMine")
                emit changedAsset(x, y, curTool, 0);
            else
                emit changedAsset(x, y, curTool, curPlayer);
        }
    }
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
        brushing = true;
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if ((mouseEvent->buttons() & Qt::LeftButton) && brushing)
        addToolItem(mouseEvent);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton) {
        addToolItem(mouseEvent);
        brushing = false;
    }
}
