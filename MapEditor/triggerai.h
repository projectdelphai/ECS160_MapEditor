#ifndef TRIGGERAI_H
#define TRIGGERAI_H

#include <QObject>
#include <QString>
#include <QPoint>
#include <QTimer>
#include <QWidget>
#include "tile.h"
#include <QDebug>
#include <QGraphicsEllipseItem>

class TriggerAI
{
//    Q_OBJECT
public:
    TriggerAI(QString name);
    QString infoAI() const;
    void startTimer(QWidget *widget);
    void setMarker(Tile *tile);
    void setTimer(double);
    void setRange(double);

    bool isRangeOn();
    double getTimer();
    Tile* getMarker();
    void hook();
    void displayRange(QGraphicsScene *scene);
    void removeRange(QGraphicsScene *scene);





private:
    QString triggerName;
    QPointF position;
    double time;
    QTimer *timer;
    Tile *tile;
    double radius;
    QGraphicsEllipseItem *circleRange;

};



#endif // TRIGGERAI_H
