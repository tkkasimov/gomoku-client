#-------------------------------------------------
#
# Project created by QtCreator 2012-09-23T23:14:57
#
#-------------------------------------------------

QT       += core gui network

TARGET = gomoku
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    field.cpp \
    net.cpp \
    ConnectionInfoDialog.cpp

HEADERS  += mainwindow.h \
    field.h \
    defines.h \
    net.h \
    ConnectionInfoDialog.h

FORMS    += mainwindow.ui

RESOURCES += \
    resourse/resourse.qrc
