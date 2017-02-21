#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphicsscene.h"
#include <QDebug>
#include "mapview2.h"

#include "dgabout.h"
#include "dgmapproperties.h"
#include "dgplayerproperties.h"
#include "dgassets.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // set up UI elements
    ui->setupUi(this);
    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView_2->setMouseTracking(true);
    curTool = "hand";

    // Load and display a new file
    MainWindow::newFile();
    MainWindow::updateUI();

    // resize minimap
    ui->graphicsView_2->fitInView(0,0,256,192, Qt::KeepAspectRatio);

    // connect signals and slots
    QObject::connect(scene, &GraphicsScene::changedLayout, this, &MainWindow::changeLayout);
    QObject::connect(scene, &GraphicsScene::changedAsset, this, &MainWindow::changeAsset);

    // default values
    curPlayer = 1;
    scene->curPlayer = 1;

}

MainWindow::~MainWindow()
{
    delete ui;
}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    if( event ) {

    }
    /*QMenu menu(this);
    menu.addAction(ui->actionOpen);
    menu.addAction(ui->actionSave);

    menu.exec(event->globalPos());
    */
}
#endif // QT_NO_CONTEXTMENU

void MainWindow::mousePressEvent(QMouseEvent *event){

    if (event->button() == Qt::LeftButton ){
         //statusBar()->showMessage("Left Click");
    }
    /*else if (event->button() == Qt::RightButton ){
        statusBar()->showMessage("Right Click");
    }*/
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton ){
         // something
    }
    //statusBar()->showMessage(QString::number(event->x()) + ", " + QString::number(event->y()), 500);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton ){
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

    // Set up the map grid
    curMap = MapView2();
    scene = new GraphicsScene(this, &curMap);
    curMap.displayMap(scene);

    // show map + minimap
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    ui->graphicsView_2->setScene(scene);
    ui->graphicsView_2->show();

    // update status
    on_tool_grass_clicked();
    statusBar()->showMessage("New File created", 2000);
}

bool MainWindow::open()
{
    QFileDialog dialog(this);
    dialog.restoreState(curFileDialogState);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setNameFilter(tr("Map Files (*.map)"));
    if (!maybeSave())
        return false;
    if(dialog.exec() != QDialog::Accepted)
        return false;
    curFileDialogState = dialog.saveState();
    return loadFile(dialog.selectedFiles().first());
}

bool MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return false;
    }


    // load and display map and minimap

    QString mapName = fileName;
    QString texture = ":/data/img/Terrain.png";
    curMap = MapView2(mapName, texture);

    scene = new GraphicsScene(this, &curMap);
    curMap.displayMap(scene);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView->show();

    ui->graphicsView_2->setScene(scene);
    ui->graphicsView_2->setMouseTracking(true);
    ui->graphicsView_2->show();

    // connect signals and slots
    QObject::connect(scene, &GraphicsScene::changedLayout, this, &MainWindow::changeLayout);
    QObject::connect(scene, &GraphicsScene::changedAsset, this, &MainWindow::changeAsset);

    setCurrentFile(fileName);
    statusBar()->showMessage(fileName + " loaded!", 2000);

    curPlayer = 1;
    scene->curPlayer = 1;

    return true;
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
    if (curFile.isEmpty()) { // set file to save to
        if (!setSaveFile(&curFile)) // if fails
            return false;
    }

    return saveFile(curFile);
}

void MainWindow::saveAs() {
    if (!setSaveFile(&curFile)) return;
    saveFile(curFile);
}

bool MainWindow::setSaveFile(QString* fileName)
{
    if (curMap.getPlayers().size() < 3)
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Not enough players")
                             );
        return false;
    }

    QFileDialog dialog(this);
    dialog.restoreState(curFileDialogState);
    dialog.setDirectory(curPath);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return false;
    curFileDialogState = dialog.saveState();

    *fileName = dialog.selectedFiles().first();
    return true;
}

bool MainWindow::saveFile(const QString &fileName)
{
    // check if able to write to file
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName),
                                  file.errorString()));
        return false;
    }

   // write map file
   writeMapFile(&file);
   file.close();

   setCurrentFile(fileName);
   statusBar()->showMessage(tr("File saved"), 2000);
   return true;
}

