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


void Texture::display(){

}

