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
#include "QFile"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    CustomerInformationServiceSubscriber("CustomerInformationService","AllData","2.2CZ1.0","_ibisip_http._tcp",48479),//puvodni port 48479, novy 59631
    svgVykreslovani(QCoreApplication::applicationDirPath()),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    // fonty
    fdb.addApplicationFont(":/fonts/fonty/21-pid-1.ttf");
    fdb.addApplicationFont(":/fonts/fonty/21-pid-3.ttf");
    fdb.addApplicationFont(":/fonts/fonty/21-pid-5.ttf");
    fdb.addApplicationFont(":/fonts/fonty/21-pid-8.ttf");
    fdb.addApplicationFont(":/fonts/fonty/21-pid-10.ttf");

    fdb.addApplicationFont(":/fonts/fonty/Roboto-Regular.ttf");
    fdb.addApplicationFont(":/fonts/fonty/Roboto-Bold.ttf");
    fdb.addApplicationFont(":/fonts/fonty/Roboto-Black.ttf");
    fdb.addApplicationFont(":/fonts/fonty/Roboto-Light.ttf");

    font8.setFamily("21-PID 8");
    font8.setPointSize(65);

    font10.setFamily("21-PID 10");
    font10.setPointSize(65);

    //LCD fonty
    fontPasmoVelke.setPointSize(36);
    fontPasmoVelke.setBold(true);
    fontPasmoVelke.setFamily("Roboto");

    fontPasmoMale.setPointSize(20);
    fontPasmoMale.setBold(true);


    //klávesové zkratky menu
    keyCtrlF = new QShortcut(this); // Initialize the object Zdroj: https://evileg.com/en/post/75/
    keyCtrlF->setKey(Qt::CTRL + Qt::Key_F); // Set the key code

    keyF1 = new QShortcut(this);
    keyF1->setKey(Qt::Key_F1);

    keyF2 = new QShortcut(this);
    keyF2->setKey(Qt::Key_F2);

    keyF3 = new QShortcut(this);
    keyF3->setKey(Qt::Key_F3);

    keyF4 = new QShortcut(this);
    keyF4->setKey(Qt::Key_F4);

    keyF5 = new QShortcut(this);
    keyF5->setKey(Qt::Key_F5);

    keyF6 = new QShortcut(this);
    keyF6->setKey(Qt::Key_F6);

    keyF7 = new QShortcut(this);
    keyF7->setKey(Qt::Key_F7);

    keyF8 = new QShortcut(this);
    keyF8->setKey(Qt::Key_F8);

    vsechnyConnecty();


    hlavniNaplnPoleLabelu(); //naplni pointery na labely do pole, aby se nimi dalo iterovat
    naplnMapBarev();

    ui->prepinadloStran->setCurrentWidget(ui->page_hlavniObrazovka);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_hlavni_2);

    formatZobrazeni();
    //instanceXMLparser.Test();


    CustomerInformationServiceSubscriber.odebirano=false ;


    this->ledInicializujVirtualniPanely();

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
    //


    timer->start(1000); //refresh vterin
    timerBocniPanel->start(intervalBocniPanel);

    timerStridejStranky->setInterval(intervalStridaniStranek);
    timerOpozdenyStart->setInterval(intervalOpozdeniStartu);
    timerOpozdenyStart->setSingleShot(true);


    existujeKonfigurak();




    hlavniAutoformat();

    timerOpozdenyStart->start();

}

void MainWindow::slotOpozdenyStart()
{
    qDebug()<<"MainWindow::slotOpozdenyStart()";
    //  CustomerInformationServiceSubscriber.hledejSluzby("_ibisip_http._tcp.",0);
  //  CustomerInformationServiceSubscriber.hledejSluzby("_ibisip_http._tcp.",1);
    CustomerInformationServiceSubscriber.novePrihlaseniOdberu();
}

int MainWindow::existujeKonfigurak()
{
    qDebug()<<"MainWindow::existujeKonfigurak";
    QString cestaSouboru=QCoreApplication::applicationDirPath()+"/fullscreen.txt";
    QFile file(cestaSouboru);
    if (!file.open(QIODevice::ReadOnly))
    {

        qDebug()<<"fail1";
        return 0;
    }
    else
    {
        QString obsah= file.readAll();
        int obsahInt=obsah.toInt();

        switch(obsahInt)
        {
        case 0:
            return 0;
            break;

        case 1:
            on_tlacitkoHlavni_clicked();
            break;

        case 2:
            on_svgTlacitko_clicked();
            break;
        case 3:
            on_tlacitkoLed_clicked();

            break;
        case 4:
            on_tlacitkoSeznamSluzeb_clicked();
            break;



        }
        toggleFullscreen();


    }
    file.close();
    return 1;
}

void MainWindow::fullscreenPoZapnuti()
{


}

void MainWindow::vsechnyConnecty()
{
    qDebug()<<"MainWindow::vsechnyConnecty";
    connect(&CustomerInformationServiceSubscriber, &IbisIpSubscriber::dataNahrana  ,this, &MainWindow::xmlDoPromenne);
  //  connect(&CustomerInformationServiceSubscriber,&IbisIpSubscriber::nalezenaSluzba,this,&MainWindow::sluzbaDoTabulky);
    connect(&CustomerInformationServiceSubscriber,&IbisIpSubscriber::aktualizaceSeznamu,this,&MainWindow::slotAktualizaceTabulkySluzeb);



    connect(timer, &QTimer::timeout, this, &MainWindow::slotKazdouVterinu);

    connect(timerBocniPanel, &QTimer::timeout, this, &MainWindow::ledIiterujVsechnyPanely);
    connect(timerNacestneZastavky, &QTimer::timeout, this, &MainWindow::slotPosunNacestnych);
    connect(timerStridejStranky, &QTimer::timeout, this, &MainWindow::slotHlavniStridejStranky);
    connect(timerOpozdenyStart, &QTimer::timeout, this, &MainWindow::slotOpozdenyStart);


    connect(CustomerInformationServiceSubscriber.timer,&QTimer::timeout ,this,&MainWindow::vyprselCasovacSluzby);
    connect(&CustomerInformationServiceSubscriber,&IbisIpSubscriber::signalZtrataOdberu ,this,&MainWindow::slotZtrataOdberu);

    //klávesové zkratky
    // connect(keyCtrlF, SIGNAL(activated()), this, SLOT(toggleFullscreen()));
    connect(keyCtrlF, &QShortcut::activated, this, &MainWindow::toggleFullscreen);
    connect(keyF1, &QShortcut::activated, this,&MainWindow::on_tlacitkoHlavni_clicked );
    connect(keyF2, &QShortcut::activated, this,&MainWindow::on_svgTlacitko_clicked );
    connect(keyF3, &QShortcut::activated, this, &MainWindow::on_tlacitkoLed_clicked );
    connect(keyF4, &QShortcut::activated, this, &MainWindow::on_tlacitkoSeznamSluzeb_clicked);
    connect(keyF5, &QShortcut::activated, this, &MainWindow::on_tlacitkoCasovac_clicked );
    connect(keyF6, &QShortcut::activated, this, &MainWindow::toggleFullscreen);
    connect(keyF7, &QShortcut::activated, this, &MainWindow::on_refreshTlac_clicked);
    connect(keyF8, &QShortcut::activated, this, &MainWindow::on_quitTlacitko_clicked);
}

