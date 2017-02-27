#include "dgassets.h"
#include "ui_dgassets.h"

DgAssets::DgAssets(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DgAssets)
{
    ui->setupUi(this);
}

DgAssets::~DgAssets()
{
    delete ui;
}
