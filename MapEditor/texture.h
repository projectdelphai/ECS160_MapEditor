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
    void open(const QString &mapTexture);
    QImage createImageTile(QImage* image, const QRect &rect);

    QImage fullImage;
    QString texName;
    QVector<QChar> mapLayOut;
    QRect tileDim;
    void scanTexture();

};

#endif // TEXTURE_H
