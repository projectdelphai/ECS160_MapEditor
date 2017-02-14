#ifndef DGPLAYERPROPERTIES_H
#define DGPLAYERPROPERTIES_H

#include <QDialog>

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
