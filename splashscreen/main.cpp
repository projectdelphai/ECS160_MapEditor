#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPixmap>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();


    QApplication a(argc, argv);
      QGraphicsScene scene;
      QGraphicsView view(&scene);
      QGraphicsPixmapItem item(QPixmap(":/images/babyanimal_open.jpg"));
//      QGraphicsPixmapItem item(QPixmap("/home/allan/Pictures/babyanimal_open.jpg"));
      scene.addItem(&item);
      view.show();

    return a.exec();
}
