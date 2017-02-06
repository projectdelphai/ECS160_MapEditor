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

    const QMap<QString, QImage>* getTxMap();

//private:
    QImage open(const QString &mapTexture);
    void loadTypeList(const QString &str);

    QImage fullImage;
    QString texName;
    QRect tileDim;
    QVector< QMap<QString, int > > typeList;

    QImage getImageTile(Type);

    // refactoring to work with singular texture map
    QMap< QString, QImage> txMap;
    QMap< QString, QImage>* rTxMap = &txMap;
    QString datFileName;
    void scan();

    const QImage* getRImg(QString txName);

};

#endif // TEXTURE_H
