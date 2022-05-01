QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    character.cpp \
    combatwindow.cpp \
    gamemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    player.cpp \
    pokemon.cpp \
    pokemondatabase.cpp \
    tile.cpp \
    trainer.cpp \
    utility.cpp

HEADERS += \
    character.h \
    combatwindow.h \
    gamemanager.h \
    mainwindow.h \
    map.h \
    player.h \
    pokemon.h \
    pokemondatabase.h \
    tile.h \
    trainer.h \
    utility.h

FORMS += \
    combatwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
