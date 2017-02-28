#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "mapview2.h"
#include "texture.h"
#include "graphicsscene.h"
#include "dialogs/dgassets.h"
#include "quazip/quazip.h"
#include "quazip/quazipfile.h"
#include <QStack>

class RecordedTile
{//Used to store a tile + its x- and y-coordinates for undo-redo functionality
public:
    RecordedTile();
    RecordedTile(Terrain::Type u, Terrain::Type r, int a, int b);
    Terrain::Type utype, rtype;
    int x, y;
};

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void changeLayout(int x, int y, Terrain::Type type);
    void changeAsset(int x, int y, QString asset, int player);
    void activateAI();

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
    void undo();
    void redo();

    void exportPkg();

    void on_button_new_clicked();
    void on_button_open_clicked();
    void on_button_save_clicked();
    void on_button_undo_clicked();
    void on_button_redo_clicked();
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
    void on_tool_scouttower_clicked();
    void on_tool_archer_clicked();
    void on_tool_knight_clicked();
    void on_tool_ranger_clicked();
    void on_tool_hand_clicked();
    void on_tool_pX_clicked(QAbstractButton* Button);
    void on_actionBrush_size_1_triggered();
    void on_actionBrush_size_2_triggered();
    void on_actionBrush_size_3_triggered();
    void on_actionBrush_size_4_triggered();
    void on_tool_aitrigger_clicked();
    void on_actionHide_Trigger_triggered();

    void open_DgAbout();
    void open_DgMapProperties();
    void open_DgPlayerProperties();
    void open_DgAssets();
    void open_DTrigger(QGraphicsScene* , Tile* );
    void open_exporttoweb();

    void setupAssets();



private:
    Ui::MainWindow *ui;
    void setupUI();
    void writeSettings();
    void loadScene();
    bool loadMapFile(QString fileName, QIODevice &file);
    bool maybeSave();
    bool setSaveFile(QString*);
    void writeMapFile(QIODevice*);
    bool loadPkgFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    Terrain::Type getTileType(QChar tile);
    void updateUIPlayers();
    void hideTriggers(bool visible);


    int curPlayer;
    //int curBrushSize;
    QString curTool;
    QString curFile;
    QByteArray curFileDialogState;
    QString curPath = QDir::homePath(); // current directory
    DgAssets *wAssets = 0;
    QMap<QString,Texture*> assets;

    Texture *asset = 0;

    //Stores tiles from undo button
     QStack<RecordedTile> undoTiles;

    //Stores tiles from undo/redo
    QStack<RecordedTile> undoTiles;
    QStack<RecordedTile> redoTiles;


    //Prevents already-dealt-with elements from being re-pushed onto either stack
    bool undone;
};


#endif // MAINWINDOW_H
