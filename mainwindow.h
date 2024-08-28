#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "xmlparser.h"
//#include "httpserver2/myhttpserver.h"
//#include "VDV301subscriber/ibisipsubscriber.h"

#include "VDV301publisher/devicemanagementservice.h"
#include "VDV301subscriber/cissubscriber.h"


#include "VDV301subscriber/VDV301DataStructures/stoppointdestination.h"
#include "VDV301subscriber/VDV301DataStructures/vehiclestate.h"
#include "VDV301subscriber/VDV301DataStructures/connection.h"

#include "pasmovedvojicelcd.h"
#include "svgvykreslovani.h"
#include "displaylabelled.h"
#include "displaylabellcd.h"

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


//#include <QWidget>

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

    void ledUpdateDisplayedInformationFromDisplayContentList2_3(QVector<Vdv301DisplayContent> globalDisplayContent);

private:

    QCommandLineParser qCommandLineParser;
    QSettings settings;

    // complex class instances
    XmlParser xmlParser;


    DisplayLabelLcd displayLabelLcd;

    DisplayLabelLed displayLabelLed;


    SvgVykreslovani svgVykreslovani;

    CisSubscriber cisSubscriber;
    DeviceManagementService deviceManagementService;




    //complex variables
    QVector<StopPointDestination> currentDestinationPointList;
    QVector<Vdv301StopPoint> currenVdv301StopPointList;
    QVector<StopPointDestination> nextDestinationPointList;

    Vdv301AllData vdv301AllData;
    VehicleState vehicleState;

    QString nazevCile="";
    QString additionalTextMessageType="";
    QString additionalTextMessageHeadline="";
    QString additionalTextMessageText="";
    QVector<FareZone> fareZoneChangeFrom;
    QVector<FareZone> fareZoneChangeTo;

    BarvyLinek barvyLinek;

    //stavove promenne
    bool isFareZone=false;
    int stopIndex=0;


    int lcdLabelCurrentPageIndex =0;

    bool showTimeColon=0;

    //constants





    const int intervalSideDisplay=2000;


    const int intervalDelayedStart=500;

    //font sizes in points
    //const int velikostFontLinka=200;


    //velikosti oken






    //other variables


    //Fonty





    //timers

    // QTimer *timerScrollingText = new QTimer(this);
    //  QTimer *timerUpdateSeconds = new QTimer(this);
    //  QTimer *timerLabelPageSwitch = new QTimer(this);
    //  QTimer *timerDelayedStart = new QTimer(this);


    QTimer timerUpdateSeconds;

    QTimer timerDelayedStart;

    //common functions
    int setDestinationName ();
    void menuSwitchTabs(int tabNumber);
    int labelUpdateFormat();

    QString createProgramVersionString();
    int showReceivedData();
    void eraseTable(QTableWidget *tableWidget);

    void debugServiceListToTable(QVector<QZeroConfService> serviceList);

    void allConnects();


    //funkce pomocne
    void popUpMessage(QString messageContent);
    int isInRange(int index, int limit); //nepouzito


    //functions initiliaze
    void initilializeFonts();
    void initilializeShortcuts();

    //functions display LCD with labels
    void lcdResizeLabels();
    void displayLabelFillArray();
    void displayLabelLineName(StopPointDestination selectedStopPointDestinationstavka, QString subMode);
    //void displayLabelViaPoints();
    void displayLabelDestination(QString alias);
  //  void displayLabelConnectionList(QVector<Connection> connectionList);
    void displayLabelStopList(QVector<StopPointDestination> thisStopPointDestinationList, QVector<StopPointDestination> nextStopPointDestinationList, int index);
  //  void displayLabelStopFareZone(QVector<StopPointDestination> thisStopPointDestinationList, QVector<StopPointDestination> nextStopPointDestinationList);
    void displayLabelEraseInformation();
    void displayLabelShowAnnoucement(QString title, QString type, QString textCz, QString textEn);
    void displayLabelShowFareZoneChange(QVector<FareZone> fromFareZoneList, QVector<FareZone> toFareZoneList);
    void displayLabelDrawLineNumber(QString subMode, Line line, QLabel *label, int iconSize, bool isConnection);
    void displayLabelDrawLineNumber2_4(QString subMode, Line line, QLabel *label, int velikostPiktogramu, bool prestup);



    //funkce led






    //funkce SVG
    bool svgOpenFile(const QString &fileName);

    //obecne Udalosti
    int isVehicleOnFinalStop(VehicleState stav, QVector<StopPointDestination> zastavky);
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
    void eventShowPageFareZoneChange(QVector<FareZone> zPasem, QVector<FareZone> naPasma);
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

    //polozky potrebne pro vykresleni svg
    QGraphicsScene scene;
    QGraphicsSvgItem *m_svgItem;
    QGraphicsRectItem *m_outlineItem;
    bool svgVykresleni();





    QString replaceIconTagWithImage(QString vstup, int vyskaObrazku, QString slozka);

    void debugStopPointToTable(StopPointDestination selectedStopPointDestination, bool isFollowingTrip);
    void debugStopPointListToTable(QVector<StopPointDestination> seznamZastavek, bool navazny);

   // void displayLabelStopPoint(StopPointDestination selectedStopPointDestination, bool isFollowingTrip, QLabel *labelStopName, QLabel *labelFarezoneBottom, QLabel *labelFarezoneTop);


    QVector<StopPointDestination> vektorZastavkaCilZahoditZacatek(QVector<StopPointDestination> vstup, int zacatek);//unused


    void eventDisplayAbnormalStateScreen(QString displayState);
    void displayNormalOnLineState();
    void receivedDataVariablesReset();
    void connectionToTable(Connection connection, QTableWidget *tableWidget);
    void connectionListToTable(QVector<Connection> connectionList, QTableWidget *tableWidget);
    void eventStopRequestedActivated();
    void eventStopRequestedDectivated();


    void retranslateUi(QString language);


    void updateMainScreenDebugLabels();
    void ledLabelInitialize2_3();
    void lcdLabelInitialize2_3();
    void eraseDisplayedInformation();

    void eventEraseDisplayInformation();
    void eventLcdSetMainPage();
    void eventLcdShowFollowingTripDestination(QString followingTripLine, QString followingTripDestination);
    void eventLcdReturnToStopList();
private slots:

    void on_actiontestPolozka_triggered();
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
    void slotXmlDoPromenne(QString vstupniXml);
    void slotDebugServiceToTable(QZeroConfService zcs);
    void slotDelayedStartup();
    void slotUpdateServiceTable();
    void slotSubscriptionLost();

    void slotHeartbeatTimeout();
    void slotShutdownReady(bool isReady);

    void slotDebugPublisherToTable(QZeroConfService zcs);

    void slotDeviceParametersToConfigFile();
public slots:


};

#endif // MAINWINDOW_H