int MainWindow::slotKazdouVterinu()
{
    ui->labelZbyvajiciVteriny->setText(QString::number(CustomerInformationServiceSubscriber.timer->remainingTime()/1000) );
    ui->label_hodiny->setText(QTime::currentTime().toString("hh:mm") );
    return 1;
}

void MainWindow::slotZtrataOdberu()
{
    vymazObrazovku();
    qDebug()<<"MainWindow::slotZtrataOdberu";

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
        labelVykreslovani.vykresliNacestneForce(globalniSeznamZastavek,stavSystemu,ui->label_nacestne);
    }

    else

    {
        ui->scrollAreaWidgetContents->scroll(-krok,0);
    }

}

void MainWindow::slotAktualizaceTabulkySluzeb()
{
    qDebug()<<"MainWindow::slotAktualizaceTabulkySluzeb";
    vykresliSluzbyDoTabulky(CustomerInformationServiceSubscriber.seznamSluzeb);
}

void MainWindow::vyprselCasovacSluzby()
{
    qDebug()<<"MainWindow::vyprselCasovacSluzby()";

}



void MainWindow::hlavniNaplnPoleLabelu()
{
    qDebug()<<"MainWindow::hlavniNaplnPoleLabelu()";
    seznamLabelNazevZastavky.push_back(ui->Lnacestna1);
    seznamLabelNazevZastavky.push_back(ui->Lnacestna2);
    seznamLabelNazevZastavky.push_back(ui->Lnacestna3);
    seznamLabelNazevZastavky.push_back(ui->Lnacestna4);
    seznamLabelNazevZastavky.push_back(ui->Lnacestna5);

    seznamLabelPasmoDolni.push_back(ui->label_pasmo1_1);
    seznamLabelPasmoDolni.push_back(ui->label_pasmo2_1);
    seznamLabelPasmoDolni.push_back(ui->label_pasmo3_1);
    seznamLabelPasmoDolni.push_back(ui->label_pasmo4_1);
    seznamLabelPasmoDolni.push_back(ui->label_pasmo5_1);

    seznamLabelPasmoHorni.push_back(ui->label_pasmo1_2);
    seznamLabelPasmoHorni.push_back(ui->label_pasmo2_2);
    seznamLabelPasmoHorni.push_back(ui->label_pasmo3_2);
    seznamLabelPasmoHorni.push_back(ui->label_pasmo4_2);
    seznamLabelPasmoHorni.push_back(ui->label_pasmo5_2);


    seznamLabelPrestupCil .push_back(ui->label_prestup0_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup1_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup2_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup3_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup4_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup5_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup6_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup7_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup8_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup9_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup10_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup11_cil);

    seznamLabelPrestupLinka.push_back(ui->label_prestup0_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup1_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup2_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup3_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup4_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup5_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup6_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup7_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup8_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup9_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup10_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup11_linka);

    seznamLabelPrestupOdjezd.push_back(ui->label_prestup0_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup1_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup2_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup3_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup4_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup5_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup6_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup7_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup8_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup9_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup10_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup11_odjezd);

    seznamLabelPrestupNastupiste.push_back(ui->label_prestup0_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup1_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup2_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup3_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup4_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup5_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup6_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup7_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup8_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup9_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup10_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup11_nastupiste);

    /*
    seznamFramePrestup.push_back(ui->frame_odjezd0);
    seznamFramePrestup.push_back(ui->frame_odjezd1);
    seznamFramePrestup.push_back(ui->frame_odjezd2);
    seznamFramePrestup.push_back(ui->frame_odjezd3);
    seznamFramePrestup.push_back(ui->frame_odjezd4);
    seznamFramePrestup.push_back(ui->frame_odjezd5);
    seznamFramePrestup.push_back(ui->frame_odjezd6);
    seznamFramePrestup.push_back(ui->frame_odjezd7);
    seznamFramePrestup.push_back(ui->frame_odjezd8);
    seznamFramePrestup.push_back(ui->frame_odjezd9);
    seznamFramePrestup.push_back(ui->frame_odjezd10);
    seznamFramePrestup.push_back(ui->frame_odjezd11);
    */
}

