#ifndef NEWPROJECT_H
#define NEWPROJECT_H

#include <QWidget>

namespace Ui {
class newproject;
}

class newproject : public QWidget
{
    Q_OBJECT

public:
    explicit newproject(QWidget *parent = 0);
    ~newproject();

signals:
    void changeProjectName(QString projectName);

private slots:
    void on_confirmProject_clicked();

private:
    Ui::newproject *ui;
};

#endif // NEWPROJECT_H
