#-------------------------------------------------
#
# Project created by QtCreator 2022-05-08T14:33:09
#
#-------------------------------------------------

QT       += core gui
QT  +=  multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StrangeAdventure
TEMPLATE = app
CONFIG += C++11

SOURCES += main.cpp\
        mainwindow.cpp \
    gamebutton.cpp \
    gameobject.cpp \
    gamepage.cpp \
    global.cpp

HEADERS  += mainwindow.h \
    gamebutton.h \
    gameobject.h \
    gamepage.h \
    global.h

FORMS    += mainwindow.ui

RESOURCES += \
    source.qrc
