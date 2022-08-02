#-------------------------------------------------
#
# Project created by QtCreator 2018-06-07T13:35:40
#
#-------------------------------------------------

QT       += core gui
QT += xml
QT       += core gui network
QT+= httpserver
QT += svg



#QT += svg
#QT += webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VDV301display
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES+= QZEROCONF_STATIC
include(VDV301subscriber/QtZeroConf/qtzeroconf.pri)
target.path=/home/pi
target.files=VDV301displayNew
INSTALLS+=target

SOURCES += \
    VDV301subscriber/newhttpserver.cpp \
    VDV301subscriber/ibisipsubscriber.cpp \
    labelvykreslovani.cpp \
        main.cpp \
        mainwindow.cpp \
    pasmovedvojicelcd.cpp \
    svgvykreslovani.cpp \
    xmlparser.cpp \
    VDV301struktury/zastavka.cpp\
    VDV301struktury/zastavkacil.cpp\
    VDV301struktury/cestaudaje.cpp\
    VDV301struktury/linka.cpp\
    VDV301struktury/obeh.cpp\
    VDV301struktury/spoj.cpp\
    VDV301struktury/pasmo.cpp\
    VDV301struktury/prestup.cpp\
    VDV301struktury/specialnihlaseni.cpp
HEADERS += \
    VDV301subscriber/newhttpserver.h \
    VDV301subscriber/ibisipsubscriber.h \
    labelvykreslovani.h \
        mainwindow.h \
    pasmovedvojicelcd.h \
    svgvykreslovani.h \
    xmlparser.h \
    VDV301struktury/zastavka.h\
    VDV301struktury/zastavkacil.h\
    VDV301struktury/pasmo.h\
    VDV301struktury/linka.h\
    VDV301struktury/obeh.h\
    VDV301struktury/spoj.h\
    VDV301struktury/prestup.h\
    VDV301struktury/cestaudaje.h\
    VDV301struktury/specialnihlaseni.cpp


FORMS += \
        mainwindow.ui

RESOURCES += \
    resources.qrc
