#-------------------------------------------------
#
# Project created by QtCreator 2015-06-04T15:20:27
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GradeCollector
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameboard.cpp

HEADERS  += mainwindow.h \
    gameboard.h

FORMS    += mainwindow.ui \
    gameboard.ui

RESOURCES += \
    images.qrc
