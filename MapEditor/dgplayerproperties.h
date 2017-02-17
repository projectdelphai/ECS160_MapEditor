#ifndef DGPLAYERPROPERTIES_H
#define DGPLAYERPROPERTIES_H

#include <QDialog>

/* Name: dgplayerproperties.h
 * Class: DgPlayerProperties
 *
 * This file includes the class for the Player Properties dialog box.
 * Create an instance and then run exec()
 *
 */

namespace Ui {
class DgPlayerProperties;
}

class DgPlayerProperties : public QDialog
{
    Q_OBJECT

public:
    explicit DgPlayerProperties(QWidget *parent = 0);
    ~DgPlayerProperties();

private:
    Ui::DgPlayerProperties *ui;
};

#endif // DGPLAYERPROPERTIES_H
