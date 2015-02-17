#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T17:30:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TUNet-pc
TEMPLATE = app


SOURCES +=\
        loginui.cpp \
    main.cpp \
    controller.cpp \
    accountui.cpp \
    network.cpp

HEADERS  += loginui.h \
    controller.h \
    accountui.h \
    network.h

FORMS    += loginui.ui \
    accountui.ui

QT += network

RESOURCES += \
    resource.qrc

OTHER_FILES +=
