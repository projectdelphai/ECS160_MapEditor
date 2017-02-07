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
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    QString curTool;
signals:
    void changedLayout(int x, int y, Terrain::Type type);

public slots:

private:
    QObject *parent;
    MapView2 *mapInfo;
};

#endif // GRAPHICSSCENE_H
