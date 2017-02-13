#include "terrain.h"
#include <QDebug>

Terrain::Terrain(QString texFileName) : Texture(texFileName)
{
    Terrain::texture = Texture::getTxMap();
}

QImage* Terrain::getImageTile(QString typeS){

    // type-n are split
    QStringList tokens = typeS.split("-");
    QString typeName = "";

    // temporary code until all type can be evaluted
    if(tokens.size() <= 1){
        // these are unfinished
        if (tokens.at(0) == "grass"){
            typeName = "grass-0";
        }
        else if( tokens.at(0) == "tree"){
            typeName = "tree-63";
        }
        else if(tokens.at(0) == "wall"){
            typeName = "wall-0";
        }
        else if(tokens.at(0) == "wall-damaged"){
            typeName = "wall-damaged-0";
        }
        else if( tokens.at(0) == "dirt" ){
            typeName = "dirt-255";
        }
        else if( tokens.at(0) == "rock"){
            typeName = "rock-255";
        }

    }
    else {

        // returns the alias number or the same one
        int numKey = getAlias(tokens.at(0),tokens.at(1).toInt());
        typeName = tokens.at(0) + "-" + QString().setNum(numKey);
        if (!texture->contains(typeName)){
            typeName = "rock-107";
        }
    }




    return texture->value(typeName);
}

int Terrain::getAlias(QString typeS, int num){

    QString typeKey = "";

    // defaults to the same number
    int output = num;

    for( int i = 0; i < alias.size(); i++){
        typeKey = typeS + QString().setNum(i);
        if ( alias.value(typeKey).contains(num) ){
            // any match number in the list is an alias to the first number within the list.
            output = alias.value(typeKey).at(0);
            break;
        }
    }

    return output;
}

void Terrain::renderingInfo(QString datFileName){

    QFile file(datFileName);

    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"opening file error",file.errorString());
    }

    int lineNum = 0;
    int nItems =  0;
//    QMap<QString,QVector<int>> alias;

    QTextStream in(&file);
    while(!in.atEnd()){

        QString line = in.readLine();

        // skip blankline
        if (line == QString(" "))
            continue;

        lineNum++;

        if(lineNum == 1){
            // RGBA color values
            // Not used for now
            nItems = line.toInt();
            for(int i = 0; i < nItems; i++){
                line = in.readLine();
                // alpha color
                lineNum++;
            }
        }
        else if ( lineNum > nItems && nItems != 0 ){

            // number of different terrain tile type having a list of alias numbers to the first number
            nItems = line.toInt();

            int countTree = 0;
            int countDirt = 0;
            int countWater = 0;
            int countRock = 0;
            QString strConvert = "";
            for( int i = 0; i < nItems; i++){

                line = in.readLine();

                bool ok = false;
                // Map with key in format type-n where n is the nth same type parsed
                QString keyType = "";
                // store the list numbers for one entry
                QVector<int> aliasNums;

                // list of strings from the line
                QStringList typeAlias = line.split(" ");

                if ( typeAlias.at(0) == "tree"){
                    aliasNums.clear();
                    keyType = "tree" + strConvert.setNum(countTree,10);
                    for(int i = 1; i < typeAlias.size(); i++){
                        aliasNums.append(typeAlias.at(i).toInt(&ok,16));
                    }
                    countTree++;

                }
                else if ( typeAlias.at(0) == "dirt" ){
                    aliasNums.clear();
                    keyType = "dirt" + strConvert.setNum(countDirt,10);
                    for(int i = 1; i < typeAlias.size(); i++){
                        aliasNums.append(typeAlias.at(i).toInt(&ok,16));
                    }
                    countDirt++;
                }
                else if ( typeAlias.at(0) == "water"){
                    aliasNums.clear();
                    keyType = "water"+strConvert.setNum(countWater,10);
                    for(int i = 1; i < typeAlias.size(); i++){
                        aliasNums.append(typeAlias.at(i).toInt(&ok,16));
                    }
                    countWater++;
                }
                else if ( typeAlias.at(0) == "rock"){
                    aliasNums.clear();
                    keyType = "rock" + strConvert.setNum(countRock,10);
                    for(int i = 1; i < typeAlias.size(); i++){
                        int x = typeAlias.at(i).toInt(&ok,16);
                        aliasNums.append(typeAlias.at(i).toInt(&ok,16));
                    }
                    countRock++;
                }
                // store each list of alias number for all same and diferrent type
                alias.insert(keyType,aliasNums);

            }

        }


    }

}
