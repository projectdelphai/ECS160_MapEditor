#ifndef TRIGGERAI_H
#define TRIGGERAI_H

#include <QString>
#include <QPoint>
#include <QTimer>
#include <QWidget>
#include "tile.h"

class TriggerAI
{
public:
    TriggerAI(QString name);
    QString infoAI() const;
    void hook();
    void startTimer(QWidget *widget);

    void setMarker(Tile *tile);
    void setTimer(double);
    double getTimer();
    Tile* getMarker();




private:
    QString triggerName;
    QPoint position;
    double time;
    QTimer *timer;
    Tile *tile;

};



#endif // TRIGGERAI_H
