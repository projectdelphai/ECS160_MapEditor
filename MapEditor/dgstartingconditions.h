#ifndef DGSTARTINGCONDITIONS_H
#define DGSTARTINGCONDITIONS_H

#include <QDialog>

namespace Ui {
class DgStartingConditions;
}

class DgStartingConditions : public QDialog
{
    Q_OBJECT

public:
    explicit DgStartingConditions(QWidget *parent = 0);
    ~DgStartingConditions();

private:
    Ui::DgStartingConditions *ui;
};

#endif // DGSTARTINGCONDITIONS_H
