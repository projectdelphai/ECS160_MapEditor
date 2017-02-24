#include "triggerai.h"



TriggerAI::TriggerAI(QString name)
{
   triggerName = name;
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
    timer->start(time);
    QObject::connect(timer, SIGNAL(timeout()), widget, SLOT(update()));

}

void TriggerAI::hook(){

}
