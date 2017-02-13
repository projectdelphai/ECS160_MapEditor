#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "mapview2.h"
#include "texture.h"
#include "graphicsscene.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadFile(const QString &fileName);

public slots:
    void changeLayout(int x, int y, Terrain::Type type);
    void changeAsset(int x, int y, QString asset, int player);

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;
#endif // QT_NO_CONTEXTMENU
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

    MapView2 curMap;
    GraphicsScene *scene;

private slots:
    bool save();
    bool saveAs();
    void newFile();
    void open();
    void on_button_new_clicked();
    void on_button_open_clicked();
    void on_button_save_clicked();
    void on_tool_grass_clicked();
    void on_tool_dirt_clicked();
    void on_tool_water_clicked();
    void on_tool_rock_clicked();
    void on_tool_tree_clicked();
    void on_tool_wall_clicked();
    void on_tool_peasant1_clicked();
    void on_tool_townhall1_clicked();
    void on_tool_goldmine_clicked();
    void on_tool_barracks_clicked();
    void on_tool_cannontower_clicked();
    void on_tool_castle_clicked();
    void on_tool_farm_clicked();
    void on_tool_guardtower_clicked();
    void on_tool_keep_clicked();
    void on_tool_p1_clicked();
    void on_tool_p2_clicked();

    void on_tool_mill_clicked();

    void on_tool_smith_clicked();

    void on_tool_tower_clicked();

    void on_tool_p3_clicked();

    void on_tool_p4_clicked();

    void on_tool_p5_clicked();

    void on_tool_p6_clicked();

    void on_tool_p7_clicked();

    void on_tool_p8_clicked();

private:
    Ui::MainWindow *ui;
    void updateUI();
    void writeSettings();
    bool maybeSave();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);

    int curPlayer;
    QString curTool;
    QString curFile;
};


#endif // MAINWINDOW_H
