#include "mainwindow.h"
#include "ui_mainwindow.h"



#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QWidget>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QSvgWidget>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    CustomerInformationServiceSubscriber("CustomerInformationService","AllData","2.2CZ1.0","_ibisip_http._tcp",48479)
{

    // fonty
    fdb.addApplicationFont("fonty/21-pid-1.ttf");
    fdb.addApplicationFont("fonty/21-pid-3.ttf");
    fdb.addApplicationFont("fonty/21-pid-5.ttf");
    fdb.addApplicationFont("fonty/21-pid-8.ttf");
    fdb.addApplicationFont("fonty/21-pid-10.ttf");

    font8.setFamily("21-PID 8");
    font8.setPointSize(65);

    font10.setFamily("21-PID 10");
    font10.setPointSize(65);

    ui->setupUi(this);

    vsechnyConnecty();


    naplnPoleLabelu();

    ui->prepinadloStran->setCurrentIndex(0);
    ui->stackedWidget_prostredek->setCurrentIndex(0);
    ui->stackedWidget_prostredek->setCurrentIndex(0);

    FormatZobrazeni();
    instanceXMLparser.Test();
     timer->start(1000);
    timerBocniPanel->start(2000);
    timerNacestneZastavky->start(20);

    CustomerInformationServiceSubscriber.odebirano=false ;
    CustomerInformationServiceSubscriber.hledejSluzby("_ibisip_http._tcp.",1);

    this->inicializujVirtualniLedPanely();

    // ui->tabulkaSubscriberu->setColumnCount(4);


    bool dvaradky=true;
    if(dvaradky==true)
    {
        ui->labelFrontSingle->setVisible(false);
        ui->labelFrontBottomRow->setVisible(true);
        ui->labelFrontTopRow->setVisible(true);
    }
    else
    {
        ui->labelFrontSingle->setVisible(true);
        ui->labelFrontBottomRow->setVisible(false);
        ui->labelFrontTopRow->setVisible(false);
    }
    /*
    auto    sw1 = new QSvgWidget(QString("vystupanim.svg"), this);
    ui->verticalLayout_3->addWidget(sw1);
    sw1->setGeometry(50, 50, rect().width(), rect().height());
    */

    QString compilationTime = QString(__DATE__);
    compilationTime+="T";
    compilationTime+=QString(__TIME__);
    ui->label_build->setText(compilationTime);


}

void MainWindow::vsechnyConnecty()
{
    QObject::connect(&CustomerInformationServiceSubscriber, &IbisIpSubscriber::dataNahrana  ,this, &MainWindow::xmlDoPromenne);
    QObject::connect(&CustomerInformationServiceSubscriber,&IbisIpSubscriber::nalezenaSluzba,this,&MainWindow::sluzbyDoTabulky);

    connect(timer, &QTimer::timeout, this, &MainWindow::kazdouVterinu);

    connect(timerBocniPanel, &QTimer::timeout, this, &MainWindow::iterujVsechnyPanely);
    connect(timerNacestneZastavky, &QTimer::timeout, this, &MainWindow::slotPosunNacestnych);


    connect(CustomerInformationServiceSubscriber.timer,&QTimer::timeout ,this,&MainWindow::vyprselCasovacSluzby);

}

int MainWindow::kazdouVterinu()
{
    ui->labelZbyvajiciVteriny->setText(QString::number(CustomerInformationServiceSubscriber.timer->remainingTime()/1000) );
    return 1;
}

void MainWindow::slotPosunNacestnych()
{
    int delkaTextu=ui->label_nacestne->width();
    int krok=1;

    if(delkaTextu<ui->scrollArea->width() )
    {
        return;
    }
    // qDebug()<<"delka beziciho textu "<< delkaTextu << " posun rotovani: "<<posunRotovani;

    posunRotovani-=krok;

    if (abs(posunRotovani)>delkaTextu)
    {
        posunRotovani=0;
        vykresliNacestneForce();
    }

    else

    {
        ui->scrollAreaWidgetContents->scroll(-krok,0);
    }

}

void MainWindow::vyprselCasovacSluzby()
{
    qDebug()<<"MainWindow::vyprselCasovacSluzby()";
    vymazObrazovku();
}



