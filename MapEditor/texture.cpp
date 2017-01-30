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


void Texture::open(const QString &textureName){
    QImage img;
    if( !img.load(textureName)){
        QMessageBox::information(0,"error","image");
    }

    fullImage = img;
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

QImage Texture::getImageTile(Type type){
    int width = 32;
    int height = 32;
    int offsetH = typeList[type].last();
    QImage image = fullImage.copy(0,offsetH,width,height);
    return image;
}

void Texture::display(){}