void MainWindow::naplnMapBarev()
{
    qDebug()<<"MainWindow::naplnMapBarev";
    //dd1 Metro, nahrazuje se piktogramem
    barvaTextu["metro"]=barva_cerna_0_0_0;
    barvaPozadi["metro"]=barva_bila_255_255_255;

    //dd2 Denní tramvaj
    barvaTextu["localTram"]=barva_Tramvaj_120_2_0;
    barvaPozadi["localTram"]=barva_bila_255_255_255;

    barvaTextu["localTramDiversion"]=barva_Tramvaj_120_2_0;
    barvaPozadi["localTramDiversion"]=barva_Vyluky_255_170_30;

    //dd3 Denní městská autobusová linka
    barvaTextu["localBus"]=barva_Autobus_0_120_160;
    barvaPozadi["localBus"]=barva_bila_255_255_255;

    barvaTextu["localBusDiversion"]=barva_Autobus_0_120_160;
    barvaPozadi["localBusDiversion"]=barva_Vyluky_255_170_30;


    //dd4 Denní příměstská nebo regionální linka
    barvaTextu["regionalBus"]=barva_cerna_0_0_0;
    barvaPozadi["regionalBus"]=barva_bila_255_255_255;


    barvaTextu["regionalBusDiversion"]=barva_cerna_0_0_0;
    barvaPozadi["regionalBusDiversion"]=barva_Vyluky_255_170_30;

    //dd5 Noční městská autobusová linka
    barvaTextu["localBusNight"]=barva_bila_255_255_255;
    barvaPozadi["localBusNight"]=barva_Autobus_0_120_160;


    barvaTextu["localBusNightDiversion"]=barva_Vyluky_255_170_30;
    barvaPozadi["localBusNightDiversion"]=barva_Autobus_0_120_160;

    //dd6 Noční tramvaj

    barvaTextu["localTramNight"]=barva_bila_255_255_255;
    barvaPozadi["localTramNight"]=barva_Tramvaj_120_2_0;

    barvaTextu["localTramNightDiversion"]=barva_Vyluky_255_170_30;
    barvaPozadi["localTramNightDiversion"]=barva_Tramvaj_120_2_0;

    //dd7 Linka náhradní dopravy, městský autobus
    barvaTextu["localBusReplacement"]=barva_Vyluky_255_170_30;
    barvaPozadi["localBusReplacement"]=barva_bila_255_255_255;

    //dd8 Lanovka
    barvaTextu["funicular"]=barva_Lanovka_201_208_34;
    barvaPozadi["funicular"]=barva_bila_255_255_255;
    //dd9 Školní linka
    barvaTextu["schoolBus"]=barva_Autobus_0_120_160;
    barvaPozadi["schoolBus"]=barva_bila_255_255_255;
    //dd10 Invalidní
    barvaTextu["specialNeedsBus"]=barva_Specialni_143_188_25;
    barvaPozadi["specialNeedsBus"]=barva_bila_255_255_255;
    //dd11 Smluvni
    barvaTextu["localBusSpecial"]=barva_Specialni_143_188_25;
    barvaPozadi["localBusSpecial"]=barva_bila_255_255_255;
    //dd12 Přívoz
    barvaTextu["localPassengerFerry"]=barva_Privoz_0_164_167;
    barvaPozadi["localPassengerFerry"]=barva_bila_255_255_255;
    //dd13 Vlaky PID – linky S nebo R
    barvaTextu["regionalRail"]=barva_bila_255_255_255;
    barvaPozadi["regionalRail"]=barva_Vlak_15_30_65;
    //dd14 Linka náhradní dopravy, NAD za vlak
    barvaTextu["railReplacementBus"]=barva_Vyluky_255_170_30;
    barvaPozadi["railReplacementBus"]=barva_bila_255_255_255;

    barvaTextu["railReplacementBusReplacement"]=barva_Vyluky_255_170_30;
    barvaPozadi["railReplacementBusReplacement"]=barva_bila_255_255_255;



    //dd15 Linka náhradní dopravy, Tram
    barvaTextu["localTramReplacement"]=barva_Vyluky_255_170_30;
    barvaPozadi["localTramReplacement"]=barva_bila_255_255_255;
    //dd16 Noční příměstská nebo regionální linka
    barvaTextu["regionalBusNight"]=barva_bila_255_255_255;
    barvaPozadi["regionalBusNight"]=barva_Nocni_9_0_62;

    barvaTextu["regionalBusNightDiversion"]=barva_Vyluky_255_170_30;
    barvaPozadi["regionalBusNightDiversion"]=barva_Nocni_9_0_62;

    //dd17 Linka mimo systém PID (3 znaky)
    //  barvaTextu[""]=barva_PozadiD_150_150_150;
    //  barvaPozadi[""]=barva_bila_255_255_255;
    barvaTextu["unknown"]=barva_PozadiD_150_150_150;
    barvaPozadi["unknown"]=barva_bila_255_255_255;
    barvaTextu["undefined"]=barva_PozadiD_150_150_150;
    barvaPozadi["undefined"]=barva_bila_255_255_255;
    //dd18 Denní trolejbusová linka
    barvaTextu["localTrolleybus"]=barva_Trolejbus_128_22_111;
    barvaPozadi["localTrolleybus"]=barva_bila_255_255_255;


    /*
    barvaTextu[""]=barva;
    barvaPozadi[""]=barva;

    barvaTextu[""]=barva;
    barvaPozadi[""]=barva;

*/

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
    hlavniVymazObrazovku();
    svgVykreslovani.vymazObrazovku();
    ledVymazPanely();


}


void MainWindow::hlavniVymazObrazovku()
{
    qDebug()<<"MainWindow::hlavniVymazObrazovku";
    ui->Lcil->setText("");
    ui->Llinka->setText("");
    ui->label_nacestne->setText("");

    ui->frame_navaznySpoj->hide();

    vymazPoleLabelu(seznamLabelNazevZastavky);
    vymazPoleLabelu(seznamLabelPasmoDolni);
    vymazPoleLabelu(seznamLabelPasmoHorni);
    //obrazovka prestupu
    vymazPoleLabelu(seznamLabelPrestupCil);
    vymazPoleLabelu(seznamLabelPrestupLinka);
    vymazPoleLabelu(seznamLabelPrestupNastupiste);
    vymazPoleLabelu(seznamLabelPrestupOdjezd);

    timerStridejStranky->stop();
    strankyKeStridani.clear();
    strankyKeStridani.push_back(ui->page_hlavni_2);
}


int MainWindow::vykresleniPrijatychDat()
{
    qDebug()<<"MainWindow::VykresleniPrijatychDat";

    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_hlavni_2);

    hlavniVymazObrazovku();
    ui->label_locationState->setText(stavSystemu.locationState);
    ui->label_currentStopIndex->setText(QString::number(stavSystemu.indexAktZastavky+1));

    hlavniVykresliNazevCile(nazevCile);
    hlavniVykresliCisloLinky(globalniSeznamZastavek.at(stavSystemu.indexAktZastavky),stavSystemu.vehicleSubMode);
    hlavniVykreslZastavkyiPasma(globalniSeznamZastavek,globalniSeznamZastavekNavaznehoSpoje);
    hlavniVykresliNacestne();

    strankyKeStridani.clear();





    //strankyKeStridani.push_back(ui->page_hlavni_2);



    if(!instanceXMLparser.existujeNavaznySpoj(globalniSeznamZastavekNavaznehoSpoje))
    {
        qDebug()<<"navazny spoj neni";
        ui->frame_navaznySpoj->hide();
        // ui->horizontalLayout_navaznySpoj;

    }
    else
    {
        QString navaznyCil="";
        QString navaznaLinka="";
        if(instanceXMLparser.udajeNavaznehoSpoje(globalniSeznamZastavekNavaznehoSpoje,navaznaLinka,navaznyCil))
        {
            ui->label_navaznaLinka->setText(navaznaLinka);
            ui->label_navaznyCil->setText(navaznyCil);
            ui->frame_navaznySpoj->show();
        }
    }

    //additional text message

    if(additionalTextMessageText!="")
    {
        zobrazAnnoucement(additionalTextMessageHeadline,additionalTextMessageType,additionalTextMessageText,"");
        strankyKeStridani.push_back(ui->page_oznameni);
    }
    else
    {
        labelVykreslovani.naplnAnouncementLabel("",ui->label_announcement);
    }

    //konecna

    if(jeVozidloNaKonecne(stavSystemu,globalniSeznamZastavek)&&(!instanceXMLparser.existujeNavaznySpoj(globalniSeznamZastavekNavaznehoSpoje)))
    {
        strankyKeStridani.push_front(ui->page_konecna);
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
           if(instanceXMLparser.zmenaDat==true)
           {
            navratJizda();
           }
            strankyKeStridani.push_front(ui->page_hlavni_2);
            // skryjZmenuPasma();
        }

    }


    if(!globalniSeznamZastavek.at(stavSystemu.indexAktZastavky).zastavka.seznamPrestupu.isEmpty())
    {
        strankyKeStridani.push_back(ui->page_prestupy);
        hlavniVykresliPrestupy(globalniSeznamZastavek.at(stavSystemu.indexAktZastavky).zastavka.seznamPrestupu);


    }


    //   hlavniVykresliNasledne();

    formatZobrazeni();
    indexAktualniStridaneStranky=0;
    timerStridejStranky->start();

    return 1;
}





