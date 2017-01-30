#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphicsscene.h"
#include <QDebug>
#include "mapview2.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView_2->setMouseTracking(true);

    curTool = "hand";
    // map view
    curMap = MapView2();
    GraphicsScene *scene = new GraphicsScene(this);
    curMap.displayMap(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

    // this is for the mini map
    ui->graphicsView_2->setScene(scene);
    ui->graphicsView_2->fitInView(0,0,256,192, Qt::KeepAspectRatio);
    ui->graphicsView_2->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(ui->actionOpen);
    menu.addAction(ui->actionSave);

    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

void MainWindow::mousePressEvent(QMouseEvent *event){

    if (event->button() == Qt::LeftButton ){
         statusBar()->showMessage("Left Click");
    }
    else if (event->button() == Qt::RightButton ){
        statusBar()->showMessage("Right Click");
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    statusBar()->showMessage(QString::number(event->x()) + ", " + QString::number(event->y()), 500);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton ){
        // something
    }
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::newFile()
{
    if (maybeSave()) {
        // fill tile here
    }

    // map view
    curMap = MapView2();
    GraphicsScene *scene = new GraphicsScene();
    curMap.displayMap(scene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

    // this is for the mini map
    ui->graphicsView_2->setScene(scene);
    ui->graphicsView_2->show();

    statusBar()->showMessage("New File created", 2000);
}

void MainWindow::open()
{
    QFileDialog dialog;
    dialog.setDirectory(QDir::home());
    if (maybeSave()) {
        QString fileName = dialog.getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }


    // load and display map and minimap

    QString mapName = fileName;
    QString texture = ":/data/img/Terrain.png";
    curMap = MapView2(mapName, texture);

    GraphicsScene *scene = new GraphicsScene();
    curMap.displayMap(scene);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView->show();

    ui->graphicsView_2->setScene(scene);
    ui->graphicsView_2->setMouseTracking(true);
    ui->graphicsView_2->show();


    setCurrentFile(fileName);
    statusBar()->showMessage(fileName + " loaded!", 2000);
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

bool MainWindow::maybeSave()
{
    //if (!ui->textEdit->document()->isModified()) return true;
    return true;
    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, tr("Application"),
                               tr("The document has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}

bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QFileDialog dialog(this);
    dialog.setDirectory(QDir::home());
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return false;
    return saveFile(dialog.selectedFiles().first());
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName),
                                  file.errorString()));
        return false;
    }

   QTextStream stream(&file);
   stream << curMap.getMapName() << endl;
   stream << curMap.getMapDim().width()-2 << " " << curMap.getMapDim().height()-2 << endl;

   QVector<QChar>::iterator itr;

   QVector<QChar> layout = curMap.getMapLayout();

   int i = 0;
   for (itr = layout.begin(); itr != layout.end(); itr++)
   {
       stream << *itr;
       i++;
       if (i == 98)
       {
           stream << endl;
           i = 0;
       }
   }

   QVector<Player> players = curMap.getPlayers();

   stream << curMap.getNumPlayers() << endl;

   for (auto iter = players.begin(); iter != players.end(); iter++) {
        stream << iter->num << " " << iter->gold << " " << iter->lumber << endl;
   }

   stream << curMap.getNumUnits() << endl;

   for (int i = 0; i < curMap.getNumPlayers() + 1; i++)
   {
       QVector<Unit> units = players[i].units;
       QVector<Unit>::iterator itr3;

       for (itr3 = units.begin(); itr3 != units.end(); itr3++)
       {
           stream << itr3->name << " " << i << " " << itr3->x << " " << itr3->y << endl;
       }
   }


   setCurrentFile(fileName);
   statusBar()->showMessage(tr("File saved"), 2000);
   return true;
}

void MainWindow::writeSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
}

void MainWindow::on_button_new_released()
{
    newFile();
}

void MainWindow::on_button_open_released()
{
    open();
}

void MainWindow::on_button_save_released()
{
    save();
}

void MainWindow::on_tool_grass_released()
{
    curTool = "grass";
    statusBar()->showMessage(tr("Grass tool selected"), 2000);
}

void MainWindow::on_tool_dirt_released()
{
    curTool = "dirt";
    statusBar()->showMessage(tr("Dirt tool selected"), 2000);
}

void MainWindow::on_tool_water_released()
{
    curTool = "water";
    statusBar()->showMessage(tr("Water tool selected"), 2000);
}
