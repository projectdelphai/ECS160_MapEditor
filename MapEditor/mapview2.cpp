#include "mapview2.h"
#include <QDebug>

MapView2::MapView2(const QString &mapFileName , const QString &mapTexName )
{
    openMap(mapFileName);
    texture = new Texture(mapTexName);
    currentImage = texture->fullImage;
    // upper-left corner and the rectangle size of width and height
    tileDim.setRect(1,1,32,32);
    tileMap.reserve(mapDim.width()*mapDim.height());
    //scene = new QGraphicsScene();

}


void MapView2::openMap(const QString &mapFileName){
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
            mapDim.setHeight(nums[0]);
            mapDim.setWidth(nums[1]);
        }
        else if (lineNum > 2 && lineNum <= maxMapLine ){
            // key layout of the map
            for (auto iter = line.begin(); iter != line.end(); iter++ ){
                mapLayOut.append(*iter);
            }
        }
        else if (lineNum > maxMapLine ){
            // the remaining map configurations
            mapConfig.append(line);
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

void MapView2::builtmap(QGraphicsScene *scene){

    QString tileType = " ";
    int x = 0;
    int y = 0;
    for(int i = 0; i < mapDim.width(); ++i){
        for( int j = 0; j < mapDim.height(); ++j){

            tileType = QString( mapLayOut.at(i*mapDim.height() + j) );

            int offsetHeight = i*mapDim.height() + j;
            QImage imageDx = currentImage.copy(0,offsetHeight,tileDim.width(),tileDim.height());
            QPixmap pixmap = QPixmap::fromImage(imageDx);
            QGraphicsPixmapItem * pixItem = new Tile(tileType , pixmap );
            // sets each tile image x = 0*32,1*32,2*32,... y= 0*32,1*32,2*32,...
            x = i*tileDim.width();
            y = j*tileDim.height();
            pixItem->setPos(x,y);
            scene->addItem(pixItem);

        }
    }


}

void MapView2::displayMap(QGraphicsScene *scene){

    //QGraphicsView* view = new QGraphicsView(scene);
    // single tile from texture image
    builtmap(scene);

    //view->show();
}

