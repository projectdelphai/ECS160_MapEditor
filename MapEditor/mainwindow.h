#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "mapview2.h"
#include "texture.h"
#include "graphicsscene.h"
#include "dgassets.h"
#include "quazip/quazip.h"
#include "quazip/quazipfile.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool loadFile(const QString &fileName);

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
    void newFile();
    bool open();
    bool save();
    void saveAs();

    void exportPkg();

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
    void on_tool_mill_clicked();
    void on_tool_smith_clicked();
    void on_tool_tower_clicked();
    void on_tool_archer_clicked();
    void on_tool_knight_clicked();

    void on_tool_pX_clicked(QAbstractButton*);
    void open_DgAbout();
    void open_DgMapProperties();
    void open_DgPlayerProperties();
    void open_DgAssets();

private:
    Ui::MainWindow *ui;
    void updateUI();
    void writeSettings();
    bool maybeSave();
    bool setSaveFile(QString*);
    bool saveFile(const QString &fileName);
    void writeMapFile(QIODevice*);
    void setCurrentFile(const QString &fileName);

    int curPlayer;
    QString curTool;
    QString curFile;
    QByteArray curFileDialogState;
    QString curPath = QDir::homePath(); // current directory
    DgAssets *wAssets = 0;
};


#endif // MAINWINDOW_H
