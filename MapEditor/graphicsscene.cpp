#include "graphicsscene.h"
#include <QDebug>
#include "ui_mainwindow.h"
#include "tile.h"
#include "texture.h"
#include "mainwindow.h"
#include <QMediaPlayer>
#include <QUrl>


GraphicsScene::GraphicsScene(QObject *parent, MapView2 *curMap) : QGraphicsScene(parent)
{
    GraphicsScene::parent = parent;
    GraphicsScene::mapInfo = curMap;
    brushing = false;
    unitsound = new QMediaPlayer();
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
        else if (curTool == "Peasant"){
            asset = mapInfo->getAsset("Peasant");
            unitsound -> setMedia(QUrl("qrc:/archer/ready.wav"));
            unitsound->play();
        }
        else if (curTool == "Ranger"){
            asset = mapInfo->getAsset("Ranger");
            unitsound -> setMedia(QUrl("qrc:/archer/ready.wav"));
            unitsound->play();
        }
        else if (curTool == "Archer"){
            asset = mapInfo->getAsset("Archer");
            unitsound -> setMedia(QUrl("qrc:/archer/ready.wav"));
            unitsound->play();
        }
        else if (curTool == "Knight"){
            asset = mapInfo->getAsset("Knight");
            unitsound -> setMedia(QUrl("qrc:/archer/ready.wav"));
            unitsound->play();
        }
        else if (curTool == "GoldMine"){
            asset = mapInfo->getAsset("GoldMine");
            unitsound -> setMedia(QUrl("qrc:/buildings/gold-mine.wav"));
            unitsound->play();
        }
        else if (curTool == "TownHall")
            asset = mapInfo->getAsset("TownHall");
        else if (curTool == "Barracks")
            asset = mapInfo->getAsset("Barracks");
        else if (curTool == "BlackSmith"){
            asset = mapInfo->getAsset("Blacksmith");
            unitsound -> setMedia(QUrl("qrc:/buildings/blacksmith.wav"));
            unitsound->play();
        }
        else if (curTool == "CannonTower")
            asset = mapInfo->getAsset("CannonTower");
        else if (curTool == "Castle")
            asset = mapInfo->getAsset("Castle");
        else if (curTool == "Farm"){
            asset = mapInfo->getAsset("Farm");
            unitsound -> setMedia(QUrl("qrc:/buildings/farm.wav"));
            unitsound->play();
        }
        else if (curTool == "GuardTower")
            asset = mapInfo->getAsset("GuardTower");
        else if (curTool == "ScoutTower")
            asset = mapInfo->getAsset("ScoutTower");
        else if (curTool == "Keep")
            asset = mapInfo->getAsset("Keep");
        else if (curTool == "LumberMill"){
            asset = mapInfo->getAsset("LumberMill");
            unitsound -> setMedia(QUrl("qrc:/buildings/lumber-mill.wav"));
            unitsound->play();
        }
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
