#-------------------------------------------------
#
# Project created by QtCreator 2019-03-08T13:46:03
#
#-------------------------------------------------

QT += core gui widgets

TARGET = ImageApp
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
    graphicsview.cpp \
    graphicsscene.cpp \
    mygraphicsrectitem.cpp \
    cornergrabber.cpp

HEADERS += \
    graphicsview.h \
    graphicsscene.h \
    mygraphicsrectitem.h \
    cornergrabber.h
