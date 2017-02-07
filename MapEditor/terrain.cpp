#include "terrain.h"
#include <QDebug>

Terrain::Terrain(QString texFileName) : Texture(texFileName)
{
    Terrain::texture = Texture::rTxMap;
}

QImage* Terrain::getImageTile(Terrain::Type type){
    QString typeName;


    // these are the default values (BEFORE MAP RENDERING)
    switch(type) {
        case Grass:
            typeName = "grass-0";
        break;
        case Tree:
            typeName = "tree-63";
        break;
        case Dirt:
            typeName = "dirt-255";
        break;
        case Wall:
            typeName = "wall-0";
        break;
        case WallDamage:
            typeName = "wall-damaged-0";
        break;
        case Rock:
            typeName = "rock-255";
        break;
        case Water:
            typeName = "water-255";
        break;
        case Rubble:
            typeName = "rubble-0";
        break;
    }

    return texture->value(typeName);
}

