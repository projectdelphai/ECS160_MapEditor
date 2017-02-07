#ifndef TERRAIN_H
#define TERRAIN_H

#include "texture.h"

class Terrain: private Texture
{
public:
    explicit Terrain(QString txFile = ":/data/img/Terrain.png");

    enum  Type { Grass = 0, Dirt , Tree , Water , Rock , WallDamage , Wall , Rubble };

    QImage fullImage;
    QImage getImageTile(Terrain::Type type);
    void loadTypeList(const QString &str);

};

#endif // TERRAIN_H
