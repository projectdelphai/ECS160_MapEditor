#include "dgplayerproperties.h"
#include "ui_dgplayerproperties.h"
#include <qdebug.h>
#include <QCloseEvent>

#define DEFAULT_VALUE 1000
#define DEFAULT_CONTROLLER 0

DgPlayerProperties::DgPlayerProperties(QWidget *parent, MapView2 &curMap) :
    QDialog(parent),
    ui(new Ui::DgPlayerProperties)
{
    ui->setupUi(this);

    DgPlayerProperties::curMap = &curMap;
    DgPlayerProperties::setupUI();

}

// set up UI based on what is currently available.
void DgPlayerProperties::setupUI() {
    // get UI info
    numPlayers = curMap->getNumPlayers();
    players = curMap->getPlayers();

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
                if(i <= numPlayers)
                    curIndex = players.at(i).type;
                ((QComboBox*)item->widget())->setCurrentIndex(curIndex);

            } else if(itemType == "QLineEdit") {
                QLineEdit* lineBox = (QLineEdit *)item->widget();
                QValidator* validator = new QIntValidator(0, 999999, this);
                int value = DEFAULT_VALUE;
                if(i <= numPlayers) {
                    if(c == 1) value = players.at(i).gold;
                    else if(c == 2) value = players.at(i).lumber;
                    else if(c == 3) value = players.at(i).stone;
                }

                lineBox->setText(QString::number(value));
                lineBox->setValidator(validator);
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

    for(int r = 2; r < row; r++ ) {
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

void DgPlayerProperties::on_buttonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::ButtonRole role = ui->buttonBox->buttonRole(button);

    if (role == QDialogButtonBox::ResetRole)
        DgPlayerProperties::setupUI();

    // other buttons will trigger QDialog::accept() or reject()
}


void DgPlayerProperties::accept() {
    // double check they want to commit changes
    if(numPlayers < curMap->getNumPlayers()) {
        const QMessageBox::StandardButton ret =
                   QMessageBox::warning(this, tr("Application"),
                   tr("You have reduced the amount of players.\n"
                      "This will remove all units of those players.\n"
                      "Are you sure you want to proceed?"),
                   QMessageBox::Save | QMessageBox::Cancel);

        if(ret == QMessageBox::Cancel) {
            //DgPlayerProperties::reject();
            return;
        }
    }

    DgPlayerProperties::commitChanges();
    QDialog::accept();
}

// store UI elements into the players vector
void DgPlayerProperties::commitChanges() {
    QVector<Player> new_players;

    int col = ui->gridLayout->columnCount();
    int row = ui->gridLayout->rowCount();

    // save UI elements
    for(int r = 2, i = 0; i <= numPlayers; r++, i++) {
        Player newPlayer;
        newPlayer.num = i;

        for(int c = 1; c < col; c++) {
            QLayoutItem* item = ui->gridLayout->itemAtPosition(r, c);
            if(!item) continue;

            QString itemType = item->widget()->metaObject()->className();

            if(itemType == "QComboBox") {
                int curIndex = ((QComboBox*)item->widget())->currentIndex();
                if(curIndex == Player::AI)
                    newPlayer.type = Player::AI;
                else
                    newPlayer.type = Player::Human;

            } else if(itemType == "QLineEdit") {
                QString lineBoxText = ((QLineEdit *)item->widget())->text();

                int value = lineBoxText.toInt();
                if(i <= numPlayers) {
                    if(c == 1) newPlayer.gold = value;
                    else if(c == 2) newPlayer.lumber = value;
                    else if(c == 3) newPlayer.stone = value;
                }
            } // if QLineEdit
        } // for every col

        new_players.append(newPlayer);
    } // for every row

    players = new_players;
}
