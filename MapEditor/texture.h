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


    QImage open(const QString &mapTexture);

    enum  colors{ Blue = 0, Red , Green , Purple, Orange , Yellow, Black , Gray } ;


    void scanTexture(const QString &str);
    void openColor(const QString &colorFile);
    QVector<QImage> paintUnit(int colorPick);
    void paintAll();


    QImage fullImage;
    QString textureName;
    QRect tileDim;

    // refactoring to work with singular texture map
    QMap< QString, QImage*> txMap;
    QMap< QString, QImage*>* rTxMap = &txMap;
    QString datFileName;
    void scanDatFile(const QString datFileName);

    const QMap<QString, QImage*>* getTxMap();
    const QImage* getImage(QString txName);

    QVector<QImage> imageList;
    // color with gradient level shades
    QMap< int,QVector<QColor> >colorMap;
    // recolor images of player's color
    // colorPlayerImg[playerColor][imageTile]
    QMap< int , QVector<QImage> > colorPlayerImg;
};

#endif // TEXTURE_H
