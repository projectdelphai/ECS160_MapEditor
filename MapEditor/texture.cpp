#include "texture.h"
#include <QDebug>

Texture::Texture(const QString &TexFileName )
{
    open(TexFileName);
    // upper-left corner and the rectangle size of width and height
    tileDim.setRect(1,1,32,32);

}


void Texture::open(const QString &textureName){
    QImage img;
    if( !img.load(textureName)){
        QMessageBox::information(0,"error","image");
    }

    fullImage = img;
    QStringList filePath = textureName.split(".");
    QStringList pathnames = filePath[0].split("/");
    qDebug() << pathnames.back();

}

//Reference: http://stackoverflow.com/questions/12681554/dividing-qimage-to-smaller-pieces
QImage Texture::createImageTile(QImage* image, const QRect & rect) {
    size_t offset = rect.x() * image->depth() / 8
                    + rect.y() * image->bytesPerLine();
    return QImage(image->bits() + offset, rect.width(), rect.height(),
                  image->bytesPerLine(), image->format());
}



void Texture::display(){

    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(scene);
    // single tile from texture image
    QImage imageDx = createImageTile( &fullImage, tileDim);

    QPixmap pixmap = QPixmap::fromImage(imageDx);


    scene->addPixmap(pixmap);

    view->show();
}

