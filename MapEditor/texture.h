#ifndef TEXTURE_H
#define TEXTURE_H

#include <QGraphicsView>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>


class Texture
{
public:
    explicit Texture(const QString &mapTexName);
    Texture();

    void display();
    enum  Type { Grass = 0, Dirt , Tree , Water , Rock , WallDamage , Wall , Rubble };

//private:
    void open(const QString &mapTexture);
    void scanTexture(const QString &str);
    void scanTexture2(const QString &str);


    QImage fullImage;
    QString texName;
    QRect tileDim;
    QVector< QMap<QString, int > > typeList;
    QMap<QString,QMap<QString,int>> itemList;
    QMap<QString,QImage> imgLoaded;

    QImage getImageTile(Type);
    QImage getImageTile( QString strType ="");

};

#endif // TEXTURE_H
