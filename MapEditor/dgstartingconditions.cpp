#include "dgstartingconditions.h"
#include "ui_dgstartingconditions.h"

DgStartingConditions::DgStartingConditions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DgStartingConditions)
{
    ui->setupUi(this);
}

DgStartingConditions::~DgStartingConditions()
{
    delete ui;
}
