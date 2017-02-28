#ifndef DGABOUT_H
#define DGABOUT_H

#include <QDialog>

/* Name: dgabout.h
 * Class: DgAbout
 *
 * This file includes the class for the About dialog box.
 * Create an instance and then run exec()
 *
 */


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