// this function takes an **opened** map file, writes everything that goes inside
void MainWindow::writeMapFile(QIODevice *file){

    QTextStream stream(file);

    // write descriptive properties
    stream << curMap.getMapName() << endl;
    stream << curMap.getMapDim().width()-2 << " " << curMap.getMapDim().height()-2 << endl;
    stream << "description" << endl;
    stream << "General" << endl;

    QVector<QChar>::iterator itr;

    QVector<QChar> layout = curMap.getMapLayout();

    // write out layout
    int x = 0;
    for (itr = layout.begin(); itr != layout.end(); itr++)
    {
        stream << *itr;
        x++;
        if (x == curMap.getMapDim().width())
        {
            stream << endl;
            x = 0;
        }
    }

    // write players
    QVector<Player> players = curMap.getPlayers();

    stream << curMap.getNumPlayers() << endl;

    for (auto iter = players.begin(); iter != players.end(); iter++) {
         stream << iter->num << " " << iter->gold << " " << iter->lumber << endl;
    }

    stream << curMap.getNumUnits() << endl;

    for (int t = 0; t < curMap.getPlayers().size(); t++)
    {
        QVector<Unit> units = players[t].units;
        QVector<Unit>::iterator itr3;

        for (itr3 = units.begin(); itr3 != units.end(); itr3++)
        {
            stream << itr3->name << " " << t << " " << itr3->x << " " << itr3->y << endl;
        }
    }
}

// this function saves all assets and stores them inside a zip file
void MainWindow::exportPkg()
{
    QString pkgFileName;
    // set file to save to
    if (!setSaveFile(&pkgFileName))
        return;

    // pkgFileName contains full path; eg. "Users/felix/Desktop/test.map"
    QFile pkgFile(pkgFileName);
    if (!pkgFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(pkgFileName),
                                  pkgFile.errorString()));
        return;
    }

    QuaZip qz(pkgFileName);
    qz.open(QuaZip::mdCreate);

    // populate zip file with empty folders
    QuaZipFile qzf(&qz);
    qzf.open(QIODevice::WriteOnly, QuaZipNewInfo("/img/")); qzf.close();
    qzf.open(QIODevice::WriteOnly, QuaZipNewInfo("/res/")); qzf.close();
    qzf.open(QIODevice::WriteOnly, QuaZipNewInfo("/snd/")); qzf.close();
    qzf.open(QIODevice::WriteOnly, QuaZipNewInfo("/upg/")); qzf.close();

    // create map file
    qzf.open(QIODevice::WriteOnly, QuaZipNewInfo("map.map")); // main.map
        writeMapFile(&qzf);
    qzf.close();

    qz.close();
}


void MainWindow::writeSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
}

// This function sets up all the UI buttons depending on what map is loaded
void MainWindow::updateUI() {
    // zoom slider and buttons in statusbar
    QToolButton *zMinus = new QToolButton();
    zMinus->setIcon(QIcon(":/toolbar/icons/toolbar/tool_zoom-.bmp"));
    zMinus->setIconSize(QSize(16,16));
    zMinus->setStyleSheet("padding: 0px; border: 1px; margin: 0px;");
    ui->statusBar->addPermanentWidget(zMinus);

    QSlider *zSlider = new QSlider(Qt::Horizontal);
    zSlider->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    zSlider->setStyleSheet("padding: 0px; border: 0px; margin: 0px;");
    ui->statusBar->addPermanentWidget(zSlider);

    QToolButton *zPlus = new QToolButton();
    zPlus->setIcon(QIcon(":/toolbar/icons/toolbar/tool_zoom+.bmp"));
    zPlus->setIconSize(QSize(16,16));
    zPlus->setStyleSheet("padding: 0px; border: 1px; margin: 0px;");
    ui->statusBar->addPermanentWidget(zPlus);

    // terrain buttons
    ui->tool_grass->setIcon(curMap.getTerrain()->getPixTile(Terrain::Grass));
    ui->tool_dirt->setIcon(curMap.getTerrain()->getPixTile(Terrain::Dirt));
    ui->tool_water->setIcon(curMap.getTerrain()->getPixTile(Terrain::Water));
    ui->tool_tree->setIcon(curMap.getTerrain()->getPixTile(Terrain::Tree));
    ui->tool_rock->setIcon(curMap.getTerrain()->getPixTile(Terrain::Rock));
    ui->tool_wall->setIcon(curMap.getTerrain()->getPixTile(Terrain::Wall));
    ui->tool_rubble->setIcon(curMap.getTerrain()->getPixTile(Terrain::Rubble));

    // player color buttons
    ui->tool_p1->setIcon(curMap.getButtonColorsTx()->getPixTile("blue-light").scaled(16,16));
    ui->tool_p2->setIcon(curMap.getButtonColorsTx()->getPixTile("red-light").scaled(16,16));
    ui->tool_p3->setIcon(curMap.getButtonColorsTx()->getPixTile("green-light").scaled(16,16));
    ui->tool_p4->setIcon(curMap.getButtonColorsTx()->getPixTile("purple-light").scaled(16,16));
    ui->tool_p5->setIcon(curMap.getButtonColorsTx()->getPixTile("orange-light").scaled(16,16));
    ui->tool_p6->setIcon(curMap.getButtonColorsTx()->getPixTile("yellow-light").scaled(16,16));
    ui->tool_p7->setIcon(curMap.getButtonColorsTx()->getPixTile("black-light").scaled(16,16));
    ui->tool_p8->setIcon(curMap.getButtonColorsTx()->getPixTile("white-light").scaled(16,16));

    // unit buttons
    ui->tool_peasant1->setIcon(curMap.getButtonIconsTx()->getPixTile("peasant"));
    ui->tool_archer->setIcon(curMap.getButtonIconsTx()->getPixTile("archer"));
    ui->tool_knight->setIcon(curMap.getButtonIconsTx()->getPixTile("knight"));

    // building buttons
    ui->tool_townhall1->setIcon(curMap.getButtonIconsTx()->getPixTile("town-hall"));
    ui->tool_smith->setIcon(curMap.getButtonIconsTx()->getPixTile("human-blacksmith"));
    ui->tool_farm->setIcon(curMap.getButtonIconsTx()->getPixTile("chicken-farm"));
    ui->tool_mill->setIcon(curMap.getButtonIconsTx()->getPixTile("human-lumber-mill"));
    ui->tool_keep->setIcon(curMap.getButtonIconsTx()->getPixTile("keep"));
    ui->tool_castle->setIcon(curMap.getButtonIconsTx()->getPixTile("castle"));
    ui->tool_barracks->setIcon(curMap.getButtonIconsTx()->getPixTile("human-barracks"));
    ui->tool_tower->setIcon(curMap.getButtonIconsTx()->getPixTile("human-guard-tower"));
    ui->tool_goldmine->setIcon(curMap.getButtonIconsTx()->getPixTile("gold-mine"));
}


