#include "texture.h"
#include <QDebug>

Texture::Texture(const QString &texFileName )
{
    int numTypes = 8;
    typeList.resize(numTypes);

    // load QImage from file
    fullImage = open(texFileName);

    // load typelist from the corresponding dat file
    QStringList filePath = texFileName.split(".");
    QStringList pathnames = filePath[0].split("/");
    texName = pathnames.back();
    datFileName = QString(":/data/img/" + texName + ".dat");
    loadTypeList(datFileName);

    // upper-left corner and the rectangle size of width and height
    tileDim.setRect(0,0,32,32);
}

// load QImage from file
QImage Texture::open(const QString &textureName){
    QImage img;
    if( !img.load(textureName)){
        QMessageBox::information(0,"error","image");
    }
    return img;
}

// reads dat file and updates typeList
void Texture::loadTypeList(const QString &texFileName){
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
        } // if line > 2
    } // while !in.atEnd

}

// this function takes all image files from a large png, chops them up and stores them in Texture::txMap
void Texture::scan() {
    QFile file(Texture::datFileName);

    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"error",file.errorString());
    }


    QString name;
    int lineNum = 0;

    QTextStream in(&file);
    while(!in.atEnd()){

        QString line  = in.readLine();

        // skip blankline
        if (line == QString(" "))
            continue;

        lineNum++;

        if(lineNum > 2){
            QImage* tile = new QImage(fullImage.copy(0,lineNum,32,32));
            Texture::txMap.insert(line, tile);
        }
    }
}

const QMap<QString, QImage*>* Texture::getTxMap() {
    return rTxMap;
}


const QImage* Texture::getImage(QString txName){
    return txMap.value(txName);
}

QImage Texture::getImageTile(Type type){
    int width = 32;
    int height = 32;
    int offsetH = typeList[type].last();
    QImage image = fullImage.copy(0,offsetH,width,height);
    return image;
}

void Texture::display(){}

