#ifndef EXPORTTOWEB_H
#define EXPORTTOWEB_H

#include <QDialog>
#include <QNetworkReply>

namespace Ui {
class ExportToWeb;
}

class ExportToWeb : public QDialog
{
    Q_OBJECT

public:
    explicit ExportToWeb(QWidget *parent = 0);
    ~ExportToWeb();
    QNetworkReply *reply;

public slots:
    void replyFinished(QNetworkReply *);
    void replyError(QNetworkReply::NetworkError e);

private slots:
    void on_etwButton_clicked();

    void on_selectFIle_clicked();



    void on_Close_clicked();

private:
    Ui::ExportToWeb *ui;
};

#endif // EXPORTTOWEB_H
