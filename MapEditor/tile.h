#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>
#include "texture.h"

class Tile : public QGraphicsPixmapItem
{
public:
    Tile(QString typeStr,QPixmap texturePix);
    Tile(Texture::Type type, QPixmap texturePix);
    QString toString();

//    QRectF boundingRect()const;
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    Texture::Type type;
    QString note;
    QString typeStr;

    QPixmap texturePix;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


private:

//    Texture *tex;

};

#endif // TILE_H
