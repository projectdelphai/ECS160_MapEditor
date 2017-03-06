#include "newproject.h"
#include "ui_newproject.h"

newproject::newproject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newproject)
{
    ui->setupUi(this);
}

newproject::~newproject()
{
    delete ui;
}

void newproject::on_confirmProject_clicked()
{

    emit changeProjectName(ui->newProjectName->text());
    this->close();
}
