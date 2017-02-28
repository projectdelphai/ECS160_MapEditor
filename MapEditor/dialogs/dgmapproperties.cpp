#include "dgmapproperties.h"
#include "ui_dgmapproperties.h"

DgMapProperties::DgMapProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DgMapProperties)
{
    ui->setupUi(this);
}

DgMapProperties::~DgMapProperties()
{
    delete ui;
}

void DgMapProperties::on_buttonBox_accepted()
{

}
