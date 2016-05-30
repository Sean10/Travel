#-------------------------------------------------
#
# Project created by QtCreator 2016-03-22T09:08:28
#
#-------------------------------------------------
QT       += core
CONFIG   += gui
#CONFIG   += console


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Travel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mapwidget.cpp

HEADERS  += mainwindow.h \
    ihead.h \
    mapwidget.h

FORMS    += mainwindow.ui \
    form.ui

RESOURCES += \
    img.qrc

DISTFILES +=
