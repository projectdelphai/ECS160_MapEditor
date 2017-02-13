#ifndef DGMAPPROPERTIES_H
#define DGMAPPROPERTIES_H

#include <QDialog>

namespace Ui {
class DgMapProperties;
}

class DgMapProperties : public QDialog
{
    Q_OBJECT

public:
    explicit DgMapProperties(QWidget *parent = 0);
    ~DgMapProperties();

private:
    Ui::DgMapProperties *ui;
};

#endif // DGMAPPROPERTIES_H
