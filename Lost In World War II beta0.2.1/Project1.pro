QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += resources_big

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BattleWindow.cpp \
    BattleWindow_Introduce.cpp \
    BattleWindow_MainFun.cpp \
    BattleWindow_Mission.cpp \
    Boss1.cpp \
    EditMap.cpp \
    Enemy.cpp \
    Object.cpp \
    Partical.cpp \
    Player.cpp \
    PlayerBullet1.cpp \
    PlayerBullet2.cpp \
    RedZone.cpp \
    main.cpp \
    mainwindow.cpp \
    playerbullet3.cpp

HEADERS += \
    All.h \
    BattleWindow.h \
    Boss1.h \
    EditMap.h \
    Enemy.h \
    Object.h \
    Partical.h \
    Player.h \
    PlayerBullet1.h \
    PlayerBullet2.h \
    RedZone.h \
    mainwindow.h \
    playerbullet3.h

FORMS += \
    BattleWindow.ui \
    EditMap.ui \
    mainwindow.ui

TRANSLATIONS += \
    Project1_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/Bedrock1.bmp \
    images/Bedrock2.bmp \
    images/River1.bmp \
    images/River2.bmp \
    images/Shot.bmp \
    images/TankDown.bmp \
    images/TankLeft.bmp \
    images/TankRight.bmp \
    images/TankUp.bmp \
    images/Wall1.bmp \
    images/Wall2.bmp

RESOURCES += \
    Images.qrc \
    maps.qrc \
    sounds.qrc
