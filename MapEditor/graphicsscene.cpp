#include "graphicsscene.h"
#include <QDebug>
#include "ui_mainwindow.h"
#include "tile.h"
#include "texture.h"
#include "mainwindow.h"


GraphicsScene::GraphicsScene(QObject *parent, MapView2 *curMap, QMap<QString, Texture *> *loadedAssets) : QGraphicsScene(parent)
{
    GraphicsScene::parent = parent;
    GraphicsScene::mapInfo = curMap;
    GraphicsScene::assets = loadedAssets;
    brushing = false;
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



        int x = item->scenePos().x();
        int y = item->scenePos().y();

        Terrain *terrain = mapInfo->getTerrain();
        Terrain::Type type;

        Texture *asset = 0;


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
        else if (curTool == "rubble")
            type = Terrain::Rubble;
        else if (curTool == "Peasant")
            asset = assets->value("Peasant");
        else if (curTool == "Ranger")
            asset = assets->value("Ranger");
        else if (curTool == "Archer")
            asset = assets->value("Archer");
        else if (curTool == "Knight")
            asset = assets->value("Knight");
        else if (curTool == "GoldMine")
            asset = assets->value("GoldMine");
        else if (curTool == "TownHall")
            asset = assets->value("TownHall");
        else if (curTool == "Barracks")
            asset = assets->value("Barracks");
        else if (curTool == "BlackSmith")
            asset = assets->value("Blacksmith");
        else if (curTool == "CannonTower")
            asset = assets->value("CannonTower");
        else if (curTool == "Castle")
            asset = assets->value("Castle");
        else if (curTool == "Farm")
            asset = assets->value("Farm");
        else if (curTool == "GuardTower")
            asset = assets->value("GuardTower");
        else if (curTool == "ScoutTower")
            asset = assets->value("ScoutTower");
        else if (curTool == "Keep")
            asset = assets->value("Keep");
        else if (curTool == "LumberMill")
            asset = assets->value("LumberMill");
        else
        {
            QGraphicsScene::mousePressEvent(mouseEvent);
            return;
        }

        QImage imageDx;
        if (!asset){
//            imageDx = *terrain->getImageTile(type);
           // tile change
            mapInfo->changeMapTile(this, mouseEvent->scenePos(),type);

        }
        else
        {
            if (curTool == "GoldMine")
                imageDx = asset->imageList[0];
            else if (curTool == "CannonTower" || curTool == "Castle" || curTool == "Keep" || curTool == "GuardTower")
                imageDx = asset->colorPlayerImg[curPlayer][1];
            else if (curTool == "Peasant" || curTool == "Knight" || curTool == "Archer" || curTool == "Ranger")
                imageDx = asset->colorPlayerImg[curPlayer][20];
            else
                imageDx = asset->colorPlayerImg[curPlayer][2];

            QPixmap pixmap = QPixmap::fromImage(imageDx);
            Tile * pixItem = new Tile(type, pixmap);


            pixItem->setPos(x, y);
            addItem(pixItem);
        }



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
    if (mouseEvent->button() == Qt::LeftButton && withinBounds(mouseEvent))
        brushing = true;
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if ((mouseEvent->buttons() & Qt::LeftButton) && brushing && withinBounds(mouseEvent))
        addToolItem(mouseEvent);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton && withinBounds(mouseEvent)) {
        addToolItem(mouseEvent);
        brushing = false;
    }
}

bool GraphicsScene::withinBounds(QGraphicsSceneMouseEvent *mouseEvent)
{//Checks to see if the mouse event occurs within map bounds to prevent crashing
    return mouseEvent->scenePos().x() >= 0 && mouseEvent->scenePos().x() < width()
            && mouseEvent->scenePos().y() >= 0 && mouseEvent->scenePos().y() < height();
}
