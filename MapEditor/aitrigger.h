#ifndef AITRIGGER_H
#define AITRIGGER_H

#include <QObject>
#include <QString>
#include <QPoint>
#include <QWidget>
#include "tile.h"
#include <QDebug>

class AITrigger
{
//    Q_OBJECT
public:
    AITrigger(QString name);
    AITrigger(QString name, QString type, bool persistence, QString event, QStringList trigArgsList, QStringList eventArgsList);
    QString infoAI() const;

    // gets
    Tile* getTile();
    QString getType();
    QPoint* getPos();

    // sets
    void setTile(Tile *tile);
    void setName(QString name);
    void setType(QString type);
    void setPersistence(bool checked);
    void setPosition(int x, int y);
    void setEvent(QString &func);
    void setTrigArgsList(QStringList &list);
    void setEventArgsList(QStringList &list);

private:
    QString triggerName;
    QString type;
    QPointF position;
    bool persistence;
    QString event;
    QStringList trigArgsList;
    QStringList eventArgsList;

    Tile *tile;
};


#endif // AITRIGGER_H
