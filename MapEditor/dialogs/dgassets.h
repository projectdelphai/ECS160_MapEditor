#ifndef DGASSETS_H
#define DGASSETS_H

#include <QMainWindow>

/* Name: dgassets.h
 * Class: DgAssets
 *
 * This file includes the class for the Assets Editor window.
 * See MainWindow::open_DgAssets()
 *
 */

namespace Ui {
class DgAssets;
}

class DgAssets : public QMainWindow
{
    Q_OBJECT

public:
    explicit DgAssets(QWidget *parent = 0);
    ~DgAssets();

private:
    Ui::DgAssets *ui;
};

#endif // DGASSETS_H
