#ifndef NEWFILE_H
#define NEWFILE_H

#include <QDialog>

namespace Ui {
class NewFile;
}

class NewFile : public QDialog
{
    Q_OBJECT

public:
    explicit NewFile(QWidget *parent = 0);
    ~NewFile();

signals:
    void changeProjectName(QString projectName);

private slots:

    void on_testValid_clicked();

    void on_accept_accepted();

private:
    Ui::NewFile *ui;
    bool copy_dir_recursive(QString from_dir, QString to_dir, bool replace_on_conflit);
};

#endif // NEWFILE_H
