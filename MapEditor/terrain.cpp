#include "terrain.h"

Terrain::Terrain()
{

}

QImage Texture::getImageTile(Terrain::Type type){
    int width = 32;
    int height = 32;
    int offsetH = typeList[type].last();
    QImage image = fullImage.copy(0,offsetH,width,height);
    return image;
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
                typeList[Terrain::Grass].insert(line , offsetHeight);
            }
            else if ( line.contains(QRegExp("dirt+")) ){
                typeList[Terrain::Dirt].insert(line, offsetHeight);
            }
            else if (line.contains(QRegExp("tree+")) ){
                typeList[Terrain::Tree].insert(line, offsetHeight);
            }
            else if (line.contains(QRegExp("water+")) ){
                typeList[Terrain::Water].insert(line , offsetHeight);
            }
            else if (line.contains(QRegExp("rock+")) ){
                typeList[Terrain::Rock].insert( line, offsetHeight);
            }
            else if (line.contains(QRegExp("wall-d+")) ){
                typeList[Terrain::WallDamage].insert( line , offsetHeight);
            }
            else if(line.contains(QRegExp("wall-\\d+"))){
                typeList[Terrain::Wall].insert( line , offsetHeight);
            }
            else if(line.contains(QRegExp("rubble+"))){
                typeList[Terrain::Rubble].insert( line , offsetHeight);
            }

            offsetHeight += tileSize;
        } // if line > 2
    } // while !in.atEnd

}