void MainWindow::naplnPoleLabelu()
{
    seznamNazvuZastavek.push_back(ui->Lnacestna1);
    seznamNazvuZastavek.push_back(ui->Lnacestna2);
    seznamNazvuZastavek.push_back(ui->Lnacestna3);
    seznamNazvuZastavek.push_back(ui->Lnacestna4);
    seznamNazvuZastavek.push_back(ui->Lnacestna5);

    seznamPasem1.push_back(ui->label_pasmo1_1);
    seznamPasem1.push_back(ui->label_pasmo2_1);
    seznamPasem1.push_back(ui->label_pasmo3_1);
    seznamPasem1.push_back(ui->label_pasmo4_1);
    seznamPasem1.push_back(ui->label_pasmo5_1);

    seznamPasem2.push_back(ui->label_pasmo1_2);
    seznamPasem2.push_back(ui->label_pasmo2_2);
    seznamPasem2.push_back(ui->label_pasmo3_2);
    seznamPasem2.push_back(ui->label_pasmo4_2);
    seznamPasem2.push_back(ui->label_pasmo5_2);
}


void MainWindow::vymazPoleLabelu(QVector<QLabel*> vstup)
{
    foreach( QLabel* odkaz, vstup)
    {
        odkaz->setText("");
    }
}



void MainWindow::vymazObrazovku()
{
    qDebug()<<"MainWindow::vymazObrazovku()";
    ui->Lcil->setText("");
    ui->Llinka->setText("");

    vymazPoleLabelu(seznamNazvuZastavek);
    vymazPoleLabelu(seznamPasem1);
    vymazPoleLabelu(seznamPasem2);

    const QObjectList localChildren = ui->centralWidget->children();

    foreach (QObject *obj, localChildren)
    {
        QLabel *label = qobject_cast<QLabel *>(obj);
        if(label)
        {
            qDebug() << label->text();
        }
    }

}


int MainWindow::VykresleniPrijatychDat()
{
    qDebug()<<"MainWindow::VykresleniPrijatychDat";

    ui->Lcil->setText(nazevCile);
    ui->Llinka->setText(nazevLinky);


    QPixmap m_logo_pic;
    QLabel *m_pic_label;
    m_pic_label=new QLabel();

        m_logo_pic.load(":/image/bank.png");
        m_pic_label->setPixmap(m_logo_pic);


    ui->label_locationState->setText(stavSystemu.locationState);
    ui->label_currentStopIndex->setText(QString::number(stavSystemu.indexAktZastavky));

    int pocetZastavekVykreslit=0;

    pocetZastavekVykreslit=minimum(globalniSeznamZastavek.length()-stavSystemu.indexAktZastavky,pocetVykreslovanychZastavek);

    vymazPoleLabelu(seznamPasem1);
    vymazPoleLabelu(seznamPasem2);
    vymazPoleLabelu(seznamNazvuZastavek);

    hlavniVykreslZastavkyiPasma(pocetZastavekVykreslit);

    hlavniVykresliNacestne();

    //additional text message

    if(additionalTextMessage!="")
    {
        zobrazAnnoucement("","",additionalTextMessage,"");
    }
    else
    {
        naplnAnouncementLabel("");
    }

    //konecna

    if(jeVozidloNaKonecne(stavSystemu,globalniSeznamZastavek))
    {
        zobrazKonecnou();
    }
    else
    {
        if(zmenaPasma==true)
        {
            zobrazZmenuPasma(pasmaZ,pasmaDo);
        }
        else
        {
            navratJizda();
            // skryjZmenuPasma();
        }

    }
    //   hlavniVykresliNasledne();




    return 1;
}

