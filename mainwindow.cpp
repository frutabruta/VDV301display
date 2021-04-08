#include "mainwindow.h"
#include "ui_mainwindow.h"



#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  //, mNetMan(new QNetworkAccessManager(this))
  //, mNetReply(nullptr)
  // , mDataBuffer(new QByteArray)
  , CustomerInformationService("CustomerInformationService","AllData","2.2CZ1.0","_ibisip_http._tcp",48479)
{
    ui->setupUi(this);
    FormatZobrazeni();
    instanceXMLparser.Test();
    //ui->prepinaciOkno->setCurrentIndex(0);
    //QMainWindow::setWindowState(Qt::WindowFullScreen);
    //QObject::connect(&instanceHttpServeru, &myHTTPserver::dataNahrana  ,this, &MainWindow::refreshujZobrazeni);
    QObject::connect(&CustomerInformationService, &IbisIpSubscriber::dataNahrana  ,this, &MainWindow::xmlDoPromenne);
    QObject::connect(&CustomerInformationService,&IbisIpSubscriber::nalezenaSluzba,this,&MainWindow::sluzbyDoTabulky);

    connect(timer, &QTimer::timeout, this, &MainWindow::kazdouVterinu);
    connect(CustomerInformationService.timer,&QTimer::timeout ,this,&MainWindow::vyprselCasovacSluzby);
    timer->start(1000);

    CustomerInformationService.odebirano=false ;
    CustomerInformationService.hledejSluzby("_ibisip_http._tcp.",1);


   // ui->tabulkaSubscriberu->setColumnCount(4);




}

int MainWindow::kazdouVterinu()
{
    ui->labelZbyvajiciVteriny->setText(QString::number(CustomerInformationService.timer->remainingTime()/1000) );
    return 1;
}

void MainWindow::vyprselCasovacSluzby()
{
    qDebug()<<"MainWindow::vyprselCasovacSluzby()";
    vymazObrazovku();
}

void MainWindow::vymazObrazovku()
{
    qDebug()<<"MainWindow::vymazObrazovku()";
    ui->Lcil->setText("");
    ui->Llinka->setText("");
    ui->Lnacestna1->setText("");
    ui->Lnacestna2->setText("");
    ui->Lnacestna3->setText("");
    ui->Lnacestna4->setText("");

}
/*
 *MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    DeviceManagementService("DeviceManagementService","_ibisip_http._tcp",47477),
    CustomerInformationService("CustomerInformationService","_ibisip_http._tcp",47479)
 * */

int MainWindow::VykresleniPrijatychDat()
{
    qDebug()<<"MainWindow::VykresleniPrijatychDat";
    qInfo()<<"\n VykresleniPrijatychDat";
    //nazevCile=QString( nazevCile.fromUtf8(test1));
    ui->Lcil->setText(nazevCile);
    ui->Llinka->setText(nazevLinky);
    if(indexZastavky<globalniSeznamZastavek.size())
    {

        ui->Lnacestna1->setText(globalniSeznamZastavek[indexZastavky].StopName);
        if ((indexZastavky+1)<pocetZastavek)
        {
            ui->Lnacestna2->setText(globalniSeznamZastavek[indexZastavky+1].StopName);
        }
        else
        {
            ui->Lnacestna2->setText(" ");
        }
        if ((indexZastavky+2)<pocetZastavek)
        {
            ui->Lnacestna3->setText(globalniSeznamZastavek[indexZastavky+2].StopName);
        }
        else
        {
            ui->Lnacestna3->setText(" ");
        }
        if ((indexZastavky+3)<pocetZastavek)
        {
            ui->Lnacestna4->setText(globalniSeznamZastavek[indexZastavky+3].StopName);
        }
        else
        {
            ui->Lnacestna4->setText(" ");

        }

    }
    else
    {
        qDebug()<<"indexZastavky je"<<QString::number(indexZastavky)<<" velikost globSezZast="<<QString::number(globalniSeznamZastavek.size());
    }

    if()


    return 1;
}

int MainWindow::DoplneniPromennych()
{
    qDebug()<<"MainWindow::DoplneniPromennych";
    qInfo()<<"\n DoplneniPromennych";
    if (globalniSeznamZastavek.size()>indexZastavky)
    {
        nazevCile=globalniSeznamZastavek.at(indexZastavky).DestinationName;
        nazevLinky=globalniSeznamZastavek.at(indexZastavky).LineName;
    }
    else
    {
        qDebug()<<"indexZastavky je"<<QString::number(indexZastavky)<<" velikost globSezZast="<<QString::number(globalniSeznamZastavek.size());
    }
    qInfo()<<"nazevCile "<<nazevCile;
    return 1;
}

