#ifndef MAPVIEW2_H
#define MAPVIEW2_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "tile.h"
#include "texture.h"

class Unit
{
public:
    Unit();
    Unit(QString name, int x, int y);
    QString name;
    int x;
    int y;
};

class Player
{
public:
    Player();
    Player(int n, int g, int l);
    int num;
    int gold;
    int lumber;
    QVector<Unit> units;
};



class MapView2
{
public:
    MapView2();
    MapView2(const QString &mapFileName, const QString &mapTexName);

    void displayMap(QGraphicsScene *scene);
    void builtmap(QGraphicsScene *scene);
    QSize getMapDim();
    QString getMapName();
    QVector<QChar> getMapLayout();
    void setMapLayout(QVector<QChar> layout);
    QVector<Player> getPlayers();
    int getNumPlayers();
    int getNumUnits();

//private:
    void defaultMap();
    void openMap(const QString &mapName);
    void openMapTexture(const QString &mapTexture);
    QImage createImageTile(QImage* image, const QRect &rect);


    QImage currentImage;
    QString mapName;

private:
    QVector<QChar> mapLayOut;
    QRect tileDim;
    QSize mapDim;
    int numPlayers;
    int numUnits;
    QVector<Player> players;

    Texture *texture;
    Terrain *terrain;

    QVector<Tile*> tileMap;





};

#endif // MAPVIEW2_H
