#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "texture.h"

// reference: http://stackoverflow.com/questions/26901540/arc-in-qgraphicsscene/26903599#26903599

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(QObject *parent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void addToolItem(QGraphicsSceneMouseEvent *mouseEvent);
    QString curTool;
    int curPlayer;
signals:
    void changedLayout(int x, int y, Texture::Type type);
    void changedAsset(int x, int y, QString asset, int curPlayer);

public slots:

private:
    QObject *parent;
    bool brushing;
};

#endif // GRAPHICSSCENE_H