void MainWindow::hlavniVykresliCisloLinky(ZastavkaCil aktZastavka,QString subMode)
{
    //  labelVykreslovani.naplnCisloLinkyLabel(alias,ui->Llinka);
    qDebug()<<"vypis linky:"<<aktZastavka.cil.NameLcd<<" "<<aktZastavka.linka.LineName<<" vylukova:"<<aktZastavka.linka.isDiversion ;

    naplnPoleLinky(subMode,aktZastavka.linka,ui->Llinka, qFloor(pomerPixelBod*200),false);
    //  labelVykreslovani.zmensiCisloLinkyLabel(ui->Llinka);

}

void MainWindow::hlavniVykresliNazevCile(QString nazev)
{
    labelVykreslovani.naplnNazevCileLabel(nazev,ui->Lcil);
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


void MainWindow::hlavniVykreslZastavkyiPasma(QVector<ZastavkaCil>aktZastavky, QVector<ZastavkaCil>navazZastavky )
{
    qDebug()<<"MainWindow::hlavniVykreslZastavkyiPasma";
    int offset=0;
    offset=hlavniVykresliSkupinuZastavek(0,pocetVykreslovanychZastavek,aktZastavky,false);
    hlavniVykresliSkupinuZastavek(offset,pocetVykreslovanychZastavek,navazZastavky,true);
}

int MainWindow::hlavniVykresliSkupinuZastavek(int offset, int pocetPoli, QVector<ZastavkaCil> zastavky, bool navazny)
{
    qDebug()<<"MainWindow::hlavniVykresliSkupinuZastavek";
    if(zastavky.isEmpty())
    {
        return 0;
    }


    int vysledek=0;

    int posunIndexuZastavky=0;
    if(!navazny)
    {
        posunIndexuZastavky=stavSystemu.indexAktZastavky;
    }
    int konec=labelVykreslovani.minimum(zastavky.length()-posunIndexuZastavky,pocetPoli);



    int counterNavazny=0;
    for(int i=offset;i<konec ; i++)
    {


        int pomocnyIndex=0;

        qDebug()<<"zpracovavam label i="<<i<<" pomocnyIndex="<<pomocnyIndex<<" offset="<<offset<<" pocetZastavek="<<zastavky.count()<<" "<<navazny;


        Zastavka aktualniZastavka;

        if(navazny==false)
        {
            pomocnyIndex=indexZastavky+i;
            aktualniZastavka=zastavky.at(pomocnyIndex).zastavka;
        }
        else
        {
            aktualniZastavka=zastavky.at(counterNavazny).zastavka;
            pomocnyIndex=i;
        }



        PasmoveDvojiceLcd pasmoveDvojiceLcd;
        pasmoveDvojiceLcd.roztridPasma(aktualniZastavka.seznamPasem);


        seznamLabelNazevZastavky.at(i)->setText(labelVykreslovani.zabalHtmlDoZnacek(labelVykreslovani.doplnPiktogramyBezZacatkuKonce(aktualniZastavka.NameLcd,aktualniZastavka.seznamPiktogramu,seznamLabelNazevZastavky.at(i)->font().pixelSize() )));


        //if(navazny==true)
        if(stavSystemu.locationState=="AtStop")
        {
            //    seznamLabelNazevZastavky.at(i)->setStyleSheet("color:"+barva_PozadiC_100_100_100+";");
            // seznamPasem1.at(i)->setStyleSheet("color:"+barva_PozadiC_100_100_100);
            // seznamPasem2.at(i)->setStyleSheet("color:"+barva_PozadiC_100_100_100);
        }
        else
        {
            //    seznamLabelNazevZastavky.at(i)->setStyleSheet("color:"+barva_bila_255_255_255+";");
            //   seznamPasem1.at(i)->setStyleSheet("color:"+barva_bila_255_255_255);
            // seznamPasem2.at(i)->setStyleSheet("color:"+barva_bila_255_255_255);
        }


        // ui->Lnacestna5->setText(globalniSeznamZastavek[indexZastavky+4].zastavka.NameLcd);

        if(pasmoveDvojiceLcd.pasmaSystemu1.isEmpty())
        {
            seznamLabelPasmoDolni.at(i)->setText("");

        }
        else
        {
            QString pasmaString1=svgVykreslovani.pasmaDoStringu( pasmoveDvojiceLcd.pasmaSystemu1);
            QString zkratkaSystemuDvojtecka="";
            if (!pasmoveDvojiceLcd.pasmaSystemu2.isEmpty())
            {

                zkratkaSystemuDvojtecka=pasmoveDvojiceLcd.pasmaSystemu1.first().system+":";
            }
            seznamLabelPasmoDolni.at(i)->setText(zkratkaSystemuDvojtecka+pasmaString1);
            seznamLabelPasmoDolni.at(i)->setFont(fontPasmoVelke);
        }

        if(pasmoveDvojiceLcd.pasmaSystemu2.isEmpty())
        {
            seznamLabelPasmoHorni.at(i)->hide();
            seznamLabelPasmoHorni.at(i)->setFont(fontPasmoVelke);
        }
        else
        {
            QString pasmaString2=svgVykreslovani.pasmaDoStringu( pasmoveDvojiceLcd.pasmaSystemu2);
            seznamLabelPasmoHorni.at(i)->show();

            seznamLabelPasmoHorni.at(i)->setFont(fontPasmoMale );
            seznamLabelPasmoDolni.at(i)->setFont(fontPasmoMale );

            seznamLabelPasmoHorni.at(i)->setText(pasmoveDvojiceLcd.pasmaSystemu2.first().system+":"+pasmaString2);
        }

        if(navazny==false)
        {
            seznamLabelNazevZastavky.at(i)->setStyleSheet("color:"+barva_bila_255_255_255+";");
            seznamLabelPasmoHorni.at(i)->setStyleSheet("color:"+barva_bila_255_255_255+";");
            seznamLabelPasmoDolni.at(i)->setStyleSheet("color:"+barva_bila_255_255_255+";");
        }
        else
        {
            seznamLabelNazevZastavky.at(i)->setStyleSheet("color:"+barva_PozadiC_100_100_100+";");
            seznamLabelPasmoHorni.at(i)->setStyleSheet("color:"+barva_PozadiC_100_100_100+";");
            seznamLabelPasmoDolni.at(i)->setStyleSheet("color:"+barva_PozadiC_100_100_100+";");
        }



        //  qDebug()<<"label pasma "<<i<<" "<<stavSystemu.indexAktZastavky<<" p1:"<<pasmaString1<<" p2:"<<pasmaString2<<" "<<"pomocnyIndex";

        counterNavazny++;
        vysledek=i;
    }

    return (vysledek+1);
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

    QString novyVstup=labelVykreslovani.vykresliNacestneZastavkyText(globalniSeznamZastavek.at(stavSystemu.indexAktZastavky).nacestneZastavky, ui->label_nacestne->font().pixelSize());
    if(ui->label_nacestne->text()!=novyVstup)
    {
        timerNacestneZastavky->start(intervalPosunuNacest);
        ui->label_nacestne->setText( novyVstup);
    }


}



int MainWindow::doplneniPromennych()
{
    qDebug()<<"MainWindow::DoplneniPromennych";
    // qInfo()<<"\n DoplneniPromennych";

    if (globalniSeznamZastavek.size()>indexZastavky)
    {
        ZastavkaCil aktualniZastavka=globalniSeznamZastavek.at(indexZastavky);
        nazevCile=labelVykreslovani.zabalHtmlDoZnacek(labelVykreslovani.doplnPiktogramyBezZacatkuKonce(aktualniZastavka.cil.NameLcd,aktualniZastavka.cil.seznamPiktogramu,ui->Lcil->font().pixelSize()));
        nazevLinky=aktualniZastavka.linka.LineName;
    }
    else
    {
        qDebug()<<"indexZastavky je"<<QString::number(indexZastavky)<<" velikost globSezZast="<<QString::number(globalniSeznamZastavek.size());
    }
    qInfo()<<"nazevCile "<<nazevCile;
    return 1;
}

int MainWindow::formatZobrazeni()
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

    // hlavniAutoformat();
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
    /*
    instanceXMLparser.VytvorSeznamZastavek(globalniSeznamZastavek,globalniSeznamZastavekNavaznehoSpoje, stavSystemu.indexAktZastavky, pocetZastavek);
    instanceXMLparser.nactiVehicleGroup(stavSystemu,instanceXMLparser.dokument);
    qInfo()<<indexZastavky;
    qInfo()<<"CIl:"<<nazevCile;
    DoplneniPromennych();
    VykresleniPrijatychDat();
    FormatZobrazeni();
    qInfo()<<"CIl:"<<nazevCile;
    */
    toggleFullscreen();
}


