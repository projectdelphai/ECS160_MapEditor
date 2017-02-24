#ifndef MAPVIEW2_H
#define MAPVIEW2_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "tile.h"
#include "texture.h"
#include "triggerai.h"

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

    Terrain* getTerrain();
    Texture* getButtonColorsTx();
    Texture* getButtonIconsTx();
    QSize getMapDim();
    QString getMapName();
    QVector<QChar> getMapLayout();
    int getNumPlayers();
    int getNumUnits();
    Texture *getAsset(QString assetName);
    QVector<Player> getPlayers();
    QVector<TriggerAI*> getTriggers();

    void setMapLayout(QVector<QChar> layout);
    void addTrigger(TriggerAI *trigger );
    void addUnit(Unit u, int player);
    void displayMap(QGraphicsScene *scene);
    void displayNewMap(QGraphicsScene *scene);

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

//    QImage createImageTile(QImage* image, const QRect &rect);
    QChar strToMapkey(QString str);
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
    QStringList mapAllowedAIs;
    QString mapDescription;
    QMap<QString,Texture*> assets;
    QVector<TriggerAI*> triggers;

};

#endif // MAPVIEW2_H
