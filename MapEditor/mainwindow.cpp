#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphicsscene.h"
#include <QDebug>
#include "mapview2.h"
#include "dgabout.h"
#include "dgmapproperties.h"
#include "dgplayerproperties.h"
#include "dgassets.h"
#include <QMediaPlayer>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // set up UI elements
    ui->setupUi(this);
    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView_2->setMouseTracking(true);
    curTool = "hand";

    // Load all assets using
    MainWindow::setupAssets();

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
    // play background music
    QMediaPlayer * backgroundMusic = new QMediaPlayer();
    backgroundMusic->setMedia(QUrl("qrc:/data/snd/basic/annoyed2.wav"));
    backgroundMusic->play();
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
    curMap = MapView2(assets);
    scene = new GraphicsScene(this, &curMap,&assets);
    curMap.displayNewMap(scene);

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
    dialog.setNameFilter(tr("Map Files (*.map *.mpk *.zip)"));
    if (!maybeSave())
        return false;
    if(dialog.exec() != QDialog::Accepted)
        return false;
    curFileDialogState = dialog.saveState();

    if(dialog.selectedFiles().first().split(".").last() == "map") {
        QFile file(dialog.selectedFiles().first());
        return loadMapFile(dialog.selectedFiles().first(), file);
    } else
        return loadPkgFile(dialog.selectedFiles().first());
}

bool MainWindow::loadMapFile(QString fileName, QIODevice &file)
{
    // check if the file is good
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(0,"error opening map",file.errorString());
        return false;
    }
    file.close();

    // load and display map and minimap
    QString mapName = fileName;
    QString texture = ":/data/img/Terrain.png";

    curMap = MapView2(file, assets, texture );

    scene = new GraphicsScene(this, &curMap, &assets);
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

    setCurrentFile(mapName);
    statusBar()->showMessage(mapName + " loaded!", 2000);

    curPlayer = 1;
    scene->curPlayer = 1;
    on_tool_grass_clicked();

    return true;
}

