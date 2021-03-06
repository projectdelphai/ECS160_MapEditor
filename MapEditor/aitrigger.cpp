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
    QString ai = triggerName + "," +
                 type + "," +
                 QString::number(persistence) + "," +
                 trigArgsList.join(',') + "," +
                 event + "," +
                 eventArgsList.join(',');
    return ai;
}

// gets
Tile* AITrigger::getTile(){
    return tile;
}

QString AITrigger::getType(){
    return type;
}

QPoint* AITrigger::getPos(){
    if(type != "TriggerTypeLocation") return 0;
    QPoint* pos = new QPoint(trigArgsList.front().toInt(), trigArgsList.back().toInt());
    return pos;
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
    tile->setPos(position);
}

void AITrigger::setEvent(QString &func) {
    event = func;
}

void AITrigger::setTrigArgsList(QStringList &list) {
    trigArgsList = list;
}

void AITrigger::setEventArgsList(QStringList &list) {
    eventArgsList = list;
}

void AITrigger::setTile(Tile *marker){
    tile = marker;
    position = tile->pos();
}