/*
void MainWindow::hlavniVykresliNasledne()
{
    qDebug()<<"MainWindow::hlavniVykresliNasledne()";
    if(indexZastavky<globalniSeznamZastavek.size())
    {





        ui->Lnacestna1->setText(globalniSeznamZastavek[indexZastavky].zastavka.NameLcd);
        if ((indexZastavky+1)<pocetZastavek)
        {
            ui->Lnacestna2->setText(globalniSeznamZastavek[indexZastavky+1].zastavka.NameLcd);
        }
        else
        {
            ui->Lnacestna2->setText(" ");
        }

        if ((indexZastavky+2)<pocetZastavek)
        {
            ui->Lnacestna3->setText(globalniSeznamZastavek[indexZastavky+2].zastavka.NameLcd);
        }
        else
        {
            ui->Lnacestna3->setText(" ");
        }

        if ((indexZastavky+3)<pocetZastavek)
        {
            ui->Lnacestna4->setText(globalniSeznamZastavek[indexZastavky+3].zastavka.NameLcd);
        }
        else
        {
            ui->Lnacestna4->setText(" ");

        }

        if ((indexZastavky+4)<pocetZastavek)
        {
            ui->Lnacestna5->setText(globalniSeznamZastavek[indexZastavky+4].zastavka.NameLcd);
        }
        else
        {
            ui->Lnacestna5->setText(" ");

        }

    }
    else
    {
        qDebug()<<"indexZastavky je"<<QString::number(indexZastavky)<<" velikost globSezZast="<<QString::number(globalniSeznamZastavek.size());
    }
}
*/


void MainWindow::hlavniVykreslZastavkyiPasma(int pocetZastavekVykreslit )
{
    qDebug()<<"";

    for(int i=0;i<pocetZastavekVykreslit ; i++)
    {

        int pomocnyIndex=indexZastavky+i;
        Zastavka aktualniZastavka=globalniSeznamZastavek.at(pomocnyIndex).zastavka;

        PasmoveDvojiceLcd pasmoveDvojiceLcd;
        pasmoveDvojiceLcd.roztridPasma(aktualniZastavka.seznamPasem);

        seznamNazvuZastavek.at(i)->setText(doplnPiktogramy(aktualniZastavka.NameLcd,aktualniZastavka.seznamPiktogramu));


        // ui->Lnacestna5->setText(globalniSeznamZastavek[indexZastavky+4].zastavka.NameLcd);

        if(pasmoveDvojiceLcd.pasmaSystemu1.isEmpty())
        {
            seznamPasem1.at(i)->setText("");
        }
        else
        {
            QString pasmaString1=svgVykreslovac.pasmaDoStringu( pasmoveDvojiceLcd.pasmaSystemu1);
            QString zkratkaSystemuDvojtecka="";
            if (!pasmoveDvojiceLcd.pasmaSystemu2.isEmpty())
            {
                zkratkaSystemuDvojtecka=pasmoveDvojiceLcd.pasmaSystemu1.first().system+":";
            }
            seznamPasem1.at(i)->setText(zkratkaSystemuDvojtecka+pasmaString1);
        }

        if(pasmoveDvojiceLcd.pasmaSystemu2.isEmpty())
        {
            seznamPasem2.at(i)->hide();
        }
        else
        {
            QString pasmaString2=svgVykreslovac.pasmaDoStringu( pasmoveDvojiceLcd.pasmaSystemu2);
            seznamPasem2.at(i)->show();
            seznamPasem2.at(i)->setText(pasmoveDvojiceLcd.pasmaSystemu2.first().system+":"+pasmaString2);
        }


        //  qDebug()<<"label pasma "<<i<<" "<<stavSystemu.indexAktZastavky<<" p1:"<<pasmaString1<<" p2:"<<pasmaString2<<" "<<"pomocnyIndex";

    }

}


QString MainWindow::doplnPiktogramy(QString nazevZastavky,QVector<QString> seznamPiktogramu)
{
    QString vystup="";
    int vyskaObrazku=40;

    // <html><head/><body><p>Dalsi 2<span style=" color:#ffffff; background-color:#ff00ff;">M</span><img src=":/images/UndergroundB"/><img src=":/images/Trolleybus"/></p></body></html>


    QString htmlZacatek="<html><head/><body><p>";
                     //   "Dalsi 2<span style=" color:#ffffff; background-color:#ff00ff;">M</span>"

    QString htmlObrazky="";
    foreach(QString nazevPiktogramu,seznamPiktogramu)
    {           //height=\""+QString::number(vyskaObrazku)+" \"
        htmlObrazky+="<img  src=\":/images/"+nazevPiktogramu+"\" height=\""+QString::number(vyskaObrazku)+"\"  >";
    }


     QString htmlKonec="</p></body></html>";


     vystup=htmlZacatek+nazevZastavky+htmlObrazky+htmlKonec;
    return vystup;

}

