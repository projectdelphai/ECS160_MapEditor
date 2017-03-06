#include "newfile.h"
#include "ui_newfile.h"
#include "QDir"
#include "QString"
#include "QFile"

NewFile::NewFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFile)
{
    ui->setupUi(this);
}

NewFile::~NewFile()
{
    delete ui;
}

void NewFile::on_testValid_clicked()
{
    QString newProjectName = ui->newFileName->text();

    QDir dir(QDir::currentPath() + "/" + newProjectName);

    if (dir.exists())
    {
        ui->validStatus->setText("Valid Status: Folder already exists, try again");
    }
    else
    {
        ui->validStatus->setText("Valid Status: Folder valid to create");
        ui->accept->setEnabled(true);
    }
}

void NewFile::on_accept_accepted()
{
    QString newProjectName = ui->newFileName->text();

    QDir dir(QDir::currentPath() + "/" + newProjectName);

    QDir imgDir(QDir::currentPath() + "/" + newProjectName + "/img");
    QDir resDir(QDir::currentPath() + "/" + newProjectName + "/res");
    QDir sndDir(QDir::currentPath() + "/" + newProjectName + "/snd");
    QDir upgDir(QDir::currentPath() + "/" + newProjectName + "/upg");

    dir.mkpath(".");
    imgDir.mkpath(".");
    resDir.mkpath(".");
    sndDir.mkpath(".");
    upgDir.mkpath(".");

    foreach (const QString &img, QDir(":data/default/img/").entryList() )
    {
        QFile::copy(":/data/default/img/" + img, imgDir.path() + "/" + img);
    }

    foreach (const QString &snd, QDir(":data/default/snd/").entryList() )
    {
        QFile::copy(":/data/default/snd/" + snd, sndDir.path() + "/" + snd);
    }



    emit changeProjectName(dir.path());
}

bool NewFile::copy_dir_recursive(QString from_dir, QString to_dir, bool replace_on_conflit)
{

}
