#include "mainwindow.h"
#include "ui_mainwindow.h"



#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QWidget>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  //, mNetMan(new QNetworkAccessManager(this))
  //, mNetReply(nullptr)
  // , mDataBuffer(new QByteArray)
  , CustomerInformationServiceSubscriber("CustomerInformationService","AllData","2.2CZ1.0","_ibisip_http._tcp",48479)
{
    ui->setupUi(this);
    FormatZobrazeni();
    instanceXMLparser.Test();
    //ui->prepinaciOkno->setCurrentIndex(0);
    //QMainWindow::setWindowState(Qt::WindowFullScreen);
    //QObject::connect(&instanceHttpServeru, &myHTTPserver::dataNahrana  ,this, &MainWindow::refreshujZobrazeni);
    QObject::connect(&CustomerInformationServiceSubscriber, &IbisIpSubscriber::dataNahrana  ,this, &MainWindow::xmlDoPromenne);
    QObject::connect(&CustomerInformationServiceSubscriber,&IbisIpSubscriber::nalezenaSluzba,this,&MainWindow::sluzbyDoTabulky);

    connect(timer, &QTimer::timeout, this, &MainWindow::kazdouVterinu);
    connect(CustomerInformationServiceSubscriber.timer,&QTimer::timeout ,this,&MainWindow::vyprselCasovacSluzby);
    timer->start(1000);

    CustomerInformationServiceSubscriber.odebirano=false ;
    CustomerInformationServiceSubscriber.hledejSluzby("_ibisip_http._tcp.",1);


    // ui->tabulkaSubscriberu->setColumnCount(4);




}

int MainWindow::kazdouVterinu()
{
    ui->labelZbyvajiciVteriny->setText(QString::number(CustomerInformationServiceSubscriber.timer->remainingTime()/1000) );
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
    //ui->Lnacestna1->setStyleSheet("QLabel { background-color :"+barva2+" ; color : "+barva1+"; }");
    ui->Lnacestna2->setStyleSheet("QLabel { background-color :"+barva1+" ; color : "+barva2+"; }");
    ui->Lnacestna3->setStyleSheet("QLabel { background-color :"+barva1+" ; color : "+barva2+"; }");
    ui->Lnacestna4->setStyleSheet("QLabel { background-color :"+barva1+" ; color : "+barva2+"; }");
    ui->sipka->setStyleSheet("QLabel { background-color :"+barva1+" ; color : "+barva2+"; }");
    //ui->prepinaciOkno->setStyleSheet("QStackedWidget {margin: 0;}");
    if (stavSystemu.locationState=="AtStop" )
    {
        obarviPozadiPristi(barva1,barva2 );
    }
    else
    {
        obarviPozadiPristi(barva2,barva1);
    }
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

    instanceXMLparser.VytvorSeznamZastavek(globalniSeznamZastavek, stavSystemu.indexAktZastavky, pocetZastavek);
    instanceXMLparser.nactiVehicleGroup(stavSystemu,instanceXMLparser.dokument);
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
    CustomerInformationServiceSubscriber.odebirano=false ;
    CustomerInformationServiceSubscriber.hledejSluzby("_ibisip_http._tcp.",1);
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

    instanceXMLparser.VytvorSeznamZastavek(globalniSeznamZastavek, indexZastavky, pocetZastavek);
    instanceXMLparser.nactiVehicleGroup(stavSystemu,instanceXMLparser.dokument);
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

void MainWindow::obarviPozadiPristi(QString barvaPisma,QString barvaPozadi)
{
    qDebug()<<"MainWindow::obarviPozadiPristi";
    //
    //ui->Lnacestna1->setAutoFillBackground(true);

    ui->Lnacestna1->setStyleSheet("background-color :"+barvaPozadi+" ; color : "+barvaPisma+"; ");

    //ui->Lnacestna1->repaint();
}


void MainWindow::on_quitTlacitko_clicked()
{
    qDebug()<<"\n on_quitTlacitko_clicked \n";
    MainWindow::close();
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_svgTlacitko_clicked()
{

    ui->prepinadloStran->setCurrentIndex(3);


    //QSvgRenderer *m_renderer = new QSvgRenderer(QLatin1String("./Verlauf.svg"));


    if (globalniSeznamZastavek.length()>0)
    {
    svgVykreslovac.svgReplaceName("Verlauf2.svg","vystup.txt",globalniSeznamZastavek.last().StopName,globalniSeznamZastavek.at(stavSystemu.indexAktZastavky).StopName,globalniSeznamZastavek.at(stavSystemu.indexAktZastavky+1).StopName,globalniSeznamZastavek.at(stavSystemu.indexAktZastavky+2).StopName);
    }
    int vysledek=svgOpenFile("./vystup.txt");
    qDebug()<<"vysledek otevirani SVG je"<<QString::number(vysledek);

    /*
    ui->graphicsView->setScene(&novaScena);
    ui->graphicsView->update();
    ui->graphicsView->show();
    */

}


//zkpirovano z svgviewer demo


bool MainWindow::svgOpenFile(const QString &fileName)
{
    qDebug()<<"MainWindow::openFile";
    QGraphicsScene *s = &scene;

    // const bool drawBackground = (m_backgroundItem ? m_backgroundItem->isVisible() : false);
    // const bool drawOutline = (m_outlineItem ? m_outlineItem->isVisible() : true);
    QFile soubor;

    QScopedPointer<QGraphicsSvgItem> svgItem(new QGraphicsSvgItem(fileName));
    //QScopedPointer<QGraphicsSvgItem> svgItem(new QGraphicsSvgItem(soubor));
    if (!svgItem->renderer()->isValid())
        return false;

    s->clear();
    // resetTransform();

    m_svgItem = svgItem.take();
    m_svgItem->setFlags(QGraphicsItem::ItemClipsToShape);
    m_svgItem->setCacheMode(QGraphicsItem::NoCache);
    m_svgItem->setZValue(0);

    /*m_backgroundItem = new QGraphicsRectItem(m_svgItem->boundingRect());
    m_backgroundItem->setBrush(Qt::white);
    m_backgroundItem->setPen(Qt::NoPen);
    m_backgroundItem->setVisible(drawBackground);
    m_backgroundItem->setZValue(-1);
    */


    m_outlineItem = new QGraphicsRectItem(m_svgItem->boundingRect());
    QPen outline(Qt::black, 2, Qt::DashLine);
    outline.setCosmetic(true);
    m_outlineItem->setPen(outline);
    m_outlineItem->setBrush(Qt::NoBrush);
    //m_outlineItem->setVisible(drawOutline);
    m_outlineItem->setZValue(1);


    //s->addItem(m_backgroundItem);
    s->addItem(m_svgItem);
    //s->addItem(m_outlineItem);

    s->setSceneRect(m_outlineItem->boundingRect().adjusted(-10, -10, 10, 10));
    ui->graphicsView->setScene(s);
    return true;
}
