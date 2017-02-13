#include "graphicsscene.h"
#include <QDebug>
#include "ui_mainwindow.h"
#include "tile.h"
#include "texture.h"
#include "mainwindow.h"


GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent)
{
    GraphicsScene::parent = parent;
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


        Texture *texture = new Texture(":/data/img/Terrain.png");
        Texture::Type type;
        Texture *asset = 0;


        if (curTool == "grass")
            type = Texture::Grass;
        else if (curTool == "dirt")
            type = Texture::Dirt;
        else if (curTool == "water")
            type = Texture::Water;
        else if (curTool == "rock")
            type = Texture::Rock;
        else if (curTool == "tree")
            type = Texture::Tree;
        else if (curTool == "wall")
            type = Texture::Wall;
        else if (curTool == "Peasant")
        {
            asset = new Texture(":/data/img/Peasant.dat",":/data/img/Colors.png");
            asset->paintAll();

        }
        else if (curTool == "GoldMine")
        {
            asset = new Texture(":/data/img/GoldMine.dat",":/data/img/Colors.png");

        }
        else
        {
            QGraphicsScene::mousePressEvent(mouseEvent);
            return;
        }

        QImage imageDx;
        if (!asset)
            imageDx = texture->terrainType.value(type).first();
        else
        {
            if (curTool == "GoldMine")
                imageDx = asset->imageList[0];
            else
                imageDx = asset->colorPlayerImg[curPlayer][0];
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
{
    return mouseEvent->scenePos().x() >= 0 && mouseEvent->scenePos().x() <= width()
            && mouseEvent->scenePos().y() >= 0 && mouseEvent->scenePos().y() <= height();
}
