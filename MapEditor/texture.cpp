#include "texture.h"
#include <QDebug>

Texture::Texture(const QString &texFileName )
{

    int numTypes = 8;
    typeList.resize(8);

    // image is initialized
    open(texFileName);

    QStringList filePath = texFileName.split(".");
    QStringList pathnames = filePath[0].split("/");
    texName = pathnames.back();

    scanTexture(QString(":/data/img/Terrain.dat"));

    // upper-left corner and the rectangle size of width and height
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

    qDebug() << "color open:" << colorMap.size();

}

QImage Texture::paintUnit(QString unitname,int colorPick){
    QImage image = getImageTile(unitname);
    int blue = 0;
    int shade = 0;

    for(int i=0; i < image.height() ;i++)
    {
        for(int j=0 ; j < image.width();j++ )
        {
            QColor color(image.pixel(i,j));

            for(int index = 0; index < colorMap[blue].size(); index++ ){
                if (color == colorMap[blue].at(index)){
                    qDebug() << "color match";
                    shade = index;
                    QColor c = colorMap.value(colorPick).at(shade);
                    image.setPixel( i,j, c.rgb() );
                }
            }

        }
    }

//    QGraphicsScene *scene = new QGraphicsScene();
//    QGraphicsView *view = new QGraphicsView(scene);
//    QPixmap pix = QPixmap::fromImage(image);
//    scene->addPixmap(pix);
//    view->show();

    return image;
}


void Texture::scanTexture(const QString &texFileName){
    QFile file(texFileName);

    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"error",file.errorString());
    }


    QString name;
    int lineNum = 0;
    int offsetHeight = 0;
    int tileSize = 32;
    int size = 0;

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

            if( line.contains(QRegExp("grass+")) ){
                typeList[Grass].insert(line , offsetHeight);
            }
            else if ( line.contains(QRegExp("dirt+")) ){
                typeList[Dirt].insert(line, offsetHeight);
            }
            else if (line.contains(QRegExp("tree+")) ){
                typeList[Tree].insert(line, offsetHeight);
            }
            else if (line.contains(QRegExp("water+")) ){
                typeList[Water].insert(line , offsetHeight);
            }
            else if (line.contains(QRegExp("rock+")) ){
                typeList[Rock].insert( line, offsetHeight);
            }
            else if (line.contains(QRegExp("wall-d+")) ){
                typeList[WallDamage].insert( line , offsetHeight);
            }
            else if(line.contains(QRegExp("wall-\\d+"))){
                typeList[Wall].insert( line , offsetHeight);
            }
            else if(line.contains(QRegExp("rubble+"))){
                typeList[Rubble].insert( line , offsetHeight);
            }

            offsetHeight += tileSize;
        }

    }

}

void Texture::scanTexture2(const QString &texFileName){
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
            name = name.remove(QRegExp(".png"));
            qDebug() << name;
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
    QString textureName = path+name+".png";

    QImage img;
    if( !img.load(textureName)){
        QMessageBox::information(0,"error","image");
    }




    // store image loaded to reaccess
    imgLoaded.insert(name,img);


    int offsetHeight = 0;
    // assumes each img is squared.
    int width = img.width();
    QMap<QString,int> imgTypes;
    for(int i = 0; i < numTypes; ++i){
        imgTypes.insert(types[i],offsetHeight);
        offsetHeight += width;
    }

    // will use item name has key to retrieve the same group of items
    itemList.insert(name,imgTypes);

    QVector<QImage> imgColor;
    int nPlayers = 8;

    for(int i = 0; i < nPlayers; i++){
        imgColor.append(paintUnit(name,i));
//        objectImgColor.insert(name,imgColo)
    }
    objectImgColor.insert(name,imgColor);

}

QImage Texture::getImageTile(QString strType ){

    QImage img = imgLoaded.value(strType);
    // assume size is square
    int width = img.width();
    int height = width;
    int offsetH = itemList.value(strType).last();
    QImage image = img.copy(0,offsetH,width,height);
    return image;
}

QImage Texture::getImageTile(Type type ){

    int width = 32;
    int height = 32;
    int offsetH = typeList[type].first();
    QImage image = fullImage.copy(0,offsetH,width,height);
    return image;
}

void Texture::display(){}

