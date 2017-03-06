#include "aitrigger.h"


AITrigger::AITrigger(QString name)
{
   triggerName = name;
}

AITrigger::AITrigger(QString name, QString type, bool persistence, QString event, QStringList trigArgsList, QStringList eventArgsList)
{
    setName(name);
    setType(type);
    setPersistence(persistence);
    setEvent(event);
    setTrigArgsList(trigArgsList);
    setEventArgsList(eventArgsList);
}

QString AITrigger::infoAI() const{
    QString ai = triggerName + " " +
                 QString().setNum(position.x()) + " " +
                 QString().setNum(position.y()) + " " +
                 event + " ";
    return ai;
}

// gets
Tile* AITrigger::getTile(){
    return tile;
}


// sets
void AITrigger::setName(QString name) {
    triggerName = name;
}

void AITrigger::setType(QString t) {
    type = t;
}

void AITrigger::setPersistence(bool checked) {
    persistence = checked;
}

void AITrigger::setPosition(int x, int y) {
    position = QPointF(x, y);
}

void AITrigger::setEvent(QString &func) {
    event = func;
}

void AITrigger::setTrigArgsList(QStringList &list) {
    eventArgsList = list;
}

void AITrigger::setEventArgsList(QStringList &list) {
    eventArgsList = list;
}

void AITrigger::setTile(Tile *marker){
    tile = marker;
    position = tile->pos();
}