// reference  http://www.qtcentre.org/threads/52603-Zoom-effect-by-mouse-Wheel-in-QGraphicsview
void MainWindow::wheelEvent(QWheelEvent *event)
{
    if( (event->modifiers() & Qt::ControlModifier) && event->orientation() == Qt::Vertical )  // if ctrl is held down
    {
        ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        static const double scaleFactor = 1.15;
        static double currentScale = 0.5;  // stores the current scale value.
        static const double scaleMin = 0.1; // defines the min scale limit.
        static const double scaleMax = 4.0;

        //bool scrollVertical = event->orientation() == Qt::Vertical;
        int scrollDir = event->delta();

        if(currentScale > scaleMax) {
            currentScale = scaleMax;
        } else if(currentScale < scaleMin) {
            currentScale = scaleMin;
        } else if(scrollDir > 0 && currentScale < scaleMax) {   // zoom out
            ui->graphicsView->scale(scaleFactor, scaleFactor);
            currentScale *= scaleFactor;
        } else if(scrollDir < 0 && currentScale > scaleMin) {   // zoom in
            ui->graphicsView->scale(1 / scaleFactor, 1 / scaleFactor);
            currentScale /= scaleFactor;
        }

        //ui->graphicsView->fitInView(0,0,3075,2065);
    }
}
void MainWindow::on_button_new_clicked()
{
    newFile();
}

void MainWindow::on_button_open_clicked()
{
    open();
}

void MainWindow::on_button_save_clicked()
{
    save();
}

void MainWindow::on_tool_grass_clicked()
{
    curTool = "grass";
    scene->curTool = "grass";
    statusBar()->showMessage(tr("Grass tool selected"), 2000);
}

void MainWindow::on_tool_dirt_clicked()
{
    curTool = "dirt";
    scene->curTool = "dirt";
    statusBar()->showMessage(tr("Dirt tool selected"), 2000);
}

void MainWindow::on_tool_water_clicked()
{
    curTool = "water";
    scene->curTool = "water";
    statusBar()->showMessage(tr("Water tool selected"), 2000);
}

void MainWindow::on_tool_rock_clicked()
{
    curTool = "rock";
    scene->curTool = "rock";
    statusBar()->showMessage(tr("Rock tool selected"), 2000);
}

void MainWindow::on_tool_tree_clicked()
{
    curTool = "tree";
    scene->curTool = "tree";
    statusBar()->showMessage(tr("Tree tool selected"), 2000);
}

void MainWindow::on_tool_wall_clicked()
{
    curTool = "wall";
    scene->curTool = "wall";
    statusBar()->showMessage(tr("Wall tool selected"), 2000);
}
void MainWindow::changeLayout(int x, int y, Terrain::Type type)
{
    int newX = x / 32;
    int newY = y / 32;

    int n = newY * curMap.getMapDim().width() + newX;
    statusBar()->showMessage("x: " + QString::number(newX) + ", y: " + QString::number(newY) + ", n: " + QString::number(n));

    QChar c;

    switch (type)
    {
    case Terrain::Water:
        c = ' ';
        break;
    case Terrain::Grass:
        c = 'G';
        break;
    case Terrain::Dirt:
        c = 'D';
        break;
    case Terrain::Rock:
        c = 'R';
        break;
    case Terrain::Tree:
        c = 'F';
        break;
    case Terrain::Wall:
        c = 'W';
        break;
    default:
        qCritical() << "Saving rubble or wall-damaged incomplete";
    break;
    }


    QVector<QChar> layout = curMap.getMapLayout();
    layout[n] = c;
    curMap.setMapLayout(layout);


}

