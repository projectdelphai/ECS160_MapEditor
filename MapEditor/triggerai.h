#ifndef TRIGGERAI_H
#define TRIGGERAI_H

#include <QString>
#include <QPoint>
#include <QTimer>
#include <QWidget>

class TriggerAI
{
public:
    TriggerAI(QString name);
    void setTimer(double);
    QString infoAI();
    void hook();
    void startTimer(QWidget *widget);




private:
    QString triggerName;
    QPoint position;
    double time;
    QTimer *timer;

};



#endif // TRIGGERAI_H
