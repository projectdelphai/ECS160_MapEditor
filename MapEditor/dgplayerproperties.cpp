#include "dgplayerproperties.h"
#include "ui_dgplayerproperties.h"

DgPlayerProperties::DgPlayerProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DgPlayerProperties)
{
    ui->setupUi(this);
}

DgPlayerProperties::~DgPlayerProperties()
{
    delete ui;
}
