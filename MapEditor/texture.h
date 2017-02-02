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
    Texture();

    void display();
    enum  Type { Grass = 0, Dirt , Tree , Water , Rock , WallDamage , Wall , Rubble };
    enum  colors{ Blue = 0, Red , Green , Purple, Orange , Yellow, Black , Gray } ;


//private:
    void open(const QString &mapTexture);
    void scanTexture(const QString &str);
    void scanTexture2(const QString &str);
    void openColor(const QString &colorFile);

    QImage paintUnit(QString unitname,int colorPick);

    QImage fullImage;
    QString texName;
    QRect tileDim;
    QVector< QMap<QString, int > > typeList;
    QMap<QString,QMap<QString,int>> itemList;
    QMap<QString,QImage> imgLoaded;

    QImage getImageTile(Type);
    QImage getImageTile( QString strType ="");

    QMap< int,QVector<QColor> >colorMap;
    // number player to access corresponding  color palette asset.
//    QMap< int , QMap<QString,QVector<QImage>>> playerColorItems;

    QMap< QString, QVector<QImage> > objectImgColor;
};

#endif // TEXTURE_H
