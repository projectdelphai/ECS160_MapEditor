#include "tile.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

Tile::Tile(QString type){
    type = type;
}

Tile::Tile(QString type,QPixmap texturePix): QGraphicsPixmapItem(texturePix){
    type = type;
    texturePix = texturePix;
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qWarning() << Q_FUNC_INFO << event->scenePos();
}




//QRectF Tile::boundingRect() const {
//    return QRectF(0,0,100,100);
//}

//void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
//    QRectF rect = boundingRect();

//}

