#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "VDV301xmlparser/xmlparser1_0.h"
//#include "VDV301xmlparser/xmlparser2_2cz1_0.h"
#include "VDV301xmlparser/xmlparser2_3.h"
#include "VDV301xmlparser/xmlparser2_3cz1_0.h"


#include "VDV301publisher/devicemanagementservice.h"
#include "VDV301subscriber/cissubscriber.h"

#include "svgvykreslovani.h"
#include "DisplayLabel/displaylabelled.h"
#include "DisplayLabel/displaylabellcd2_3cz1_0.h"
#include "DisplayLabel/displaylabellcd2_3cz1_0_jis.h"

#include "GolemioClient/golemiov4.h"
#include "barvylinek.h"
#include "typeconvertor.h"
#include "mainwindowhelper.h"

#include <QApplication>
#include <QCoreApplication>
//#include <QtDebug>
#include <QFile>
#include <QFontDatabase>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QShortcut>
#include <QTableWidget>
#include <QTextStream>
#include <QUrl>
#include <QLoggingCategory>

#include <QGraphicsSvgItem>
#include <QGraphicsScene>
#include <QSvgRenderer>
#include <QSvgWidget>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class QByteArray;
class QNetworkAccessManager;
class QNetworkReply;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QString configurationFilePath, QWidget *parent = nullptr);
    Ui::MainWindow *ui;
    ~MainWindow();



