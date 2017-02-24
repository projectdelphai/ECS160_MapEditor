#include "dialogtrigger.h"
#include "ui_dialogtrigger.h"

DialogTrigger::DialogTrigger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTrigger)
{
    ui->setupUi(this);
}

DialogTrigger::~DialogTrigger()
{
    delete ui;
}
