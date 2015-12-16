#-------------------------------------------------
#
# Project created by QtCreator 2015-12-14T22:32:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtPathEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        pathreader.cpp

HEADERS  += mainwindow.h \
        pathreader.h

FORMS    += mainwindow.ui

win32:LIBS += -luser32
win32:LIBS += advapi32.lib
