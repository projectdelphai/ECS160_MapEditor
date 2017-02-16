#include "dgabout.h"
#include "ui_dgabout.h"

DgAbout::DgAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DgAbout)
{
    ui->setupUi(this);
}

DgAbout::~DgAbout()
{
    delete ui;
}
