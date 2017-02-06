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
    /*Tile *item = (Tile *)this->itemAt(mouseEvent->scenePos(), QTransform());

    Texture *texture = new Texture(":/data/img/Terrain.png");
    Texture::Type type;

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

    QImage imageDx = texture->getImageTile(type);
    QPixmap pixmap = QPixmap::fromImage(imageDx);
    Tile * pixItem = new Tile(type, pixmap);
    int x = item->scenePos().x();
    int y = item->scenePos().y();
    pixItem->setPos(x, y);
    addItem(pixItem);
    emit changedLayout(x, y, type);
}
*/
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
        else
        {
            QGraphicsScene::mousePressEvent(mouseEvent);
            return;
        }

        QImage imageDx = texture->terrainType.value(type).first();
        QPixmap pixmap = QPixmap::fromImage(imageDx);
        Tile * pixItem = new Tile(type, pixmap);

        int x = item->scenePos().x();
        int y = item->scenePos().y();
        pixItem->setPos(x, y);
        addItem(pixItem);

        emit changedLayout(x, y, type);
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
