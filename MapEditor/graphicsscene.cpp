#include "graphicsscene.h"
#include <QDebug>
#include "ui_mainwindow.h"
#include "tile.h"
#include "texture.h"
#include "mainwindow.h"
#include <QMediaPlayer>

#include <QUrl>

GraphicsScene::GraphicsScene(QObject *parent, MapView2 *curMap, QMap<QString, Texture *> *loadedAssets) : QGraphicsScene(parent)
{
    GraphicsScene::parent = parent;
    GraphicsScene::mapInfo = curMap;
    GraphicsScene::assets = loadedAssets;
    brushing = false;
    brushable = false;
}

void GraphicsScene::delayUnit(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
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
        QMediaPlayer * music = new QMediaPlayer();


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
        {
            asset = mapInfo->getAsset("Peasant");
            music->setMedia(QUrl("qrc:/data/snd/peasant/ready.wav"));
        }
        else if (curTool == "Ranger")
        {
            asset = mapInfo->getAsset("Ranger");
            music->setMedia(QUrl("qrc:/data/snd/archer/ready.wav"));
        }
        else if (curTool == "Archer")
        {
            asset = mapInfo->getAsset("Archer");
            music->setMedia(QUrl("qrc:/data/snd/archer/ready.wav"));
        }
        else if (curTool == "Knight")
        {
            asset = mapInfo->getAsset("Knight");
            music->setMedia(QUrl("qrc:/data/snd/knight/ready.wav"));
        }
        else if (curTool == "GoldMine")
        {
            asset = mapInfo->getAsset("GoldMine");
            music->setMedia(QUrl("qrc:/data/snd/buildings/gold-mine.wav"));
        }
        else if (curTool == "TownHall")
        {
            asset = mapInfo->getAsset("TownHall");
            music->setMedia(QUrl("qrc:/data/snd/misc/thunk.wav"));
        }
        else if (curTool == "Barracks")
        {
            asset = mapInfo->getAsset("Barracks");

            music->setMedia(QUrl("qrc:/data/snd/misc/thunk.wav"));
        }
        else if (curTool == "BlackSmith")
        {
            asset = mapInfo->getAsset("Blacksmith");
            music->setMedia(QUrl("qrc:/data/snd/buildings/blacksmith.wav"));
        }
        else if (curTool == "CannonTower")
        {
            asset = mapInfo->getAsset("CannonTower");
            music->setMedia(QUrl("qrc:/data/snd/misc/thunk.wav"));
        }
        else if (curTool == "Castle")
        {
            asset = mapInfo->getAsset("Castle");

        else if (curTool == "Farm")
        {
            asset = mapInfo->getAsset("Farm");
            music->setMedia(QUrl("qrc:/data/snd/buildings/farm.wav"));
        }
        else if (curTool == "GuardTower")
        {
            asset = mapInfo->getAsset("GuardTower");
            music->setMedia(QUrl("qrc:/data/snd/misc/construct.wav"));
        }
        else if (curTool == "ScoutTower")
        {
            asset = mapInfo->getAsset("ScoutTower");
            music->setMedia(QUrl("qrc:/data/snd/misc/construct.wav"));
        }
        else if (curTool == "Keep")
        {
            asset = mapInfo->getAsset("Keep");

            music->setMedia(QUrl("qrc:/data/snd/misc/thunk.wav"));
        }
        else if (curTool == "LumberMill")
        {
            asset = mapInfo->getAsset("LumberMill");
             music->setMedia(QUrl("qrc:/data/snd/buildings/lumber-mill.wav"));
        }
        else if (curTool == "hand")
        {
            clearSelection();
            return;
        }

        QImage imageDx;
        if (!asset){
           //imageDx = *terrain->getImageTile(type);
           // tile change
            brushable = true;
            mapInfo->changeMapTile(this, mouseEvent->scenePos(),type);
        }
        else
        {//Loads/Animates the assets
            if (curTool == "GoldMine"){
                brushable = false;
                for (int i=0; i<= 1;i++){
                    imageDx = imageDx = asset->imageList[i];
                    QPixmap pixmap = QPixmap::fromImage(imageDx);
                    Tile * pixItem = new Tile(type, pixmap);

                    pixItem->setPos(x, y);
                    addItem(pixItem);
                    delayUnit(1000);
                    if (i!=1){
                        removeItem(pixItem);
                    }
                }
            }
            else if (curTool == "CannonTower" || curTool == "Castle" || curTool == "Keep" || curTool == "GuardTower"){
                for (int i=0; i<= 1;i++){
                    imageDx = asset->colorPlayerImg[curPlayer][i];
                    QPixmap pixmap = QPixmap::fromImage(imageDx);
                    Tile * pixItem = new Tile(type, pixmap);

                    pixItem->setPos(x, y);
                    addItem(pixItem);
                    delayUnit(1000);
                    if (i!=1){
                        removeItem(pixItem);
                    }
                }
            }
            //for some reason barracks do not work
            else if (curTool == "TownHall" || curTool == "Barracks" || curTool == "Blacksmith" || curTool == "Farm" || curTool == "ScoutTower" || curTool == "LumberMill"){
                for (int i=0; i<= 3;i++){
                    imageDx = asset->colorPlayerImg[curPlayer][i];
                    QPixmap pixmap = QPixmap::fromImage(imageDx);
                    Tile * pixItem = new Tile(type, pixmap);

                    pixItem->setPos(x, y);
                    addItem(pixItem);
                    delayUnit(1000);
                    if (i!=3){
                        removeItem(pixItem);
                    }
                }
            }

            else if (curTool == "Peasant" || curTool == "Knight" || curTool == "Archer" || curTool == "Ranger"){
                for (int i=0; i<= 39;i++){
                    imageDx = asset->colorPlayerImg[curPlayer][i];
                    QPixmap pixmap = QPixmap::fromImage(imageDx);
                    Tile * pixItem = new Tile(type, pixmap);

                    pixItem->setPos(x, y);
                    addItem(pixItem);
                    delayUnit(500);
                    if (i!=39){
                       removeItem(pixItem);
                    }
                 }

              
              
            }

        
         QString x, y;
         x.setNum(pixItem->scenePos().x());
         y.setNum(pixItem->scenePos().y());
         y.prepend(x);
         if(addedItems.contains(y) == false){
            addedItems.append(y);
            addItem(pixItem);
            // play background music
            music->play();
         }
          else
                return;
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

void GraphicsScene::removeToolItem(QGraphicsSceneMouseEvent *mouseEvent)
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
        QString x, y;
        x.setNum(item->scenePos().x());
        y.setNum(item->scenePos().y());
        y.prepend(x);
        if (addedItems.contains(y))
        {
            this->removeItem(item);
            addedItems.removeOne(y);
            qDebug() << addedItems;
        }
        else
            return;
    }
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton && withinBounds(mouseEvent))
        brushing = true;
        brushable = true;
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if ((mouseEvent->buttons() & Qt::LeftButton) && brushing && withinBounds(mouseEvent) && brushable)
        addToolItem(mouseEvent);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton && withinBounds(mouseEvent) && brushable) {
        addToolItem(mouseEvent);
        brushing = false;
    }
    if (mouseEvent->button() == Qt::RightButton){
        removeToolItem(mouseEvent);
        brushing = false;
    }
}

bool GraphicsScene::withinBounds(QGraphicsSceneMouseEvent *mouseEvent)
{//Checks to see if the mouse event occurs within map bounds to prevent crashing
    return mouseEvent->scenePos().x() >= 0 && mouseEvent->scenePos().x() < width()
            && mouseEvent->scenePos().y() >= 0 && mouseEvent->scenePos().y() < height();
}
