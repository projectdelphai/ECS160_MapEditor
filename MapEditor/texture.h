#ifndef TEXTURE_H
#define TEXTURE_H

#include <QGraphicsView>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>


class Texture
{
public:
    explicit Texture(const QString &mapTexName);

    void display();
    enum  Type { Grass = 0, Dirt , Tree , Water , Rock , WallDamage , Wall , Rubble };

//private:
    void open(const QString &mapTexture);
    void scanTexture(const QString &str);

    QImage fullImage;
    QString texName;
    QRect tileDim;
    QVector< QMap<QString, int > > typeList;

    QImage getImageTile(Type);

};

#endif // TEXTURE_H
