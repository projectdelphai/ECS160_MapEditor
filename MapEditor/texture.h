#ifndef TEXTURE_H
#define TEXTURE_H

#include <QGraphicsView>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QColor>

class Texture
{
public:
    explicit Texture(const QString &mapTexName);
    Texture(const QString &mapTexName, const QString &color);
    Texture();

    void display();
    enum  Type { Grass = 0, Dirt , Tree , Water , Rock , WallDamage , Wall , Rubble };
    enum  colors{ Blue = 0, Red , Green , Purple, Orange , Yellow, Black , Gray } ;


//private:
    void open(const QString &mapTexture);
    void scanTerrain(const QString &str);
    void scanTexture(const QString &str);
    void openColor(const QString &colorFile);
    QImage getImageTile(Type);
    QVector<QImage> paintUnit(int colorPick);
    void paintAll();

    QImage fullImage;
    QString textureName;
    QRect tileDim;

    QVector< QMap<QString, QImage > > terrainType;
    // testing
    QVector< QVector<QImage> > terrainType2;

    QVector<QImage> imageList;
    // color with gradient level shades
    QMap< int,QVector<QColor> >colorMap;
    // recolor images of player's color
    QMap< int , QVector<QImage> > colorPlayerImg;
};

#endif // TEXTURE_H
