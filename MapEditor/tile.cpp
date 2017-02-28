#include "tile.h"
#include "texture.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>


Tile::Tile(Terrain::Type type){ // not sure if needed
    Tile::typeTile = type;
}

Tile::Tile(QString typeS,QPixmap texturePix):QGraphicsPixmapItem(texturePix){
    typeStr = typeS;
    texturePix = texturePix;

}

Tile::Tile(Terrain::Type type,QPixmap texturePix): QGraphicsPixmapItem(texturePix){
    Tile::typeTile = type;
    Tile::texturePix = texturePix;
    note = "test";
}

int Tile::type()const{
//    if (typeStr == "grass" || typeStr == "water" || typeStr == "tree" || typeStr == "wall" || typeStr == "rock"){
//        return TerrainTile;
//    }
    return Type;
}
//void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
    //qWarning() << Q_FUNC_INFO << event->scenePos();
    //qDebug() << "in Tile:mousePressEvent";
//}

//void Tile::setTileImage(QPixmap pix){
//    setPixmap(pix);
//}

void Tile::setTileImage(QPixmap pix, QString typeS){
    setPixmap(pix);
    typeStr = typeS;
}


QString Tile::getType(){
    return typeStr;
}



QString Tile::toString()
{
    // enum  Type { Grass = 0, Dirt , Tree , Water , Rock , WallDamage , Wall , Rubble };
    switch(typeTile)
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
    return 0;
}




//QRectF Tile::boundingRect() const {
//    return QRectF(0,0,100,100);
//}

//void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
//    QRectF rect = boundingRect();

//}

