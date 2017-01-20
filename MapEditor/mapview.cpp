#include "mapview.h"

MapView::MapView(const QString &mapFileName , const QString &mapTexName )
{
    openMap(mapFileName);
    openMapTexture(mapTexName);
    // upper-left corner and the rectangle size of width and height
    tileDim.setRect(1,1,32,32);

}


void MapView::openMap(const QString &mapFileName){
    QFile mapFile(mapFileName);

    if ( !mapFile.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"error",mapFile.errorString());

    }


    QTextStream in(&mapFile);

    QString blankLine = " ";
    QSize mapDim(0,0);
    QVector<QString> mapConfig;

    int maxMapLine = 68;
    int lineNum = 0;

    // Parse .map file
    while(!in.atEnd()){

        QString line = in.readLine();
//        QMessageBox::information(0,"file",line);
        if (line == blankLine){
            QMessageBox::information(0,"file","blankLine");
            continue;
        }

        lineNum++;
//        if(lineNum > 0 ){
        if ( lineNum == 1){
            // Name of the map
            mapName = line;
            QMessageBox::information(0,"File line",mapName);
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


void MapView::openMapTexture(const QString &textureName){
    QImage img;
    if( !img.load(textureName)){
        QMessageBox::information(0,"error","image");
    }
    // just a test
    /*
    else{
        QMessageBox::information(0,"Loaded Image", "Succuss");
    }
    */

    currentImage = img;

}

//Reference: http://stackoverflow.com/questions/12681554/dividing-qimage-to-smaller-pieces
QImage MapView::createImageTile(QImage* image, const QRect & rect) {
    size_t offset = rect.x() * image->depth() / 8
                    + rect.y() * image->bytesPerLine();
    return QImage(image->bits() + offset, rect.width(), rect.height(),
                  image->bytesPerLine(), image->format());
}

void MapView::displayMap(){

    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(scene);
    // single tile from texture image
    QImage imageDx = createImageTile( &currentImage, tileDim);

    QPixmap pixmap = QPixmap::fromImage(imageDx);
    scene->addPixmap(pixmap);

    view->show();
}

