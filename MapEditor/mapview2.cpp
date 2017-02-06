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

// Default
MapView2::MapView2()
{
    defaultMap();
    texture = new Texture(":/data/img/Terrain.png");
    currentImage = texture->fullImage;
    tileDim.setRect(1,1,32,32);
    tileMap.reserve(mapDim.width()*mapDim.height());
}

MapView2::MapView2(const QString &mapFileName , const QString &mapTexName = ":/data/img/Terrain.png" )
{
    openMap(mapFileName);
    texture = new Texture(mapTexName);
    currentImage = texture->fullImage;

    // upper-left corner and the rectangle size of width and height
    tileDim.setRect(1,1,32,32);
    tileMap.reserve(mapDim.width()*mapDim.height());
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

            QImage imageDx = texture->getImageTile(type);
            QPixmap pixmap = QPixmap::fromImage(imageDx);
            //QGraphicsPixmapItem * pixItem = new Tile(type, pixmap );
            Tile * pixItem = new Tile(type, pixmap);
            // sets each tile image x = 0*32,1*32,2*32,... y= 0*32,1*32,2*32,...
            x = j*tileDim.width();
            y = i*tileDim.height();
            pixItem->setPos(x,y);
            scene->addItem(pixItem);

//            qDebug() << n;
//            qDebug() << tileType << ":" << t;
//            qDebug() << "(" <<  x << "," << y << ")";

        }
    }
}

void MapView2::displayMap(QGraphicsScene *scene){

    //QGraphicsView* view = new QGraphicsView(scene);
    // single tile from texture image
    builtmap(scene);

    //view->show();
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

