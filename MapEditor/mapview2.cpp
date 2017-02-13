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
    buttonColors = new Texture(":/data/img/ButtonColors.png", 1, 1);
    buttonIcons = new Texture(":/data/img/Icons.png", 46, 38);
    tileDim.setRect(1,1,32,32);
    tileMap.reserve(mapDim.width()*mapDim.height());

    // testing for MapRendering parsing
    terrain->renderingInfo(":/data/img/MapRendering.dat");


}

MapView2::MapView2(const QString &mapFileName , const QString &mapTexName = ":/data/img/Terrain.png" )
{
    openMap(mapFileName);
    setup();
    terrain = new Terrain(mapTexName);

    // upper-left corner and the rectangle size of width and height
    tileDim.setRect(1,1,32,32);
    tileMap.reserve(mapDim.width()*mapDim.height());

    // testing for MapRendering parsing
    terrain->renderingInfo(":/data/img/MapRendering.dat");
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


QString MapView2::tileEncode(QString strType ,int i , int j){

    QString valueStrType ="";
//    qDebug() << strType;
    QVector<QChar> tiles;
    QString encodeStr = "";
    // the following code to get the right tiles for the borders
    if( i == 0 || j == 0 || i == mapDim.height()-1  || j == mapDim.width() -1 ){
        if(j== 0 && strType == "grass" && i+2 < mapDim.height()  &&mapLayOut.at((i+1)*mapDim.width() + (j)) != 'G')
        {
            return "dirt-64";
        }
       else if(j== 0 && strType == "grass" && i-1 > 0 &&mapLayOut.at((i-1)*mapDim.width() + (j)) != 'G')
        {
            return "dirt-4";
        }
        else if(j== mapDim.width()-1 && strType == "rock" && i+2 < mapDim.height()&&mapLayOut.at((i+1)*mapDim.width() + (j)) != 'R')
         {
             return "rock-31";
         }
        else if(j== 0 && strType == "rock" && i+2 < mapDim.height()&&mapLayOut.at((i+1)*mapDim.width() + (j)) != 'R')
         {
             return "rock-31";
        }
        else if(j== 0 && strType == "rock" && i-1 >0 &&mapLayOut.at((i-1)*mapDim.width() + (j)) != 'R')
         {
             return "rock-248";
         }
        else if(j== mapDim.width()-1 && strType == "grass" && i-1 > 0&&mapLayOut.at((i-1)*mapDim.width() + (j)) != 'G')
        {
            return "dirt-22";
        }

        else{
            return strType;

        }
    }
    // the following to ckeck whats around the current tile and get the right tile based in what around it.
    QChar upperLTile = mapLayOut.at((i-1)*mapDim.width() + (j-1));
    QChar TopTile = mapLayOut.at((i-1)*mapDim.width() + j );
    QChar upperRTile = mapLayOut.at((i-1)*mapDim.width() + (j+1));
    QChar centerLTile = mapLayOut.at((i)*mapDim.width() + (j-1));
    QChar centerRTile = mapLayOut.at((i)*mapDim.width() + (j+1));
    QChar downLTile = mapLayOut.at((i+1)*mapDim.width() + (j-1));
    QChar belowTile = mapLayOut.at((i+1)*mapDim.width() + (j));
    QChar downRTile = mapLayOut.at((i+1)*mapDim.width() + (j+1));
    QChar centerType = mapLayOut.at(i*mapDim.width() + j);

    // water and rock have the same way of getting the right tile we are using 3 by 3 matrix of 0 and 1's zero for unmatch and 1 for match
    // the current tile will be at position 1,1.

    if (strType == "water" || strType == "rock"  ){

        tiles.append(downRTile);
        tiles.append(belowTile);
        tiles.append(downLTile);
        tiles.append(centerRTile);
        tiles.append(centerType);
        tiles.append(centerLTile);
        tiles.append(upperRTile);
        tiles.append(TopTile);
        tiles.append(upperLTile);
        for(int i = 0; i < tiles.size(); i++){
            if (i == 4){
                continue;
            }
            else if ( tiles.at(i) == centerType ){
                encodeStr += "1";
            }
            else {
                encodeStr += "0";
            }

        }
        bool ok;
        int num = encodeStr.toInt(&ok,2);
        valueStrType = strType +"-"+ QString().setNum(num);

    }
    else if(strType == "tree" ){

        tiles.append(downRTile);
        tiles.append(belowTile);
        tiles.append(downLTile);
        tiles.append(centerRTile);
        tiles.append(centerType);
        tiles.append(centerLTile);

        tiles.append(upperRTile);
        tiles.append(TopTile);
        tiles.append(upperLTile);

       // qDebug() <<"this is the cordinate "<< "(" << i << "," << j << ")";



        for(int i = 0; i < tiles.size(); i++){
            if ( tiles.at(i) == centerType ){
                encodeStr += "1";
            }
            else {
                encodeStr += "0";
            }
        }

       // qDebug() << encodeStr;

        bool ok;

        int num1 = encodeStr.left(6).toInt(&ok,2);
        int num2 = encodeStr.right(6).toInt(&ok,2);
        if(TopTile != centerType){
            QString sPoint = QString().setNum( j*tileDim.width() ) + " " +  QString().setNum( (i-1)*tileDim.height() );
            treeTopTiles.insert( sPoint, strType + "-" + QString().setNum(num2) );
          //  qDebug() << "tree top: " << strType + "-" + QString().setNum(num2);
        }




//        qDebug() << "n1 " << encodeStr.left(6);
//        qDebug() << "n2: "<< encodeStr.right(6);
        valueStrType = strType + "-" + QString().setNum(num1);



    }
    else if(strType == "wall"){
        tiles.append(centerLTile);
        tiles.append(belowTile);
        tiles.append(centerRTile);
        tiles.append(TopTile);

        for(int i = 0; i < tiles.size(); i++){
            if ( tiles.at(i) == centerType ){
                encodeStr += "1";
            }
            else {
                encodeStr += "0";
            }
        }

        bool ok;
        int num = encodeStr.toInt(&ok,2);

        valueStrType = strType+ "-" + QString().setNum(num);

    }
   else if (strType == "grass"){

        tiles.append(downRTile);
        tiles.append(belowTile);
        tiles.append(downLTile);
        tiles.append(centerRTile);
        tiles.append(centerType);
        tiles.append(centerLTile);
        tiles.append(upperRTile);
        tiles.append(TopTile);
        tiles.append(upperLTile);

       // qDebug() << "(" << i << "," << j << ")";

        for(int i = 0; i < tiles.size(); i++){
            if (i == 4){
                continue;
            }
            else if ( tiles.at(i) == centerType){
                encodeStr += "0";
            }
            else if(tiles.at(i) == 'W'|| tiles.at(i) == 'F'){
               // qDebug() << "Its a wall";
                encodeStr += "0";
            }
            else {
                encodeStr += "1";
            }

        }

        bool ok;
        int num = encodeStr.toInt(&ok,2);
        if(num==0)
        {
            //qDebug() << "all graas";

            valueStrType =  strType;
        }
        else
        {
            valueStrType = "dirt-"+ QString().setNum(num);
        }

    }
    else {
//        qDebug() << "default";
        valueStrType =  strType;

    }

    return valueStrType;

}

void MapView2::builtTreeTop(QGraphicsScene *scene){
    if(treeTopTiles.empty()){
      //  qDebug() << "No tree tops";
        return;
    }

    QString x = "";
    QString y = "";
    // sPoint is a string such as "32 64" this is the coordinates of tile
    for ( auto sPoint: treeTopTiles.keys()){

        QString typeS = treeTopTiles.value(sPoint);
        QImage image = *terrain->getImageTile(typeS);
        Tile * tile = new Tile(typeS,QPixmap::fromImage(image));

        QStringList ptStr = sPoint.split(" ");
        x = ptStr.at(0);
        y = ptStr.at(1);
        tile->setPos( x.toInt() , y.toInt()  );
        scene->addItem(tile);
    }
}

// reads map array and updates the scene
void MapView2::builtmap(QGraphicsScene *scene)
{
    int x = 0;
    int y = 0;
    QString typeS = "";
    QString tileStr = "";
    int n = 0;

    for(int i = 0; i < mapDim.height(); ++i){
        for( int j = 0; j < mapDim.width(); ++j){

            n = i*mapDim.width() + j;
            switch ( mapLayOut.at(n).toLatin1() ){
                case 'G':
                    typeS = "grass";
                    break;
                case 'F':
                    typeS = "tree";
                    break;
                case 'D':
                    typeS = "dirt";
                    break;
                case 'W':
                    typeS = "wall";
                    break;
                case 'w':
                    typeS = "wall-damaged";
                    break;
                case 'R':
                    typeS = "rock";
                    break;
                case ' ':
                    typeS = "water";
                    break;
            }

//            qDebug() << "(" << i << "," << j << ")";

            tileStr = tileEncode(typeS,i,j);



            QImage imageDx = *terrain->getImageTile(tileStr);
            QPixmap pixmap = QPixmap::fromImage(imageDx);
            Tile* pixItem = new Tile(typeS, pixmap);

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
    builtTreeTop(scene);
    builtAssets(scene);
}

Texture* MapView2::getButtonColorsTx(){
    return buttonColors;
}

Texture* MapView2::getButtonIconsTx(){
    return buttonIcons;
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
