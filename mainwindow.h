#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

#include "mainwindowhelper.h"

#include "LogHandler/loggerrelay.h"
#include "LogHandler/loghandler.h"





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

    LoggerRelay relay;
    LogHandler logHandler;

    //complex variables

    QVector<Vdv301StopPoint> currentVdv301StopPointList;

    Vdv301AllData vdv301AllData;
    Vdv301AllData2_3CZ1_0 vdv301AllData2_3CZ1_0;
    Vdv301AllData2_3CZ1_0 vdv301AllData2_3CZ1_0_previous;

    int previousAnnouncementCount=0;

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

    bool logOnStartup=true;

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

    //common functions


    //funkce pomocne
    void popUpMessage(QString messageContent);
    int isInRange(int index, int limit, QString functionName);

    void allConnects();

    bool allDataChanged(Vdv301AllData2_3CZ1_0 oldAllData, Vdv301AllData2_3CZ1_0 newAllData);

    void constantsToSettingsPage();
    QString createProgramVersionString();

    void deviceManagementServiceInternalVariablesToSettingFile();
    void debugServiceListToTable(QVector<QZeroConfService> serviceList);
    void debugStopPointListToTable(QVector<Vdv301StopPoint> seznamZastavek, bool navazny);
    void debugStopPointListToTable(QVector<Vdv301StopPoint2_3CZ1_0> seznamZastavek, bool navazny);

    void debugStopPointToTable(Vdv301StopPoint selectedStopPointDestination, bool isFollowingTrip);

    //functions display LCD with labels
    void displayLabelFillArray();
    void displayLabelFillArrayJis();
    void displayLabelReturnToStopList();
    void displayLabelShowAnnoucement(QString title, QString type, QString textCz, QString textEn);

    void displayLabelShowFareZoneChange(QVector<Vdv301InternationalText> fromFareZoneList, QVector<Vdv301InternationalText> toFareZoneList);
    void displayLabelShowAnnoucement(QVector<Vdv301InternationalText> additionalTextMessageList, QVector<Vdv301InternationalText> additionalTextMessage1List, QVector<Vdv301InternationalText> additionalTextMessage2List, QVector<Vdv301InternationalText> additionalTextMessage3List, QVector<Vdv301InternationalText> additionalTextMessage4List);
    void displayLabelShowPageFinalStop();

    void eraseDisplayedInformation();

    void eventHideAnnouncement(); //nepouzito
    void eventHideFareZoneChange(); //nepouzito

    void eventDisplayAbnormalStateScreen(QString displayState);
    void eventEraseDisplayInformation();
    void eventLcdReturnToStopList();
    void eventLcdSetMainPage();
    void eventLcdShowFollowingTripDestination(QString followingTripLine, QString followingTripDestination); //unused

    void eventNotOnLine();
    void eventShowPageFareZoneChange(QVector<Vdv301InternationalText> fromFareZones, QVector<Vdv301InternationalText> toFareZones); //unused
    void eventShowPageSpecialAnnouncement(QString title, QString type, QString textCz, QString textEn);
    void eventShowPageSpecialAnnouncement(QVector<Vdv301InternationalText> additionalTextMessage, QVector<Vdv301InternationalText> additionalTextMessage1, QVector<Vdv301InternationalText> additionalTextMessage2, QVector<Vdv301InternationalText> additionalTextMessage3, QVector<Vdv301InternationalText> additionalTextMessage4);

    void eventStopRequestedActivated();
    void eventStopRequestedDectivated();

    QString golemioRequestCompose(QString aswId, QString vehicleRef, int vehicleType);
    void golemioUpdateVariables();

    void handleDisplayContentInner(QVector<Vdv301DisplayContent> displayContentList, bool following);
    void handleDisplayContentFront(QVector<Vdv301DisplayContent> displayContentList); // unused
    void handleDisplayContentSide(QVector<Vdv301DisplayContent> displayContentList); // unused
    void handleDisplayContentRear(QVector<Vdv301DisplayContent> displayContentList); // unused

    //functions initiliaze
    void initilializeFonts();
    void initilializeShortcuts();

    void labelLcdUpdateStopBackground(Vdv301Enumerations::LocationStateEnumeration locationState);
    void labelSetNextStopBackground(QString barvaPisma, QString barvaPozadi);
    void labelSetNextStopBackgroundJis(QString barvaPisma, QString barvaPozadi);
    void ledLabelInitialize2_3();
    void lcdLabelInitialize2_3();
    void loadConstants();

    void manualSubscription();

    void menuSwitchTabs(int tabNumber);

    void messageToTable(Vdv301AllData2_3CZ1_0 input);

    void settingsWindowToSettingsFile();
    int showReceivedDataLcdVdv301(Vdv301AllData vdv301AllData);
    void showReceivedDataVdv301(Vdv301AllData vdv301AllData);
    void showReceivedDataLedVdv301(QVector<Vdv301DisplayContent> stopDisplayContentList, QVector<Vdv301DisplayContent> globalDisplayContentList);
    void showReceivedDataVdv301_2_3CZ1_0(Vdv301AllData2_3CZ1_0 vdv301AllData);
    int showReceivedDataLcdVdv301_2_3CZ1_0(Vdv301AllData2_3CZ1_0 vdv301AllData);
    void showReceivedDataVdv301_2_3CZ1_0(Vdv301CurrentDisplayContent vdv301currentDisplayContent);

    bool svgOpenFile(const QString &fileName);

    void receivedDataVariablesReset();
    void retranslateUi(QString language);

    void updateLabelCurrentStopindex(QString currentStopIndex);
    void updateLabelLocationState(QString locationState);
    void updateLabelAnnouncement(QString announcementText);
    void updateMainScreenDebugLabels();


