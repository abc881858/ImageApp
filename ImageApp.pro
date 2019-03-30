#-------------------------------------------------
#
# Project created by QtCreator 2019-03-28T20:21:00
#
#-------------------------------------------------

QT += core gui
QT += widgets
#QT += opengl

TARGET = ImageApp
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    graphicsview.cpp \
    graphicsscene.cpp \
    graphicsrectitem.cpp \
    cornergrabber.cpp

HEADERS += \
        mainwindow.h \
    graphicsview.h \
    graphicsscene.h \
    graphicsrectitem.h \
    cornergrabber.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    res.qrc
