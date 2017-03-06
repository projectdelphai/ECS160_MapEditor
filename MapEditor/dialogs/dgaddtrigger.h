#ifndef DGADDTRIGGER_H
#define DGADDTRIGGER_H

#include <QDialog>
#include <QDebug>
#include <QStringListModel>
#include "aitrigger.h"

namespace Ui {
class DgAddTrigger;
}

class DgAddTrigger : public QDialog
{
    Q_OBJECT

public:
    explicit DgAddTrigger(QWidget *parent = 0);
    ~DgAddTrigger();

    AITrigger* aiTrigger = 0;

    void accept();

private slots:
    void on_tool_addTrigArg_clicked();
    void on_tool_remTrigArg_clicked();
    void on_tool_addEventArg_clicked();
    void on_tool_remEventArg_clicked();

private:
    Ui::DgAddTrigger *ui;
    QStringListModel* trigArgsListModel;
    QStringListModel* eventArgsListModel;

    QString name;
    QString type;
    bool persistence;
    QStringList trigArgsList;
    QString event;
    QStringList eventArgsList;
};

#endif // DIALOGTRIGGER_H