/*


SITOVA CAST, ODPOVIDAC
nejsem autorem




*/







void MainWindow::on_refreshTlac_clicked()
{
    qDebug()<<"MainWindow::on_refreshTlac_clicked";
    qInfo()<<"\n on_refreshTlac_clicked";

  //  CustomerInformationServiceSubscriber.odebirano=false ;
  //  CustomerInformationServiceSubscriber.hledejSluzby("_ibisip_http._tcp.",1);
    this->vymazObrazovku();
    slotAktualizaceTabulkySluzeb();
    //xmlDoPromenne(1);


    vymazObrazovku();
    CustomerInformationServiceSubscriber.novePrihlaseniOdberu();
}


void MainWindow::vymazTabulkuSubscriberu(QTableWidget *tableWidget)
{
    qDebug()<<"MainWindow::vymazTabulkuSubscriberu";
    //  https://stackoverflow.com/a/31564541
    tableWidget->clearSelection();

    // Disconnect all signals from table widget ! important !
    tableWidget->disconnect();

    // Remove all items
    tableWidget->clearContents();

    // Set row count to 0 (remove rows)
    tableWidget->setRowCount(0);

}

void MainWindow::vykresliSluzbyDoTabulky(QVector<QZeroConfService> seznamSluzeb)
{
    qDebug()<<"MainWindow::vykresliSluzbyDoTabulky";
  // ui->tabulkaSubscriberu->setRowCount(0);
    vymazTabulkuSubscriberu(ui->tabulkaSubscriberu);


    foreach(QZeroConfService sluzba, seznamSluzeb)
    {
        sluzbaDoTabulky(sluzba);
    }
}


void MainWindow::sluzbaDoTabulky(QZeroConfService zcs)
{
    qDebug()<<"MainWindow::sluzbaDoTabulky";
    qint32 row;
    QTableWidgetItem *cell;

    QString nazev=zcs->name();
    QString ipadresa=zcs->ip().toString();
    QString host=zcs->host();
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

    cell = new QTableWidgetItem(ipadresa);
    ui->tabulkaSubscriberu->setItem(row, 2, cell);

    cell = new QTableWidgetItem(QString::number(port));
    ui->tabulkaSubscriberu->setItem(row, 3, cell);

    cell = new QTableWidgetItem(host);
    ui->tabulkaSubscriberu->setItem(row, 4, cell);


    ui->tabulkaSubscriberu->resizeColumnsToContents();


    qDebug()<<"sluzbaDoTabulky_konec";

}

