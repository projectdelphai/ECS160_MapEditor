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

    Terrain* getTerrain();
    void displayMap(QGraphicsScene *scene);
    //void builtmap(QGraphicsScene *scene);
   // void builtAssets(QGraphicsScene *scene);
    QString tileEncode(QString typeS,int i, int j);
    void builtTreeTop(QGraphicsScene *scene);

    QSize getMapDim();
    QString getMapName();
    QVector<QChar> getMapLayout();
    void setMapLayout(QVector<QChar> layout);
    QVector<Player> getPlayers();
    int getNumPlayers();
    int getNumUnits();
    void addUnit(Unit u, int player);

private:
    void builtmap(QGraphicsScene *scene);
    void builtAssets(QGraphicsScene *scene);

    void openMap(const QString &mapName);
    void openMapTexture(const QString &mapTexture);
    QImage createImageTile(QImage* image, const QRect &rect);

    QString mapName;
    QVector<Player> players;
    QVector<QChar> mapLayOut;
    QRect tileDim;
    QSize mapDim;
    int numPlayers;
    int numUnits;
    void addPlayer(Player p);

    Terrain* terrain;
    // QPoint , QString not possible
    QMap<QString , QString> treeTopTiles;
    void setup();
    void defaultMap();

    QStringList mapAllowedAIs;
    QString mapDescription;
    Texture *terrainTexture;
    QMap<QString,Texture*> assets;
    QVector<Tile*> tileMap;
};

#endif // MAPVIEW2_H
