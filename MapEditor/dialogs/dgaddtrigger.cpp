#include "dgaddtrigger.h"
#include "ui_dgaddtrigger.h"
#include "aitrigger.h"

DgAddTrigger::DgAddTrigger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DgAddTrigger)
{
    ui->setupUi(this);

    QValidator* minsValid = new QIntValidator(0, 255, this);
    QValidator* secsValid = new QIntValidator(0, 59, this);

    ui->txt_min->setValidator(minsValid);
    ui->txt_sec->setValidator(secsValid);
}

DgAddTrigger::~DgAddTrigger()
{
    delete ui;
}

void DgAddTrigger::accept() {
    name = ui->txt_name->text();
    type = ui->txt_type->currentText();
    time = ui->txt_min->text().toInt() * 60 + ui->txt_sec->text().toInt();
    condition = "{" + ui->txt_condition->text() + "}";
    trigger = ui->txt_trigger->text();

    if(name.isEmpty() || type.isEmpty()) {
        QMessageBox::warning(this, "Needs a name", "Please fill out name and type", QMessageBox::Ok);
        return;
    }

    QDialog::accept();
}
