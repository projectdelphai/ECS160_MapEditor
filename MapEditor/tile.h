#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>
#include "texture.h"
#include "terrain.h"

class Tile : public QGraphicsPixmapItem
{
public:
    enum { Type = UserType + 1, OtherTile = UserType + 2};
    Tile(Terrain::Type type);
    Tile(Terrain::Type type, QPixmap texturePix);
    Tile(QString typeStr,QPixmap texturePix);
    int type()const;
    QString toString();
//    void setTileImage(QPixmap pix);
    void setTileImage(QPixmap pix, QString typeS);
    QString getType();


//protected:
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    Terrain::Type typeTile;
    QString note;

    QString typeStr;
    QPixmap texturePix;

//    Texture *tex;

};

#endif // TILE_H
