#ifndef DIALOGTRIGGER_H
#define DIALOGTRIGGER_H

#include <QDialog>

namespace Ui {
class DialogTrigger;
}

class DialogTrigger : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTrigger(QWidget *parent = 0);
    ~DialogTrigger();

private:
    Ui::DialogTrigger *ui;
};

#endif // DIALOGTRIGGER_H