QString MainWindow::doplnPiktogramyBezZacatkuKonce(QString nazevZastavky,QVector<QString> seznamPiktogramu)
{
    QString vystup="";
    int vyskaObrazku=40;

    // <html><head/><body><p>Dalsi 2<span style=" color:#ffffff; background-color:#ff00ff;">M</span><img src=":/images/UndergroundB"/><img src=":/images/Trolleybus"/></p></body></html>



                     //   "Dalsi 2<span style=" color:#ffffff; background-color:#ff00ff;">M</span>"

    QString htmlObrazky="";
    foreach(QString nazevPiktogramu,seznamPiktogramu)
    {           //height=\""+QString::number(vyskaObrazku)+" \"
htmlObrazky+="<img  src=\":/images/"+nazevPiktogramu+"\" height=\""+QString::number(vyskaObrazku)+"\"  >";
    }



     vystup=nazevZastavky+htmlObrazky;
    return vystup;

}

QString MainWindow::vykresliNacestneZastavkyText( QVector<Zastavka> nacestneZastavky)
{
    qDebug()<<"MainWindow::vykresliNacestneZastavkyText";
    if (nacestneZastavky.count()==0)
    {
        return "";
    }

    QString nacestyString="";



    nacestyString+=  doplnPiktogramyBezZacatkuKonce(nacestneZastavky.at(0).NameLcd,nacestneZastavky.at(0).seznamPiktogramu);
    for (int i=1;i<nacestneZastavky.count();i++)
    {
        nacestyString+=" – "+doplnPiktogramyBezZacatkuKonce( nacestneZastavky.at(i).NameLcd, nacestneZastavky.at(i).seznamPiktogramu);
    }


    QString htmlZacatek="<html><head/><body><p>";
     QString htmlKonec="</p></body></html>";

     QString vysledek=htmlZacatek+nacestyString+htmlKonec;
qDebug()<<"vypis radku nacestnych zastavek text html"<<vysledek;
    return vysledek;
}

int MainWindow::minimum(int cislo1, int cislo2)
{
    if(cislo1<cislo2)
    {
        return cislo1;
    }
    return cislo2;
}

void MainWindow::hlavniVykresliNacestne()
{
    qDebug()<<"MainWindow::vykresliNacestne()";
    //ui->label_nacestne->setText(" ");

    if(globalniSeznamZastavek.isEmpty())
    {
        ui->label_nacestne->setText("");
        return;
    }

    QString novyVstup=this->vykresliNacestneZastavkyText(globalniSeznamZastavek.at(stavSystemu.indexAktZastavky).nacestneZastavky);
    if(ui->label_nacestne->text()!=novyVstup)
    {
        ui->label_nacestne->setText( novyVstup);
    }


}

void MainWindow::vykresliNacestneForce()
{
    qDebug()<<"MainWindow::vykresliNacestneForce()";


    if(globalniSeznamZastavek.isEmpty())
    {
        ui->label_nacestne->setText("");
        return;
    }

    ui->label_nacestne->setText(" ");
    QString novyVstup=svgVykreslovac.vykresliNacestneZastavkyText(globalniSeznamZastavek.at(stavSystemu.indexAktZastavky).nacestneZastavky);
    ui->label_nacestne->setText( novyVstup);
}

