QT       += core gui
QT       += multimedia
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += resources_big

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0




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

INCLUDEPATH += Lib \


RESOURCES += \
    Images.qrc \
    maps.qrc \
    sounds.qrc

DISTFILES += \
    Lib/Player_Hit1.mp3 \
    Lib/Player_Hit2.mp3 \
    Lib/Player_Hit3.mp3

HEADERS += \
    Lib/All.h \
    Lib/Bar.h \
    Lib/BattleWindow.h \
    Lib/Boss1.h \
    Lib/Button.h \
    Lib/EditMap.h \
    Lib/Enemy.h \
    Lib/Object.h \
    Lib/Partical.h \
    Lib/Player.h \
    Lib/PlayerBullet1.h \
    Lib/PlayerBullet2.h \
    Lib/RedZone.h \
    Lib/Skill.h \
    Lib/glwidget.h \
    Lib/mainwindow.h \
    Lib/playerbullet3.h

SOURCES += \
    Lib/Bar.cpp \
    Lib/BattleWindow.cpp \
    Lib/BattleWindow_Introduce.cpp \
    Lib/BattleWindow_MainFun.cpp \
    Lib/BattleWindow_Mission.cpp \
    Lib/Boss1.cpp \
    Lib/Button.cpp \
    Lib/EditMap.cpp \
    Lib/Enemy.cpp \
    Lib/Object.cpp \
    Lib/Partical.cpp \
    Lib/Player.cpp \
    Lib/PlayerBullet1.cpp \
    Lib/PlayerBullet2.cpp \
    Lib/RedZone.cpp \
    Lib/Skill.cpp \
    Lib/glwidget.cpp \
    Lib/main.cpp \
    Lib/mainwindow.cpp \
    Lib/playerbullet3.cpp
