#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

class MapView
{
public:
    MapView(const QString &mapFileName, const QString &mapTexName);

    void displayMap();

private:
    void openMap(const QString &mapName);
    void openMapTexture(const QString &mapTexture);
    QImage createImageTile(QImage* image, const QRect &rect);



    QImage currentImage;
    QSize currentSize;

    QRect tileDim;





};

#endif // MAPVIEW_H
