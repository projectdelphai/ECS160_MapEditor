#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>

// reference: http://stackoverflow.com/questions/26901540/arc-in-qgraphicsscene/26903599#26903599

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(QObject *parent = 0);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
signals:

public slots:

private:
};

#endif // GRAPHICSSCENE_H
