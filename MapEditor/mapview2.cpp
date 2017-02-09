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

    // create and store all assets
    setup();
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
    setup();
    terrain = new Terrain(mapTexName);

    // upper-left corner and the rectangle size of width and height
    tileDim.setRect(1,1,32,32);
    tileMap.reserve(mapDim.width()*mapDim.height());
}


void MapView2::setup(){
    // grab all the asset files
    QString path = ":/data/img";
    QString colorFile = ":/data/img/Colors.png";
    QString peasantFile =":/data/img/Peasant.dat";
    QString Goldmine  =":/data/img/GoldMine.dat";
    QString townHall = ":/data/img/TownHall.dat";
    int nObjects = 3;

    // append them to a vector
    QVector<QString> files;
    files.append(peasantFile);
    files.append(Goldmine);
    files.append(townHall);

    // create a texture for each asset
    for(int i = 0; i < nObjects; i++){
        Texture *tex = new Texture(files.at(i),colorFile);
        assets.insert( tex->textureName, tex);
    }
    assets.value("Peasant")->paintAll();
    assets.value("TownHall")->paintAll();

}

// creates a blank map and updates variables
void MapView2::defaultMap(){
    mapName = "untitled.map";

    // add 2 tiles for border
    mapDim.setHeight(64 + 2);
    mapDim.setWidth(96 + 2);

    // loop through all the tiles and add grass tiles
    for(int h = 0; h < mapDim.height(); h++ ){
        for(int w = 0; w < mapDim.width(); w++) {
            mapLayOut.append('G');
        }
    }
    int MAXPLAYERS= 8;
    players.resize(MAXPLAYERS);

    // player zero is neutral

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

    int lineNum = 0;

    QTextStream in(&mapFile);

    // Parse .map file
    while(!in.atEnd()){
        QString line = in.readLine();

        if (line == blankLine){
            QMessageBox::information(0,"file","blankLine");
            continue;
        }

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
        else if ( lineNum == 3)
        {
            mapDescription = line;
        }
        else if ( lineNum == 4)
        {
            mapAllowedAIs = line.split(" ");
        }
        else if (!intTest && lineNum > 4){
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
    int n = 0;

    for(int i = 0; i < mapDim.height(); ++i){
        for( int j = 0; j < mapDim.width(); ++j){

            n = i*mapDim.width() + j;
            switch ( mapLayOut.at(n).toLatin1() ){
                case 'G':
                    type = Terrain::Grass;
                    break;
                case 'F':
                    type = Terrain::Tree;
                    break;
                case 'D':
                    type = Terrain::Dirt;
                    break;
                case 'W':
                    type = Terrain::Wall;
                    break;
                case 'w':
                    type = Terrain::WallDamage;
                    break;
                case 'R':
                    type = Terrain::Rock;
                    break;
                case ' ':
                    type = Terrain::Water;
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

void MapView2::builtAssets(QGraphicsScene *scene){

    QString unitName = "";
    int x = 0;
    int y = 0;
    for(int i = 0; i < players.size(); ++i){
        for(int j = 0; j < players[i].units.size(); ++j){

            unitName = players[i].units[j].name;
            // skip player 0, since it has no color assets
            QImage imageDx;
            if( i > 0){
                imageDx = assets.value(unitName)->colorPlayerImg.value(i).at(2);
            }
            else{
                imageDx = assets.value(unitName)->imageList.at(0);
            }
            Tile *unitItem = new Tile(unitName, QPixmap::fromImage(imageDx));
            x = tileDim.width()*players[i].units[j].x;
            y = tileDim.height()*players[i].units[j].y;
            unitItem->setPos(x,y);
            scene->addItem(unitItem);
        }
     }
}

void MapView2::displayMap(QGraphicsScene *scene){
    builtmap(scene);
    builtAssets(scene);
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

void MapView2::addPlayer(Player p)
{
    players.append(p);
}

int MapView2::getNumPlayers()
{
    return players.size();
}

int MapView2::getNumUnits()
{
    return numUnits;
}

void MapView2::addUnit(Unit u, int player)
{
    if (getNumPlayers() < player)
    {
        for (int i = getNumPlayers(); i < player + 1; i++)
        {
            Player player = Player(i, 100, 100);
            addPlayer(player);
        }
    }

    players[player].units.append(u);
}

void MapView2::setMapLayout(QVector<QChar> layout)
{
    mapLayOut = layout;
}
