#include "dgaddtrigger.h"
#include "ui_dgaddtrigger.h"
#include "aitrigger.h"

DgAddTrigger::DgAddTrigger(Tile *t, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DgAddTrigger)
{
    ui->setupUi(this);
    DgAddTrigger::tile = t;

    // setup list views with their models
    QStringList trigArgsList;
    trigArgsList << "trigArg1" << "trigArg2";
    trigArgsListModel = new QStringListModel(trigArgsList);
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
    eventArgsList = eventArgsListModel->stringList();

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
    aiTrigger->setTile(tile);
    QDialog::accept();
}

// for adding new conditions, update listModel and then do some View stuff
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

void DgAddTrigger::on_tool_curLocation_clicked()
{
    if(QMessageBox::question(this, "", "Are you sure you want to set the current location as the trigger arguments?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
        return;

    QStringList newList;
    newList << QString::number(tile->pos().x()/32) << QString::number(tile->pos().y()/32);
    trigArgsListModel->setStringList(newList);
}
