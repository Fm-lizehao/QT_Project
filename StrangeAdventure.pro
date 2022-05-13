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
        mainwindow.cpp

HEADERS  += mainwindow.h \
    resources.h

FORMS    += mainwindow.ui

RESOURCES += \
    source.qrc
