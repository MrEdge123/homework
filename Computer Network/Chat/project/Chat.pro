#-------------------------------------------------
#
# Project created by QtCreator 2020-06-06T21:12:42
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chat
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        loginwindow.cpp \
    listwindow.cpp \
    chatwindow.cpp \
    user.cpp \
    udpsend.cpp \
    filesendwindow.cpp \
    filegetwindow.cpp \
    fileprogresswindow.cpp

HEADERS += \
        loginwindow.h \
    listwindow.h \
    chatwindow.h \
    user.h \
    udpsend.h \
    msghead.h \
    filesendwindow.h \
    filegetwindow.h \
    fileprogresswindow.h

FORMS += \
        loginwindow.ui \
    listwindow.ui \
    chatwindow.ui \
    filesendwindow.ui \
    filegetwindow.ui \
    fileprogresswindow.ui

RESOURCES += \
    source.qrc