// opens up .mpk files
bool MainWindow::loadPkgFile(const QString &pkgFileName){
    QuaZip qz(pkgFileName);
    if(!qz.open(QuaZip::mdUnzip)) {
        QMessageBox::warning(0,"error opening map","MPK file is corrupted.");
        return false;
    }

    qz.setCurrentFile("data.map");

    QuaZipFile qzFile(&qz);

    // check if the file is good
    if(!qzFile.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(0,"error opening map",qzFile.errorString());
    }
    qzFile.close();

    loadMapFile(qzFile.getFileName(), qzFile );

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

    // check if able to write to file
    QFile file(curFile);
    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, "Application", file.errorString());
        return false;
    }

    writeMapFile(&file);

    setCurrentFile(curFile);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::saveAs() {
    if (!setSaveFile(&curFile)) return;
    save();
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


// this function takes an **opened** map file, writes everything that goes inside, and then closes it
void MainWindow::writeMapFile(QIODevice *file){

    QTextStream stream(file);

    // write descriptive properties
    stream << curMap.getMapName() << endl;
    stream << curMap.getMapDim().width()-2 << " " << curMap.getMapDim().height()-2 << endl;
    stream << "description" << endl;
    stream << "General" << endl;

    // write out layout
    QVector<QChar>::iterator itr;
    QVector<QChar> layout = curMap.getMapLayout();
    int x = 0;
    for (itr = layout.begin(); itr != layout.end(); itr++) {
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

    // write units
    stream << curMap.getNumUnits() << endl;
    for (int t = 0; t < curMap.getPlayers().size(); t++) {
        QVector<Unit> units = players[t].units;
        QVector<Unit>::iterator itr3;

        for (itr3 = units.begin(); itr3 != units.end(); itr3++) {
            stream << itr3->name << " " << t << " " << itr3->x << " " << itr3->y << endl;
        }
    }

    file->close();
}

// this function saves all assets and stores them inside a zip file
void MainWindow::exportPkg()
{
    QString pkgFileName;

    // set file to save to
    QFileDialog dialog(this);
    dialog.restoreState(curFileDialogState);
    dialog.setDirectory(curPath);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setDefaultSuffix(".mpk");
    if (dialog.exec() != QDialog::Accepted)
        return;
    curFileDialogState = dialog.saveState();
    pkgFileName = dialog.selectedFiles().first();

    // pkgFileName contains full path; eg. "Users/felix/Desktop/test.map"
    QuaZip qz(pkgFileName);
    qz.open(QuaZip::mdCreate);

    // populate zip file with empty folders
    QuaZipFile qzf(&qz);
    qzf.open(QIODevice::WriteOnly, QuaZipNewInfo("/img/")); qzf.close();
    qzf.open(QIODevice::WriteOnly, QuaZipNewInfo("/res/")); qzf.close();
    qzf.open(QIODevice::WriteOnly, QuaZipNewInfo("/scripts/")); qzf.close();
    qzf.open(QIODevice::WriteOnly, QuaZipNewInfo("/snd/")); qzf.close();
    qzf.open(QIODevice::WriteOnly, QuaZipNewInfo("/upg/")); qzf.close();

    // create map file
    qzf.open(QIODevice::WriteOnly, QuaZipNewInfo("data.map"));
        writeMapFile(&qzf);

    // create an index file with all assets
    qzf.open(QIODevice::WriteOnly, QuaZipNewInfo("index.dat"));
        QTextStream stream(&qzf);
        stream << "index.dat" << endl;
        stream << "data.map" << endl;
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
    ui->tool_hand->setIcon(QIcon(":/toolbar/icons/toolbar/tool_hand.png"));

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
    ui->tool_ranger->setIcon(curMap.getButtonIconsTx()->getPixTile("ranger"));
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

void MainWindow::on_tool_hand_clicked()
{
    curTool = "hand";
    scene->curTool = "hand";
    statusBar()->showMessage(tr("Hand/Cursor tool selected"), 2000);
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
    curTool = "Knight";
    scene->curTool = "Knight";
    statusBar()->showMessage(tr("Player 1 Knight selected"), 2000);
}

void MainWindow::on_tool_ranger_clicked()
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

void MainWindow::setupAssets(){
    // grab all the asset files
    QString path = ":/data/img";
    QString colorFile = ":/data/img/Colors.png";
    QString goldmineTool = ":/data/img/GoldMine.dat";
    QString peasantTool = ":/data/img/Peasant.dat";
    QString archerTool = ":/data/img/Archer.dat";
    QString knightTool = ":/data/img/Knight.dat";
    QString rangerTool = ":/data/img/Ranger.dat";
    QString townhallTool = ":/data/img/TownHall.dat";
    QString barracksTool = ":/data/img/Barracks.dat";
    QString blacksmithTool = ":/data/img/Blacksmith.dat";
    QString cannontowerTool = ":/data/img/CannonTower.dat";
    QString castleTool = ":/data/img/Castle.dat";
    QString farmTool = ":/data/img/Farm.dat";
    QString guardtowerTool = ":/data/img/GuardTower.dat";
    QString keepTool = ":/data/img/Keep.dat";
    QString lumbermillTool = ":/data/img/LumberMill.dat";
    QString scouttowerTool = ":/data/img/ScoutTower.dat";



    int nObjects = 15;

//    assets = new QMap<QString,Texture*>;

    // append them to a vector
    QVector<QString> files;
    files.append(peasantTool);
    files.append(archerTool);
    files.append(knightTool);
    files.append(rangerTool);
    files.append(goldmineTool);
    files.append(townhallTool);
    files.append(barracksTool);
    files.append(blacksmithTool);
    files.append(cannontowerTool);
    files.append(castleTool);
    files.append(farmTool);
    files.append(guardtowerTool);
    files.append(keepTool);
    files.append(lumbermillTool);
    files.append(scouttowerTool);

    // create a texture for each asset
    for(int i = 0; i < nObjects; i++){
        Texture *tex = new Texture(files.at(i),colorFile);
        assets.insert( tex->textureName, tex);
    }
    assets.value("Peasant")->paintAll();
    assets.value("Ranger")->paintAll();
    assets.value("Archer")->paintAll();
    assets.value("Knight")->paintAll();
    assets.value("TownHall")->paintAll();
    assets.value("Barracks")->paintAll();
    assets.value("Blacksmith")->paintAll();
    assets.value("CannonTower")->paintAll();
    assets.value("Castle")->paintAll();
    assets.value("Farm")->paintAll();
    assets.value("GuardTower")->paintAll();
    assets.value("Keep")->paintAll();
    assets.value("LumberMill")->paintAll();
    assets.value("ScoutTower")->paintAll();
}

void MainWindow::on_actionBrush_size_1_triggered()
{
    scene->CurBrushSize = 1;
}

void MainWindow::on_actionBrush_size_2_triggered()
{
    scene->CurBrushSize = 2;
}

void MainWindow::on_actionBrush_size_3_triggered()
{
    scene->CurBrushSize = 3;
}

void MainWindow::on_actionBrush_size_4_triggered()
{
    scene->CurBrushSize = 4;
}
