#include "triggerai.h"



TriggerAI::TriggerAI(QString name)
{
   triggerName = name;
   radius = 100;
}

QString TriggerAI::infoAI() const{
    QString ai = triggerName + " " + QString().setNum(position.x()) + " " + QString().setNum(position.y()) + " " + QString().setNum(time);
    return ai;
}

void TriggerAI::setTimer(double setTime){
    time = setTime;
}

void TriggerAI::startTimer(QWidget *widget){
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), widget, SLOT(activateAI()));
    timer->start(time);
    timer->setSingleShot(true);

}

void TriggerAI::setRange(double rangeR){
    if(rangeR <= 0){
        radius = 100;
    }
    else{
        radius = rangeR;
    }

}

void TriggerAI::displayRange(QGraphicsScene * scene){
    circleRange = new QGraphicsEllipseItem( position.x()-32,position.y()-32,radius,radius);
    circleRange->setStartAngle(0);
    circleRange->setSpanAngle(360*16);

    circleRange->setBrush(QBrush(QColor(128, 128, 255, 128)));
    circleRange->setZValue(100);
    scene->addItem(circleRange);
}

void TriggerAI::removeRange(QGraphicsScene *scene){
    scene->removeItem(circleRange);
}

void TriggerAI::hook(){
    qDebug() << "hell";
}

void TriggerAI::setMarker(Tile *marker){
    tile = marker;
    position = tile->pos();
}

Tile* TriggerAI::getMarker(){
    return tile;
}

bool TriggerAI::isRangeOn(){
    bool init = false;
    if (  circleRange != 0 ){
        init = true;
    }
    return init;
}
