#-------------------------------------------------
#
# Project created by QtCreator 2020-10-23T10:52:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cryptProgram
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
        widget.cpp \
    des.cpp \
    des_ui.cpp \
    main_ui.cpp \
    xor_ui.cpp \
    clib.cpp \
    xor.cpp \
    des_ui_sbox.cpp \
    des_ui_change.cpp \
    dh.cpp \
    elgamal.cpp \
    rsa.cpp \
    dh_ui.cpp \
    elgamal_ui.cpp \
    rsa_ui.cpp \
    short_en.cpp

HEADERS += \
        widget.h \
    des.h \
    des_ui.h \
    main_ui.h \
    xor_ui.h \
    clib.h \
    xor.h \
    des_ui_sbox.h \
    des_ui_change.h \
    dh.h \
    elgamal.h \
    rsa.h \
    dh_ui.h \
    elgamal_ui.h \
    rsa_ui.h \
    short_en.h

FORMS += \
        widget.ui \
    des_ui.ui \
    main_ui.ui \
    xor_ui.ui \
    des_ui_sbox.ui \
    des_ui_change.ui \
    dh_ui.ui \
    elgamal_ui.ui \
    rsa_ui.ui \
    short_en.ui