private:

    //QCommandLineParser qCommandLineParser;
    QSettings settings;

    // complex class instances
    XmlParser1_0 xmlParser1_0;
    XmlParser2_3 xmlParser2_3;
    XmlParser2_3CZ1_0 xmlParser2_3CZ1_0;


    DisplayLabelLcd2_3CZ1_0 displayLabelLcd;
    DisplayLabelLcd2_3CZ1_0_Jis displayLabelLcdJis;

    DisplayLabelLed displayLabelLed;


    SvgVykreslovani svgVykreslovani;

    CisSubscriber cisSubscriber;
    DeviceManagementService deviceManagementService;

    GolemioV4 golemio;




    //complex variables

    QVector<Vdv301StopPoint> currentVdv301StopPointList;

    Vdv301AllData vdv301AllData;
    Vdv301AllData2_3CZ1_0 vdv301AllData2_3CZ1_0;
    Vdv301AllData2_3CZ1_0 vdv301AllData2_3CZ1_0_previous;

    Vdv301CurrentDisplayContent vdv301currentDisplayContent;

    BarvyLinek barvyLinek;

    MainWindowHelper mainWindowHelper;

    //stavove promenne


    int lcdLabelCurrentPageIndex =0;
    int lcdLabelCurrentPageIndexJis =0;

    bool showTimeColon=0;

    int receivedMessagesCounter=0;
    //constants
    const int intervalSideDisplay=2000; //miliseconds
    const int intervalDelayedStart=500; //miliseconds
    int intervalLcdPageSwitchSeconds=10; //seconds


    bool useJis=false;

    bool blockBonjour=false;

    bool connectionsStandalone=false; //true = ignore connections from VDV301, download connections from Golemio directly


    bool golemioUseTestServer=false;
    QString golemioParametry="";
    QString golemioAddress="";
    QString golemioAddressTest="";
    QString golemioKey="";
    QString golemioKeyTest="";
    QString golemioVehicleRef="";
    QString golemioStopRef="";
    int golemioVehicleType=3;
    QVector<ConnectionGolemioV4> golemioConnections;
    QVector<StopGolemio> golemioStops;
    QVector<GolemioInfotext> golemioInfotexts;


    //timers

    QTimer timerUpdateSeconds;
    QTimer timerDelayedStart;

    QTimer timerUpdateGolemio;



    //common functions

    void menuSwitchTabs(int tabNumber);

    void labelLcdUpdateStopBackground(Vdv301Enumerations::LocationStateEnumeration locationState);

    QString createProgramVersionString();



    void debugServiceListToTable(QVector<QZeroConfService> serviceList);

    void allConnects();


    //funkce pomocne
    void popUpMessage(QString messageContent);
    int isInRange(int index, int limit, QString functionName); //nepouzito


    //functions initiliaze
    void initilializeFonts();
    void initilializeShortcuts();

    //functions display LCD with labels
    void displayLabelFillArray();
    void displayLabelShowAnnoucement(QString title, QString type, QString textCz, QString textEn);

    //funkce led


    //funkce SVG
    bool svgOpenFile(const QString &fileName);

    //obecne Udalosti

    void displayLabelReturnToStopList();

    void loadConstants();
    void constantsToSettingsPage();
    void settingsWindowToSettingsFile();
    void deviceManagementServiceInternalVariablesToSettingFile();


    void labelSetNextStopBackground(QString barvaPisma, QString barvaPozadi);
    
    void eventHideAnnouncement(); //nepouzito
    void eventHideFareZoneChange(); //nepouzito


    //void eraseDisplayedInformation();

    void eventShowPageSpecialAnnouncement(QString title, QString type, QString textCz, QString textEn);
    void displayLabelShowPageFinalStop();
    void eventNotOnLine();

    //keyboard shortcuts
    QShortcut *keyCtrlF; // Entity of Ctrl + D hotkeys
    QShortcut *keyF1;
    QShortcut *keyF2;
    QShortcut *keyF3;
    QShortcut *keyF4;
    QShortcut *keyF5;
    QShortcut *keyF6;
    QShortcut *keyF7;
    QShortcut *keyF8;

    //SVG rendering
    QGraphicsScene scene;
    QGraphicsSvgItem *m_svgItem;
    QGraphicsRectItem *m_outlineItem;
    bool svgRender();


    void eventDisplayAbnormalStateScreen(QString displayState);
    void receivedDataVariablesReset();

    void eventStopRequestedActivated();
    void eventStopRequestedDectivated();


    void retranslateUi(QString language);


    void updateMainScreenDebugLabels();
    void ledLabelInitialize2_3();
    void lcdLabelInitialize2_3();
    void eraseDisplayedInformation();

    void eventEraseDisplayInformation();
    void eventLcdSetMainPage();
    void eventLcdShowFollowingTripDestination(QString followingTripLine, QString followingTripDestination); //unused
    void eventLcdReturnToStopList();


    //VDV301 structures functions
    int showReceivedDataLcdVdv301(Vdv301AllData vdv301AllData);

    void debugStopPointListToTable(QVector<Vdv301StopPoint> seznamZastavek, bool navazny);
    void debugStopPointToTable(Vdv301StopPoint selectedStopPointDestination, bool isFollowingTrip);



    void showReceivedDataVdv301(Vdv301AllData vdv301AllData);

    void handleDisplayContentInner(QVector<Vdv301DisplayContent> displayContentList, bool following);
    void handleDisplayContentFront(QVector<Vdv301DisplayContent> displayContentList); // unused
    void handleDisplayContentSide(QVector<Vdv301DisplayContent> displayContentList); // unused
    void handleDisplayContentRear(QVector<Vdv301DisplayContent> displayContentList); // unused
    void showReceivedDataLedVdv301(QVector<Vdv301DisplayContent> stopDisplayContentList, QVector<Vdv301DisplayContent> globalDisplayContentList);


    void debugStopPointListToTable(QVector<Vdv301StopPoint2_3CZ1_0> seznamZastavek, bool navazny);

    void showReceivedDataVdv301_2_3CZ1_0(Vdv301AllData2_3CZ1_0 vdv301AllData);
    int showReceivedDataLcdVdv301_2_3CZ1_0(Vdv301AllData2_3CZ1_0 vdv301AllData);
    void showReceivedDataVdv301_2_3CZ1_0(Vdv301CurrentDisplayContent vdv301currentDisplayContent);
    void displayLabelShowFareZoneChange(QVector<Vdv301InternationalText> fromFareZoneList, QVector<Vdv301InternationalText> toFareZoneList);
    void eventShowPageFareZoneChange(QVector<Vdv301InternationalText> fromFareZones, QVector<Vdv301InternationalText> toFareZones); //unused

    void displayLabelShowAnnoucement(QVector<Vdv301InternationalText> additionalTextMessageList, QVector<Vdv301InternationalText> additionalTextMessage1List, QVector<Vdv301InternationalText> additionalTextMessage2List, QVector<Vdv301InternationalText> additionalTextMessage3List, QVector<Vdv301InternationalText> additionalTextMessage4List);
    void eventShowPageSpecialAnnouncement(QVector<Vdv301InternationalText> additionalTextMessage, QVector<Vdv301InternationalText> additionalTextMessage1, QVector<Vdv301InternationalText> additionalTextMessage2, QVector<Vdv301InternationalText> additionalTextMessage3, QVector<Vdv301InternationalText> additionalTextMessage4);

    void updateLabelCurrentStopindex(QString currentStopIndex);
    void updateLabelLocationState(QString locationState);
    void updateLabelAnnouncement(QString announcementText);
    void messageToTable(Vdv301AllData2_3CZ1_0 input);
    void displayLabelFillArrayJis();
    void labelSetNextStopBackgroundJis(QString barvaPisma, QString barvaPozadi);
    bool allDataChanged(Vdv301AllData2_3CZ1_0 oldAllData, Vdv301AllData2_3CZ1_0 newAllData);

  
    QString golemioRequestCompose(QString aswId, QString vehicleRef, int vehicleType);
    void golemioUpdateVariables();
    int vehicleSubmodeToGolemioType(QString subMode);
