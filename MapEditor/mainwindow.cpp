#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);

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
         qDebug() << event->pos();
    }
    else if (event->button() == Qt::RightButton ){
         qDebug() << event->pos();
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

void MainWindow::resizeEvent(QResizeEvent *event)
{
    // On the event of resizing the main window
    // resize the graphicsview to match the main window

    if ( ui->graphicsView->width() < ui->centralWidget->width() || ui->graphicsView->width() > ui->centralWidget->width()
         || ui->graphicsView->height() < ui->centralWidget->height() || ui->graphicsView->height() > ui->centralWidget->height() ){

        int newWidth =  ui->centralWidget->width();
        int newHeight = ui->centralWidget->height();
        ui->graphicsView->resize(newWidth,newHeight);
    //  update();
    }
    QWidget::resizeEvent(event);
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

void MainWindow::on_actionOpen_triggered()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}


bool MainWindow::maybeSave()
{
    //if (!ui->textEdit->document()->isModified()) return true;
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

void MainWindow::on_actionSave_triggered()
{
    save();
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

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    // stuff happens here

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

