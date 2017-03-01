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
        int frames = 0;
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
            widthXheight = 1;
            frames = 40;
        }
        else if (curTool == "Ranger")
        {
            asset = mapInfo->getAsset("Ranger");
            music->setMedia(QUrl("qrc:/data/snd/archer/ready.wav"));
            widthXheight = 1;
            frames = 40;
        }
        else if (curTool == "Archer")
        {
            asset = mapInfo->getAsset("Archer");
            music->setMedia(QUrl("qrc:/data/snd/archer/ready.wav"));            
            widthXheight = 1;
            frames = 40;
        }
        else if (curTool == "Knight")
        {
            asset = mapInfo->getAsset("Knight");
            music->setMedia(QUrl("qrc:/data/snd/knight/ready.wav"));
            widthXheight = 1;
            frames = 40;
        }
        else if (curTool == "GoldMine")
        {
            asset = mapInfo->getAsset("GoldMine");
            music->setMedia(QUrl("qrc:/data/snd/buildings/gold-mine.wav"));
            widthXheight = 4;
            frames = 1;
        }
        else if (curTool == "TownHall")
        {
            asset = mapInfo->getAsset("TownHall");
            music->setMedia(QUrl("qrc:/data/snd/misc/thunk.wav"));
            widthXheight = 4;
            frames = 3;
        }
        else if (curTool == "Barracks")
        {
            asset = mapInfo->getAsset("Barracks");

            music->setMedia(QUrl("qrc:/data/snd/misc/thunk.wav"));
            widthXheight = 3;
            frames = 3;
        }
        else if (curTool == "BlackSmith")
        {
            asset = mapInfo->getAsset("Blacksmith");
            music->setMedia(QUrl("qrc:/data/snd/buildings/blacksmith.wav"));
            widthXheight = 3;
            frames = 3;
        }
        else if (curTool == "CannonTower")
        {
            asset = mapInfo->getAsset("CannonTower");
            music->setMedia(QUrl("qrc:/data/snd/misc/thunk.wav"));
            widthXheight = 2;
            frames = 2;
        }
        else if (curTool == "Castle")
        {
            asset = mapInfo->getAsset("Castle");
            music->setMedia(QUrl("qrc:/data/snd/misc/thunk.wav"));
            widthXheight = 4;
            frames = 2;
        }
        else if (curTool == "Farm")
        {
            asset = mapInfo->getAsset("Farm");
            music->setMedia(QUrl("qrc:/data/snd/buildings/farm.wav"));
            widthXheight = 2;
            frames = 3;
        }
        else if (curTool == "GuardTower")
        {
            asset = mapInfo->getAsset("GuardTower");
            music->setMedia(QUrl("qrc:/data/snd/misc/construct.wav"));
            widthXheight = 2;
            frames = 2;
        }
        else if (curTool == "ScoutTower")
        {
            asset = mapInfo->getAsset("ScoutTower");
            music->setMedia(QUrl("qrc:/data/snd/misc/construct.wav"));
            widthXheight = 2;
            frames = 3;
        }
        else if (curTool == "Keep")
        {
            asset = mapInfo->getAsset("Keep");

            music->setMedia(QUrl("qrc:/data/snd/misc/thunk.wav"));
            widthXheight = 4;
            frames = 2;
        }
        else if (curTool == "LumberMill")
        {
            asset = mapInfo->getAsset("LumberMill");
            music->setMedia(QUrl("qrc:/data/snd/buildings/lumber-mill.wav"));
            widthXheight = 3;
            frames = 3;
        }
        else if (curTool == "hand")
        {
            clearSelection();
            return;
        }
        else if( curTool == "Trigger"){
            brushable = false;
            QImage image;
            image.load(":/data/img/Trigger.png");
            Tile *item = new Tile("Trigger", QPixmap::fromImage(image));
            item->setPos(x,y);
            item->setZValue(10);
            addItem(item);
            emit open_DTrigger(this, item);
            return;
        }

        QImage imageDx;
        if (!asset){
           //imageDx = *terrain->getImageTile(type);
           // tile change
            brushable = true;
            mapInfo-> brush_size(this, mouseEvent->scenePos(),type,CurBrushSize);
            QString x, y;
            x.setNum(item->scenePos().x());
            y.setNum(item->scenePos().y());
            y.prepend(x);
            if(addedItems.contains(y))
            {
                QMessageBox::warning(0,"Error!","Cannot put tile on assets");
                qDebug() << y;
                return;
            }
            else
            {
                brushable = true;
                mapInfo->changeMapTile(this, mouseEvent->scenePos(),type);
                if(type == Terrain::Water || type == Terrain::Rock || type == Terrain::Tree || type == Terrain::Wall)
                {
                    if(loc.contains(y) == false)
                    {
                        loc.append(y);
                        qDebug() << loc;
                    }
                }
            }


        }
        else
        {//Loads/Animates the assets
            brushable = false;

            if (curTool == "GoldMine")
                imageDx = asset->imageList[0];
            else
                imageDx = asset->colorPlayerImg[curPlayer][0];
//            else if (curTool == "CannonTower" || curTool == "Castle" || curTool == "Keep" || curTool == "GuardTower")
//                imageDx = asset->colorPlayerImg[curPlayer][1];
//            else if (curTool == "Peasant" || curTool == "Knight" || curTool == "Archer" || curTool == "Ranger")
//                imageDx = asset->colorPlayerImg[curPlayer][20];


            QPixmap pixmap = QPixmap::fromImage(imageDx);
            Tile * pixItem = new Tile(type, pixmap);
            pixItem->setPos(x, y);
            posX = x;
            posY = y;
            for(int i = 0; i < widthXheight; i++)
            { 
                for(int j = 0; j < widthXheight; j++)
                {
                    tempX.setNum(posX + 32*i);
                    tempY.setNum(posY + 32*j);
                    tempY.prepend(tempX);
                    tempXY.append(tempY);
                }
            }
            bool added = true;
            for (int i = 0; i < tempXY.size(); i++)
            {
                if(addedItems.contains(tempXY[i]) || loc.contains(tempXY[i]))
                {
                    added = true;
                    break;
                }
                else
                    added = false;
            }
            tempXY.clear();
            if(added == false)
            {
                for(int i = 0; i < frames; i++)
                {
                    if(curTool == "GoldMine")
                        imageDx = asset->imageList[i];
                    else
                        imageDx = asset->colorPlayerImg[curPlayer][i];
                    QPixmap pixmap = QPixmap::fromImage(imageDx);
                    Tile * pixItem = new Tile(type, pixmap);
                    pixItem->setPos(x, y);
                    addItem(pixItem);
                    delayUnit(500);
                    if(i != frames-1)
                        removeItem(pixItem);
                }

                // play background music
                music->play();
                for(int i = 0; i < widthXheight; i++)
                {
                    for(int j = 0; j < widthXheight; j++)
                    {
                        tempX.setNum(posX + 32*i);
                        tempY.setNum(posY + 32*j);
                        tempY.prepend(tempX);
                        addedItems.append(tempY);
                    }
                }
                qDebug() << addedItems;
            }
            else
            {
                QMessageBox::warning(0,"Cannot overlap","Place somewhere else!");
                return;
            }
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
        posX = item->scenePos().x();
        posY = item->scenePos().y();
        QString x, y;
        x.setNum(item->scenePos().x());
        y.setNum(item->scenePos().y());
        y.prepend(x);

        if (addedItems.contains(y))
        {
            for(int i = 0; i < widthXheight; i++)
            {
                for(int j = 0; j < widthXheight; j++)
                {
                    tempX.setNum(posX + 32*i);
                    tempY.setNum(posY + 32*j);
                    tempY.prepend(tempX);
                    addedItems.removeOne(tempY);
                }
            }
            this->removeItem(item);
            qDebug() << addedItems;
        }
        else
            return;
    }
}

void GraphicsScene::setBrushable(bool b)
{
    brushable = b;
}

MapView2 * GraphicsScene::getMapInfo()
{
    return mapInfo;
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
