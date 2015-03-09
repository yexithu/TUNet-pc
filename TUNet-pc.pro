#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T17:30:48
#
#-------------------------------------------------
QT       += webkit
QT       += webkitwidgets
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TUNet-pc
TEMPLATE = app

SOURCES += \
    src/loginui.cpp \
    src/main.cpp \
    src/controller.cpp \
    src/accountui.cpp \
    src/network.cpp \
    src/aboutui.cpp \
    src/info.cpp \
    src/loadingui.cpp \
    src/failui.cpp \
    src/ipui.cpp

HEADERS  += \
    src/loginui.h \
    src/controller.h \
    src/accountui.h \
    src/network.h \
    src/aboutui.h \
    src/info.h \
    src/loadingui.h \
    src/failui.h \
    src/ipui.h

FORMS    += \
    form/loginui.ui \
    form/accountui.ui \
    form/aboutui.ui \
    form/loadingui.ui \
    form/failui.ui \
    form/ipui.ui

QT += network

RESOURCES += \
    res/resource.qrc

OTHER_FILES +=
