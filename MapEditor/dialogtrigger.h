#ifndef DIALOGTRIGGER_H
#define DIALOGTRIGGER_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class DialogTrigger;
}

class DialogTrigger : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTrigger(QWidget *parent = 0);
    ~DialogTrigger();

    QString name;
    int time;
    QString condition;
    QString trigger;

    void accept();

private:
    Ui::DialogTrigger *ui;

};

#endif // DIALOGTRIGGER_H
