#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "mapview2.h"
#include "texture.h"
#include "terrain.h"
#include <QMediaPlayer>
#include <QUrl>

// reference: http://stackoverflow.com/questions/26901540/arc-in-qgraphicsscene/26903599#26903599

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(QObject *parent, MapView2 *curMap, QMap<QString , Texture*> *loadedAssets);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void delayUnit(int millisecondsToWait);
    void addToolItem(QGraphicsSceneMouseEvent *mouseEvent);
    void removeToolItem(QGraphicsSceneMouseEvent *mouseEvent);
    bool withinBounds(QGraphicsSceneMouseEvent *mouseEvent);
    void delayUnit(int millisecondsToWait);
    void setBrushable(bool b);
    MapView2 * getMapInfo();
    QString curTool;
    int CurBrushSize = 1;
    int curPlayer;
signals:
    void changedLayout(int x, int y, Terrain::Type type);
    void changedAsset(int x, int y, QString asset, int curPlayer);
    void open_DTrigger(QGraphicsScene* scene, Tile* );
public slots:

private:
    QObject *parent;
    MapView2 *mapInfo;
    bool brushing;
    bool brushable;
    QVector<QString> addedItems;
    QVector<QString> tempXY;
    QVector<QString> loc;
    QMap<QString,Texture*> *assets;
    QString tempX, tempY, x, y;
    int posX, posY, widthXheight = 0;
};

#endif // GRAPHICSSCENE_H