void MainWindow::changeAsset(int x, int y, QString asset, int player)
{
    int newX = x / 32;
    int newY = y / 32;

    int n = newY * curMap.getMapDim().width() + newX;
    statusBar()->showMessage("x: " + QString::number(newX) + ", y: " + QString::number(newY) + ", n: " + QString::number(n));

    Unit unit = Unit(asset, newX, newY);

    curMap.addUnit(unit, player);
}

void MainWindow::on_tool_peasant1_clicked()
{
    curTool = "Peasant";
    scene->curTool = "Peasant";
    statusBar()->showMessage(tr("Player 1 Peasant selected"), 2000);
}

void MainWindow::on_tool_townhall1_clicked()
{
    curTool = "TownHall";
    scene->curTool = "TownHall";
    statusBar()->showMessage(tr("Player 1 Townhall selected"), 2000);
}

void MainWindow::on_tool_goldmine_clicked()
{
    curTool = "GoldMine";
    scene->curTool = "GoldMine";
    statusBar()->showMessage(tr("Goldmine Tool selected"), 2000);
}

void MainWindow::on_tool_barracks_clicked()
{
    curTool = "Barracks";
    scene->curTool = "Barracks";
    statusBar()->showMessage(tr("Barracks Tool selected"), 2000);
}

void MainWindow::on_tool_smith_clicked()
{
    curTool = "BlackSmith";
    scene->curTool = "BlackSmith";
    statusBar()->showMessage(tr("Black Smith Tool selected"), 2000);
}

void MainWindow::on_tool_cannontower_clicked()
{
    curTool = "CannonTower";
    scene->curTool = "CannonTower";
    statusBar()->showMessage(tr("Cannon Tower Tool selected"), 2000);
}

void MainWindow::on_tool_castle_clicked()
{
    curTool = "Castle";
    scene->curTool = "Castle";
    statusBar()->showMessage(tr("Castle Tool selected"), 2000);
}

void MainWindow::on_tool_farm_clicked()
{
    curTool = "Farm";
    scene->curTool = "Farm";
    statusBar()->showMessage(tr("Farm Tool selected"), 2000);
}

void MainWindow::on_tool_guardtower_clicked()
{
    curTool = "GuardTower";
    scene->curTool = "GuardTower";
    statusBar()->showMessage(tr("Guard Tower Tool selected"), 2000);
}

void MainWindow::on_tool_tower_clicked()
{
    curTool = "ScoutTower";
    scene->curTool = "ScoutTower";
    statusBar()->showMessage(tr("Scout Tower Tool selected"), 2000);
}

void MainWindow::on_tool_keep_clicked()
{
    curTool = "Keep";
    scene->curTool = "Keep";
    statusBar()->showMessage(tr("Keep Tool selected"), 2000);
}

void MainWindow::on_tool_mill_clicked()
{
    curTool = "LumberMill";
    scene->curTool = "LumberMill";
    statusBar()->showMessage(tr("LumberMill Tool selected"), 2000);
}

void MainWindow::on_tool_archer_clicked()
{
    curTool = "Archer";
    scene->curTool = "Archer";
    statusBar()->showMessage(tr("Player 1 Archer selected"), 2000);
}

void MainWindow::on_tool_knight_clicked()
{
    curTool = "Ranger";
    scene->curTool = "Ranger";
    statusBar()->showMessage(tr("Player 1 Ranger selected"), 2000);
}


// function to generalize all the player button click events
void MainWindow::on_tool_pX_clicked(QAbstractButton* button) {
    curPlayer = button->text().toInt();
    scene->curPlayer = button->text().toInt();
    ui->statusBar->showMessage("Player " + button->text() + " selected");
}

// for various dialog boxes
void MainWindow::open_DgAbout(){
    DgAbout w(this);
    w.exec();
}

void MainWindow::open_DgMapProperties(){
    DgMapProperties w(this);
    w.exec();
}

void MainWindow::open_DgPlayerProperties(){
    DgPlayerProperties w(this);
    w.exec();
}

// for the assets editor window
void MainWindow::open_DgAssets(){
    // if doesn't exist, open a new one
    if (MainWindow::wAssets == 0)
        wAssets = new DgAssets(this);

    wAssets->show();
    wAssets->raise();
    wAssets->activateWindow();
}

