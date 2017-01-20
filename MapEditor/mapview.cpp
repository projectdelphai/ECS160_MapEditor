#include "mapview.h"

MapView::MapView(const QString &mapFileName , const QString &mapTexName )
{
    openMap(mapFileName);
    openMapTexture(mapTexName);

    // upper-left corner and the rectangle size of width and height
    tileDim.setRect(1,1,32,32);


}


void MapView::openMap(const QString &mapName){
    QFile mapFile(mapName);

    if ( !mapFile.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"error",mapFile.errorString());

    }

    // just a test
/*
    else{
        QMessageBox::information(0,"Loaded File","Succuss");
    }
*/
    QTextStream in(&mapFile);

//    while(!in.atEnd()){
//        QString line = in.readLine();

//    }
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

    currentSize = img.size();
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

