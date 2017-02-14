#ifndef DGABOUT_H
#define DGABOUT_H

#include <QDialog>

namespace Ui {
class DgAbout;
}

class DgAbout : public QDialog
{
    Q_OBJECT

public:
    explicit DgAbout(QWidget *parent = 0);
    ~DgAbout();

private:
    Ui::DgAbout *ui;
};

#endif // DGABOUT_H
