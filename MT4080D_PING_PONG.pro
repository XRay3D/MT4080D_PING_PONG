#-------------------------------------------------
#
# Project created by QtCreator 2016-07-02T00:13:15
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MT4080D_PING_PONG
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tester.cpp

HEADERS  += mainwindow.h \
    tester.h

FORMS    += mainwindow.ui
