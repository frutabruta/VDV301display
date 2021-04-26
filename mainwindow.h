#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define MAX_ZAST 100



void on_actionstahnoutXML_triggered();

#include <QMainWindow>
#include "xmlparser.h"
//#include "httpserver2/myhttpserver.h"
#include "VDV301subscriber/ibisipsubscriber.h"
#include "VDV301struktury/cestaudaje.h"
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
    QVector <SeznamZastavek> globalniSeznamZastavek;
    QString nazevLinky = "";
    QString nazevCile="";
    int indexZastavky=0;
    int pocetZastavek=0;
    int VykresleniPrijatychDat();
    int DoplneniPromennych ();
    int FormatZobrazeni();
    ~MainWindow();

    IbisIpSubscriber CustomerInformationServiceSubscriber;
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
};

#endif // MAINWINDOW_H
