#ifndef DGADDTRIGGER_H
#define DGADDTRIGGER_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class DgAddTrigger;
}

class DgAddTrigger : public QDialog
{
    Q_OBJECT

public:
    explicit DgAddTrigger(QWidget *parent = 0);
    ~DgAddTrigger();

    QString name;
    int time;
    QString condition;
    QString trigger;
    QString type;

    void accept();

private:
    Ui::DgAddTrigger *ui;

};

#endif // DIALOGTRIGGER_H
