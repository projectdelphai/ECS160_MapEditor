#ifndef TRIGGERAI_H
#define TRIGGERAI_H


class TriggerAI
{
public:
    TriggerAI();

    void setTimer(double);
    void writeAI();
private:
    QString triggerName;
    QPoint position;
    double time;
    void hook();

};



#endif // TRIGGERAI_H
