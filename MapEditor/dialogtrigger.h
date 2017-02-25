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
    QString textLine1;
    QString textLine2;

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);



private:
    Ui::DialogTrigger *ui;

};

#endif // DIALOGTRIGGER_H
