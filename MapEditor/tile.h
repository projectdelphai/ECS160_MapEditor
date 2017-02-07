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
    QString toString();

//    QRectF boundingRect()const;
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


private:
    Terrain::Type type;
    QString note;
    QPointF pos;

    QPixmap texturePix;

//    Texture *tex;

};

#endif // TILE_H
