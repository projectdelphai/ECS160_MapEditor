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

//private:
    QImage open(const QString &mapTexture);

    QImage fullImage;
    QString texName;
    QRect tileDim;
    QVector< QMap<QString, int > > typeList;


    // refactoring to work with singular texture map
    QMap< QString, QImage*> txMap;
    QMap< QString, QImage*>* rTxMap = &txMap;
    QString datFileName;
    void scan();

    const QMap<QString, QImage*>* getTxMap();
    const QImage* getImage(QString txName);

};

#endif // TEXTURE_H