int MainWindow::DoplneniPromennych()
{
    qDebug()<<"MainWindow::DoplneniPromennych";
    // qInfo()<<"\n DoplneniPromennych";
    if (globalniSeznamZastavek.size()>indexZastavky)
    {
        ZastavkaCil aktualniZastavka=globalniSeznamZastavek.at(indexZastavky);
        nazevCile=doplnPiktogramy(aktualniZastavka.cil.NameLcd,aktualniZastavka.cil.seznamPiktogramu);
        nazevLinky=aktualniZastavka.linka.LineName;
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






    if (stavSystemu.locationState=="AtStop" )
    {
        obarviPozadiPristi(barva_PozadiB_50_50_50,barva_Zastavka_180_180_180 );
    }
    else
    {
        obarviPozadiPristi(barva_bila_255_255_255,barva_PozadiB_50_50_50);
    }
    return 1;

}

MainWindow::~MainWindow()
{
    qDebug()<<"MainWindow::~MainWindow";
    delete ui;
}



void MainWindow::on_actiontestPolozka_triggered()
{
    qDebug()<<"MainWindow::on_actiontestPolozka_triggered";
    qInfo()<<"\n on_actiontestPolozka_triggered";

    instanceXMLparser.VytvorSeznamZastavek(globalniSeznamZastavek, stavSystemu.indexAktZastavky, pocetZastavek);
    instanceXMLparser.nactiVehicleGroup(stavSystemu,instanceXMLparser.dokument);
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
    /*
    CustomerInformationServiceSubscriber.odebirano=false ;
    CustomerInformationServiceSubscriber.hledejSluzby("_ibisip_http._tcp.",1);
    this->vymazObrazovku();
    ui->tabulkaSubscriberu->setRowCount(0);
    //xmlDoPromenne(1);
*/
    /*
    QWidget *wdg = new QWidget;
    wdg->show();
    hide();//this will disappear main window


    ui->graphicsView->setParent(wdg);
   wdg->showFullScreen();
   */
    //  ui->stackedWidget_obrazovka->showFullScreen();
    vymazObrazovku();
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
    cell = new QTableWidgetItem(nazev);
    ui->tabulkaSubscriberu->setItem(row, 0, cell);

    cell = new QTableWidgetItem(verze);
    ui->tabulkaSubscriberu->setItem(row, 1, cell);
    ui->tabulkaSubscriberu->resizeColumnsToContents();

    cell = new QTableWidgetItem(ipadresa);
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

    //additional text message
    instanceXMLparser.nactiAdditionalTextMessage(instanceXMLparser.dokument, additionalTextMessage);

    //zmena tarifniho pasma

    zmenaPasma= instanceXMLparser.nactiFareZoneChange(instanceXMLparser.dokument,pasmaZ,pasmaDo);


    //instanceXMLparser.nactiXML(globalniSeznamZastavek, &indexZastavky, &pocetZastavek);
    //qInfo()<<globalniSeznamZastavek[4].StopName;
    qInfo()<<indexZastavky;
    qInfo()<<"CIl:"<<nazevCile;
    if( globalniSeznamZastavek.size()>0)
    {
        DoplneniPromennych();
        VykresleniPrijatychDat();
        FormatZobrazeni();
        this->aktualizujZobrazeniVirtualnichLedPanelu(globalniSeznamZastavek,stavSystemu);
        this->svgVykresleni();
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

    //ui->Lnacestna1->setStyleSheet("background-color :"+barvaPozadi+" ; color : "+barvaPisma+"; ");

    ui->frame_spodniRadek->setStyleSheet("background-color :"+barvaPozadi+" ; color : "+barvaPisma+"; ");


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

    this->svgVykresleni();
    /*
    ui->graphicsView->setScene(&novaScena);
    ui->graphicsView->update();
    ui->graphicsView->show();
    */

}


//zkpirovano z svgviewer demo

bool MainWindow::svgVykresleni()
{

    if (globalniSeznamZastavek.length()>0)
    {
        //svgVykreslovac.svgReplaceName("Verlauf2.svg","vystup.txt",globalniSeznamZastavek.last().StopName,globalniSeznamZastavek.at(stavSystemu.indexAktZastavky).StopName,globalniSeznamZastavek.at(stavSystemu.indexAktZastavky+1).StopName,globalniSeznamZastavek.at(stavSystemu.indexAktZastavky+2).StopName);
        svgVykreslovac.aktualizujVse(globalniSeznamZastavek,stavSystemu);
    }
    else
    {
        qDebug()<<"seznam zastavek je prazdny";
    }

    //int vysledek=svgOpenFile("./bubbles.svg");
    int vysledek=svgOpenFile("./vystup.svg");
    qDebug()<<"vysledek otevirani SVG je"<<QString::number(vysledek);

    return true;
}


bool MainWindow::svgOpenFile(const QString &fileName)
{
    qDebug()<<"MainWindow::openFile";
    QGraphicsScene *s = &scene;

    // const bool drawBackground = (m_backgroundItem ? m_backgroundItem->isVisible() : false);
    // const bool drawOutline = (m_outlineItem ? m_outlineItem->isVisible() : true);
    QFile soubor;

    QScopedPointer<QGraphicsSvgItem> svgItem(new QGraphicsSvgItem(fileName));
    svgItem->renderer()->setFramesPerSecond(20);
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

void MainWindow::on_tlacitkoLed_clicked()
{
    ui->prepinadloStran->setCurrentIndex(4);
    ui->labelFrontBottomRow->setText("");
}


void MainWindow::naplnLedObsah(QVector<QString> zobrazit)
{
    qDebug()<<"MainWindow::naplnLedObsah";
}


void MainWindow::naplnLedFront(QString linka,QString horniRadek,QString dolniRadek)
{
    qDebug()<<"MainWindow::naplnLedFront";

    if (dolniRadek!="")
    {
        ui->labelFrontSingle->setVisible(false);
        ui->labelFrontBottomRow->setVisible(true);
        ui->labelFrontTopRow->setVisible(true);
    }
    else
    {
        ui->labelFrontSingle->setVisible(true);
        ui->labelFrontBottomRow->setVisible(false);
        ui->labelFrontTopRow->setVisible(false);
    }

    ui->labelFrontLine->setText(linka);
    ui->labelFrontTopRow->setText(horniRadek);
    ui->labelFrontBottomRow->setText(dolniRadek);
    ui->labelFrontSingle->setText(horniRadek);

    if (linka.length()>3)
    {
        ui->labelFrontLine->setFont(font10);
    }
    else
    {
        ui->labelFrontLine->setFont(font8);
    }
}

void MainWindow::naplnLedSide(QString linka,QString horniRadek,QString dolniRadek)
{
    qDebug()<<"MainWindow::naplnLedSide";
    ui->labelSideLine->setText(linka);
    ui->labelSideTopRow->setText(horniRadek);
    ui->labelSideBottomRow->setText(dolniRadek);

    if (linka.length()>3)
    {

        ui->labelSideLine->setFont(font10);
    }
    else
    {
        ui->labelSideLine->setFont(font8);
    }
}

void MainWindow::naplnLedRear(QString linka)
{
    qDebug()<<"MainWindow::naplnLedRear";
    ui->labelRearLine->setText(linka);

    if (linka.length()>3)
    {

        ui->labelRearLine->setFont(font10);
    }
    else
    {
        ui->labelRearLine->setFont(font8);
    }

}

void MainWindow::naplnLedInner(QString linka,QString horniRadek,QString dolniRadek)
{
    qDebug()<<"MainWindow::naplnLedInner";
    ui->labelInnerLine->setText(linka);
    ui->labelInnerTopRow->setText(horniRadek);
    ui->labelInnerBottomRow->setText(dolniRadek);
}


void MainWindow::inicializujVirtualniLedPanely()
{

    qDebug()<<"MainWindow::inicializujVirtualniLedPanely";
    naplnLedFront("123","čelní horní","čelní dolní");
    naplnLedSide("456","Boční cíl","Boční nácestné");
    naplnLedRear("789");
    naplnLedInner("123","vnitřní cíl", "vnitřní nácesty");
}

void MainWindow::aktualizujZobrazeniVirtualnichLedPanelu(QVector<ZastavkaCil> zastavky, CestaUdaje stav )
{
    qDebug()<<"MainWindow::aktualizujZobrazeniVirtualnichLedPanelu";
    ZastavkaCil aktZast=zastavky.at(stav.indexAktZastavky);

    naplnLedFront(aktZast.linka.LineName,aktZast.cil.NameFront,aktZast.cil.NameFront2);
    naplnLedSide(aktZast.linka.LineName,aktZast.cil.NameSide,aktZast.zastavka.NameSide );
    naplnLedRear(aktZast.linka.LineName);
    naplnLedInner(aktZast.linka.LineName,aktZast.cil.NameInner, aktZast.zastavka.NameInner);

    textyBocniPanelkIteraci=naplnNacestyBocniPanel(aktZast);

}

QVector<QString> MainWindow::naplnNacestyBocniPanel(ZastavkaCil aktualniZastavka)
{
    qDebug()<<"MainWindow::naplnNacestyBocniPanel";
    Zastavka nacesta;
    QVector<QString> textyNaBocniPanel;
    textyNaBocniPanel.append("přes:");
    foreach (nacesta,aktualniZastavka.nacestneZastavky)
    {
        textyNaBocniPanel.append(nacesta.NameSide);
        qDebug()<<"pridavam nacestnou na bocni"<<nacesta.NameSide;
    }
    return textyNaBocniPanel;

}


void MainWindow::iterujVsechnyPanely()
{
    // qDebug()<<"MainWindow::iterujVsechnyPanely()";
    iterujBocniPanel(textyBocniPanelkIteraci,cyklovaniIndex);
}

void MainWindow::iterujBocniPanel(QVector<QString> texty, int &iteracniIndex)
{
    // qDebug()<<"MainWindow::iterujBocniPanel";

    if(iteracniIndex<texty.length())
    {
        ui->labelInnerBottomRow->setText(texty.at(iteracniIndex));

        ui->labelSideBottomRow->setText(texty.at(iteracniIndex));

        iteracniIndex++;

    }
    else
    {
        iteracniIndex=0;
    }
}


void MainWindow::naplnZmenaLabel(QString vstup)
{
    qDebug()<<"MainWindow::naplnZmenaLabel";
    ui->label_zmena->setText(vstup);
}

void MainWindow::naplnAnouncementLabel(QString vstup)
{
    qDebug()<<"MainWindow::naplnAnouncementLabel";
    ui->label_announcement->setText(vstup);
}

void MainWindow::zobrazZmenuPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma)
{
    qDebug()<<"MainWindow::zobrazZmenuPasma";
    ui->stackedWidget_obrazovka->setCurrentWidget(ui->page_hlavni);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_zmenaPasma);

    ui->label_pasmo1->setText(SvgVykreslovani::pasmaDoStringu(Pasmo::vratPidPasma(zPasem,"PID")));
    ui->label_pasmo2->setText(SvgVykreslovani::pasmaDoStringu(Pasmo::vratPidPasma(naPasma,"PID")));

    naplnZmenaLabel(vyrobTextZmenyPasma(zPasem,naPasma));
}


void MainWindow::zobrazAnnoucement(QString title,QString type,QString textCz, QString textEn)
{
    qDebug()<<"MainWindow::zobrazAnnoucement";
    naplnAnouncementLabel(textCz);
    ui->stackedWidget_obrazovka->setCurrentWidget(ui->page_hlavni);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_oznameni);

    ui->label_oznTitle->setText(title);
    ui->label_oznType->setText(type);
    ui->label_oznTextCs->setText(textCz);
    ui->label_oznTextEn->setText(textEn);


    //  ui->label_pasmo1->setText(SvgVykreslovani::pasmaDoStringu(zPasem));
    //  ui->label_pasmo2->setText(SvgVykreslovani::pasmaDoStringu(naPasma));

    // naplnZmenaLabel(vyrobTextZmenyPasma(zPasem,naPasma));


}


