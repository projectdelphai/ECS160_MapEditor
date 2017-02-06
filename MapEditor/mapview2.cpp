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

MapView2::MapView2()
{
    defaultMap();
    setup();
    terrainTexture = new Texture(":/data/img/Terrain.png");
    currentImage = terrainTexture->fullImage;
    tileDim.setRect(1,1,32,32);
    tileMap.reserve(mapDim.width()*mapDim.height());
}

MapView2::MapView2(const QString &mapFileName , const QString &mapTexName = ":/data/img/Terrain.png" )
{
    openMap(mapFileName);
    setup();
    terrainTexture = new Texture(mapTexName);
    currentImage = terrainTexture->fullImage;
    // upper-left corner and the rectangle size of width and height
    tileDim.setRect(1,1,32,32);
    tileMap.reserve(mapDim.width()*mapDim.height());
    //scene = new QGraphicsScene();

}

void MapView2::setup(){
    QString path = ":/data/img";
    QString colorFile = ":/data/img/Colors.png";
    QString peasantFile =":/data/img/Peasant.dat";
    QString Goldmine  =":/data/img/GoldMine.dat";
    int nObjects = 2;

    QVector<QString> files;
    files.append(peasantFile);
    files.append(Goldmine);
    for(int i = 0; i < nObjects; i++){
        Texture *tex = new Texture(files.at(i),colorFile);
        assets.insert( tex->textureName, tex);
    }
    assets.value("Peasant")->paintAll();

}


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
//        if(lineNum > 0 ){
        if ( lineNum == 1){
            // Name of the map
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
            mapA llowedAIs = line.split(" ");
        }
        else if (!intTest && lineNum > 4 && lineNum <= maxMapLine ){
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


void MapView2::openMapTexture(const QString &textureName){
    QImage img;
    if( !img.load(textureName)){
        QMessageBox::information(0,"error","image");
    }

    currentImage = img;

}

//Reference: http://stackoverflow.com/questions/12681554/dividing-qimage-to-smaller-pieces
QImage MapView2::createImageTile(QImage* image, const QRect & rect) {
    size_t offset = rect.x() * image->depth() / 8
                    + rect.y() * image->bytesPerLine();
    return QImage(image->bits() + offset, rect.width(), rect.height(),
                  image->bytesPerLine(), image->format());
}

void MapView2::builtmap(QGraphicsScene *scene)
{
    int x = 0;
    int y = 0;
    Texture::Type type;
    int n = 0;

    for(int i = 0; i < mapDim.height(); ++i){
        for( int j = 0; j < mapDim.width(); ++j){

            n = i*mapDim.width() + j;
            switch ( mapLayOut.at(n).toLatin1() ){
                case 'G': type = Texture::Grass;
                    break;
                case 'F': type = Texture::Tree;
                    break;
                case 'D': type = Texture::Dirt;
                    break;
                case 'W': type = Texture::Wall;
                    break;
                case 'w': type = Texture::WallDamage;
                    break;
                case 'R': type = Texture::Rock;
                    break;
                case ' ': type = Texture::Water;
                    break;

            }


//            QImage imageDx = terrainTexture->terrainType[type].first();
            QImage imageDx = terrainTexture->terrainType2[type].at(0);
            QPixmap pixmap = QPixmap::fromImage(imageDx);
            Tile * pixItem = new Tile(type, pixmap);
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
            qDebug() << unitName;
            QImage imageDx;
            if( i > 1){
                imageDx = assets.value(unitName)->colorPlayerImg.value(i).at(0);
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

