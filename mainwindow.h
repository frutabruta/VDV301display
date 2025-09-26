#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "VDV301xmlparser/xmlparser1_0.h"
#include "VDV301xmlparser/xmlparser2_2cz1_0.h"
#include "VDV301xmlparser/xmlparser2_3.h"
#include "VDV301xmlparser/xmlparser2_3cz1_0.h"


#include "VDV301publisher/devicemanagementservice.h"
#include "VDV301subscriber/cissubscriber.h"

#include "svgvykreslovani.h"
#include "displaylabelled.h"
#include "displaylabellcd2_3cz1_0.h"

#include "barvylinek.h"

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
    DisplayLabelLcd2_3CZ1_0 displayLabelLcdJis;

    DisplayLabelLed displayLabelLed;


    SvgVykreslovani svgVykreslovani;

    CisSubscriber cisSubscriber;

    DeviceManagementService deviceManagementService;




    //complex variables

    QVector<Vdv301StopPoint> currentVdv301StopPointList;

    Vdv301AllData vdv301AllData;
    Vdv301AllData2_3CZ1_0 vdv301AllData2_3CZ1_0;

    Vdv301CurrentDisplayContent vdv301currentDisplayContent;

    BarvyLinek barvyLinek;

    //stavove promenne


    int lcdLabelCurrentPageIndex =0;

    bool showTimeColon=0;

    int receivedMessagesCounter=0;
    //constants
    const int intervalSideDisplay=2000;
    const int intervalDelayedStart=500;

    bool useJis=false;

    //timers

    QTimer timerUpdateSeconds;
    QTimer timerDelayedStart;



    //common functions

    void menuSwitchTabs(int tabNumber);

    void labelLcdUpdateStopBackground(Vdv301Enumerations::LocationStateEnumeration locationState);

    QString createProgramVersionString();

    void eraseTable(QTableWidget *tableWidget);

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
    void displayNormalOnLineState(); //unused
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
    void connectionListToTable(QVector<Vdv301Connection> connectionList, QTableWidget *tableWidget);
    void connectionToTable(Vdv301Connection connection, QTableWidget *tableWidget);
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


    void on_radioButton_stateDefective_clicked();
    void on_radioButton_stateWarning_clicked();
    void on_radioButton_stateNotAvailable_clicked();
    void on_radioButton_stateRunning_clicked();
    void on_radioButton_stateReadyForShutdown_clicked();

    void on_pushButton_settings_save_clicked();
    void on_radioButton_settings_languageCs_clicked();
    void on_radioButton_settings_languageEn_clicked();

    void on_spinBox_frontSignWidth_valueChanged(int arg1);


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

    void slotDebugPublisherToTable(QZeroConfService zcs);

    void slotDeviceParametersToConfigFile();
    void on_pushButton_debugConvertInline_clicked();

    void on_pushButton_debugShowHtml_clicked();

    void on_pushButton_messageLogReset_clicked();

    void on_checkBox_settings_useJis_stateChanged(int arg1);

public slots:


};

#endif // MAINWINDOW_H
