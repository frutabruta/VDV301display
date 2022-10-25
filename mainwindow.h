#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "xmlparser.h"
//#include "httpserver2/myhttpserver.h"
#include "VDV301subscriber/ibisipsubscriber.h"
#include "VDV301publisher/devicemanagementservice.h"
#include "VDV301struktury/cestaudaje.h"
#include "VDV301struktury/zastavkacil.h"
#include "VDV301struktury/prestup.h"
#include "pasmovedvojicelcd.h"
#include "svgvykreslovani.h"
#include "labelvykreslovani.h"

#include <QApplication>
//#include <QtDebug>
#include <QFile>
#include <QFontDatabase>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
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
    explicit MainWindow(QWidget *parent = nullptr);
    Ui::MainWindow *ui;
    ~MainWindow();

private:

    //instance trid
    XmlParser instanceXMLparser;
    CestaUdaje stavSystemu;
    LabelVykreslovani labelVykreslovani;

    IbisIpSubscriber CustomerInformationServiceSubscriber;
    SvgVykreslovani svgVykreslovani;
    DeviceManagementService deviceManagementService1_0;





    //datoveStruktury jizda
    QVector<ZastavkaCil> globalniSeznamZastavek;
    QVector<ZastavkaCil> globalniSeznamZastavekNavaznehoSpoje;
    //QVector<Prestup> prestupy;
    QString nazevLinky="";
    QString nazevCile="";
    QString additionalTextMessageType="";
    QString additionalTextMessageHeadline="";
    QString additionalTextMessageText="";
    QVector<Pasmo> pasmaZ;
    QVector<Pasmo> pasmaDo;

    //stavove promenne
    bool zmenaPasma=false;
    int indexZastavky=0;
    int pocetZastavek=0;
    int cyklovaniIndex=0;
    int indexAktualniStridaneStranky =0;
    bool zobrazDvojtecku=0;

    //konstanty
    int posunRotovani=0;
    int pocetVykreslovanychZastavek=5;

    const int intervalBocniPanel=2000;
    const int intervalPosunuNacest=20;
    const int intervalStridaniStranek=10000;
    const int intervalOpozdeniStartu=2000;

    //velikosti fontu v bodech
    //const int velikostFontLinka=200;
    const int velikostFontCil=100;
    const int velikostFontNacestne=72;
    const int velikostFontNasledujici=100;

    const int velikostFontPrestupLinka=48;
    const int velikostFontPrestupCil=36;

    const int velikostPiktogramPrestup=65;
    int velikostPiktogramPrestupDynamic=20;
    const int velikostPrestupRamecekSirka=95;
    const int velikostPrestupRamecekVyska=65;

    //velikosti oken

    float pomerPixelBod=1080.0/1050.0;

    //Fonty

    QFontDatabase fdb;

    //_LED fonty
    QFont font8;
    QFont font10;

    //_RobotoRegular
    //QFont standardPismoRegular;

    //_LCD fonty

    QFont fontPasmoVelke;
    QFont fontPasmoMale;

    //casovace
    QTimer *timerBocniPanel = new QTimer(this);
    QTimer *timerNacestneZastavky = new QTimer(this);
    QTimer *timer = new QTimer(this);
    QTimer *timerStridejStranky = new QTimer(this);
    QTimer *timerOpozdenyStart = new QTimer(this);

    //funkce spolecne (vsem typum zobrazeni)
    int doplneniPromennych ();
    int existujeKonfigurak();
    int formatZobrazeni();
    void naplnMapBarev();
    int vykresleniPrijatychDat();
    void vymazTabulkuSubscriberu(QTableWidget *tableWidget);
    void vykresliSluzbyDoTabulky(QVector<QZeroConfService> seznamSluzeb);
    void vsechnyConnecty();

    //funkce pomocne

    int jeVRozsahu(int index, int pocetHodnot); //nepouzito

    //funkce hlavni
    void hlavniAutoformat();
    void hlavniNaplnPoleLabelu();
    void hlavniVykresliCisloLinky(ZastavkaCil aktZastavka, QString subMode);
    void hlavniVykresliNacestne();
    void hlavniVykresliNazevCile(QString alias);
    void hlavniVykresliPrestupy(QVector<Prestup> seznamPrestupu);
    int  hlavniVykresliSkupinuZastavek(int offset, int pocetPoli, QVector<ZastavkaCil> zastavky, bool navazny);
    void hlavniVykresliZastavkyiPasma(QVector<ZastavkaCil> aktZastavky, QVector<ZastavkaCil> navazZastavky);
    void hlavniVymazObrazovku();
    void hlavniZobrazAnnoucement(QString title, QString type, QString textCz, QString textEn);
    void hlavniZobrazZmenuPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma);
    void naplnPoleLinky(QString subMode, Linka line, QLabel *label, int velikostPiktogramu, bool prestup);

    QVector<QWidget*> strankyKeStridani;

    //funkce led
    void ledAktualizujZobrazeniVirtualnichPanelu(QVector<ZastavkaCil> zastavky, CestaUdaje stav);
    void ledNaplnFront(QString linka, QString horniRadek, QString dolniRadek);
    void ledNaplnInner(QString linka, QString horniRadek, QString dolniRadek);
    QVector<QString> ledNaplnNacestyBocniPanel(ZastavkaCil aktualniZastavka);
    QVector<QString> ledNaplnNacestyVnitrniPanel(ZastavkaCil aktualniZastavka);
    void ledInicializujVirtualniPanely();
    void ledIterujBocniPanel(QVector<QString> texty, int &iteracniIndex);
    void ledIterujVnitrniPanel(QVector<QString> texty, int &iteracniIndex);
    void ledIterujVsechnyPanely();
    void ledNaplnSide(QString linka, QString horniRadek, QString dolniRadek);
    void ledNaplnRear(QString linka);
    void ledVymazPanely();

    QVector<QString> textyBocniPanelkIteraci;
    QVector<QString> textyVnitrniPanelkIteraci;

    //funkce SVG
    bool svgOpenFile(const QString &fileName);

    //obecne Udalosti
    int jeVozidloNaKonecne(CestaUdaje stav, QVector<ZastavkaCil> zastavky);
    void navratJizda();
    void obarviPozadiPristi(QString barvaPisma, QString barvaPozadi);

    void skryjAnnouncement(); //nepouzito
    void skryjZmenuPasma(); //nepouzito

    void vyprselCasovacSluzby();
    void vymazObrazovku();

    void zobrazAnnoucement(QString title, QString type, QString textCz, QString textEn);
    void zobrazZmenuPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma);
    void zobrazKonecnou();

    //klávesové zkratky
    QShortcut *keyCtrlF;  // Entity of Ctrl + D hotkeys
    QShortcut  *keyF1;
    QShortcut  *keyF2;
    QShortcut  *keyF3;
    QShortcut  *keyF4;
    QShortcut  *keyF5;
    QShortcut  *keyF6;
    QShortcut  *keyF7;
    QShortcut  *keyF8;

    //polozky potrebne pro vykresleni svg
    QGraphicsScene scene;
    QGraphicsSvgItem *m_svgItem;
    QGraphicsRectItem *m_outlineItem;
    bool svgVykresleni();

    //vektory Labelu Hlavni
    QVector<QLabel*> seznamLabelNazevZastavky;
    QVector<QLabel*> seznamLabelPasmoDolni;
    QVector<QLabel*> seznamLabelPasmoHorni;

    QVector<QLabel*> seznamLabelPrestupLinka;
    QVector<QLabel*> seznamLabelPrestupCil;
    QVector<QLabel*> seznamLabelPrestupOdjezd;
    QVector<QLabel*> seznamLabelPrestupNastupiste;

    //nezarazeno
    QMap<QString, QString> barvaTextu;
    QMap<QString, QString> barvaPozadi;
    //definice barev

    QString barva_PozadiA_25_25_25 ="rgb(25,25,25)";
    QString barva_PozadiB_50_50_50 ="rgb(50,50,50)"; //tmave seda
    QString barva_PozadiC_100_100_100 ="rgb(100,100,100)";
    QString barva_PozadiD_150_150_150 ="rgb(150,150,150)"; //Pozadí D
    QString barva_Zastavka_180_180_180 ="rgb(180,180,180)"; //Zastávka
    QString barva_bila_255_255_255 ="rgb(255,255,255)"; //bila
    QString barva_cerna_0_0_0 ="rgb(0,0,0);"; //bila

    QString barva_Vyluky_255_170_30 ="rgb(255,170,30)";
    QString barva_Cervena_200_0_20 ="rgb(200,0,20)";
    QString barva_CervenaTexty_220_40_40 ="rgb(220,40,40)";
    QString barva_Zelena_210_215_15 ="rgb(210,215,15)";

    QString barva_MetroA_0_165_98 ="rgb(0,165,98)";
    QString barva_MetroB_248_179_34 ="rgb(248,179,34)";
    QString barva_MetroC_207_0_61 ="rgb(207,0,61)";
    QString barva_MetroD_0_140_190 ="rgb(0,140,190)";
    QString barva_Tramvaj_120_2_0 ="rgb(120,2,0)";
    QString barva_Trolejbus_128_22_111 ="rgb(128,22,111)";
    QString barva_Autobus_0_120_160 ="rgb(0,120,160)";
    QString barva_Vlak_15_30_65 ="rgb(15,30,65)";
    QString barva_Lanovka_201_208_34 ="rgb(201,208,34)";
    QString barva_Privoz_0_164_167 ="rgb(0,164,167)";
    QString barva_Nocni_9_0_62 ="rgb(9,0,62)";
    QString barva_Letiste_155_203_234 ="rgb(155,203,234)";
    QString barva_Specialni_143_188_25 ="rgb(143,188,25)";

private slots:

    void on_actiontestPolozka_triggered();
    //tlacitka
    void on_pushButton_menu_refreh_clicked();
    void on_pushButton_menu_sluzby_clicked();
    void on_pushButton_menu_hlavni_clicked();
    void on_pushButton_menu_casovac_clicked();
    void on_pushButton_menu_quit_clicked();
    void on_pushButton_menu_svg_clicked();
    void on_pushButton_menu_led_clicked();
    void on_pushButton_menu_fullscreen_clicked();

    //sloty
    int slotKazdouVterinu();
    void slotPosunNacestnych();
    void slotHlavniStridejStranky();
    void slotToggleFullscreen();
    void slotXmlDoPromenne(QString vstupniXml);
    void slotSluzbaDoTabulky(QZeroConfService zcs);
    void slotOpozdenyStart();
    void slotAktualizaceTabulkySluzeb();
    void slotZtrataOdberu();

public slots:

};

#endif // MAINWINDOW_H
