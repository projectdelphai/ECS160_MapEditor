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
    MapView2(QMap<QString,Texture*>& loadedAssets);

    MapView2(QIODevice &mapFile, QMap<QString,Texture*>& ,const QString &mapTexName);
//    QString tileEncode(QString strType,int i, int j);
//    void builtTreeTop(QGraphicsScene *scene);

    Terrain* getTerrain();
    Texture* getButtonColorsTx();
    Texture* getButtonIconsTx();
    void displayMap(QGraphicsScene *scene);
    void displayNewMap(QGraphicsScene *scene);

    QSize getMapDim();
    QString getMapName();
    QVector<QChar> getMapLayout();
    void setMapLayout(QVector<QChar> layout);
    QVector<Player> getPlayers();
    int getNumPlayers();
    int getNumUnits();
    void addUnit(Unit u, int player);
    Texture *getAsset(QString assetName);

    // change tile at some pos and tiles around it
    void changeMapTile(QGraphicsScene *scene , QPointF point , Terrain::Type type);

private:
    void defaultMap();
    void builtmap(QGraphicsScene *scene);
    void builtAssets(QGraphicsScene *scene);
    QString tileEncode(QString typeS,int i, int j);
    void builtTreeTop(QGraphicsScene *scene);

    void openMap(QIODevice &mapFile);
    void openMapTexture(const QString &mapTexture);
    void addPlayer(Player p);

    QImage createImageTile(QImage* image, const QRect &rect);

    QString mapName;
    QVector<Player> players;
    QVector<QChar> mapLayOut;
    QRect tileDim;
    QSize mapDim;
    QMap<QString , QString> treeTopTiles;
    Terrain* terrain;
    Texture* toolbar;
    Texture* buttonColors;
    Texture* buttonIcons;
    QChar strToMapkey(QString str);

    QStringList mapAllowedAIs;
    QString mapDescription;
    QMap<QString,Texture*> assets;
};

#endif // MAPVIEW2_H
