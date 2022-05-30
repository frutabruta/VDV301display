#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define MAX_ZAST 100



void on_actionstahnoutXML_triggered();

#include <QMainWindow>
#include <QWidget>


#include "xmlparser.h"
//#include "httpserver2/myhttpserver.h"
#include "VDV301subscriber/ibisipsubscriber.h"
#include "VDV301struktury/cestaudaje.h"
#include "VDV301struktury/zastavkacil.h"
#include "pasmovedvojicelcd.h"
#include "svgvykreslovani.h"
#include "labelvykreslovani.h"

#include <QGraphicsSvgItem>
#include <QGraphicsScene>
#include <QSvgRenderer>
#include <QFontDatabase>
#include <QtDebug>

#include <QLabel>
#include <QMessageBox>



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
    XmlParser instanceXMLparser;
    QVector <ZastavkaCil> globalniSeznamZastavek;
    QVector <ZastavkaCil> globalniSeznamZastavekNavaznehoSpoje;
    QString nazevLinky = "";
    QString nazevCile="";

    QString additionalTextMessage="";
    QVector<Pasmo> pasmaZ;
    QVector<Pasmo> pasmaDo;
    bool zmenaPasma=false;

    int indexZastavky=0;
    int pocetZastavek=0;
    int VykresleniPrijatychDat();
    int DoplneniPromennych ();
    int FormatZobrazeni();
    ~MainWindow();

    IbisIpSubscriber CustomerInformationServiceSubscriber;
    bool svgOpenFile(const QString &fileName);
    SvgVykreslovani svgVykreslovac;



    void ledNaplnFront(QString linka, QString horniRadek, QString dolniRadek);
    void ledNaplnInner(QString linka, QString horniRadek, QString dolniRadek);
    void ledIterujBocniPanel(QVector<QString> texty, int &iteracniIndex);
    QVector<QString> ledNaplnNacestyBocniPanel(ZastavkaCil aktualniZastavka);
    void ledIiterujVsechnyPanely();

    QFontDatabase fdb;

    QFont font8;
    QFont font10;

    //void naplnZmenaLabel(QString vstup);
  //  void naplnAnouncementLabel(QString vstup);
    void zobrazZmenuPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma);

    //QString vyrobTextZmenyPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma);

    void skryjZmenuPasma();

    //  void hlavniVykresliNasledne();

    void ledIterujVnitrniPanel(QVector<QString> texty, int &iteracniIndex);
    int hlavniVykresliSkupinuZastavek(int offset, int pocetPoli, QVector<ZastavkaCil> zastavky, bool navazny);
private slots:
    void on_actiontestPolozka_triggered();
    void OnRefreshClicked();
    void OnDataReadyToRead();
    void OnListReadFinished();

    void on_refreshTlac_clicked();

    void on_tlacitkoSeznamSluzeb_clicked();

    void on_tlacitkoHlavni_clicked();

    int slotKazdouVterinu();
    void on_tlacitkoCasovac_clicked();

    void on_quitTlacitko_clicked();

    void on_pushButton_clicked();

    void on_svgTlacitko_clicked();

    void on_tlacitkoLed_clicked();

    void slotPosunNacestnych();
public slots:
    void xmlDoPromenne(QString vstupniXml);
    void sluzbyDoTabulky(QZeroConfService zcs);
private:
    Ui::MainWindow *ui;
    QTimer *timer = new QTimer(this);
    void vsechnyConnecty();

    //konstanty

    int posunRotovani=0;
    int pocetVykreslovanychZastavek=5;



    //instance knihoven
    CestaUdaje stavSystemu;
    LabelVykreslovani labelVykreslovani;

    //udalosti
    void obarviPozadiPristi(QString barvaPisma, QString barvaPozadi);
    void vyprselCasovacSluzby();
    void vymazObrazovku();

    //polozky potrebne pro vykresleni svg
    QGraphicsScene scene;
    QGraphicsSvgItem *m_svgItem;
    QGraphicsRectItem *m_outlineItem;
     bool svgVykresleni();

     //virtuální LED panely

    void ledNaplnSide(QString linka, QString horniRadek, QString dolniRadek);
    void ledNaplnRear(QString linka);
    void ledInicializujVirtualniPanely();
    void ledAktualizujZobrazeniVirtualnichPanelu(QVector<ZastavkaCil> zastavky, CestaUdaje stav);

    QVector<QString> textyBocniPanelkIteraci;
     QVector<QString> textyVnitrniPanelkIteraci;
    int cyklovaniIndex=0;

    QTimer *timerBocniPanel = new QTimer(this);
    QTimer *timerNacestneZastavky = new QTimer(this);


    //hlavni
    void hlavniNaplnPoleLabelu();
    void hlavniVykresliNacestne();
    void hlavniVykreslZastavkyiPasma(QVector<ZastavkaCil> aktZastavky, QVector<ZastavkaCil> navazZastavky);
    void hlavniZobrazAnnoucement(QString title, QString type, QString textCz, QString textEn);
    void hlavniZobrazZmenuPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma);
    void hlavniVymazObrazovku();

    //obecne Udalosti
    void skryjAnnouncement();
    void zobrazAnnoucement(QString title, QString type, QString textCz, QString textEn);

    void zobrazKonecnou();
    void navratJizda();
    int jeVozidloNaKonecne(CestaUdaje stav, QVector<ZastavkaCil> zastavky);

   // void hlavniVykresliNacestneForce();


    //vektory Labelu Hlavni
    QVector<QLabel*> seznamNazvuZastavek;
    QVector<QLabel*> seznamPasem1;
    QVector<QLabel*> seznamPasem2;

    void vymazPoleLabelu(QVector<QLabel*> vstup);
    int minimum(int cislo1, int cislo2);








    QString barva_PozadiA_25_25_25 ="rgb(25,25,25)";
    QString barva_PozadiB_50_50_50 ="rgb(50,50,50)"; //tmave seda
    QString barva_PozadiC_100_100_100 ="rgb(100,100,100)";
    QString barva_PozadiD_150_150_150 ="rgb(150,150,150)"; //Pozadí D
    QString barva_Zastavka_180_180_180 ="rgb(180,180,180)"; //Zastávka
    QString barva_bila_255_255_255 ="#ffffff"; //bila

    QString barva_Vyluky_255_170_30 ="rgb(255,170,30)";
    QString barva_Cervena_200_0_20 ="rgb(200,0,20)";
    QString barva_CervenaTexty_220_40_40 ="rgb(220,40,40)";
    QString barva_Zelena_210_215_15 ="rgb(210,215,15)";

    void hlavniVykresliCisloLinky(QString alias);
    /*
     QString barva____ ="rgb(,,)";
     QString barva____ ="rgb(,,)";
     QString barva____ ="rgb(,,)";
     QString barva____ ="rgb(,,)";
     QString barva____ ="rgb(,,)";
     QString barva____ ="rgb(,,)";
     QString barva____ ="rgb(,,)";
     QString barva____ ="rgb(,,)";
     QString barva____ ="rgb(,,)";
     QString barva____ ="rgb(,,)";
     QString barva____ ="rgb(,,)";
     QString barva____ ="rgb(,,)";

 */


    int jeVRozsahu(int index, int pocetHodnot);
    QVector<QString> ledNaplnNacestyVnitrniPanel(ZastavkaCil aktualniZastavka);
};

#endif // MAINWINDOW_H
