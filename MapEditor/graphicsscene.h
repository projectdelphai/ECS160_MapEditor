#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "mapview2.h"
#include "texture.h"
#include "terrain.h"

// reference: http://stackoverflow.com/questions/26901540/arc-in-qgraphicsscene/26903599#26903599

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(QObject *parent, MapView2 *curMap);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void addToolItem(QGraphicsSceneMouseEvent *mouseEvent);
    void removeToolItem(QGraphicsSceneMouseEvent *mouseEvent);
    bool withinBounds(QGraphicsSceneMouseEvent *mouseEvent);
    QString curTool;
    int curPlayer;
signals:
    void changedLayout(int x, int y, Terrain::Type type);
    void changedAsset(int x, int y, QString asset, int curPlayer);
public slots:

private:
    QObject *parent;
    MapView2 *mapInfo;
    bool brushing;
    bool brushable;
    QVector<QString> addedItems;
};

#endif // GRAPHICSSCENE_H