void MainWindow::xmlDoPromenne(QString vstupniXml)
{
    qDebug()<<"MainWindow::xmlDoPromenne";

    instanceXMLparser.nactiXML(vstupniXml);

    globalniSeznamZastavek.clear();
    globalniSeznamZastavekNavaznehoSpoje.clear();

    qDebug()<<"timestamp:"<<instanceXMLparser.vyparsujTimestamp(instanceXMLparser.dokument).toString(Qt::ISODate);

    if(!instanceXMLparser.VytvorSeznamZastavek(globalniSeznamZastavek,globalniSeznamZastavekNavaznehoSpoje, indexZastavky, pocetZastavek))
    {
        vymazObrazovku();
    }
    instanceXMLparser.nactiVehicleGroup(stavSystemu,instanceXMLparser.dokument);

    //additional text message
    instanceXMLparser.nactiAdditionalTextMessage(instanceXMLparser.dokument,additionalTextMessageType,additionalTextMessageHeadline, additionalTextMessageText);

    //zmena tarifniho pasma

    zmenaPasma= instanceXMLparser.nactiFareZoneChange(instanceXMLparser.dokument,pasmaZ,pasmaDo);


    //instanceXMLparser.nactiXML(globalniSeznamZastavek, &indexZastavky, &pocetZastavek);
    //qInfo()<<globalniSeznamZastavek[4].StopName;
    qInfo()<<indexZastavky;
    qInfo()<<"CIl:"<<nazevCile;
    if( globalniSeznamZastavek.size()>0)
    {
        doplneniPromennych();
        vykresleniPrijatychDat();
        formatZobrazeni();
        this->ledAktualizujZobrazeniVirtualnichPanelu(globalniSeznamZastavek,stavSystemu);
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
    ui->prepinadloStran->setCurrentWidget(ui->page_seznamSluzeb);
}

void MainWindow::on_tlacitkoHlavni_clicked()
{
    ui->prepinadloStran->setCurrentWidget(ui->page_hlavniObrazovka);
}

void MainWindow::on_tlacitkoCasovac_clicked()
{
    ui->prepinadloStran->setCurrentWidget(ui->page_casovac);
}

void MainWindow::obarviPozadiPristi(QString barvaPisma,QString barvaPozadi)
{
    qDebug()<<"MainWindow::obarviPozadiPristi";
    //
    labelVykreslovani.obarviPozadiPristi(barvaPisma,barvaPozadi,ui->frame_spodniRadek);
    svgVykreslovani.obarviPozadiPristi(barvaPisma,barvaPozadi);


    QString stylTextu="color:"+barvaPisma;
    ui->Lnacestna1->setStyleSheet(stylTextu);
    ui->label_pasmo1_1->setStyleSheet(stylTextu);
    ui->label_pasmo1_2->setStyleSheet(stylTextu);


}


void MainWindow::on_quitTlacitko_clicked()
{
    qDebug()<<"\n on_quitTlacitko_clicked \n";
    MainWindow::close();
}



void MainWindow::on_svgTlacitko_clicked()
{

    ui->prepinadloStran->setCurrentWidget(ui->page_svg);


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
        svgVykreslovani.aktualizujVse(globalniSeznamZastavek,stavSystemu);
    }
    else
    {
        qDebug()<<"seznam zastavek je prazdny";
    }

    //int vysledek=svgOpenFile("./bubbles.svg");
    int vysledek=svgOpenFile(QCoreApplication::applicationDirPath()+"/vystup.svg");
    qDebug()<<"vysledek otevirani SVG je"<<QString::number(vysledek);

    return true;
}


bool MainWindow::svgOpenFile(const QString &fileName)
{
    qDebug()<<"MainWindow::openFile";
    QGraphicsScene *s = &scene;

    QFile soubor;

    QScopedPointer<QGraphicsSvgItem> svgItem(new QGraphicsSvgItem(fileName));
    svgItem->renderer()->setFramesPerSecond(20);
    if (!svgItem->renderer()->isValid())
        return false;

    s->clear();
    // resetTransform();

    m_svgItem = svgItem.take();
    m_svgItem->setFlags(QGraphicsItem::ItemClipsToShape);
    m_svgItem->setCacheMode(QGraphicsItem::NoCache);
    m_svgItem->setZValue(0);




    m_outlineItem = new QGraphicsRectItem(m_svgItem->boundingRect());
    QPen outline(Qt::black, 2, Qt::DashLine);
    outline.setCosmetic(true);
    m_outlineItem->setPen(outline);
    m_outlineItem->setBrush(Qt::NoBrush);
    m_outlineItem->setZValue(1);

    s->addItem(m_svgItem);
    s->setSceneRect(m_outlineItem->boundingRect().adjusted(-10, -10, 10, 10));
    ui->graphicsView->setScene(s);

    return true;
}

void MainWindow::on_tlacitkoLed_clicked()
{
    ui->prepinadloStran->setCurrentWidget(ui->page_led);
    ui->labelFrontBottomRow->setText("");
}


void MainWindow::ledNaplnFront(QString linka,QString horniRadek,QString dolniRadek)
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

void MainWindow::ledNaplnSide(QString linka,QString horniRadek,QString dolniRadek)
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

void MainWindow::ledNaplnRear(QString linka)
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

void MainWindow::ledNaplnInner(QString linka,QString horniRadek,QString dolniRadek)
{
    qDebug()<<"MainWindow::naplnLedInner";
    ui->labelInnerLine->setText(linka);
    ui->labelInnerTopRow->setText(horniRadek);
    ui->labelInnerBottomRow->setText(dolniRadek);
}


void MainWindow::ledInicializujVirtualniPanely()
{
    qDebug()<<"MainWindow::inicializujVirtualniLedPanely";
    ledNaplnFront("123","čelní horní","čelní dolní");
    ledNaplnSide("456","Boční cíl","Boční nácestné");
    ledNaplnRear("789");
    ledNaplnInner("123","vnitřní cíl", "vnitřní nácesty");
}

void MainWindow::ledVymazPanely()
{
    qDebug()<<"MainWindow::ledVymazPanelyy";
    ledNaplnFront("","","");
    ledNaplnSide("","","");
    ledNaplnRear("");
    ledNaplnInner("","", "");
    textyBocniPanelkIteraci.clear();
    textyVnitrniPanelkIteraci.clear();
}

void MainWindow::ledAktualizujZobrazeniVirtualnichPanelu(QVector<ZastavkaCil> zastavky, CestaUdaje stav )
{
    qDebug()<<"MainWindow::aktualizujZobrazeniVirtualnichLedPanelu";
    ZastavkaCil aktZast=zastavky.at(stav.indexAktZastavky);

    ledNaplnFront(aktZast.linka.LineName,aktZast.cil.NameFront,aktZast.cil.NameFront2);
    ledNaplnSide(aktZast.linka.LineName,aktZast.cil.NameSide,aktZast.zastavka.NameSide );
    ledNaplnRear(aktZast.linka.LineName);
    ledNaplnInner(aktZast.linka.LineName,aktZast.cil.NameInner, aktZast.zastavka.NameInner);

    textyBocniPanelkIteraci=ledNaplnNacestyBocniPanel(aktZast);
    textyVnitrniPanelkIteraci=ledNaplnNacestyVnitrniPanel(aktZast);

}

