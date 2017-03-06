#-------------------------------------------------
#
# Project created by QtCreator 2017-01-17T11:15:12
#
#-------------------------------------------------

QT       += core gui \
         multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(quazip/quazip.pri)

TARGET = MapEditor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS \
    QUAZIP_STATIC

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += console

SOURCES += main.cpp\
        mainwindow.cpp \
    mapview2.cpp \
    texture.cpp \
    tile.cpp \
    graphicsscene.cpp \
    terrain.cpp \
    dialogs/dgmapproperties.cpp \
    dialogs/dgabout.cpp \
    dialogs/dgplayerproperties.cpp \
    dialogs/dgassets.cpp \
    mapview.cpp \
    exporttoweb.cpp \
    dialogs/dgaddtrigger.cpp \
    aitrigger.cpp \
    newproject.cpp

HEADERS  += mainwindow.h \
    mapview2.h \
    texture.h \
    tile.h \
    graphicsscene.h \
    terrain.h \
    dialogs/dgmapproperties.h \
    dialogs/dgabout.h \
    dialogs/dgplayerproperties.h \
    dialogs/dgassets.h \
    mapview.h \
    exporttoweb.h \
    dialogs/dgaddtrigger.h \
    aitrigger.h \
    newproject.h

FORMS    += mainwindow.ui \
    dialogs/dgmapproperties.ui \
    dialogs/dgabout.ui \
    dialogs/dgplayerproperties.ui \
    dialogs/dgassets.ui \
    exporttoweb.ui \
    dialogs/dgaddtrigger.ui \
    newproject.ui

RESOURCES += \
    icons.qrc \
    maps.qrc \
    images.qrc \
    snd.qrc


