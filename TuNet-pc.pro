#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T17:30:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TuNet-pc
TEMPLATE = app


SOURCES += main.cpp\
        loginui.cpp \
    accountui.cpp

HEADERS  += loginui.h \
    accountui.h

FORMS    += loginui.ui \
    accountui.ui

QT += network
