#include "dgaddtrigger.h"
#include "ui_dgaddtrigger.h"
#include "aitrigger.h"

DgAddTrigger::DgAddTrigger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DgAddTrigger)
{
    ui->setupUi(this);

    // setup list views with their models
    trigArgsListModel = new QStringListModel;
    ui->list_trigArgs->setModel(trigArgsListModel);
    eventArgsListModel = new QStringListModel;
    ui->list_eventArgs->setModel(eventArgsListModel);
}

DgAddTrigger::~DgAddTrigger()
{
    delete ui;
}

// before accepting, check text parameters
void DgAddTrigger::accept() {
    // save the easy ones first
    name = ui->txt_name->text();
    type = "TriggerType" + ui->select_type->currentText().remove(" "); // removes all spaces
    persistence = ui->check_persistence->isChecked();
    event = ui->txt_event->text();

    trigArgsList = trigArgsListModel->stringList();
    eventArgsList = trigArgsListModel->stringList();

    if(name.isEmpty()) {
        QMessageBox::warning(this, "Needs a name", "Must have a trigger name!", QMessageBox::Ok);
        ui->txt_name->setFocus();
        return;
    } else if(type == "TriggerType") {
        QMessageBox::warning(this, "Needs a type", "Must have a type!", QMessageBox::Ok);
        ui->txt_event->setFocus();
        return;
    } else if(event.isEmpty()) {
        QMessageBox::warning(this, "Needs a trigger", "Must have an event function!", QMessageBox::Ok);
        ui->txt_event->setFocus();
        return;
    }

    if(true) {
        qDebug() << name;
        qDebug() << type;
        qDebug() << persistence;
        qDebug() << event;
        qDebug() << trigArgsList;
        qDebug() << eventArgsList;
    }

    aiTrigger = new AITrigger(name, type, persistence, event, trigArgsList, eventArgsList);
    QDialog::accept();
}

// for adding new conditions, update listModel and then do some View stuff
void DgAddTrigger::on_tool_addTrigArg_clicked()
{
    trigArgsListModel->insertRow(trigArgsListModel->rowCount());

    QModelIndex index = trigArgsListModel->index(trigArgsListModel->rowCount()-1);
    trigArgsListModel->setData(index, "TrigArg" + QString::number(index.row()) );
    ui->list_trigArgs->setFocus();
    ui->list_trigArgs->setCurrentIndex(index);
    ui->list_trigArgs->edit(index);
}

void DgAddTrigger::on_tool_remTrigArg_clicked()
{
    QModelIndex index = ui->list_trigArgs->currentIndex();

    trigArgsListModel->removeRow(index.row());
    ui->list_trigArgs->setFocus();
}

void DgAddTrigger::on_tool_addEventArg_clicked()
{
    eventArgsListModel->insertRow(eventArgsListModel->rowCount());

    QModelIndex index = eventArgsListModel->index(eventArgsListModel->rowCount()-1);
    eventArgsListModel->setData(index, "EventArg" + QString::number(index.row()) );
    ui->list_eventArgs->setFocus();
    ui->list_eventArgs->setCurrentIndex(index);
    ui->list_eventArgs->edit(index);
}

void DgAddTrigger::on_tool_remEventArg_clicked()
{
    QModelIndex index = ui->list_eventArgs->currentIndex();

    eventArgsListModel->removeRow(index.row());
    ui->list_eventArgs->setFocus();
}
