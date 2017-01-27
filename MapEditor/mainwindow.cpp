#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphicsscene.h"
#include <QDebug>



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // map view
    QString mapName = ":/data/map/maze.map";
    QString texture = ":/data/img/Terrain.png";
    MapView2 map(mapName, texture);

    GraphicsScene *scene = new GraphicsScene();
    map.displayMap(scene);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView->show();

    ui->graphicsView_2->setScene(scene);
    ui->graphicsView_2->fitInView(0, 0, 256, 192, Qt::KeepAspectRatioByExpanding);
    ui->graphicsView_2->setMouseTracking(true);
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


//    QString mapName = fileName;
//    QString texture = fileName;

//    Texture tx(texture);

//    QImage imageDx = tx.createImageTile(&tx.fullImage, tx.tileDim);
//    QPixmap pixmap = QPixmap::fromImage(imageDx);

//    QGraphicsScene* scene = new QGraphicsScene();
//    scene->addPixmap(pixmap);

//    ui->graphicsView->setMouseTracking(true);
//    ui->graphicsView->setScene(scene);
//    ui->graphicsView->show();

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

   // stuff happens here

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
