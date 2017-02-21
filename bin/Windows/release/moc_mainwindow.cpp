/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MapEditor/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[48];
    char stringdata0[807];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "changeLayout"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 1), // "x"
QT_MOC_LITERAL(4, 27, 1), // "y"
QT_MOC_LITERAL(5, 29, 13), // "Terrain::Type"
QT_MOC_LITERAL(6, 43, 4), // "type"
QT_MOC_LITERAL(7, 48, 11), // "changeAsset"
QT_MOC_LITERAL(8, 60, 5), // "asset"
QT_MOC_LITERAL(9, 66, 6), // "player"
QT_MOC_LITERAL(10, 73, 7), // "newFile"
QT_MOC_LITERAL(11, 81, 4), // "open"
QT_MOC_LITERAL(12, 86, 4), // "save"
QT_MOC_LITERAL(13, 91, 6), // "saveAs"
QT_MOC_LITERAL(14, 98, 9), // "exportPkg"
QT_MOC_LITERAL(15, 108, 21), // "on_button_new_clicked"
QT_MOC_LITERAL(16, 130, 22), // "on_button_open_clicked"
QT_MOC_LITERAL(17, 153, 22), // "on_button_save_clicked"
QT_MOC_LITERAL(18, 176, 21), // "on_tool_grass_clicked"
QT_MOC_LITERAL(19, 198, 20), // "on_tool_dirt_clicked"
QT_MOC_LITERAL(20, 219, 21), // "on_tool_water_clicked"
QT_MOC_LITERAL(21, 241, 20), // "on_tool_rock_clicked"
QT_MOC_LITERAL(22, 262, 20), // "on_tool_tree_clicked"
QT_MOC_LITERAL(23, 283, 20), // "on_tool_wall_clicked"
QT_MOC_LITERAL(24, 304, 24), // "on_tool_peasant1_clicked"
QT_MOC_LITERAL(25, 329, 25), // "on_tool_townhall1_clicked"
QT_MOC_LITERAL(26, 355, 24), // "on_tool_goldmine_clicked"
QT_MOC_LITERAL(27, 380, 24), // "on_tool_barracks_clicked"
QT_MOC_LITERAL(28, 405, 27), // "on_tool_cannontower_clicked"
QT_MOC_LITERAL(29, 433, 22), // "on_tool_castle_clicked"
QT_MOC_LITERAL(30, 456, 20), // "on_tool_farm_clicked"
QT_MOC_LITERAL(31, 477, 26), // "on_tool_guardtower_clicked"
QT_MOC_LITERAL(32, 504, 20), // "on_tool_keep_clicked"
QT_MOC_LITERAL(33, 525, 20), // "on_tool_mill_clicked"
QT_MOC_LITERAL(34, 546, 21), // "on_tool_smith_clicked"
QT_MOC_LITERAL(35, 568, 21), // "on_tool_tower_clicked"
QT_MOC_LITERAL(36, 590, 22), // "on_tool_archer_clicked"
QT_MOC_LITERAL(37, 613, 22), // "on_tool_knight_clicked"
QT_MOC_LITERAL(38, 636, 22), // "on_tool_ranger_clicked"
QT_MOC_LITERAL(39, 659, 20), // "on_tool_hand_clicked"
QT_MOC_LITERAL(40, 680, 18), // "on_tool_pX_clicked"
QT_MOC_LITERAL(41, 699, 16), // "QAbstractButton*"
QT_MOC_LITERAL(42, 716, 6), // "Button"
QT_MOC_LITERAL(43, 723, 12), // "open_DgAbout"
QT_MOC_LITERAL(44, 736, 20), // "open_DgMapProperties"
QT_MOC_LITERAL(45, 757, 23), // "open_DgPlayerProperties"
QT_MOC_LITERAL(46, 781, 13), // "open_DgAssets"
QT_MOC_LITERAL(47, 795, 11) // "setupAssets"

    },
    "MainWindow\0changeLayout\0\0x\0y\0Terrain::Type\0"
    "type\0changeAsset\0asset\0player\0newFile\0"
    "open\0save\0saveAs\0exportPkg\0"
    "on_button_new_clicked\0on_button_open_clicked\0"
    "on_button_save_clicked\0on_tool_grass_clicked\0"
    "on_tool_dirt_clicked\0on_tool_water_clicked\0"
    "on_tool_rock_clicked\0on_tool_tree_clicked\0"
    "on_tool_wall_clicked\0on_tool_peasant1_clicked\0"
    "on_tool_townhall1_clicked\0"
    "on_tool_goldmine_clicked\0"
    "on_tool_barracks_clicked\0"
    "on_tool_cannontower_clicked\0"
    "on_tool_castle_clicked\0on_tool_farm_clicked\0"
    "on_tool_guardtower_clicked\0"
    "on_tool_keep_clicked\0on_tool_mill_clicked\0"
    "on_tool_smith_clicked\0on_tool_tower_clicked\0"
    "on_tool_archer_clicked\0on_tool_knight_clicked\0"
    "on_tool_ranger_clicked\0on_tool_hand_clicked\0"
    "on_tool_pX_clicked\0QAbstractButton*\0"
    "Button\0open_DgAbout\0open_DgMapProperties\0"
    "open_DgPlayerProperties\0open_DgAssets\0"
    "setupAssets"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      38,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,  204,    2, 0x0a /* Public */,
       7,    4,  211,    2, 0x0a /* Public */,
      10,    0,  220,    2, 0x08 /* Private */,
      11,    0,  221,    2, 0x08 /* Private */,
      12,    0,  222,    2, 0x08 /* Private */,
      13,    0,  223,    2, 0x08 /* Private */,
      14,    0,  224,    2, 0x08 /* Private */,
      15,    0,  225,    2, 0x08 /* Private */,
      16,    0,  226,    2, 0x08 /* Private */,
      17,    0,  227,    2, 0x08 /* Private */,
      18,    0,  228,    2, 0x08 /* Private */,
      19,    0,  229,    2, 0x08 /* Private */,
      20,    0,  230,    2, 0x08 /* Private */,
      21,    0,  231,    2, 0x08 /* Private */,
      22,    0,  232,    2, 0x08 /* Private */,
      23,    0,  233,    2, 0x08 /* Private */,
      24,    0,  234,    2, 0x08 /* Private */,
      25,    0,  235,    2, 0x08 /* Private */,
      26,    0,  236,    2, 0x08 /* Private */,
      27,    0,  237,    2, 0x08 /* Private */,
      28,    0,  238,    2, 0x08 /* Private */,
      29,    0,  239,    2, 0x08 /* Private */,
      30,    0,  240,    2, 0x08 /* Private */,
      31,    0,  241,    2, 0x08 /* Private */,
      32,    0,  242,    2, 0x08 /* Private */,
      33,    0,  243,    2, 0x08 /* Private */,
      34,    0,  244,    2, 0x08 /* Private */,
      35,    0,  245,    2, 0x08 /* Private */,
      36,    0,  246,    2, 0x08 /* Private */,
      37,    0,  247,    2, 0x08 /* Private */,
      38,    0,  248,    2, 0x08 /* Private */,
      39,    0,  249,    2, 0x08 /* Private */,
      40,    1,  250,    2, 0x08 /* Private */,
      43,    0,  253,    2, 0x08 /* Private */,
      44,    0,  254,    2, 0x08 /* Private */,
      45,    0,  255,    2, 0x08 /* Private */,
      46,    0,  256,    2, 0x08 /* Private */,
      47,    0,  257,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 5,    3,    4,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::Int,    3,    4,    8,    9,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 41,   42,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeLayout((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< Terrain::Type(*)>(_a[3]))); break;
        case 1: _t->changeAsset((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 2: _t->newFile(); break;
        case 3: { bool _r = _t->open();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: _t->saveAs(); break;
        case 6: _t->exportPkg(); break;
        case 7: _t->on_button_new_clicked(); break;
        case 8: _t->on_button_open_clicked(); break;
        case 9: _t->on_button_save_clicked(); break;
        case 10: _t->on_tool_grass_clicked(); break;
        case 11: _t->on_tool_dirt_clicked(); break;
        case 12: _t->on_tool_water_clicked(); break;
        case 13: _t->on_tool_rock_clicked(); break;
        case 14: _t->on_tool_tree_clicked(); break;
        case 15: _t->on_tool_wall_clicked(); break;
        case 16: _t->on_tool_peasant1_clicked(); break;
        case 17: _t->on_tool_townhall1_clicked(); break;
        case 18: _t->on_tool_goldmine_clicked(); break;
        case 19: _t->on_tool_barracks_clicked(); break;
        case 20: _t->on_tool_cannontower_clicked(); break;
        case 21: _t->on_tool_castle_clicked(); break;
        case 22: _t->on_tool_farm_clicked(); break;
        case 23: _t->on_tool_guardtower_clicked(); break;
        case 24: _t->on_tool_keep_clicked(); break;
        case 25: _t->on_tool_mill_clicked(); break;
        case 26: _t->on_tool_smith_clicked(); break;
        case 27: _t->on_tool_tower_clicked(); break;
        case 28: _t->on_tool_archer_clicked(); break;
        case 29: _t->on_tool_knight_clicked(); break;
        case 30: _t->on_tool_ranger_clicked(); break;
        case 31: _t->on_tool_hand_clicked(); break;
        case 32: _t->on_tool_pX_clicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 33: _t->open_DgAbout(); break;
        case 34: _t->open_DgMapProperties(); break;
        case 35: _t->open_DgPlayerProperties(); break;
        case 36: _t->open_DgAssets(); break;
        case 37: _t->setupAssets(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 32:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
