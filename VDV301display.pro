#-------------------------------------------------
#
# Project created by QtCreator 2018-06-07T13:35:40
#
#-------------------------------------------------

QT += core gui
QT += xml
QT += core gui network
QT += httpserver
QT += svg
#CONFIG   += console



#DEFINES+= QZEROCONF_STATIC

#include(qtzeroconf/qtzeroconf.pri)



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

greaterThan(QT_MAJOR_VERSION, 5): QT += svgwidgets

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
    VDV301DataStructures/connectionmpv.cpp \
    VDV301DataStructures/additionalannoucement.cpp \
    VDV301DataStructures/connection.cpp \
    VDV301DataStructures/connectiongolemio.cpp \
    VDV301DataStructures/farezone.cpp \
    VDV301DataStructures/line.cpp \
    VDV301DataStructures/stoppoint.cpp \
    VDV301DataStructures/stoppointdestination.cpp \
    VDV301DataStructures/trip.cpp \
    VDV301DataStructures/vdv301destination.cpp \
    VDV301DataStructures/vdv301displaycontent.cpp \
    VDV301DataStructures/vdv301internationaltext.cpp \
    VDV301DataStructures/vdv301line.cpp \
    VDV301DataStructures/vdv301stoppoint.cpp \
    VDV301DataStructures/vdv301trip.cpp \
    VDV301DataStructures/vdv301viapoint.cpp \
    VDV301DataStructures/vehiclerun.cpp \
    VDV301DataStructures/vehiclestate.cpp \
    VDV301publisher/colordisplayrules.cpp \
    VDV301publisher/customerinformationservice.cpp \
    VDV301publisher/devicemanagementservice.cpp\
    VDV301publisher/httpserverpublisher.cpp \
    VDV301publisher/httpservice.cpp \
    VDV301publisher/subscriber.cpp \
    VDV301publisher/ticketvalidationservice.cpp \
    VDV301publisher/xmlcommon.cpp \
    VDV301publisher/xmlcustomerinformationservice.cpp \
    VDV301publisher/xmldevicemanagementservice.cpp \
    VDV301publisher/xmlticketvalidationservice.cpp \
    VDV301subscriber/cissubscriber.cpp \
    VDV301subscriber/devmgmtpublisherstruct.cpp \
    VDV301subscriber/devmgmtsubscriber.cpp \
    VDV301subscriber/httpserversubscriber.cpp \
    VDV301subscriber/ibisipsubscriber.cpp \
    VDV301subscriber/xmlgeneratorsubscriber.cpp \
    VDV301subscriber/xmlparsersubscriber.cpp \
    inlineformatparser.cpp \
    VDV301subscriber/ibisipsubscriberonepublisher.cpp \
    labelvykreslovani.cpp \
        main.cpp \
        mainwindow.cpp \
    pasmovedvojicelcd.cpp \
    svgvykreslovani.cpp \
    xmlparser.cpp \
    barvylinek.cpp

HEADERS += \
    VDV301DataStructures/additionalannoucement.h \
    VDV301DataStructures/connection.h \
    VDV301DataStructures/connectiongolemio.h \
    VDV301DataStructures/connectionmpv.h \
    VDV301DataStructures/farezone.h \
    VDV301DataStructures/line.h \
    VDV301DataStructures/stoppoint.h \
    VDV301DataStructures/stoppointdestination.h \
    VDV301DataStructures/trip.h \
    VDV301DataStructures/vdv301destination.h \
    VDV301DataStructures/vdv301displaycontent.h \
    VDV301DataStructures/vdv301internationaltext.h \
    VDV301DataStructures/vdv301line.h \
    VDV301DataStructures/vdv301stoppoint.h \
    VDV301DataStructures/vdv301trip.h \
    VDV301DataStructures/vdv301viapoint.h \
    VDV301DataStructures/vehiclerun.h \
    VDV301DataStructures/vehiclestate.h \
    VDV301publisher/colordisplayrules.h \
    VDV301publisher/customerinformationservice.h \
    VDV301publisher/devicemanagementservice.h \
    VDV301publisher/httpserverpublisher.h \
    VDV301publisher/httpservice.h \
    VDV301publisher/subscriber.h \
    VDV301publisher/ticketvalidationservice.h \
    VDV301publisher/xmlcommon.h \
    VDV301publisher/xmlcustomerinformationservice.h \
    VDV301publisher/xmldevicemanagementservice.h \
    VDV301publisher/xmlticketvalidationservice.h \
    VDV301subscriber/cissubscriber.h \
    VDV301subscriber/devmgmtpublisherstruct.h \
    VDV301subscriber/devmgmtsubscriber.h \
    VDV301subscriber/httpserversubscriber.h \
    VDV301subscriber/ibisipsubscriber.h \
    VDV301subscriber/ibisipsubscriberonepublisher.h \
    VDV301subscriber/xmlgeneratorsubscriber.h \
    VDV301subscriber/xmlparsersubscriber.h \
    inlineformatparser.h \
    labelvykreslovani.h \
    mainwindow.h \
    pasmovedvojicelcd.h \
    svgvykreslovani.h \
    xmlparser.h \
    barvylinek.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    lang.qrc \
    resources.qrc


TRANSLATIONS += \
    lang_en.ts\
    lang_cs.ts


RESOURCES += \
    lang.qrc


RC_ICONS = vdv301display_K17_icon.ico
