#-------------------------------------------------
#
# Project created by QtCreator 2017-01-17T11:15:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MapEditor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += console

SOURCES += main.cpp\
        mainwindow.cpp \
    mapview2.cpp \
    texture.cpp \
    tile.cpp

HEADERS  += mainwindow.h \
    mapview2.h \
    texture.h \
    tile.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc \
    maps.qrc \
    images.qrc

DISTFILES += \
    ../data/snd/music/game1.mid \
    ../data/snd/music/game2.mid \
    ../data/snd/music/game3.mid \
    ../data/snd/music/game4.mid \
    ../data/snd/music/game5.mid \
    ../data/snd/music/intro.mid \
    ../data/snd/music/load.mid \
    ../data/snd/music/lose.mid \
    ../data/snd/music/menu.mid \
    ../data/snd/music/win.mid \
    ../data/snd/generalsoundfont.sf2 \
    ../data/snd/archer/acknowledge1.wav \
    ../data/snd/archer/acknowledge2.wav \
    ../data/snd/archer/acknowledge3.wav \
    ../data/snd/archer/acknowledge4.wav \
    ../data/snd/archer/annoyed1.wav \
    ../data/snd/archer/annoyed2.wav \
    ../data/snd/archer/annoyed3.wav \
    ../data/snd/archer/ready.wav \
    ../data/snd/archer/selected1.wav \
    ../data/snd/archer/selected2.wav \
    ../data/snd/archer/selected3.wav \
    ../data/snd/archer/selected4.wav \
    ../data/snd/basic/acknowledge1.wav \
    ../data/snd/basic/acknowledge2.wav \
    ../data/snd/basic/acknowledge3.wav \
    ../data/snd/basic/acknowledge4.wav \
    ../data/snd/basic/annoyed1.wav \
    ../data/snd/basic/annoyed2.wav \
    ../data/snd/basic/annoyed3.wav \
    ../data/snd/basic/annoyed4.wav \
    ../data/snd/basic/annoyed5.wav \
    ../data/snd/basic/annoyed6.wav \
    ../data/snd/basic/annoyed7.wav \
    ../data/snd/basic/building-help.wav \
    ../data/snd/basic/death.wav \
    ../data/snd/basic/ready.wav \
    ../data/snd/basic/selected1.wav \
    ../data/snd/basic/selected2.wav \
    ../data/snd/basic/selected3.wav \
    ../data/snd/basic/selected4.wav \
    ../data/snd/basic/selected5.wav \
    ../data/snd/basic/selected6.wav \
    ../data/snd/basic/unit-help.wav \
    ../data/snd/basic/work-completed.wav \
    ../data/snd/buildings/blacksmith.wav \
    ../data/snd/buildings/farm.wav \
    ../data/snd/buildings/gold-mine.wav \
    ../data/snd/buildings/lumber-mill.wav \
    ../data/snd/misc/bowfire.wav \
    ../data/snd/misc/bowhit.wav \
    ../data/snd/misc/building-explode1.wav \
    ../data/snd/misc/building-explode2.wav \
    ../data/snd/misc/building-explode3.wav \
    ../data/snd/misc/burning.wav \
    ../data/snd/misc/cannonfire.wav \
    ../data/snd/misc/cannonhit.wav \
    ../data/snd/misc/construct.wav \
    ../data/snd/misc/explode.wav \
    ../data/snd/misc/sword1.wav \
    ../data/snd/misc/sword2.wav \
    ../data/snd/misc/sword3.wav \
    ../data/snd/misc/thunk.wav \
    ../data/snd/misc/tick.wav \
    ../data/snd/misc/tock.wav \
    ../data/snd/misc/tree1.wav \
    ../data/snd/misc/tree2.wav \
    ../data/snd/misc/tree3.wav \
    ../data/snd/misc/tree4.wav \
    ../data/snd/peasant/acknowledge1.wav \
    ../data/snd/peasant/acknowledge2.wav \
    ../data/snd/peasant/acknowledge3.wav \
    ../data/snd/peasant/acknowledge4.wav \
    ../data/snd/peasant/annoyed1.wav \
    ../data/snd/peasant/annoyed2.wav \
    ../data/snd/peasant/annoyed3.wav \
    ../data/snd/peasant/annoyed4.wav \
    ../data/snd/peasant/annoyed5.wav \
    ../data/snd/peasant/annoyed6.wav \
    ../data/snd/peasant/annoyed7.wav \
    ../data/snd/peasant/ready.wav \
    ../data/snd/peasant/selected1.wav \
    ../data/snd/peasant/selected2.wav \
    ../data/snd/peasant/selected3.wav \
    ../data/snd/peasant/selected4.wav \
    ../data/snd/peasant/work-completed.wav \
    ../data/img/Archer.png \
    ../data/img/Arrow.png \
    ../data/img/AssetColor.png \
    ../data/img/AssetNone.png \
    ../data/img/Barracks.png \
    ../data/img/Blacksmith.png \
    ../data/img/BuildingDeath.png \
    ../data/img/ButtonColors.png \
    ../data/img/Cannonball.png \
    ../data/img/CannonballDeath.png \
    ../data/img/CannonTower.png \
    ../data/img/Castle.png \
    ../data/img/Colors.png \
    ../data/img/Corpse.png \
    ../data/img/Cursors.png \
    ../data/img/Farm.png \
    ../data/img/FireLarge.png \
    ../data/img/FireSmall.png \
    ../data/img/Fog.png \
    ../data/img/FontColors.png \
    ../data/img/FontKingthings10.png \
    ../data/img/FontKingthings12.png \
    ../data/img/FontKingthings16.png \
    ../data/img/FontKingthings24.png \
    ../data/img/FontKingthings8.png \
    ../data/img/Footman.png \
    ../data/img/GoldMine.png \
    ../data/img/GuardTower.png \
    ../data/img/Icons.png \
    ../data/img/InnerBevel.png \
    ../data/img/Keep.png \
    ../data/img/ListViewIcons.png \
    ../data/img/LumberMill.png \
    ../data/img/Marker.png \
    ../data/img/MiniBevel.png \
    ../data/img/MiniIcons.png \
    ../data/img/OuterBevel.png \
    ../data/img/Peasant.png \
    ../data/img/Ranger.png \
    ../data/img/ScoutTower.png \
    ../data/img/Splash.png \
    ../data/img/Terrain.png \
    ../data/img/Texture.png \
    ../data/img/TownHall.png \
    ../data/img/Archer.dat \
    ../data/img/Arrow.dat \
    ../data/img/AssetColor.dat \
    ../data/img/AssetNone.dat \
    ../data/img/Barracks.dat \
    ../data/img/Blacksmith.dat \
    ../data/img/BuildingDeath.dat \
    ../data/img/ButtonColors.dat \
    ../data/img/Cannonball.dat \
    ../data/img/CannonballDeath.dat \
    ../data/img/CannonTower.dat \
    ../data/img/Castle.dat \
    ../data/img/Colors.dat \
    ../data/img/Corpse.dat \
    ../data/img/Cursors.dat \
    ../data/img/Farm.dat \
    ../data/img/FireLarge.dat \
    ../data/img/FireSmall.dat \
    ../data/img/Fog.dat \
    ../data/img/FontColors.dat \
    ../data/img/FontKingthings10.dat \
    ../data/img/FontKingthings12.dat \
    ../data/img/FontKingthings16.dat \
    ../data/img/FontKingthings24.dat \
    ../data/img/FontKingthings8.dat \
    ../data/img/Footman.dat \
    ../data/img/GoldMine.dat \
    ../data/img/GuardTower.dat \
    ../data/img/Icons.dat \
    ../data/img/InnerBevel.dat \
    ../data/img/Keep.dat \
    ../data/img/ListViewIcons.dat \
    ../data/img/LumberMill.dat \
    ../data/img/MapRendering.dat \
    ../data/img/Marker.dat \
    ../data/img/MiniBevel.dat \
    ../data/img/MiniIcons.dat \
    ../data/img/OuterBevel.dat \
    ../data/img/Peasant.dat \
    ../data/img/Ranger.dat \
    ../data/img/ScoutTower.dat \
    ../data/img/Splash.dat \
    ../data/img/Terrain.dat \
    ../data/img/Texture.dat \
    ../data/img/TownHall.dat \
    ../data/res/Archer.dat \
    ../data/res/Barracks.dat \
    ../data/res/Blacksmith.dat \
    ../data/res/CannonTower.dat \
    ../data/res/Castle.dat \
    ../data/res/Farm.dat \
    ../data/res/Footman.dat \
    ../data/res/GoldMine.dat \
    ../data/res/GuardTower.dat \
    ../data/res/Keep.dat \
    ../data/res/LumberMill.dat \
    ../data/res/Peasant.dat \
    ../data/res/Ranger.dat \
    ../data/res/ScoutTower.dat \
    ../data/res/TownHall.dat \
    ../data/snd/SoundClips.dat \
    ../data/upg/Armor2.dat \
    ../data/upg/Armor3.dat \
    ../data/upg/Arrow2.dat \
    ../data/upg/Arrow3.dat \
    ../data/upg/Longbow.dat \
    ../data/upg/Marksmanship.dat \
    ../data/upg/Ranger.dat \
    ../data/upg/Scouting.dat \
    ../data/upg/Weapon2.dat \
    ../data/upg/Weapon3.dat