private slots:


    //tlacitka

    void on_pushButton_menu_services_clicked();
    void on_pushButton_menu_timer_clicked();
    void on_pushButton_menu_quit_clicked();
    void on_pushButton_menu_svg_clicked();
    void on_pushButton_menu_displayLabel_clicked();
    void on_pushButton_menu_displayLed_clicked();
    void on_pushButton_menu_fullscreen_clicked();
    void on_pushButton_menu_refresh_clicked();

    void on_pushButton_unsubscribe_clicked();

    void on_pushButton_debugConvertInline_clicked();
    void on_pushButton_debugShowHtml_clicked();
    void on_pushButton_messageLogReset_clicked();
    void on_pushButton_settings_save_clicked();

    void on_radioButton_stateDefective_clicked();
    void on_radioButton_stateWarning_clicked();
    void on_radioButton_stateNotAvailable_clicked();
    void on_radioButton_stateRunning_clicked();
    void on_radioButton_stateReadyForShutdown_clicked();

    
    void on_radioButton_settings_languageCs_clicked();
    void on_radioButton_settings_languageEn_clicked();

    void on_spinBox_frontSignWidth_valueChanged(int arg1);
    void on_checkBox_settings_useJis_stateChanged(int arg1);
    void on_spinBox_pageSwitchDuration_valueChanged(int arg1);


    //sloty
    int slotEverySecond();
    void slotMoveScrollingText();
    void slotDisplayLcdLabelCyclePages();
    void slotToggleFullscreen();
    void slotXmlToVehicleStateVariables(QString inputXmlString);
    void slotDebugServiceToTable(QZeroConfService zcs);
    void slotDelayedStartup();
    void slotUpdateServiceTable();
    void slotSubscriptionLost();

    void slotHeartbeatTimeout();
    void slotShutdownReady(bool isReady);

    void slotDebugPublisherToTable(PublisherStruct publisher);

    void slotDeviceParametersToConfigFile();
    void slotDisplayLcdLabelCyclePagesJis();
    void slotGolemioReady();
    bool slotDownloadGolemio();
    void slotVehicleRefUpdate(QString vehicleRef);
    void slotStopRefUpdate(QString stopRef);
    void on_checkBox_settings_useGolemioConnections_stateChanged(int arg1);

    void on_checkBox_settings_golemioTestServer_stateChanged(int arg1);

    void on_pushButton_debugLogLevel_clicked();

public slots:
signals:
    void signalVehicleRefUpdate(QString vehicleRef);
    void signalStopRefUpdate(QString stopRef);



};

#endif // MAINWINDOW_H
