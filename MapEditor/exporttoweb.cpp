#include "exporttoweb.h"
#include "ui_exporttoweb.h"

#include <QFileDialog>
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QTextStream>
#include <QFileInfo>

ExportToWeb::ExportToWeb(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportToWeb)
{
    ui->setupUi(this);
}

ExportToWeb::~ExportToWeb()
{
    delete ui;
}

void ExportToWeb::on_etwButton_clicked()
{
    // grab authentication details
    QString username = ui->etwUsername->text();

    QString password = ui->etwPassword->text();

    QString filename = ui->selectedMap->text();

    QFileInfo fileInfo(filename);
    QString basename = fileInfo.baseName();

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart usernamePart;
    usernamePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"username\""));
    usernamePart.setBody(username.toUtf8());

    QHttpPart passwordPart;
    passwordPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"password\""));
    passwordPart.setBody(password.toUtf8());


    QHttpPart mapPart;
    mapPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
    mapPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"mpk_file\"; filename=\"" + basename + "\""));
    QFile *file = new QFile(filename);
    file->open(QIODevice::ReadOnly);
    mapPart.setBodyDevice(file);
    file->setParent(multiPart);


    multiPart->append(usernamePart);
    multiPart->append(passwordPart);
    multiPart->append(mapPart);

    // Official site url
    //QUrl url("http://54.218.34.58/mapupload/");

    // Unofficial testing url
    QUrl url("http://24.10.17.214/mapupload/");

    QNetworkRequest request(url);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QNetworkReply *reply = manager->post(request, multiPart);
    multiPart->setParent(reply);

    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(replyError(QNetworkReply::NetworkError)));

}

void ExportToWeb::replyFinished(QNetworkReply *reply)
{
    ui->response->setText(reply->readAll());
}

void ExportToWeb::replyError(QNetworkReply::NetworkError e)
{
}

void ExportToWeb::on_selectFIle_clicked()
{
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setNameFilter(tr("Map Files (*.mpk)"));

    if(dialog.exec() != QDialog::Accepted)
        return;

    if(dialog.selectedFiles().first().split(".").last() == "mpk") {
        QFile file(dialog.selectedFiles().first());
        ui->selectedMap->setText(dialog.selectedFiles().first());
    }
}

void ExportToWeb::on_Close_clicked()
{

}
