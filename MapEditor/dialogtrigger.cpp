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

void DialogTrigger::on_lineEdit_textChanged(const QString &arg1)
{
    textLine1 = arg1;
}

void DialogTrigger::on_lineEdit_2_textEdited(const QString &arg1)
{
    qDebug() << "edit";
//    QLineEdit * lineText = new QLineEdit(this);
    textLine2 = arg1;
}

