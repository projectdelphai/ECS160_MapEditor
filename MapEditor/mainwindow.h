#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "mapview2.h"
#include "texture.h"

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

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;
#endif // QT_NO_CONTEXTMENU
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    bool save();
    bool saveAs();
    void newFile();
    void open();

    void on_button_new_released();

    void on_button_open_released();

    void on_button_save_released();

    void on_tool_grass_released();

    void on_tool_dirt_released();

    void on_tool_water_released();

private:
    Ui::MainWindow *ui;
    void writeSettings();
    bool maybeSave();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);

    QString curTool;
    QString curFile;
    QGraphicsScene* scene;
};


#endif // MAINWINDOW_H
