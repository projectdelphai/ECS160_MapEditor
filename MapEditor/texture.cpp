#include "texture.h"
#include <QDebug>

// for now used only loading map terrain texture
Texture::Texture(const QString &texFileName )
{
//    int numTypes = 8;
    terrainType.resize(8);
    terrainType2.resize(8);
    // image is initialized
    open(texFileName);
    scanTerrain(QString(":/data/img/Terrain.dat"));
    // upper-left corner and the rectangle size of width and height
    tileDim.setRect(0,0,32,32);
}

Texture::Texture( const QString &textureName, const QString &colorFile){
    scanTexture(textureName);
    openColor(colorFile);
    tileDim.setRect(0,0,32,32);
}

Texture::Texture(){

}

void Texture::open(const QString &textureName){
    QImage img;
    if( !img.load(textureName)){
        QMessageBox::information(0,"error","image");
    }

    fullImage = img;
}

void Texture::openColor(const QString &colorFile){
    QImage colorImg;

    if( !colorImg.load(colorFile)){
        QMessageBox::information(0,"error","image");
    }


    // stores colors in Qmap
    QVector<QColor> colorV;
    for(int i = 0; i < colorImg.height(); i++){
        QVector<QColor> colorV;
        for(int j = 0; j < colorImg.width(); j++ ){
            QColor color(colorImg.pixel(j,i) );
            colorV.append(color);
        }

        colorMap.insert(i, colorV);
        colorV.clear();
    }

//    qDebug() << "color open:" << colorMap.size();

}

QVector<QImage> Texture::paintUnit(int colorPick){
    int blue = 0;
    int shade = 0;
    QVector< QImage > imagesPaint;
    // skip blue
    for(int nImg = 0; nImg < imageList.size(); ++nImg ){
        QImage image = imageList.at(nImg);
        for(int i=0; i < image.height() ;i++)
        {
            for(int j=0 ; j < image.width();j++ )
            {
                QColor color(image.pixel(i,j));

                for(int index = 0; index < colorMap[blue].size(); index++ ){
                    if (color == colorMap[blue].at(index)){
                        shade = index;
                        QColor c = colorMap.value(colorPick).at(shade);
                        image.setPixel( i,j, c.rgb() );
                    }
                }

            }
        }
        imagesPaint.append(image);
    }

//    QGraphicsScene *scene = new QGraphicsScene();
//    QGraphicsView *view = new QGraphicsView(scene);
//    QPixmap pix = QPixmap::fromImage(image);
//    scene->addPixmap(pix);
//    view->show();

    return imagesPaint;
}

void Texture::paintAll(){

    int nPlayers = 8;
    int blue = 1;
    // will need to change later but player 0 is neutral
    // actual player 1 is blue
    // however the colors start with blue = 0.
    colorPlayerImg.insert(blue,imageList);
    // skip first players of blue color
    for(int i = 0; i < nPlayers; i++){
         colorPlayerImg.insert(i+1,paintUnit(i));
    }
}

void Texture::scanTerrain(const QString &texFileName){
    QFile file(texFileName);

    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"error",file.errorString());
    }


    QString name;
    int lineNum = 0;
    int offsetHeight = 0;
    int tileSize = 32;
    int size = 0;
    QImage image;

    QTextStream in(&file);
    while(!in.atEnd()){

        QString line  = in.readLine();

        // skip blankline
        if (line == QString(" "))
            continue;

        lineNum++;

        if (lineNum == 1){
            name = line;
        }
        else if(lineNum == 2){
           size =  line.toInt();
        }
        // stores textures types together and each specific type is map (sometype,height)
        // image texture is assume sorted
        else if(lineNum > 2){
            image = fullImage.copy(0,offsetHeight,fullImage.width(),fullImage.width());
            if( line.contains(QRegExp("grass+")) ){
                terrainType[Grass].insert(line , image );
                terrainType2[Grass].append(image);

            }
            else if ( line.contains(QRegExp("dirt+")) ){
                terrainType[Dirt].insert(line, image);
                terrainType2[Dirt].append(image);
            }
            else if (line.contains(QRegExp("tree+")) ){
                terrainType[Tree].insert(line, image);
                terrainType2[Tree].append(image);
            }
            else if (line.contains(QRegExp("water+")) ){
                terrainType[Water].insert(line , image);
                terrainType2[Water].append(image);

            }
            else if (line.contains(QRegExp("rock+")) ){
                terrainType[Rock].insert( line, image);
                terrainType2[Rock].append( image);

            }
            else if (line.contains(QRegExp("wall-d+")) ){
                terrainType[WallDamage].insert( line , image);
                terrainType2[WallDamage].append( image);

            }
            else if(line.contains(QRegExp("wall-\\d+"))){
                terrainType[Wall].insert( line , image);
                terrainType2[Wall].append(image);
            }
            else if(line.contains(QRegExp("rubble+"))){
                terrainType[Rubble].insert( line , image);
                terrainType2[Rubble].append(image);
            }

            offsetHeight += tileSize;
        }

    }

}

void Texture::scanTexture(const QString &texFileName){
    QFile file(texFileName);

    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"error",file.errorString());
    }

    QString name;
    int lineNum = 0;
    int numTypes = 0;
    QVector<QString> types;

    QTextStream in(&file);
    while(!in.atEnd()){

        QString line  = in.readLine();

        // skip blankline
        if (line == QString(" "))
            continue;

        lineNum++;

        if (lineNum == 1){
            name = line;
            name = name.remove(0,2);
            textureName = name.remove(QRegExp(".png"));

        }
        else if(lineNum == 2){
            numTypes =  line.toInt();

        }
        else if(lineNum > 2){
            types.append(line);
        }
    }

    QDir dir;
    QString path = ":data/img/";
    QString nameFile = path+textureName+".png";

    QImage img;
    if( !img.load(nameFile)){
        QMessageBox::information(0,"error","image");
    }

    int offsetHeight = 0;
    // assumes each img is squared.  
    int width = img.width();
    int height = width;
    for(int i = 0; i < numTypes; ++i){
        QImage image = img.copy(0,offsetHeight,width,height);
        offsetHeight += width;
        imageList.append(image);
    }

}



//QImage Texture::getImageTile(Type type ){

//    int width = 32;
//    int height = 32;
//    int offsetH = typeList[type].first();
//    QImage image = fullImage.copy(0,offsetH,width,height);
//    return image;
//}

void Texture::display(){}

