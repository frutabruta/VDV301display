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

#include <QGraphicsSvgItem>
#include <QGraphicsScene>
#include <QSvgRenderer>
#include <QFontDatabase>
#include <QtDebug>

#include <QLabel>



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



    void naplnLedFront(QString linka, QString horniRadek, QString dolniRadek);
    void naplnLedInner(QString linka, QString horniRadek, QString dolniRadek);
    void iterujBocniPanel(QVector<QString> texty, int &iteracniIndex);
    QVector<QString> naplnNacestyBocniPanel(ZastavkaCil aktualniZastavka);
    void iterujVsechnyPanely();

    QFontDatabase fdb;

    QFont font8;
    QFont font10;

    void naplnZmenaLabel(QString vstup);
    void naplnAnouncementLabel(QString vstup);
    void zobrazZmenuPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma);
    QString vyrobTextZmenyPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma);

    void skryjZmenuPasma();

private slots:
    void on_actiontestPolozka_triggered();
    void OnRefreshClicked();
    void OnDataReadyToRead();
    void OnListReadFinished();

    void on_refreshTlac_clicked();

    void on_tlacitkoSeznamSluzeb_clicked();

    void on_tlacitkoHlavni_clicked();

    int kazdouVterinu();
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
    CestaUdaje stavSystemu;

    void vyprselCasovacSluzby();
    void vymazObrazovku();
    void obarviPozadiPristi(QString barvaPisma, QString barvaPozadi);




    int posunRotovani=0;
    int pocetVykreslovanychZastavek=5;


    QGraphicsScene scene;
    QGraphicsSvgItem *m_svgItem;
    QGraphicsRectItem *m_outlineItem;
    bool svgReplaceName();
    bool svgReplaceName(QString souborVstup, QString souborVystup, QString cil, QString zst0, QString zst1, QString zst2);
    bool individualniNahrazeni(QDomDocument &xmlDocument, QString hledaneId, QString novaHodnota);
    bool svgVykresleni();
    void naplnLedObsah(QVector<QString> zobrazit);
    void naplnLedSide(QString linka, QString horniRadek, QString dolniRadek);
    void naplnLedRear(QString linka);
    void inicializujVirtualniLedPanely();
    void aktualizujZobrazeniVirtualnichLedPanelu(QVector<ZastavkaCil> zastavky, CestaUdaje stav);
    QVector<QString> textyBocniPanelkIteraci;
    int cyklovaniIndex=0;

    QTimer *timerBocniPanel = new QTimer(this);
    QTimer *timerNacestneZastavky = new QTimer(this);



    void skryjAnnouncement();
    void zobrazAnnoucement(QString title, QString type, QString textCz, QString textEn);
    void zobrazKonecnou();
    void navratJizda();
    int jeVozidloNaKonecne(CestaUdaje stav, QVector<ZastavkaCil> zastavky);
    void vykresliNacestne();
    void vykresliNacestneForce();


    void naplnPoleLabelu();
    QVector<QLabel*> seznamNazvuZastavek;
    QVector<QLabel*> seznamPasem1;
    QVector<QLabel*> seznamPasem2;
    void vymazPoleLabelu(QVector<QLabel*> vstup);
    int minimum(int cislo1, int cislo2);
};

#endif // MAINWINDOW_H
