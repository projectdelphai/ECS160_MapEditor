#ifndef TERRAIN_H
#define TERRAIN_H

#include "texture.h"


/* Class name: Terrain
 * Inherits: Texture
 *
 * Takes in the terrain.png filename (or uses default)
 * Use getImageTile to get the corresponding 32x32 QImage*
 */

class Terrain: private Texture
{
public:
    explicit Terrain(QString texFileName = ":/data/img/Terrain.png");
    enum  Type { Grass = 0, Dirt , Tree , Water , Rock , WallDamage , Wall , Rubble };
    QImage* getImageTile(Terrain::Type type);

protected:
    QMap< QString, QImage* >* texture;
    QImage fullImage;

};

#endif // TERRAIN_H