int MainWindow::FormatZobrazeni()
{
    qDebug()<<"MainWindow::FormatZobrazeni";
    qInfo()<<"\n FormatZobrazeni";

    QString barva1 ="#1a1a70"; //tmave modra
    QString barva2 ="#ffffff"; //bila
    ui->Llinka->setStyleSheet("QLabel { background-color :"+barva2+" ; color : "+barva1+"; }");
    ui->Lcil->setStyleSheet("QLabel { background-color :"+barva1+" ; color : "+barva2+"; }");
    ui->Lnacestna1->setStyleSheet("QLabel { background-color :"+barva2+" ; color : "+barva1+"; }");
    ui->Lnacestna2->setStyleSheet("QLabel { background-color :"+barva1+" ; color : "+barva2+"; }");
    ui->Lnacestna3->setStyleSheet("QLabel { background-color :"+barva1+" ; color : "+barva2+"; }");
    ui->Lnacestna4->setStyleSheet("QLabel { background-color :"+barva1+" ; color : "+barva2+"; }");
    ui->sipka->setStyleSheet("QLabel { background-color :"+barva1+" ; color : "+barva2+"; }");
    //ui->prepinaciOkno->setStyleSheet("QStackedWidget {margin: 0;}");
    return 1;

}

MainWindow::~MainWindow()
{
    qDebug()<<"MainWindow::~MainWindow";
    //delete mDataBuffer;
    delete ui;
}



void MainWindow::on_actiontestPolozka_triggered()
{
    qDebug()<<"MainWindow::on_actiontestPolozka_triggered";
    qInfo()<<"\n on_actiontestPolozka_triggered";

    instanceXMLparser.VytvorSeznamZastavek(globalniSeznamZastavek, &indexZastavky, &pocetZastavek);
    //qInfo()<<globalniSeznamZastavek[4].StopName;
    qInfo()<<indexZastavky;
    qInfo()<<"CIl:"<<nazevCile;
    DoplneniPromennych();
    VykresleniPrijatychDat();
    FormatZobrazeni();
    qInfo()<<"CIl:"<<nazevCile;
}


/*


SITOVA CAST, ODPOVIDAC
nejsem autorem




*/







// == PRIVATE SLOTS ==
void MainWindow::OnRefreshClicked()
{
    qDebug()<<"MainWindow::OnRefreshClicked";
    qInfo()<<"\n OnRefreshClicked";
}

void MainWindow::OnDataReadyToRead()
{
    qDebug()<<"MainWindow::OnDataReadyToRead";
    qInfo()<<"\n OnDataReadyToRead";
    //mDataBuffer->append(mNetReply->readAll());
}

void MainWindow::OnListReadFinished()
{
    qDebug()<<"MainWindow::OnListReadFinished";


}


void MainWindow::on_refreshTlac_clicked()
{
    qDebug()<<"MainWindow::on_refreshTlac_clicked";
    qInfo()<<"\n on_refreshTlac_clicked";
    CustomerInformationService.odebirano=false ;
    CustomerInformationService.hledejSluzby("_ibisip_http._tcp.",1);
    this->vymazObrazovku();
    ui->tabulkaSubscriberu->setRowCount(0);
    //xmlDoPromenne(1);

}