QVector<QString> MainWindow::ledNaplnNacestyBocniPanel(ZastavkaCil aktualniZastavka)
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

QVector<QString> MainWindow::ledNaplnNacestyVnitrniPanel(ZastavkaCil aktualniZastavka)
{
    qDebug()<<"MainWindow::naplnNacestyVnitrniPanel";
    Zastavka nacesta;
    QVector<QString> textyNaVnitrniPanel;
    textyNaVnitrniPanel.append("přes:");
    foreach (nacesta,aktualniZastavka.nacestneZastavky)
    {
        textyNaVnitrniPanel.append(nacesta.NameInner);
        qDebug()<<"pridavam nacestnou na bocni"<<nacesta.NameSide;
    }
    return textyNaVnitrniPanel;

}


void MainWindow::ledIiterujVsechnyPanely()
{
    // qDebug()<<"MainWindow::iterujVsechnyPanely()";
    ledIterujBocniPanel(textyBocniPanelkIteraci,cyklovaniIndex);
    ledIterujVnitrniPanel(textyVnitrniPanelkIteraci,cyklovaniIndex);




}

void MainWindow::ledIterujBocniPanel(QVector<QString> texty, int &iteracniIndex)
{
    // qDebug()<<"MainWindow::iterujBocniPanel";

    if(iteracniIndex<texty.length())
    {
        ui->labelSideBottomRow->setText(texty.at(iteracniIndex));

        //  iteracniIndex++;

    }
    else
    {
        //   iteracniIndex=0;
    }
}

void MainWindow::ledIterujVnitrniPanel(QVector<QString> texty, int &iteracniIndex)
{
    // qDebug()<<"MainWindow::iterujBocniPanel";

    if(iteracniIndex<texty.length())
    {
        ui->labelInnerBottomRow->setText(texty.at(iteracniIndex));

        iteracniIndex++;

    }
    else
    {
        iteracniIndex=0;
    }
}





/*
void MainWindow::naplnZmenaLabel(QString vstup)
{
    qDebug()<<"MainWindow::naplnZmenaLabel";
    ui->label_zmena->setText(vstup);
}
*/



void MainWindow::zobrazZmenuPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma)
{
    qDebug()<<"MainWindow::zobrazZmenuPasma";
    hlavniZobrazZmenuPasma(zPasem,naPasma);
    svgVykreslovani.zobrazZmenuPasma(zPasem,naPasma);
}

void MainWindow::hlavniZobrazZmenuPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma)
{
    qDebug()<<"MainWindow::zobrazZmenuPasma";

    ui->stackedWidget_obrazovka->setCurrentWidget(ui->page_hlavni);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_zmenaPasma);

    ui->label_pasmo1->setText(SvgVykreslovani::pasmaDoStringu(Pasmo::vratPidPasma(zPasem,"PID")));
    ui->label_pasmo2->setText(SvgVykreslovani::pasmaDoStringu(Pasmo::vratPidPasma(naPasma,"PID")));

    labelVykreslovani.naplnZmenaLabel(labelVykreslovani.vyrobTextZmenyPasma(zPasem,naPasma),ui->label_zmena);
}


void MainWindow::zobrazAnnoucement(QString title,QString type,QString textCz, QString textEn)
{
    qDebug()<<"MainWindow::zobrazAnnoucement";
    hlavniZobrazAnnoucement(title,type,textCz,textEn);
    svgVykreslovani.zobrazAnnoucement(title,type,textCz,textEn);
}

void MainWindow::hlavniZobrazAnnoucement(QString title,QString type,QString textCz, QString textEn)
{
    qDebug()<<"MainWindow::hlavniZobrazAnnoucement";
    labelVykreslovani.naplnAnouncementLabel(textCz,ui->label_announcement);
    ui->stackedWidget_obrazovka->setCurrentWidget(ui->page_hlavni);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_oznameni);

    ui->label_oznTitle->setText(title);
    ui->label_oznType->setText(  labelVykreslovani.textNaPiktogramOznameni(type,100*pomerPixelBod));
    ui->label_oznTextCs->setText(textCz);
    ui->label_oznTextEn->setText(textEn);

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
    labelVykreslovani.naplnZmenaLabel("",ui->label_zmena);
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


int MainWindow::jeVRozsahu(int index, int pocetHodnot)
{
    if(index<pocetHodnot)
    {

        return 1;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("hodnota "+QString::number(index)+" je mimo rozsah "+ QString::number(pocetHodnot));
        msgBox.exec();
        qDebug()<<" hodnota mimo rozsah";

        return 0;
    }

}


void MainWindow::hlavniVykresliPrestupy(QVector<Prestup> seznamPrestupu)
{
    qDebug()<<"MainWindow::hlavniVykresliPrestupy";
    //ui->stackedWidget_prostredek->setCurrentWidget(ui->page_prestupy);

    /*
    foreach(QFrame* ramec,seznamFramePrestup)
    {
        // ramec->hide();
    }*/
    foreach(QFrame* label,seznamLabelPrestupCil)
    {
        label->hide();
    }

    foreach(QFrame* label,seznamLabelPrestupLinka)
    {
        label->hide();
    }

    foreach(QFrame* label,seznamLabelPrestupNastupiste)
    {
        label->hide();
    }

    foreach(QFrame* label,seznamLabelPrestupOdjezd)
    {
        label->hide();
    }

    vymazPoleLabelu(seznamLabelPrestupCil);
    vymazPoleLabelu(seznamLabelPrestupLinka);
    vymazPoleLabelu(seznamLabelPrestupNastupiste);
    vymazPoleLabelu(seznamLabelPrestupOdjezd);



    for (int i=0;i<labelVykreslovani.minimum(seznamPrestupu.count(), seznamLabelPrestupCil.count()) ; i++)
    {
        Prestup aktualniPrestup=seznamPrestupu.at(i);
        seznamLabelPrestupCil.at(i)->setText(aktualniPrestup.destinationName);
        seznamLabelPrestupCil.at(i)->show();

        naplnPoleLinky(aktualniPrestup.subMode,aktualniPrestup.line, seznamLabelPrestupLinka.at(i),velikostPiktogramPrestupDynamic,true);

        seznamLabelPrestupNastupiste.at(i)->setText(aktualniPrestup.platform );
        seznamLabelPrestupNastupiste.at(i)->show();

        seznamLabelPrestupOdjezd.at(i)->setText("<b>"+ QString::number( aktualniPrestup.minutDoOdjezdu(QDateTime::currentDateTime() ))+"</b> min.");
        seznamLabelPrestupOdjezd.at(i)->show();
    }
}


