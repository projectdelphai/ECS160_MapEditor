#ifndef DGPLAYERPROPERTIES_H
#define DGPLAYERPROPERTIES_H

#include <QDialog>
#include "mapview2.h"

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
    explicit DgPlayerProperties(QWidget *parent, MapView2 &curMap);
    ~DgPlayerProperties();


private slots:
    void on_select_players_currentTextChanged(const QString &arg1);

private:
    Ui::DgPlayerProperties *ui;
    void setupUI();
    QVector<Player> players;
    int numPlayers;
};

// helper class to implement setText()
class Widget : private QWidget
{
public:
    Widget(QWidget *parent = 0) : QWidget(parent) {

    }

    virtual void setText(const QString &);

};

#endif // DGPLAYERPROPERTIES_H