void MainWindow::sluzbyDoTabulky(QZeroConfService zcs)
{
    qint32 row;
    QTableWidgetItem *cell;
    // qDebug() << "Added service: " << zcs;
    QString nazev=zcs->name();
    QString ipadresa=zcs->ip().toString();
    QString verze=zcs.data()->txt().value("ver");
    int port=zcs->port();
    /*
    qDebug() <<"nazev sluzby "<<nazev<<" ip adresa "<<ipadresa<<" port "<<QString::number(port)<<" data" <<verze ;

 */
    // tableWidget->setRowCount(10);

    row = ui->tabulkaSubscriberu->rowCount();
    ui->tabulkaSubscriberu->insertRow(row);
    cell = new QTableWidgetItem(zcs->name());
    ui->tabulkaSubscriberu->setItem(row, 0, cell);

    cell = new QTableWidgetItem(verze);
    ui->tabulkaSubscriberu->setItem(row, 1, cell);
    ui->tabulkaSubscriberu->resizeColumnsToContents();

    cell = new QTableWidgetItem(zcs->ip().toString());
    ui->tabulkaSubscriberu->setItem(row, 2, cell);
    ui->tabulkaSubscriberu->resizeColumnsToContents();

    cell = new QTableWidgetItem(QString::number(port));
    ui->tabulkaSubscriberu->setItem(row, 3, cell);
    ui->tabulkaSubscriberu->resizeColumnsToContents();

#if !(defined(Q_OS_IOS) || defined(Q_OS_ANDROID))
    //setFixedSize(ui->tabulkaSubscriberu->horizontalHeader()->length() + 60, ui->tabulkaSubscriberu->verticalHeader()->length() + 100);
#endif

    //QString strukturaKodberu="/CustomerInformationService/SubscribeAllData";
    /*
   QString adresaZaLomitkem="/"+nazevSluzbyInterni+"/Subscribe"+strukturaInterni;
    QString adresaCileString="http://"+zcs->ip().toString()+":"+QString::number(zcs->port())+adresaZaLomitkem;
    qDebug()<<"adresaCile string "<<adresaCileString;
    QUrl adresaKamPostovatSubscirbe=QUrl(adresaCileString);

    if (najdiSluzbu(nazevSluzbyInterni,verzeInterni,zcs)&&(this->odebirano==false))
    {
        PostSubscribe(adresaKamPostovatSubscirbe,this->vytvorSubscribeRequest(projedAdresy(),cisloPortuInterni));
        qDebug()<<"odesilam subscribe na "<<ipadresa<<":"<<QString::number(port)<<" sluzba "<<nazev;
    }*/
}

void MainWindow::xmlDoPromenne(QString vstupniXml)
{
    qDebug()<<"MainWindow::xmlDoPromenne";
    //vstup=0;

    //QByteArray retezec ="";
    //retezec+=instanceHttpServeru.prijatoZeServeruTelo;
    instanceXMLparser.nactiXML(vstupniXml);
    QByteArray argumentXMLserveru = "";
    QByteArray hlavicka="";
    QByteArray telo="";
    hlavicka+=("HTTP/1.1 200 OK\r\n");       // \r needs to be before \n
    //hlavicka+=("Content-Type: application/xml\r\n");
    telo+=("<?xml version=\"1.0\" encoding=\"UTF-8\"?>  <body> neco </body>");
    QByteArray teloVelikost = QByteArray::number(telo.size());
    hlavicka+=("Content-Length: "+teloVelikost+"\r\n");
    hlavicka+=("Content-Type: text/xml\r\n");
    // hlavicka+=("Connection: close\r\n");
    hlavicka+=("Pragma: no-cache\r\n");
    hlavicka+=("Server: Microsoft-HTTPAPI/1.0");
    hlavicka+=("\r\n");


    QByteArray pozadavek=hlavicka+telo;
    argumentXMLserveru.append(pozadavek);
    //instanceHttpServeru.zapisDoPromenne(argumentXMLserveru);
    qInfo()<<argumentXMLserveru;
    /* konec obracena archtitektura*/
    instanceXMLparser.VytvorSeznamZastavek(globalniSeznamZastavek, &indexZastavky, &pocetZastavek);
    //instanceXMLparser.nactiXML(globalniSeznamZastavek, &indexZastavky, &pocetZastavek);
    //qInfo()<<globalniSeznamZastavek[4].StopName;
    qInfo()<<indexZastavky;
    qInfo()<<"CIl:"<<nazevCile;
    if( globalniSeznamZastavek.size()>0)
    {
        DoplneniPromennych();
        VykresleniPrijatychDat();
        FormatZobrazeni();
        qInfo()<<"CIl:"<<nazevCile;
        //instanceHttpServeru.prijatoZeServeruTelo="";
    }
    else
    {
        qDebug()<<"nepodarilo se vyparsovat zastavky";
    }
    //NetworkCleanup();

}





/*
void MainWindow::on_prepinaciOkno_currentChanged()
{

}
*/

void MainWindow::on_tlacitkoSeznamSluzeb_clicked()
{
    ui->prepinadloStran->setCurrentIndex(1);
}

void MainWindow::on_tlacitkoHlavni_clicked()
{
    ui->prepinadloStran->setCurrentIndex(0);
}

void MainWindow::on_tlacitkoCasovac_clicked()
{
    ui->prepinadloStran->setCurrentIndex(2);
}
