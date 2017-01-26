#ifndef MAPVIEW2_H
#define MAPVIEW2_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "tile.h"
#include "texture.h"

class MapView2
{
public:
    MapView2(const QString &mapFileName, const QString &mapTexName);

    void displayMap(QGraphicsScene *scene);
    void builtmap(QGraphicsScene *scene);

//private:
    void openMap(const QString &mapName);
    void openMapTexture(const QString &mapTexture);
    QImage createImageTile(QImage* image, const QRect &rect);


    QImage currentImage;
    QString mapName;

private:
    QVector<QChar> mapLayOut;
    QRect tileDim;
    QSize mapDim;
    Texture *texture;

    QVector<Tile*> tileMap;





};

#endif // MAPVIEW2_H
