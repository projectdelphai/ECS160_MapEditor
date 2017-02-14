#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>
#include "texture.h"
#include "terrain.h"

class Tile : public QGraphicsPixmapItem
{
public:
    Tile(Terrain::Type type);
    Tile(Terrain::Type type, QPixmap texturePix);
    Tile(QString typeStr,QPixmap texturePix);

    QString toString();

//protected:
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    Terrain::Type type;
    QString note;
    QString typeStr;

    QPixmap texturePix;

//    Texture *tex;

};

#endif // TILE_H
