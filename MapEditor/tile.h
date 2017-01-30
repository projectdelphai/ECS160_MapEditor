#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>
#include "texture.h"

class Tile : public QGraphicsPixmapItem
{
public:
    Tile(QString type);
    Tile(QString type, QPixmap texturePix);

//    QRectF boundingRect()const;
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QString type;
    QPointF pos;

    QPixmap texturePix;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


private:

//    Texture *tex;

};

#endif // TILE_H
