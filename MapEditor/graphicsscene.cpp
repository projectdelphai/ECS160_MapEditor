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
    goldmineTool = new Texture(":/data/img/GoldMine.dat",":/data/img/Colors.png");
    peasantTool = new Texture(":/data/img/Peasant.dat",":/data/img/Colors.png");
    peasantTool->paintAll();
    townhallTool = new Texture(":/data/img/TownHall.dat",":/data/img/Colors.png");
    townhallTool->paintAll();
    barracksTool = new Texture(":/data/img/Barracks.dat",":/data/img/Colors.png");
    barracksTool->paintAll();
    blacksmithTool = new Texture(":/data/img/Blacksmith.dat",":/data/img/Colors.png");
    blacksmithTool->paintAll();
    cannontowerTool = new Texture(":/data/img/CannonTower.dat",":/data/img/Colors.png");
    cannontowerTool->paintAll();
    castleTool = new Texture(":/data/img/Castle.dat",":/data/img/Colors.png");
    castleTool->paintAll();
    farmTool = new Texture(":/data/img/Farm.dat",":/data/img/Colors.png");
    farmTool->paintAll();
    guardtowerTool = new Texture(":/data/img/GuardTower.dat",":/data/img/Colors.png");
    guardtowerTool->paintAll();
    keepTool = new Texture(":/data/img/Keep.dat",":/data/img/Colors.png");
    keepTool->paintAll();
    lumbermillTool = new Texture(":/data/img/LumberMill.dat",":/data/img/Colors.png");
    lumbermillTool->paintAll();
    scouttowerTool = new Texture(":/data/img/ScoutTower.dat",":/data/img/Colors.png");
    scouttowerTool->paintAll();
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
        else if (curTool == "Peasant")
            asset = peasantTool;
        else if (curTool == "GoldMine")
            asset = goldmineTool;
        else if (curTool == "TownHall")
            asset = townhallTool;
        else if (curTool == "Barracks")
            asset = barracksTool;
        else if (curTool == "BlackSmith")
            asset = blacksmithTool;
        else if (curTool == "CannonTower")
            asset = cannontowerTool;
        else if (curTool == "Castle")
            asset = castleTool;
        else if (curTool == "Farm")
            asset = farmTool;
        else if (curTool == "GuardTower")
            asset = guardtowerTool;
        else if (curTool == "ScoutTower")
            asset = scouttowerTool;
        else if (curTool == "Keep")
            asset = keepTool;
        else if (curTool == "LumberMill")
            asset = lumbermillTool;
        else
        {
            QGraphicsScene::mousePressEvent(mouseEvent);
            return;
        }

        QImage imageDx;
        if (!asset)
            imageDx = *terrain->getImageTile(type);
        else
        {
            if (curTool == "GoldMine")
                imageDx = asset->imageList[0];
            else if (curTool == "CannonTower" || curTool == "Castle" || curTool == "Keep" || curTool == "GuardTower")
                imageDx = asset->colorPlayerImg[curPlayer][1];
            else
                imageDx = asset->colorPlayerImg[curPlayer][2];
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