DISTFILES += \
    ../data/default/snd/music/game1.mid \
    ../data/default/snd/music/game2.mid \
    ../data/default/snd/music/game3.mid \
    ../data/default/snd/music/game4.mid \
    ../data/default/snd/music/game5.mid \
    ../data/default/snd/music/intro.mid \
    ../data/default/snd/music/load.mid \
    ../data/default/snd/music/lose.mid \
    ../data/default/snd/music/menu.mid \
    ../data/default/snd/music/win.mid \
    ../data/default/snd/generalsoundfont.sf2 \
    ../data/default/snd/archer/acknowledge1.wav \
    ../data/default/snd/archer/acknowledge2.wav \
    ../data/default/snd/archer/acknowledge3.wav \
    ../data/default/snd/archer/acknowledge4.wav \
    ../data/default/snd/archer/annoyed1.wav \
    ../data/default/snd/archer/annoyed2.wav \
    ../data/default/snd/archer/annoyed3.wav \
    ../data/default/snd/archer/ready.wav \
    ../data/default/snd/archer/selected1.wav \
    ../data/default/snd/archer/selected2.wav \
    ../data/default/snd/archer/selected3.wav \
    ../data/default/snd/archer/selected4.wav \
    ../data/default/snd/basic/acknowledge1.wav \
    ../data/default/snd/basic/acknowledge2.wav \
    ../data/default/snd/basic/acknowledge3.wav \
    ../data/default/snd/basic/acknowledge4.wav \
    ../data/default/snd/basic/annoyed1.wav \
    ../data/default/snd/basic/annoyed2.wav \
    ../data/default/snd/basic/annoyed3.wav \
    ../data/default/snd/basic/annoyed4.wav \
    ../data/default/snd/basic/annoyed5.wav \
    ../data/default/snd/basic/annoyed6.wav \
    ../data/default/snd/basic/annoyed7.wav \
    ../data/default/snd/basic/building-help.wav \
    ../data/default/snd/basic/death.wav \
    ../data/default/snd/basic/ready.wav \
    ../data/default/snd/basic/selected1.wav \
    ../data/default/snd/basic/selected2.wav \
    ../data/default/snd/basic/selected3.wav \
    ../data/default/snd/basic/selected4.wav \
    ../data/default/snd/basic/selected5.wav \
    ../data/default/snd/basic/selected6.wav \
    ../data/default/snd/basic/unit-help.wav \
    ../data/default/snd/basic/work-completed.wav \
    ../data/default/snd/buildings/blacksmith.wav \
    ../data/default/snd/buildings/farm.wav \
    ../data/default/snd/buildings/gold-mine.wav \
    ../data/default/snd/buildings/lumber-mill.wav \
    ../data/default/snd/misc/bowfire.wav \
    ../data/default/snd/misc/bowhit.wav \
    ../data/default/snd/misc/building-explode1.wav \
    ../data/default/snd/misc/building-explode2.wav \
    ../data/default/snd/misc/building-explode3.wav \
    ../data/default/snd/misc/burning.wav \
    ../data/default/snd/misc/cannonfire.wav \
    ../data/default/snd/misc/cannonhit.wav \
    ../data/default/snd/misc/construct.wav \
    ../data/default/snd/misc/explode.wav \
    ../data/default/snd/misc/sword1.wav \
    ../data/default/snd/misc/sword2.wav \
    ../data/default/snd/misc/sword3.wav \
    ../data/default/snd/misc/thunk.wav \
    ../data/default/snd/misc/tick.wav \
    ../data/default/snd/misc/tock.wav \
    ../data/default/snd/misc/tree1.wav \
    ../data/default/snd/misc/tree2.wav \
    ../data/default/snd/misc/tree3.wav \
    ../data/default/snd/misc/tree4.wav \
    ../data/default/snd/peasant/acknowledge1.wav \
    ../data/default/snd/peasant/acknowledge2.wav \
    ../data/default/snd/peasant/acknowledge3.wav \
    ../data/default/snd/peasant/acknowledge4.wav \
    ../data/default/snd/peasant/annoyed1.wav \
    ../data/default/snd/peasant/annoyed2.wav \
    ../data/default/snd/peasant/annoyed3.wav \
    ../data/default/snd/peasant/annoyed4.wav \
    ../data/default/snd/peasant/annoyed5.wav \
    ../data/default/snd/peasant/annoyed6.wav \
    ../data/default/snd/peasant/annoyed7.wav \
    ../data/default/snd/peasant/ready.wav \
    ../data/default/snd/peasant/selected1.wav \
    ../data/default/snd/peasant/selected2.wav \
    ../data/default/snd/peasant/selected3.wav \
    ../data/default/snd/peasant/selected4.wav \
    ../data/default/snd/peasant/work-completed.wav \
    ../data/default/img/Archer.png \
    ../data/default/img/Arrow.png \
    ../data/default/img/AssetColor.png \
    ../data/default/img/AssetNone.png \
    ../data/default/img/Barracks.png \
    ../data/default/img/Blacksmith.png \
    ../data/default/img/BuildingDeath.png \
    ../data/default/img/ButtonColors.png \
    ../data/default/img/Cannonball.png \
    ../data/default/img/CannonballDeath.png \
    ../data/default/img/CannonTower.png \
    ../data/default/img/Castle.png \
    ../data/default/img/Colors.png \
    ../data/default/img/Corpse.png \
    ../data/default/img/Cursors.png \
    ../data/default/img/Farm.png \
    ../data/default/img/FireLarge.png \
    ../data/default/img/FireSmall.png \
    ../data/default/img/Fog.png \
    ../data/default/img/FontColors.png \
    ../data/default/img/FontKingthings10.png \
    ../data/default/img/FontKingthings12.png \
    ../data/default/img/FontKingthings16.png \
    ../data/default/img/FontKingthings24.png \
    ../data/default/img/FontKingthings8.png \
    ../data/default/img/Footman.png \
    ../data/default/img/GoldMine.png \
    ../data/default/img/GuardTower.png \
    ../data/default/img/Icons.png \
    ../data/default/img/InnerBevel.png \
    ../data/default/img/Keep.png \
    ../data/default/img/ListViewIcons.png \
    ../data/default/img/LumberMill.png \
    ../data/default/img/Marker.png \
    ../data/default/img/MiniBevel.png \
    ../data/default/img/MiniIcons.png \
    ../data/default/img/OuterBevel.png \
    ../data/default/img/Peasant.png \
    ../data/default/img/Ranger.png \
    ../data/default/img/ScoutTower.png \
    ../data/default/img/Splash.png \
    ../data/default/img/Terrain.png \
    ../data/default/img/Texture.png \
    ../data/default/img/TownHall.png \
    ../data/default/img/Trigger.png \
    ../data/default/img/Archer.dat \
    ../data/default/img/Arrow.dat \
    ../data/default/img/AssetColor.dat \
    ../data/default/img/AssetNone.dat \
    ../data/default/img/Barracks.dat \
    ../data/default/img/Blacksmith.dat \
    ../data/default/img/BuildingDeath.dat \
    ../data/default/img/ButtonColors.dat \
    ../data/default/img/Cannonball.dat \
    ../data/default/img/CannonballDeath.dat \
    ../data/default/img/CannonTower.dat \
    ../data/default/img/Castle.dat \
    ../data/default/img/Colors.dat \
    ../data/default/img/Corpse.dat \
    ../data/default/img/Cursors.dat \
    ../data/default/img/Farm.dat \
    ../data/default/img/FireLarge.dat \
    ../data/default/img/FireSmall.dat \
    ../data/default/img/Fog.dat \
    ../data/default/img/FontColors.dat \
    ../data/default/img/FontKingthings10.dat \
    ../data/default/img/FontKingthings12.dat \
    ../data/default/img/FontKingthings16.dat \
    ../data/default/img/FontKingthings24.dat \
    ../data/default/img/FontKingthings8.dat \
    ../data/default/img/Footman.dat \
    ../data/default/img/GoldMine.dat \
    ../data/default/img/GuardTower.dat \
    ../data/default/img/Icons.dat \
    ../data/default/img/InnerBevel.dat \
    ../data/default/img/Keep.dat \
    ../data/default/img/ListViewIcons.dat \
    ../data/default/img/LumberMill.dat \
    ../data/default/img/MapRendering.dat \
    ../data/default/img/Marker.dat \
    ../data/default/img/MiniBevel.dat \
    ../data/default/img/MiniIcons.dat \
    ../data/default/img/OuterBevel.dat \
    ../data/default/img/Peasant.dat \
    ../data/default/img/Ranger.dat \
    ../data/default/img/ScoutTower.dat \
    ../data/default/img/Splash.dat \
    ../data/default/img/Terrain.dat \
    ../data/default/img/Texture.dat \
    ../data/default/img/TownHall.dat \
    ../data/default/img/Trigger.dat \
    ../data/default/res/Archer.dat \
    ../data/default/res/Barracks.dat \
    ../data/default/res/Blacksmith.dat \
    ../data/default/res/CannonTower.dat \
    ../data/default/res/Castle.dat \
    ../data/default/res/Farm.dat \
    ../data/default/res/Footman.dat \
    ../data/default/res/GoldMine.dat \
    ../data/default/res/GuardTower.dat \
    ../data/default/res/Keep.dat \
    ../data/default/res/LumberMill.dat \
    ../data/default/res/Peasant.dat \
    ../data/default/res/Ranger.dat \
    ../data/default/res/ScoutTower.dat \
    ../data/default/res/TownHall.dat \
    ../data/default/snd/SoundClips.dat \
    ../data/default/upg/Armor2.dat \
    ../data/default/upg/Armor3.dat \
    ../data/default/upg/Arrow2.dat \
    ../data/default/upg/Arrow3.dat \
    ../data/default/upg/Longbow.dat \
    ../data/default/upg/Marksmanship.dat \
    ../data/default/upg/Ranger.dat \
    ../data/default/upg/Scouting.dat \
    ../data/default/upg/Weapon2.dat \
    ../data/default/upg/Weapon3.dat