void MainWindow::naplnPoleLinky( QString subMode, Linka line, QLabel* label, int velikostPiktogramu,bool prestup)
{
    qDebug()<<"MainWindow::naplnPoleLinky";
    QString linkaStyleSheetStandard="font-weight: bold;";

    if(prestup)
    {
        linkaStyleSheetStandard+="border-radius:6px;padding: 5px; ";
    }


    QString linkaStyleSheetPiktogram="border-radius:6px; padding: 0px; margin: 0px; font-weight: bold;";



    QString nahrazeno=labelVykreslovani.nahradMetro(line.LineName,subMode,velikostPiktogramu);

    //defaultni seda barva na bile pozadi, neznama kombinace
    QString pozadi="background-color:"+barva_bila_255_255_255+";";
    QString text="color:"+barva_PozadiD_150_150_150+";";
    if(nahrazeno==line.LineName)
    {
        if(line.isNight==true)
        {
            subMode=subMode+"Night";
        }

        if(line.isDiversion)
        {
            subMode=subMode+"Diversion";
            //  pozadi="background-color:"+barva_Vyluky_255_170_30+";";
            qDebug()<<"linka je vylukova";
        }
        if(line.isReplacement)
        {
            subMode=subMode+"Replacement";
        }
        if(line.isSpecial)
        {
            subMode=subMode+"Special";
        }


        if(barvaPozadi.contains(subMode))
        {
            pozadi="background-color:"+barvaPozadi[subMode]+";";


        }
        if(barvaTextu.contains(subMode))
        {
            text="color:"+barvaTextu[subMode]+";";
        }
        qDebug()<<"linka "<<line.LineName<<" submode "<<subMode;

        label->setStyleSheet(linkaStyleSheetStandard+text+pozadi);
        label->setText(line.LineName);
    }
    else
    {
        label->setStyleSheet(linkaStyleSheetPiktogram);
        label->setText(nahrazeno);
        qDebug()<<"nahrazeny retezec metra:"<<nahrazeno;
    }


    label->show();
}


void MainWindow::slotHlavniStridejStranky()
{
    qDebug()<<"MainWindow::slotHlavniStridejStranky"<<" counter ma hodnotu "<<indexAktualniStridaneStranky<<" v seznamu je "<<strankyKeStridani.count();

    if(indexAktualniStridaneStranky==(strankyKeStridani.count()-1))
    {
        indexAktualniStridaneStranky=0;
    }
    else
    {
        indexAktualniStridaneStranky++;
    }


    if(indexAktualniStridaneStranky<strankyKeStridani.count())
    {
        ui->stackedWidget_prostredek->setCurrentWidget(strankyKeStridani.at(indexAktualniStridaneStranky));

    }



}

void MainWindow::toggleFullscreen()
{
    qDebug()<<"MainWindow::toggleFullscreen()";
    // isFullScreen() ? showNormal() : showFullScreen();



    if (MainWindow::windowState()==Qt::WindowFullScreen )
    {
        MainWindow::setWindowState(Qt::WindowMaximized);
        // ui->verticalLayoutWidget_4->show();
        //    MainWindow::setWindowState(Qt::Window);

        ui->frame_menu->show();
        ui->menuBar->show();
        ui->statusBar->show();
        ui->mainToolBar->show();
        ui->frame_debug->show();


        // this->setWindowFlags(flags|Qt::SplashScreen);
    }
    else
    {
        MainWindow::setWindowState(Qt::WindowFullScreen);

        ui->frame_menu->hide();
        ui->menuBar->hide();
        ui->statusBar->hide();
        ui->mainToolBar->hide();
        ui->frame_debug->hide();


    }
    // hlavniAutoformat();

}


void MainWindow::hlavniAutoformat()
{
    qDebug()<<"MainWindow::hlavniAutoformat()";
    this->show();
    pomerPixelBod=ui->frame_hlavni->height()/1050.0;

    velikostPiktogramPrestupDynamic=qFloor(velikostPiktogramPrestup*pomerPixelBod);
    //ui->wid
    //   QFont fontLabelu = ui->Lnacestna5->font();
    qDebug()<<"pomerPixelBod stran vyska "<<ui->frame_hlavni->height()<<" sirka:"<<ui->frame_hlavni->width()<<" pomerPixelBod:"<<pomerPixelBod;
    // fontLabelu.setPixelSize(qFloor(pomerPixelBod*100));
    //ui->Lnacestna5->setFont(fontLabelu);


    labelVykreslovani.labelNastavVelikost(ui->Lcil,velikostFontCil,pomerPixelBod ); //100
    labelVykreslovani.labelNastavVelikost(ui->label_nacestne,velikostFontNacestne,pomerPixelBod); //72


    labelVykreslovani.poleLabelNastavVelikost(seznamLabelNazevZastavky,velikostFontNasledujici,pomerPixelBod); //100

    labelVykreslovani.poleLabelNastavVelikost(seznamLabelPrestupLinka,velikostFontPrestupLinka,pomerPixelBod); //48
    labelVykreslovani.poleLabelNastavSirku(seznamLabelPrestupLinka,pomerPixelBod*velikostPrestupRamecekSirka); //95
    labelVykreslovani.poleLabelNastavVysku(seznamLabelPrestupLinka,pomerPixelBod*velikostPrestupRamecekVyska); //65


    labelVykreslovani.poleLabelNastavVelikost(seznamLabelPrestupCil,velikostFontPrestupCil,pomerPixelBod); //36
    labelVykreslovani.poleLabelNastavVelikost(seznamLabelPrestupNastupiste,velikostFontPrestupCil,pomerPixelBod); //36
    labelVykreslovani.poleLabelNastavVelikost(seznamLabelPrestupOdjezd,velikostFontPrestupCil,pomerPixelBod); //36



    labelVykreslovani.labelNastavVelikost(ui->label_hodiny,80,pomerPixelBod); //80
    labelVykreslovani.labelNastavVelikost(ui->label_textPres,30,pomerPixelBod); //30
    labelVykreslovani.labelNastavVelikost(ui->label_textVia ,30,pomerPixelBod); //30
    /*
    labelVykreslovani.labelNastavVelikost(,,);
    labelVykreslovani.labelNastavVelikost(,,);
    labelVykreslovani.labelNastavVelikost(,,);
    labelVykreslovani.labelNastavVelikost(,,);
    */
    labelVykreslovani.zmensiCisloLinkyLabel(ui->Llinka);



}





void MainWindow::on_pushButton_fullscreen_clicked()
{
    toggleFullscreen();
}


void MainWindow::on_Llinka_linkActivated(const QString &link)
{
    toggleFullscreen();
}



