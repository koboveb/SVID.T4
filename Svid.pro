#-------------------------------------------------
#
# Project created by QtCreator 2019-10-22T14:23:47
#
#-------------------------------------------------

QT       += core gui xml sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Svid
TEMPLATE = app


SOURCES += main.cpp\
    StorData.cpp \
        mainwindow.cpp \
    DialGen.cpp \
    ModelUni.cpp \
    StorProject.cpp \
    TTextedit.cpp

HEADERS  += mainwindow.h \
    DialGen.h \
    ModelUni.h \
    StorData.h \
    StorProject.h \
    TTextedit.h

FORMS    += mainwindow.ui
