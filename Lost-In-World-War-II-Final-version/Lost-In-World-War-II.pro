QT       += core gui
QT       += multimedia
QT       += opengl
RC_ICONS = icon.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += resources_big

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0




FORMS += \
    BattleWindow.ui \
    Client.ui \
    EditMap.ui \
    Lib/Email.ui \
    Lib/Setting.ui \
    mainwindow.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += Lib \


RESOURCES += \
    Images.qrc \
    maps.qrc \
    sounds.qrc


HEADERS += \
    Lib/All.h \
    Lib/AllMusic.h \
    Lib/Bar.h \
    Lib/BattleWindow.h \
    Lib/Boss1.h \
    Lib/Button.h \
    Lib/Client.h \
    Lib/EditMap.h \
    Lib/Email.h \
    Lib/Enemy.h \
    Lib/Object.h \
    Lib/Partical.h \
    Lib/Player.h \
    Lib/PlayerBullet1.h \
    Lib/PlayerBullet2.h \
    Lib/RedZone.h \
    Lib/Setting.h \
    Lib/Skill.h \
    Lib/glwidget.h \
    Lib/glwidget_2.h \
    Lib/mainwindow.h \
    Lib/playerbullet3.h

SOURCES += \
    Lib/All.cpp \
    Lib/AllMusic.cpp \
    Lib/Bar.cpp \
    Lib/BattleWindow.cpp \
    Lib/BattleWindow_Bullet_HitCheck.cpp \
    Lib/BattleWindow_Internet.cpp \
    Lib/BattleWindow_Introduce.cpp \
    Lib/BattleWindow_MainFun.cpp \
    Lib/BattleWindow_Mission.cpp \
    Lib/Boss1.cpp \
    Lib/Button.cpp \
    Lib/Client.cpp \
    Lib/EditMap.cpp \
    Lib/Email.cpp \
    Lib/Enemy.cpp \
    Lib/Object.cpp \
    Lib/Partical.cpp \
    Lib/Player.cpp \
    Lib/PlayerBullet1.cpp \
    Lib/PlayerBullet2.cpp \
    Lib/RedZone.cpp \
    Lib/Setting.cpp \
    Lib/Skill.cpp \
    Lib/glwidget.cpp \
    Lib/glwidget_2.cpp \
    Lib/main.cpp \
    Lib/mainwindow.cpp \
    Lib/playerbullet3.cpp
