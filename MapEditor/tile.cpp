#include "tile.h"

Tile::Tile(QString type){
    type = type;
}

Tile::Tile(QString type,QPixmap texturePix): QGraphicsPixmapItem(texturePix){
    type = type;
    texturePix = texturePix;
}

//QRectF Tile::boundingRect() const {
//    return QRectF(0,0,100,100);
//}

//void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
//    QRectF rect = boundingRect();

//}

