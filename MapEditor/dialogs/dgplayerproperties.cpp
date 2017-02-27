#include "dgplayerproperties.h"
#include "ui_dgplayerproperties.h"
#include <qdebug.h>

#define DEFAULT_VALUE 1000
#define DEFAULT_CONTROLLER 0

DgPlayerProperties::DgPlayerProperties(QWidget *parent, MapView2 &curMap) :
    QDialog(parent),
    ui(new Ui::DgPlayerProperties)
{
    numPlayers = curMap.getNumPlayers();
    players = curMap.getPlayers();

    ui->setupUi(this);
    DgPlayerProperties::setupUI();


}

// set up UI based on what is currently available.
void DgPlayerProperties::setupUI() {
    // get UI info
    int col = ui->gridLayout->columnCount();
    int row = ui->gridLayout->rowCount();

    // fill out with defaults, then fill out with current values
    for(int r = 2, i = 0; r < row; r++, i++) {
        for(int c = 1; c < col; c++) {
            QLayoutItem* item = ui->gridLayout->itemAtPosition(r, c);
            if(!item) continue;

            QString itemType = item->widget()->metaObject()->className();

            if(itemType == "QComboBox") {
                int curIndex = 0;
                if(i <= numPlayers) {
                    curIndex = players.at(i).type;
                }

                ((QComboBox*)item->widget())->setCurrentIndex(curIndex);

            } else if(itemType == "QLineEdit") {
                QLineEdit* lineBox = (QLineEdit *)item->widget();

                int value = DEFAULT_VALUE;
                if(i <= numPlayers) {
                    if(c == 1) value = players.at(i).gold;
                    else if(c == 2) value = players.at(i).lumber;
                    else if(c == 3) value = players.at(i).stone;
                }

                lineBox->setText(QString::number(value));
            } // if QLineEdit

        } // for every col
    } // for every row


    // set players spin box to numPlayers (which disables unused ones)
    int curIndex = ui->select_players->findText(QString::number(numPlayers));
    ui->select_players->setCurrentIndex(curIndex);

    on_select_players_currentTextChanged( QString::number(numPlayers) );

}

DgPlayerProperties::~DgPlayerProperties()
{
    delete ui;
}

// when this changes, disable UI element for player > arg1
void DgPlayerProperties::on_select_players_currentTextChanged(const QString &arg1)
{
    numPlayers = arg1.toInt();
    int col = ui->gridLayout->columnCount();
    int row = ui->gridLayout->rowCount();

    for(int r = 0; r < row; r++ ) {
        for(int c = 0; c < col; c++) {
            QLayoutItem* item = ui->gridLayout->itemAtPosition(r, c);
            if( !item ) break;

            // re-enable
            item->widget()->setEnabled(true);

            // then disable
            if(r > numPlayers + 2 )
                item->widget()->setDisabled(true);

        } // for each row
    } // for each col
}
