#-------------------------------------------------
#
# Project created by QtCreator 2020-06-10T10:53:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BallGame
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

QMAKE_CXXFLAGS += -g -O0 -ggdb
SOURCES += \
        main.cpp \
        mainwindow.cpp \
    server.cpp \
    client.cpp \
    command.cpp \
    diagrampolygon.cpp \
    entity.cpp \
    diagrampoint.cpp \
    diagramentity.cpp \
    inputtype.cpp \
    inputvalue.cpp \
    commandfactory.cpp \
    graphicsitem.cpp \
    datamanager.cpp \
    view.cpp \
    diagramscene.cpp \
    network.cpp \
    mediator.cpp \
    diagram.cpp \
    baseentity.cpp

HEADERS += \
        mainwindow.h \
    server.h \
    client.h \
    command.h \
    diagrampolygon.h \
    entity.h \
    diagrampoint.h \
    diagramentity.h \
    inputtype.h \
    inputvalue.h \
    commandfactory.h \
    graphicsitem.h \
    datamanager.h \
    view.h \
    diagramscene.h \
    network.h \
    mediator.h \
    diagram.h \
    baseentity.h

FORMS += \
        mainwindow.ui
