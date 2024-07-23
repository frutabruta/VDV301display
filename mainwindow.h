#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "xmlparser.h"
//#include "httpserver2/myhttpserver.h"
//#include "VDV301subscriber/ibisipsubscriber.h"

#include "VDV301publisher/devicemanagementservice.h"
#include "VDV301subscriber/cissubscriber.h"


#include "VDV301DataStructures/stoppointdestination.h"
#include "VDV301DataStructures/vehiclestate.h"
#include "VDV301DataStructures/connection.h"

#include "pasmovedvojicelcd.h"
#include "svgvykreslovani.h"
#include "labelvykreslovani.h"
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

private:

    QCommandLineParser qCommandLineParser;

    //instance trid
    XmlParser xmlParser;
    VehicleState vehicleState;
    LabelVykreslovani labelVykreslovani;

    CisSubscriber cisSubscriber;
    SvgVykreslovani svgVykreslovani;
    DeviceManagementService deviceManagementService;
    QSettings settings;


    //datoveStruktury jizda
    QVector<StopPointDestination> currentDestinationPointList;
    QVector<Vdv301StopPoint> currenVdv301StopPointList;
    QVector<StopPointDestination> nextDestinationPointList;


    //QVector<Prestup> prestupy;
    // QString nazevLinky="";
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

    int currentPageIndexLed=0;
    int currentPageIndex =0;
    bool showTimeColon=0;

    //konstanty
    int posunRotovani=0;
    // int pocetVykreslovanychZastavek=5;

    QString oldViapointString="";



    const int intervalSideDisplay=2000;
    const int intervalScrollingText=20;
    const int intervalSwitchPages=10000;
    const int intervalOpozdeniStartu=500;

    //velikosti fontu v bodech
    //const int velikostFontLinka=200;
    const int sizeFontDestination=100;
    const int sizeFontViaPoints=72;
    const int sizeFontFollowing=100;

    const int sizeFontTransferLine=48;
    const int sizeFontTransferDestination=36;

    const int sizeIconConnection=65;
    int sizeIconConnectionDynamic=20;
    const int velikostPrestupRamecekSirka=95;
    const int velikostPrestupRamecekVyska=65;

    //velikosti oken

    float ratioPixelPoint=1080.0/1050.0;

    float ratioPixelLed=4.105;


    //ostatni promenne


    //Fonty

    //QFontDatabase fdb;

    //_LED fonty
    QFont fontLed1;
    QFont fontLed3;
    QFont fontLed3v;
    QFont fontLed5;
    QFont fontLed8;
    QFont fontLed10;


    //_LCD fonty

    QFont fontLabelFareZoneLarge;
    QFont fontLabelFareZoneSmall;

    //casovace
    QTimer *timerLedSideCycleViaPoints = new QTimer(this);
    QTimer *timerScrollingText = new QTimer(this);
    QTimer *timerUpdateSeconds = new QTimer(this);
    QTimer *timerLabelPageSwitch = new QTimer(this);
    QTimer *timerDelayedStart = new QTimer(this);

    //funkce spolecne (vsem typum zobrazeni)
    int doplneniPromennych ();
    void switchTabs(int tabNumber);
    int formatZobrazeni();

    QString createProgramVersionString();
    int showReceivedData();
    void eraseTable(QTableWidget *tableWidget);

    void serviceListToTable(QVector<QZeroConfService> seznamSluzeb);

    void allConnects();


    //funkce pomocne

    int isInRange(int index, int pocetHodnot); //nepouzito

    //funkce hlavni
    void hlavniAutoformat();
    void displayLabelFillArray();
    void displayLabelLineName(StopPointDestination aktZastavka, QString subMode);
    void displayLabelViaPoints();
    void displayLabelDestination(QString alias);
    void displayLabelConnectionList(QVector<Connection> seznamPrestupu);
    void displayLabelStopList(QVector<StopPointDestination> zastavky, QVector<StopPointDestination> zastavkyNavazny, int index);
    void displayLabelStopFareZone(QVector<StopPointDestination> aktZastavky, QVector<StopPointDestination> navazZastavky);
    void displayLabelEraseInformation();
    void displayLabelShowAnnoucement(QString title, QString type, QString textCz, QString textEn);
    void displayLabelShowFareZoneChange(QVector<FareZone> zPasem, QVector<FareZone> naPasma);
    void displayLabelDrawLineNumber(QString subMode, Line line, QLabel *label, int velikostPiktogramu, bool prestup);
    void displayLabelDrawLineNumber2_4(QString subMode, Line line, QLabel *label, int velikostPiktogramu, bool prestup);

    QVector<QWidget*> pageCycleList;

    //funkce led
    void ledUpdateDisplayedInformation(QVector<StopPointDestination> zastavky, VehicleState stav);
    void ledNaplnFront(QString linka, QString horniRadek, QString dolniRadek);
    void ledNaplnInner(QString linka, QString horniRadek, QString dolniRadek);
    QVector<QString> ledNaplnNacestyBocniPanel(StopPointDestination aktualniZastavka);
    QVector<QString> ledNaplnNacestyVnitrniPanel(StopPointDestination aktualniZastavka);
    void ledInicializujVirtualniPanely();
    void ledIterujBocniPanel(QVector<QString> texty, int &iteracniIndex);
    void ledIterujVnitrniPanel(QVector<QString> texty, int &iteracniIndex);
    void ledIterujVsechnyPanely();
    void ledNaplnSide(QString linka, QString horniRadek, QString dolniRadek);
    void ledNaplnRear(QString linka);
    void ledVymazPanely();

    void ledZmenVelikostPanelu();
    void ledZarovnejPretecenyRadek(QLabel *label);
    void ledZapisLinku(QLabel *label, QString text);
    void ledZmenVelikostOkna(QLabel *okno, int sirkaDot, int vyskaDot, float koeficient);

    void ledUpdateDisplayedInformation2_3(QVector<Vdv301StopPoint> &zastavky, VehicleState stav);
    void ledLabelInitialize2_3();

    LedLabelDisplay frontDisplay;
    LedLabelDisplay sideDisplay;
    LedLabelDisplay rearDisplay;



    void slotPublisherDoTabulky(QZeroConfService zcs);

    QVector<QString> textyBocniPanelkIteraci;
    QVector<QString> textyVnitrniPanelkIteraci;

    //funkce SVG
    bool svgOpenFile(const QString &fileName);

    //obecne Udalosti
    int isVehicleOnFinalStop(VehicleState stav, QVector<StopPointDestination> zastavky);
    void displayLabelReturnToStopList();

    void loadConstants();
    void constantsToSettingsPage();
    void settingsWindowToSettingsFile();
    void deviceManagementServiceInternalVariablesToSettingFile();


    void obarviPozadiPristi(QString barvaPisma, QString barvaPozadi);

    void skryjAnnouncement(); //nepouzito
    void skryjZmenuPasma(); //nepouzito


    void eraseDisplayedInformation();

    void displayLabelShowPageSpecialAnnouncement(QString title, QString type, QString textCz, QString textEn);
    void showPageFareZoneChange(QVector<FareZone> zPasem, QVector<FareZone> naPasma);
    void displayLabelShowPageFinalStop();
    void notOnLine();

    //klávesové zkratky
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

    //vektory Labelu Hlavni
    QVector<QLabel*> labelListStopPointName;
    QVector<QLabel*> labelListFareZoneUpper;
    QVector<QLabel*> labelListFareZoneLower;

    QVector<QLabel*> labelListConnectionLine;
    QVector<QLabel*> labelListConnectionDestination;
    QVector<QLabel*> labelListConnectionDeparture;
    QVector<QLabel*> labelListConnectionPlatform;


    void popUpMessage(QString poznamka);


    QString nahradIconPiktogramem(QString vstup, int vyskaObrazku, QString slozka);
    void zastavkaCilDoTabulky(StopPointDestination zastavkaCil, bool navazny);
    void vsechnyZastavkyDoTabulky(QVector<StopPointDestination> seznamZastavek, bool navazny);
    void initilializeFonts();
    void initilializeShortcuts();
    void displayLabelStopPoint(StopPointDestination aktualniZastavka, bool navazny, QLabel *nazevZastavky, QLabel *dolniPasmo, QLabel *horniPasmo);
    QVector<StopPointDestination> vektorZastavkaCilZahoditZacatek(QVector<StopPointDestination> vstup, int zacatek);


    void displayAbnormalStateScreen(QString displayState);
    void displayNormalOnLineState();
    void receivedDataVariablesReset();
    void connectionToTable(Connection connection, QTableWidget *tableWidget);
    void connectionListToTable(QVector<Connection> connectionList, QTableWidget *tableWidget);
    void stopRequestedActivated();
    void stopRequestedDectivated();

    void tickLedPanels2_3();
    void retranslateUi(QString language);


    void updateMainScreenDebugLabels();
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


    //sloty
    int slotEverySecond();
    void slotMoveScrollingText();
    void slotHlavniStridejStranky();
    void slotToggleFullscreen();
    void slotXmlDoPromenne(QString vstupniXml);
    void slotSluzbaDoTabulky(QZeroConfService zcs);
    void slotDelayedStartup();
    void slotUpdateServiceTable();
    void slotSubscriptionLost();

    void slotHeartbeatTimeout();
    void slotShutdownReady(bool isReady);

    void on_pushButton_unsubscribe_clicked();

    void on_tlacitkoNastavVteriny_clicked();





    void on_radioButton_stateDefective_clicked();
    void on_radioButton_stateWarning_clicked();
    void on_radioButton_stateNotAvailable_clicked();
    void on_radioButton_stateRunning_clicked();
    void on_radioButton_stateReadyForShutdown_clicked();

    void on_pushButton_settings_save_clicked();

    void on_radioButton_settings_languageCs_clicked();
    void on_radioButton_settings_languageEn_clicked();

    void on_spinBox_frontSignWidth_valueChanged(int arg1);

public slots:

    void slotDeviceParametersToConfigFile();
};

#endif // MAINWINDOW_H
