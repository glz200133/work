#-------------------------------------------------
#
# Project created by QtCreator 2020-05-30T15:14:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = work1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    button.cpp \
    towerparent.cpp \
    monster.cpp \
    towerson1.cpp \
    towerspot.cpp \
    gamewindow.cpp \
    selectbutton.cpp \
    towerson2.cpp \
    towerson3.cpp \
    towerson4.cpp \
    failwindow.cpp \
    winwindow.cpp \
    stilltower.cpp

HEADERS += \
        mainwindow.h \
    button.h \
    towerparent.h \
    monster.h \
    mainstruct.h \
    towerson1.h \
    towerspot.h \
    gamewindow.h \
    selectbutton.h \
    towerson2.h \
    towerson3.h \
    towerson4.h \
    failwindow.h \
    winwindow.h \
    stilltower.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    3.qrc \
    4.qrc \
    5.qrc \
    6.qrc \
    10.qrc \
    14.qrc \
    16.qrc \
    19.qrc \
    20.qrc \
    map.qrc \
    fail.qrc \
    24.qrc \
    vic.qrc \
    bullet.qrc \
    music.qrc \
    back.qrc \
    delete.qrc

QT+=multimedia
CONFIG+=resources_big
