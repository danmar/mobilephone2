
#-------------------------------------------------
#
# Project created by QtCreator 2018-02-27T12:54:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mobilephone2
TEMPLATE = app

QMAKE_CXXFLAGS += -Wno-missing-field-initializers

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -std=c++14

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        smsscreen.cpp \
        homescreen.cpp \
        phonescreen.cpp \
        gsminterface.cpp \
        hangupscreen.cpp \
        smslistwidget.cpp \
        writesmsscreen.cpp \
        virtualkeyboard.cpp

HEADERS += \
        mainwindow.h \
        smsscreen.h \
        homescreen.h \
        phonescreen.h \
        gsminterface.h \
        hangupscreen.h \
        smslistwidget.h \
        writesmsscreen.h \
        virtualkeyboard.h

FORMS += \
        mainwindow.ui \
        smsscreen.ui \
        homescreen.ui \
        phonescreen.ui \
        hangupscreen.ui \
        writesmsscreen.ui

RESOURCES = mobilephone2.qrc
