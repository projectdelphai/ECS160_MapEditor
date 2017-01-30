#include "tile.h"
#include "texture.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

Tile::Tile(Texture::Type type){
    type = type;
}

Tile::Tile(Texture::Type type,QPixmap texturePix): QGraphicsPixmapItem(texturePix){
    type = type;
    texturePix = texturePix;
    note = "test";
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qWarning() << Q_FUNC_INFO << event->scenePos();
}

QString Tile::toString()
{
    //     enum  Type { Grass = 0, Dirt , Tree , Water , Rock , WallDamage , Wall , Rubble };
    switch(type)
    {
    case Texture::Grass:
        return "Grass";
        break;
    case Texture::Dirt:
        return "Dirt";
        break;
    case Texture::Tree:
        return "Tree";
        break;
    case Texture::Water:
        return "Water";
        break;
    case Texture::Rock:
        return "Rock";
        break;
    case Texture::WallDamage:
        return "WallDamage";
        break;
    case Texture::Rubble:
        return "Rubble";
        break;
    }
}




//QRectF Tile::boundingRect() const {
//    return QRectF(0,0,100,100);
//}

//void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
//    QRectF rect = boundingRect();

//}

