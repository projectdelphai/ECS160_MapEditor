#include "tile.h"
#include "texture.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>


Tile::Tile(Terrain::Type type){ // not sure if needed
    Tile::type = type;
}

Tile::Tile(QString typeStr,QPixmap texturePix):QGraphicsPixmapItem(texturePix){
    typeStr = typeStr;
    texturePix = texturePix;
}

Tile::Tile(Terrain::Type type,QPixmap texturePix): QGraphicsPixmapItem(texturePix){
    Tile::type = type;
    Tile::texturePix = texturePix;
    note = "test";
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qWarning() << Q_FUNC_INFO << event->scenePos();
    //qDebug() << "in Tile:mousePressEvent";
}

QString Tile::toString()
{
    // enum  Type { Grass = 0, Dirt , Tree , Water , Rock , WallDamage , Wall , Rubble };
    switch(type)
    {
    case Terrain::Grass:
        return "Grass";
        break;
    case Terrain::Dirt:
        return "Dirt";
        break;
    case Terrain::Tree:
        return "Tree";
        break;
    case Terrain::Water:
        return "Water";
        break;
    case Terrain::Rock:
        return "Rock";
        break;
    case Terrain::Wall:
        return "Wall";
        break;
    case Terrain::WallDamage:
        return "WallDamage";
        break;
    case Terrain::Rubble:
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