private slots:
    void on_checkBox_debugLogEnable_stateChanged(int arg1);
    void on_checkBox_settings_jisMinutes_stateChanged(int arg1);
    void on_checkBox_settings_useJis_stateChanged(int arg1);
    void on_checkBox_settings_useGolemioConnections_stateChanged(int arg1);
    void on_checkBox_settings_golemioTestServer_stateChanged(int arg1);

    void on_pushButton_debugLogClear_clicked();
    void on_pushButton_debugConvertInline_clicked();
    void on_pushButton_debugLogLevel_clicked();
    void on_pushButton_debugShowHtml_clicked();

    void on_pushButton_menu_services_clicked();
    void on_pushButton_menu_timer_clicked();
    void on_pushButton_menu_quit_clicked();
    void on_pushButton_menu_svg_clicked();
    void on_pushButton_menu_displayLabel_clicked();
    void on_pushButton_menu_displayLed_clicked();
    void on_pushButton_menu_fullscreen_clicked();
    void on_pushButton_menu_refresh_clicked();

    void on_pushButton_messageLogReset_clicked();    
    void on_pushButton_settings_save_clicked();
    void on_pushButton_unsubscribe_clicked();

    void on_radioButton_settings_languageCs_clicked();
    void on_radioButton_settings_languageEn_clicked();
    void on_radioButton_stateDefective_clicked();
    void on_radioButton_stateWarning_clicked();
    void on_radioButton_stateNotAvailable_clicked();
    void on_radioButton_stateRunning_clicked();
    void on_radioButton_stateReadyForShutdown_clicked();

    void on_spinBox_frontSignWidth_valueChanged(int arg1);    
    void on_spinBox_pageSwitchDuration_valueChanged(int arg1);

    void slotDebugPublisherToTable(PublisherStruct publisher);
    void slotDebugServiceToTable(QZeroConfService zcs);
    void slotDelayedStartup();
    void slotDeviceIpUpdated(QHostAddress input);
    void slotDeviceParametersToConfigFile();
    void slotDisplayLcdLabelCyclePages();
    void slotDisplayLcdLabelCyclePagesJis();
    bool slotDownloadGolemio();
    int slotEverySecond();
    void slotGolemioReady();
    void slotHeartbeatTimeout();
    void slotMoveScrollingText();

    void slotShutdownReady(bool isReady);

    void slotStopRefUpdate(QString stopRef);
    void slotSubscriptionLost();
    void slotToggleFullscreen();
    void slotUpdateServiceTable();
    void slotVehicleRefUpdate(QString vehicleRef);

    void slotXmlToVehicleStateVariables(QString inputXmlString);

    void slotLogWindowAppend(const QString &text);
    
    void on_pushButton_subscriptitionManual_clicked();
  

public slots:
signals:
    void signalVehicleRefUpdate(QString vehicleRef);
    void signalStopRefUpdate(QString stopRef);
    void signalToLog(QString text);

};

#endif // MAINWINDOW_H
