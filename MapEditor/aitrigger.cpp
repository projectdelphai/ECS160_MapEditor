#include "aitrigger.h"


AITrigger::AITrigger(QString name)
{
   triggerName = name;
   radius = 100;
}

QString AITrigger::infoAI() const{
    QString ai = triggerName + " " + QString().setNum(position.x()) + " " + QString().setNum(position.y()) + " " + QString().setNum(time);
    return ai;
}

void AITrigger::setTimer(double setTime){
    time = setTime;
}

void AITrigger::startTimer(QWidget *widget){
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), widget, SLOT(activateAI()));
    timer->start(time);
    timer->setSingleShot(true);

}

void AITrigger::setRange(double rangeR){
    if(rangeR <= 0){
        radius = 100;
    }
    else{
        radius = rangeR;
    }

}

void AITrigger::setCondition(QString &cond) {
    condition = cond;
}

void AITrigger::setTriggerFunction(QString &trig) {
    triggerFunction = trig;
}

void AITrigger::setType(QString &type){
    triggerType = type;
}

void AITrigger::displayRange(QGraphicsScene * scene){
    circleRange = new QGraphicsEllipseItem( position.x()-32,position.y()-32,radius,radius);
    circleRange->setStartAngle(0);
    circleRange->setSpanAngle(360*16);

    circleRange->setBrush(QBrush(QColor(128, 128, 255, 128)));
    circleRange->setZValue(100);
    scene->addItem(circleRange);
}

void AITrigger::removeRange(QGraphicsScene *scene){
    scene->removeItem(circleRange);
}

void AITrigger::hook(){
    qDebug() << "hell";
}

void AITrigger::setMarker(Tile *marker){
    tile = marker;
    position = tile->pos();
}

Tile* AITrigger::getMarker(){
    return tile;
}

bool AITrigger::isRangeOn(){
    bool init = false;
    if (  circleRange != 0 ){
        init = true;
    }
    return init;
}
