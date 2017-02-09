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

    QMap<QString, QImage*>* getTxMap();
    const QImage* getImage(QString txName);

    QString textureName;
    void paintAll();
    QVector<QImage> imageList;

    QMap< int,QVector<QColor> >colorMap;         // color with gradient level shades
    QMap< int , QVector<QImage> > colorPlayerImg;   // recolor images of player's color

private:
    void display();

    QImage open(const QString &mapTexture);

    enum  colors{ Blue = 0, Red , Green , Purple, Orange , Yellow, Black , Gray } ;

    void scanTexture(const QString &str);
    void openColor(const QString &colorFile);
    QVector<QImage> paintUnit(int colorPick);

    QImage fullImage;
    QRect tileDim;

    // txMap IS THE CONTAINER FOR THE IMAGES
    QMap< QString, QImage*> txMap;
    QMap< QString, QImage*>* rTxMap = &txMap;
    QString datFileName;
    void scanDatFile(const QString datFileName);

};

#endif // TEXTURE_H