void MainWindow::skryjAnnouncement()
{
    qDebug()<<"MainWindow::skryjZmenuPasma";
    navratJizda();
}

void MainWindow::skryjZmenuPasma()
{
    qDebug()<<"MainWindow::skryjZmenuPasma";
    navratJizda();
}

void MainWindow::navratJizda()
{
    qDebug()<<"MainWindow::navratJizda";
    ui->stackedWidget_obrazovka->setCurrentWidget(ui->page_hlavni);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_hlavni_2);
    naplnZmenaLabel("");
}



QString MainWindow::vyrobTextZmenyPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma)
{
    qDebug()<<"MainWindow::vyrobTextZmenyPasma";
    QString vysledek="";
    vysledek+="prosím pozor! Změna tarifního pásma: "+SvgVykreslovani::pasmaDoStringu(zPasem)+"->"+SvgVykreslovani::pasmaDoStringu(naPasma);


    return vysledek;
}

void MainWindow::zobrazKonecnou()
{
    qDebug()<<"MainWindow::zobrazKonecnou()";
    ui->stackedWidget_obrazovka->setCurrentWidget(ui->page_hlavni);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_konecna);

}


int MainWindow::jeVozidloNaKonecne(CestaUdaje stav, QVector<ZastavkaCil> zastavky)
{
    qDebug()<<"MainWindow::jeVozidloNaKonecne";
    if((stav.indexAktZastavky==(zastavky.count()-1))&&(stav.locationState=="AtStop"))
    {
        return true;
    }
    return false;
}
