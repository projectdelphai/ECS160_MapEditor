#include "mapview2.h"
#include <QDebug>

Player::Player()
{
}

Player::Player(int n, int g, int l)
{
    num = n;
    gold = g;
    lumber = l;
}

Unit::Unit()
{
}

Unit::Unit(QString n, int xc, int yc)
{
    name = n;
    x = xc;
    y = yc;
}

// Default (new map)
MapView2::MapView2()
{

    defaultMap();
    terrain = new Terrain;
    tileDim.setRect(1,1,32,32);
    tileMap.reserve(mapDim.width()*mapDim.height());

    // testing for MapRendering parsing
    terrain->renderingInfo(":/data/img/MapRendering.dat");

    // testing lookup of a number to get the alias number
    int test = terrain->getAlias("rock", 5);

    qDebug() << "Should be at rock0 with alias 2: " << test;
}

MapView2::MapView2(const QString &mapFileName , const QString &mapTexName = ":/data/img/Terrain.png" )
{
    openMap(mapFileName);
    terrain = new Terrain(mapTexName);

    // upper-left corner and the rectangle size of width and height
    tileDim.setRect(1,1,32,32);
    tileMap.reserve(mapDim.width()*mapDim.height());
}

// creates a blank map and updates variables
void MapView2::defaultMap(){
    mapName = "untitled.map";
    mapDim.setHeight(64 + 2);
    mapDim.setWidth(96 + 2);

    for(int h = 0; h < mapDim.height(); h++ ){
        for(int w = 0; w < mapDim.width(); w++) {
            mapLayOut.append('G');
        }
    }
    numPlayers = 0;
    Player player = Player(0, 30000, 500);
    players.append(player);
    numUnits = 0;
}

// parses .map file and updates variables
void MapView2::openMap(const QString &mapFileName){
    bool intTest;

    QFile mapFile(mapFileName);

    if ( !mapFile.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"error opening map",mapFile.errorString());
    }


    QVector<QString> mapConfig;
    QString blankLine = " ";

    int maxMapLine = 68;
    int lineNum = 0;

    QTextStream in(&mapFile);

    // Parse .map file
    while(!in.atEnd()){
        QString line = in.readLine();

        if (line == blankLine){
            QMessageBox::information(0,"file","blankLine");
            continue;
        }

        int value = line.toInt(&intTest);

        lineNum++;
        if ( lineNum == 1){
            mapName = line;
        }
        else if ( lineNum == 2 ){            
            // Dimension of the map
            QStringList strNums = line.split(" ");
            QVector<int> nums;
            for(auto iter = strNums.begin();iter != strNums.end();iter++){
                nums.append(iter->toInt());
            }
            // plus 2 for the border
            mapDim.setHeight(nums[1]+2);
            mapDim.setWidth(nums[0]+2);
        }
        else if (!intTest && lineNum > 2 && lineNum <= maxMapLine ){
            // key layout of the map
            for (auto iter = line.begin(); iter != line.end(); iter++ ){
                mapLayOut.append(*iter);
            }
        }
        else if (intTest){
            numPlayers = line.toInt();
            lineNum++;
            line = in.readLine();
            for (int i = 0; i < numPlayers + 1; i++)
            {
                // create players and add
                QStringList playerValues = line.split(" ");
                Player player = Player(playerValues[0].toInt(), playerValues[1].toInt(), playerValues[2].toInt());
                players.append(player);
                lineNum++;
                line = in.readLine();
            }

            // grab number of units
            numUnits = line.toInt();
            lineNum++;
            line = in.readLine();

            // for each unit
            for (int i = 0; i < numUnits; i++)
            {
                QStringList unitValues = line.split(" ");

                // create unit
                Unit unit(unitValues[0], unitValues[2].toInt(), unitValues[3].toInt());

                // add to the respective player
                players[unitValues[1].toInt()].units.append(unit);

                lineNum++;
                line = in.readLine();
            }
        }
    }
}

// reads map array and updates the scene
void MapView2::builtmap(QGraphicsScene *scene)
{
    int x = 0;
    int y = 0;
    Terrain::Type type;
    QString typeS;
    int n = 0;

    for(int i = 0; i < mapDim.height(); ++i){
        for( int j = 0; j < mapDim.width(); ++j){

            n = i*mapDim.width() + j;
            switch ( mapLayOut.at(n).toLatin1() ){
                case 'G':
                    type = Terrain::Grass;
                    typeS = "grass";
                    break;
                case 'F':
                    type = Terrain::Tree;
                    typeS = "tree";
                    break;
                case 'D':
                    type = Terrain::Dirt;
                    typeS = "dirt";
                    break;
                case 'W':
                    type = Terrain::Wall;
                    typeS = "wall";
                    break;
                case 'w':
                    type = Terrain::WallDamage;
                    typeS = "wall-damaged";
                    break;
                case 'R':
                    type = Terrain::Rock;
                    typeS = "rock";
                    break;
                case ' ':
                    type = Terrain::Water;
                    typeS = "water";
                    break;
            }

            QImage imageDx = *terrain->getImageTile(type);
            QPixmap pixmap = QPixmap::fromImage(imageDx);
            Tile* pixItem = new Tile(type, pixmap);

            // sets each tile image x = 0*32,1*32,2*32,... y= 0*32,1*32,2*32,...
            x = j*tileDim.width();
            y = i*tileDim.height();
            pixItem->setPos(x,y);
            scene->addItem(pixItem);
        }
    }
}

void MapView2::displayMap(QGraphicsScene *scene){


    builtmap(scene);

    //view->show();
}

Terrain* MapView2::getTerrain(){
    return terrain;
}

QSize MapView2::getMapDim()
{
    return mapDim;
}

QString MapView2::getMapName()
{
    return mapName;
}

QVector<QChar> MapView2::getMapLayout()
{
    return mapLayOut;
}

QVector<Player> MapView2::getPlayers()
{
    return players;
}

int MapView2::getNumPlayers()
{
    return numPlayers;
}

int MapView2::getNumUnits()
{
    return numUnits;
}

void MapView2::setMapLayout(QVector<QChar> layout)
{
    mapLayOut = layout;
}

