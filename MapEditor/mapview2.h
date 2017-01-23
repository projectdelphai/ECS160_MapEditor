#ifndef MAPVIEW2_H
#define MAPVIEW2_H

#include <QGraphicsView>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>


class MapView2
{
public:
    MapView2(const QString &mapFileName, const QString &mapTexName);

    void displayMap();

//private:
    void openMap(const QString &mapName);
    void openMapTexture(const QString &mapTexture);
    QImage createImageTile(QImage* image, const QRect &rect);

    QImage currentImage;
    QString mapName;
    QVector<QChar> mapLayOut;
    QRect tileDim;

};

#endif // MAPVIEW2_H
