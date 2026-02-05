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
    GolemioClient/connectiongolemio.cpp \
    GolemioClient/connectiongolemiov4.cpp \
    GolemioClient/golemio.cpp \
    GolemioClient/golemioresultv4.cpp \
    GolemioClient/golemiov4.cpp \
    GolemioClient/stopgolemio.cpp \
    VDV301publisher/colordisplayrules.cpp \
    VDV301publisher/devicemanagementservice.cpp\
    VDV301publisher/httpserverpublisher.cpp \
    VDV301publisher/httpservice.cpp \
    VDV301publisher/subscriber.cpp \
    VDV301publisher/xmlcommon.cpp \
    VDV301publisher/xmldevicemanagementservice.cpp \
    VDV301subscriber/VDV301DataStructures/vdv301additionalannouncement.cpp \
    VDV301subscriber/VDV301DataStructures/vdv301additionalannouncement2_3cz1_0.cpp \
    VDV301subscriber/VDV301DataStructures/vdv301alldata.cpp \
    VDV301subscriber/VDV301DataStructures/vdv301alldata2_3cz1_0.cpp \
    VDV301subscriber/VDV301DataStructures/vdv301connection.cpp \
    VDV301subscriber/VDV301DataStructures/vdv301currentdisplaycontent.cpp \
    VDV301subscriber/VDV301DataStructures/vdv301destination.cpp \
    VDV301subscriber/VDV301DataStructures/vdv301displaycontent.cpp \
    VDV301subscriber/VDV301DataStructures/vdv301enumerations.cpp \
    VDV301subscriber/VDV301DataStructures/vdv301farezonechange2_3cz1_0.cpp \
    VDV301subscriber/VDV301DataStructures/vdv301internationaltext.cpp \
    VDV301subscriber/VDV301DataStructures/vdv301line.cpp \
    VDV301subscriber/VDV301DataStructures/vdv301stoppoint.cpp \
    VDV301subscriber/VDV301DataStructures/vdv301stoppoint2_3cz1_0.cpp \
    VDV301subscriber/VDV301DataStructures/vdv301trip.cpp \
    VDV301subscriber/VDV301DataStructures/vdv301trip2_3cz1_0.cpp \
    VDV301subscriber/VDV301DataStructures/vdv301vehicleinformationgroup.cpp \
    VDV301subscriber/VDV301DataStructures/vdv301viapoint.cpp \
    VDV301subscriber/cissubscriber.cpp \
    VDV301subscriber/httpserversubscriber.cpp \
    VDV301subscriber/ibisipsubscriber.cpp \
    VDV301subscriber/ibisipsubscribermultiplepublishers.cpp \
    VDV301subscriber/ibisipsubscriberonepublisher.cpp \
    VDV301subscriber/publisherstruct.cpp \
    VDV301subscriber/xmlgeneratorsubscriber.cpp \
    VDV301subscriber/xmlparsersubscriber.cpp \
    VDV301xmlparser/xmlparser.cpp \
    VDV301xmlparser/xmlparser1_0.cpp \
    VDV301xmlparser/xmlparser2_3.cpp \
    VDV301xmlparser/xmlparser2_3cz1_0.cpp \
    DisplayLabel/displaylabel.cpp \
    DisplayLabel/displaylabellcd.cpp \
    DisplayLabel/displaylabellcd2_3.cpp \
    DisplayLabel/displaylabellcd2_3cz1_0.cpp \
    DisplayLabel/displaylabellcd2_3cz1_0_jis.cpp \
    DisplayLabel/displaylabelled.cpp \
    inlineformatparser.cpp \
    mainwindowhelper.cpp \
    typeconvertor.cpp \
    main.cpp \
    mainwindow.cpp \
    svgvykreslovani.cpp \
    barvylinek.cpp


HEADERS += \
    GolemioClient/connectiongolemio.h \
    GolemioClient/connectiongolemiov4.h \
    GolemioClient/golemio.h \
    GolemioClient/golemioresultv4.h \
    GolemioClient/golemiov4.h \
    GolemioClient/stopgolemio.h \
    VDV301publisher/colordisplayrules.h \
    VDV301publisher/devicemanagementservice.h \
    VDV301publisher/httpserverpublisher.h \
    VDV301publisher/httpservice.h \
    VDV301publisher/subscriber.h \
    VDV301publisher/xmlcommon.h \
    VDV301publisher/xmldevicemanagementservice.h \
    VDV301subscriber/VDV301DataStructures/vdv301additionalannouncement.h \
    VDV301subscriber/VDV301DataStructures/vdv301additionalannouncement2_3cz1_0.h \
    VDV301subscriber/VDV301DataStructures/vdv301alldata.h \
    VDV301subscriber/VDV301DataStructures/vdv301alldata2_3cz1_0.h \
    VDV301subscriber/VDV301DataStructures/vdv301connection.h \
    VDV301subscriber/VDV301DataStructures/vdv301currentdisplaycontent.h \
    VDV301subscriber/VDV301DataStructures/vdv301destination.h \
    VDV301subscriber/VDV301DataStructures/vdv301displaycontent.h \
    VDV301subscriber/VDV301DataStructures/vdv301enumerations.h \
    VDV301subscriber/VDV301DataStructures/vdv301farezonechange2_3cz1_0.h \
    VDV301subscriber/VDV301DataStructures/vdv301internationaltext.h \
    VDV301subscriber/VDV301DataStructures/vdv301line.h \
    VDV301subscriber/VDV301DataStructures/vdv301stoppoint.h \
    VDV301subscriber/VDV301DataStructures/vdv301stoppoint2_3cz1_0.h \
    VDV301subscriber/VDV301DataStructures/vdv301trip.h \
    VDV301subscriber/VDV301DataStructures/vdv301trip2_3cz1_0.h \
    VDV301subscriber/VDV301DataStructures/vdv301vehicleinformationgroup.h \
    VDV301subscriber/VDV301DataStructures/vdv301viapoint.h \
    VDV301subscriber/cissubscriber.h \
    VDV301subscriber/httpserversubscriber.h \
    VDV301subscriber/ibisipsubscriber.h \
    VDV301subscriber/ibisipsubscribermultiplepublishers.h \
    VDV301subscriber/ibisipsubscriberonepublisher.h \
    VDV301subscriber/publisherstruct.h \
    VDV301subscriber/xmlgeneratorsubscriber.h \
    VDV301subscriber/xmlparsersubscriber.h \
    VDV301xmlparser/xmlparser.h \
    VDV301xmlparser/xmlparser1_0.h \
    VDV301xmlparser/xmlparser2_3.h \
    VDV301xmlparser/xmlparser2_3cz1_0.h \
    DisplayLabel/displaylabel.h \
    DisplayLabel/displaylabellcd.h \
    DisplayLabel/displaylabellcd2_3.h \
    DisplayLabel/displaylabellcd2_3cz1_0.h \
    DisplayLabel/displaylabellcd2_3cz1_0_jis.h \
    DisplayLabel/displaylabelled.h \
    inlineformatparser.h \
    mainwindow.h \
    mainwindowhelper.h \
    svgvykreslovani.h \
    typeconvertor.h \
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
