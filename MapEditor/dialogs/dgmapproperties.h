#ifndef DGMAPPROPERTIES_H
#define DGMAPPROPERTIES_H

#include <QDialog>

/* Name: dgmapproperties.h
 * Class: DgMapProperties
 *
 * This file includes the class for the Map Properties dialog box.
 * Create an instance and then run exec()
 *
 */

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
