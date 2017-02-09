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
    QString curTool;
    int curPlayer;
    Texture *peasantTool;
    Texture *goldmineTool;
    Texture *townhallTool;
    Texture *barracksTool;
    Texture *blacksmithTool;
    Texture *farmTool;
    Texture *lumbermillTool;
    Texture *scouttowerTool;
    Texture *cannontowerTool;
    Texture *castleTool;
    Texture *keepTool;
    Texture *guardtowerTool;
signals:
    void changedLayout(int x, int y, Terrain::Type type);
    void changedAsset(int x, int y, QString asset, int curPlayer);

public slots:

private:
    QObject *parent;
    MapView2 *mapInfo;
    bool brushing;
};

#endif // GRAPHICSSCENE_H
