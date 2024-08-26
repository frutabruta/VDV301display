#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString configurationFilePath, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    settings(configurationFilePath, QSettings::IniFormat),
    svgVykreslovani(QCoreApplication::applicationDirPath()),
    cisSubscriber("CustomerInformationService","AllData","2.2CZ1.0","_ibisip_http._tcp",48479),//puvodni port 48479, novy 59631

    deviceManagementService("DeviceManagementService","_ibisip_http._tcp",49477,"1.0") //49477

{

    ui->setupUi(this);

    /*
   * fix of program freezes when IP address is not set properly while doing HTTP POST
   * https://bugreports.qt.io/browse/QTBUG-10106
   */
    QNetworkProxyFactory::setUseSystemConfiguration(false);

    if(!QFile::exists(configurationFilePath))
    {
        popUpMessage(tr("configuration file \n")+configurationFilePath+tr(" \ndoes not exist"));
    }

    QTranslator translator;
    //settings.setValue("General/language","en");
    QString selectedLanguage=settings.value("app/language").toString();

    qDebug()<<"new language:"<<selectedLanguage;

    retranslateUi(selectedLanguage);



    labelVykreslovani.slozkaPiktogramu=QCoreApplication::applicationDirPath()+"/icons";

    initilializeFonts();

    initilializeShortcuts();

    loadConstants();
    constantsToSettingsPage();
    updateMainScreenDebugLabels();

    allConnects();



    //ui->prepinadloStran->setCurrentWidget(ui->page_hlavniObrazovka);

    displayLabelFillArray(); //naplni pointery na labely do pole, aby se nimi dalo iterovat
    ledLabelInitialize2_3();


    labelUpdateFormat();
    lcdResizeLabels();

    stopRequestedDectivated();

    displayAbnormalStateScreen("NO SUBSCRIPTION");



    cisSubscriber.isSubscriptionActive=false ;

    cisSubscriber.start();

    cisSubscriber.newSubscribeRequest();

    updateMainScreenDebugLabels();



    this->ledInitializeFormat();

    /*
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
    */



    //
    eraseDisplayedInformation();

    timerUpdateSeconds->start(1000); //refresh vterin
    timerLedSideCycleViaPoints->start(intervalSideDisplay);

    timerLabelPageSwitch->setInterval(intervalSwitchPages);

    timerDelayedStart->setInterval(intervalDelayedStart);
    timerDelayedStart->setSingleShot(true);
    timerDelayedStart->start();
}

void MainWindow::updateMainScreenDebugLabels()
{
    ui->label_subscribedVersion->setText(cisSubscriber.version());
    ui->label_deviceClass->setText(deviceManagementService.deviceClass());
    ui->label_deviceID->setText(deviceManagementService.deviceId());
    ui->label_locationState->setText(Vdv301Enumerations::LocationStateEnumerationToQString(vehicleState.locationState));

    ui->label_build->setText(createProgramVersionString());
    ui->label_lcd_version->setText(createProgramVersionString());
    ui->label_build->setTextInteractionFlags(Qt::TextSelectableByMouse);
}
void MainWindow::retranslateUi(QString language)
{
    QTranslator translator;

    qApp->removeTranslator(&translator);
    if(translator.load(":/lang_"+language+".qm"))
    {
        qApp->installTranslator(&translator);
        qDebug()<<"language change";
        ui->retranslateUi(this);
    }
    else
    {
        popUpMessage(tr("language file not found"));
    }
}


void MainWindow::constantsToSettingsPage()
{
    ui->lineEdit_settings_deviceName->setText(deviceManagementService.deviceName());
    ui->lineEdit_settings_deviceManufacturer->setText(deviceManagementService.deviceManufacturer());
    ui->lineEdit_settings_deviceSerialNumber->setText(deviceManagementService.deviceSerialNumber());
    ui->lineEdit_settings_deviceClass->setText(deviceManagementService.deviceClass());
    ui->lineEdit_settings_deviceId->setText(deviceManagementService.deviceId());

    QString language=settings.value("app/language").toString();
    if(language=="cs")
    {
        ui->radioButton_settings_languageCs->setChecked(true);
        ui->radioButton_settings_languageEn->setChecked(false);
    }
    else if(language=="en")
    {
        ui->radioButton_settings_languageCs->setChecked(false);
        ui->radioButton_settings_languageEn->setChecked(true);
    }
    else
    {
        ui->radioButton_settings_languageCs->setChecked(false);
        ui->radioButton_settings_languageEn->setChecked(false);
    }


    ui->checkBox_settings_startFullscreen->setChecked(settings.value("window/fullscreen").toBool());
    ui->spinBox_defaultScreen->setValue(settings.value("window/defaultScreen").toInt());
}

void MainWindow::settingsWindowToSettingsFile()
{

    if(ui->radioButton_settings_languageCs->isChecked())
    {
        settings.setValue("app/language","cs");
    }
    if(ui->radioButton_settings_languageEn->isChecked())
    {
        settings.setValue("app/language","en");
    }


    settings.setValue("window/defaultScreen",ui->spinBox_defaultScreen->value());
    settings.setValue("window/fullscreen",ui->checkBox_settings_startFullscreen->isChecked());
    settings.setValue("deviceManagementService/deviceName",ui->lineEdit_settings_deviceName->text());
    settings.setValue("deviceManagementService/deviceManufacturer",ui->lineEdit_settings_deviceManufacturer->text());
    settings.setValue("deviceManagementService/deviceSerialNumber",ui->lineEdit_settings_deviceSerialNumber->text());
    settings.setValue("deviceManagementService/deviceClass",ui->lineEdit_settings_deviceClass->text());
    settings.setValue("deviceManagementService/deviceId",ui->lineEdit_settings_deviceId->text());

}



void MainWindow::initilializeFonts()
{

    QFontDatabase::addApplicationFont(":/fonts/fonty/21-pid-1.ttf");
    QFontDatabase::addApplicationFont(":/fonts/fonty/21-pid-3.ttf");
    QFontDatabase::addApplicationFont(":/fonts/fonty/21-pid-5.ttf");
    QFontDatabase::addApplicationFont(":/fonts/fonty/21-pid-8.ttf");
    QFontDatabase::addApplicationFont(":/fonts/fonty/21-pid-10.ttf");
    QFontDatabase::addApplicationFont(":/fonts/fonty/pid-3v.ttf");


    QFontDatabase::addApplicationFont(":/fonts/fonty/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/fonty/Roboto-Bold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/fonty/Roboto-Black.ttf");
    QFontDatabase::addApplicationFont(":/fonts/fonty/Roboto-Light.ttf");


    fontLed1.setFamily("21-PID 1");
    fontLed1.setPointSize(65);

    fontLed3.setFamily("21-PID 3");
    fontLed3.setPointSize(65);

    fontLed3v.setFamily("pid 3v");
    fontLed3v.setPointSize(65);

    fontLed5.setFamily("21-PID 5");
    fontLed5.setPointSize(65);

    fontLed8.setFamily("21-PID 8");
    fontLed8.setPointSize(65);

    fontLed10.setFamily("21-PID 10");
    fontLed10.setPointSize(65);

    //LCD fonts
    fontLabelFareZoneLarge.setPointSize(36);
    fontLabelFareZoneLarge.setFamily("Roboto");
    fontLabelFareZoneLarge.setBold(true);

    fontLabelFareZoneSmall.setPointSize(20);
    fontLabelFareZoneSmall.setFamily("Roboto");
    fontLabelFareZoneSmall.setBold(true);

}

void MainWindow::ledLabelInitialize2_3()
{
    frontDisplay.lineLabel=ui->labelFrontLine;
    frontDisplay.destinationLabel=ui->labelFrontSingle;
    frontDisplay.destination1Label=ui->labelFrontTopRow;
    frontDisplay.destination2Label=ui->labelFrontBottomRow;
    frontDisplay.ticker=0;

    sideDisplay.lineLabel=ui->labelSideLine;
    sideDisplay.destinationLabel=ui->labelSideSingle;
    sideDisplay.destination1Label=ui->labelSideTopRow;
    sideDisplay.destination2Label=ui->labelSideBottomRow;
    sideDisplay.ticker=0;

    rearDisplay.lineLabel=ui->labelRearLine;
    rearDisplay.destinationLabel=NULL;
    rearDisplay.destination1Label=NULL;
    rearDisplay.destination2Label=NULL;
    rearDisplay.ticker=0;
}



void MainWindow::initilializeShortcuts()
{
    //klávesové zkratky menu
    keyCtrlF = new QShortcut(this); // Initialize the object Zdroj: https://evileg.com/en/post/75/
    keyCtrlF->setKey(Qt::CTRL | Qt::Key_F); // Set the key code

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

}

void MainWindow::loadConstants()
{
    deviceManagementService.setDeviceName(settings.value("deviceManagementService/deviceName").toString());
    deviceManagementService.setDeviceManufacturer(settings.value("deviceManagementService/deviceManufacturer").toString());
    deviceManagementService.setDeviceSerialNumber(settings.value("deviceManagementService/deviceSerialNumber").toString());
    deviceManagementService.setDeviceClass(settings.value("deviceManagementService/deviceClass").toString());
    deviceManagementService.setDeviceId(settings.value("deviceManagementService/deviceId").toString());
    deviceManagementService.setSwVersion(createProgramVersionString());
    deviceManagementService.setPortNumber(settings.value("deviceManagementService/port").toInt() ); //47477
    deviceManagementService.setVersion(settings.value("deviceManagementService/version").toString());

    deviceManagementService.slotDataUpdate();
    deviceManagementService.slotStartServer();

    QString vdv301version=settings.value("cisSubscriber/version").toString();
    QStringList supportedVersionList;
    supportedVersionList<<"1.0";
    supportedVersionList<<"2.2CZ1.0";
    supportedVersionList<<"2.3";
    supportedVersionList<<"2.3CZ1.0";

    if(supportedVersionList.contains(vdv301version))
    {
        cisSubscriber.setVersion(vdv301version);
    }
    else
    {
        popUpMessage(tr("version ")+vdv301version+tr(" is not supported!"));
    }
    cisSubscriber.setPortNumber(settings.value("cisSubscriber/port").toUInt());

    switchTabs(settings.value("window/defaultScreen").toInt());
    if(settings.value("window/fullscreen").toBool()==true)
    {
        slotToggleFullscreen();
    }

}

void MainWindow::slotDelayedStartup()
{
    qDebug() <<  Q_FUNC_INFO;
    //  CustomerInformationServiceSubscriber.hledejSluzby("_ibisip_http._tcp.",0);
    //  CustomerInformationServiceSubscriber.hledejSluzby("_ibisip_http._tcp.",1);
    //cisSubscriber.novePrihlaseniOdberu();
}

void MainWindow::switchTabs(int tabNumber)
{
    qDebug() <<  Q_FUNC_INFO<<" "<<tabNumber;

    switch(tabNumber)
    {
    case 0:

        break;

    case 1:
        on_pushButton_menu_displayLabel_clicked();
        break;

    case 2:
        on_pushButton_menu_svg_clicked();
        break;
    case 3:
        on_pushButton_menu_displayLed_clicked();

        break;
    case 4:
        on_pushButton_menu_services_clicked();
        break;
    }
}



void MainWindow::allConnects()
{
    qDebug() <<  Q_FUNC_INFO;
    connect(&cisSubscriber, &IbisIpSubscriber::signalDataReceived  ,this, &MainWindow::slotXmlDoPromenne);
    connect(&cisSubscriber,&IbisIpSubscriber::signalUpdateDeviceList,this,&MainWindow::slotUpdateServiceTable);
    connect(&cisSubscriber.timerHeartbeatCheck,&QTimer::timeout ,this,&MainWindow::slotHeartbeatTimeout);
    connect(&cisSubscriber,&IbisIpSubscriber::signalSubscriptionLost ,this,&MainWindow::slotSubscriptionLost);
    connect(&cisSubscriber,&IbisIpSubscriberOnePublisher::signalSubscriptionSuccessful,this,&MainWindow::slotDebugPublisherToTable);


    connect(&deviceManagementService,&DeviceManagementService::signalParametersChanged,this,&MainWindow::slotDeviceParametersToConfigFile);


    connect(timerUpdateSeconds, &QTimer::timeout, this, &MainWindow::slotEverySecond);


    if(cisSubscriber.version()=="2.3")
    {
        connect(timerLedSideCycleViaPoints, &QTimer::timeout, this, &MainWindow::tickLedPanels2_3);
    }
    else
    {
        connect(timerLedSideCycleViaPoints, &QTimer::timeout, this, &MainWindow::ledIterateAllDisplays);
    }



    connect(timerScrollingText, &QTimer::timeout, this, &MainWindow::slotMoveScrollingText);
    connect(timerLabelPageSwitch, &QTimer::timeout, this, &MainWindow::slotDisplayLcdLabelCyclePages);
    connect(timerDelayedStart, &QTimer::timeout, this, &MainWindow::slotDelayedStartup);




    //keyboard shortcuts
    // connect(keyCtrlF, SIGNAL(activated()), this, SLOT(toggleFullscreen()));
    connect(keyCtrlF, &QShortcut::activated, this, &MainWindow::slotToggleFullscreen);
    connect(keyF1, &QShortcut::activated, this,&MainWindow::on_pushButton_menu_displayLabel_clicked);
    connect(keyF2, &QShortcut::activated, this,&MainWindow::on_pushButton_menu_svg_clicked );
    connect(keyF3, &QShortcut::activated, this, &MainWindow::on_pushButton_menu_displayLed_clicked);
    connect(keyF4, &QShortcut::activated, this, &MainWindow::on_pushButton_menu_services_clicked);
    connect(keyF5, &QShortcut::activated, this, &MainWindow::on_pushButton_menu_timer_clicked );
    connect(keyF6, &QShortcut::activated, this, &MainWindow::slotToggleFullscreen);
    connect(keyF7, &QShortcut::activated, this, &MainWindow::on_pushButton_menu_refresh_clicked);
    connect(keyF8, &QShortcut::activated, this, &MainWindow::on_pushButton_menu_quit_clicked);
}


QString MainWindow::createProgramVersionString()
{
    QDate compilationDate=QLocale("en_US").toDate(QString(__DATE__).simplified(), "MMM d yyyy");
    QTime compilationTime=QTime::fromString(__TIME__,"hh:mm:ss");
    qDebug()<<" date:"<<compilationDate<<" time:"<<compilationTime;
    QString verze=compilationDate.toString("yyyyMMdd")+"_"+compilationTime.toString("hhmm");
    return verze;
}


int MainWindow::slotEverySecond()
{

    ui->label_remainingSeconds->setText(QString::number(cisSubscriber.timerHeartbeatCheck.remainingTime()/1000) );
    ui->label_odebirano->setText(QString::number(cisSubscriber.isSubscriptionActive));

    if(showTimeColon==true)
    {
        ui->label_hodiny->setText(QTime::currentTime().toString("hh:mm") );
        showTimeColon=false;
    }
    else
    {
        ui->label_hodiny->setText(QTime::currentTime().toString("hh mm") );
        showTimeColon=true;
    }

    return 1;
}

void MainWindow::slotSubscriptionLost()
{
    qDebug() <<  Q_FUNC_INFO;
    eraseTable(ui->tableWidget_selectedSubscriber);
    receivedDataVariablesReset();
    displayAbnormalStateScreen("NO SUBSCRIPTION");
}

void MainWindow::slotMoveScrollingText()
{
    int textWidthPixels=ui->label_nacestne->width();
    int stepSize=1;

    if(textWidthPixels<ui->scrollArea->width() )
    {
        return;
    }
    // qDebug()<<"delka beziciho textu "<< delkaTextu << " posun rotovani: "<<posunRotovani;

    textOffset-=stepSize;

    if (abs(textOffset)>textWidthPixels)
    {
        textOffset=0;
        labelVykreslovani.vykresliNacestneForce(currentDestinationPointList,vehicleState,ui->label_nacestne,cisSubscriber.version());
    }

    else

    {
        ui->scrollAreaWidgetContents->scroll(-stepSize,0);
    }

}

void MainWindow::slotUpdateServiceTable()
{
    qDebug() <<  Q_FUNC_INFO;
    debugServiceListToTable(cisSubscriber.serviceList);
}

void MainWindow::slotHeartbeatTimeout()
{
    qDebug() <<  Q_FUNC_INFO;

}



void MainWindow::displayLabelFillArray()
{
    qDebug() <<  Q_FUNC_INFO;
    labelListStopPointName.push_back(ui->Lnacestna1);
    labelListStopPointName.push_back(ui->Lnacestna2);
    labelListStopPointName.push_back(ui->Lnacestna3);
    labelListStopPointName.push_back(ui->Lnacestna4);
    labelListStopPointName.push_back(ui->Lnacestna5);

    labelListFareZoneUpper.push_back(ui->label_pasmo1_1);
    labelListFareZoneUpper.push_back(ui->label_pasmo2_1);
    labelListFareZoneUpper.push_back(ui->label_pasmo3_1);
    labelListFareZoneUpper.push_back(ui->label_pasmo4_1);
    labelListFareZoneUpper.push_back(ui->label_pasmo5_1);

    labelListFareZoneLower.push_back(ui->label_pasmo1_2);
    labelListFareZoneLower.push_back(ui->label_pasmo2_2);
    labelListFareZoneLower.push_back(ui->label_pasmo3_2);
    labelListFareZoneLower.push_back(ui->label_pasmo4_2);
    labelListFareZoneLower.push_back(ui->label_pasmo5_2);


    labelListConnectionDestination .push_back(ui->label_prestup0_cil);
    labelListConnectionDestination.push_back(ui->label_prestup1_cil);
    labelListConnectionDestination.push_back(ui->label_prestup2_cil);
    labelListConnectionDestination.push_back(ui->label_prestup3_cil);
    labelListConnectionDestination.push_back(ui->label_prestup4_cil);
    labelListConnectionDestination.push_back(ui->label_prestup5_cil);
    labelListConnectionDestination.push_back(ui->label_prestup6_cil);
    labelListConnectionDestination.push_back(ui->label_prestup7_cil);
    labelListConnectionDestination.push_back(ui->label_prestup8_cil);
    labelListConnectionDestination.push_back(ui->label_prestup9_cil);
    labelListConnectionDestination.push_back(ui->label_prestup10_cil);
    labelListConnectionDestination.push_back(ui->label_prestup11_cil);

    labelListConnectionLine.push_back(ui->label_prestup0_linka);
    labelListConnectionLine.push_back(ui->label_prestup1_linka);
    labelListConnectionLine.push_back(ui->label_prestup2_linka);
    labelListConnectionLine.push_back(ui->label_prestup3_linka);
    labelListConnectionLine.push_back(ui->label_prestup4_linka);
    labelListConnectionLine.push_back(ui->label_prestup5_linka);
    labelListConnectionLine.push_back(ui->label_prestup6_linka);
    labelListConnectionLine.push_back(ui->label_prestup7_linka);
    labelListConnectionLine.push_back(ui->label_prestup8_linka);
    labelListConnectionLine.push_back(ui->label_prestup9_linka);
    labelListConnectionLine.push_back(ui->label_prestup10_linka);
    labelListConnectionLine.push_back(ui->label_prestup11_linka);

    labelListConnectionDeparture.push_back(ui->label_prestup0_odjezd);
    labelListConnectionDeparture.push_back(ui->label_prestup1_odjezd);
    labelListConnectionDeparture.push_back(ui->label_prestup2_odjezd);
    labelListConnectionDeparture.push_back(ui->label_prestup3_odjezd);
    labelListConnectionDeparture.push_back(ui->label_prestup4_odjezd);
    labelListConnectionDeparture.push_back(ui->label_prestup5_odjezd);
    labelListConnectionDeparture.push_back(ui->label_prestup6_odjezd);
    labelListConnectionDeparture.push_back(ui->label_prestup7_odjezd);
    labelListConnectionDeparture.push_back(ui->label_prestup8_odjezd);
    labelListConnectionDeparture.push_back(ui->label_prestup9_odjezd);
    labelListConnectionDeparture.push_back(ui->label_prestup10_odjezd);
    labelListConnectionDeparture.push_back(ui->label_prestup11_odjezd);

    labelListConnectionPlatform.push_back(ui->label_prestup0_nastupiste);
    labelListConnectionPlatform.push_back(ui->label_prestup1_nastupiste);
    labelListConnectionPlatform.push_back(ui->label_prestup2_nastupiste);
    labelListConnectionPlatform.push_back(ui->label_prestup3_nastupiste);
    labelListConnectionPlatform.push_back(ui->label_prestup4_nastupiste);
    labelListConnectionPlatform.push_back(ui->label_prestup5_nastupiste);
    labelListConnectionPlatform.push_back(ui->label_prestup6_nastupiste);
    labelListConnectionPlatform.push_back(ui->label_prestup7_nastupiste);
    labelListConnectionPlatform.push_back(ui->label_prestup8_nastupiste);
    labelListConnectionPlatform.push_back(ui->label_prestup9_nastupiste);
    labelListConnectionPlatform.push_back(ui->label_prestup10_nastupiste);
    labelListConnectionPlatform.push_back(ui->label_prestup11_nastupiste);

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






void MainWindow::eraseDisplayedInformation()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->stackedWidget_obrazovka->setCurrentWidget(ui->page_version);
    displayLabelEraseInformation();
    svgVykreslovani.vymazObrazovku();
    ledClearDisplays();
}


void MainWindow::displayLabelEraseInformation()
{
    qDebug() <<  Q_FUNC_INFO;

    ui->Lcil->setText("");
    ui->label_linka->setText("");
    //   ui->label_nacestne->setText("");

    ui->frame_navaznySpoj->hide();

    labelVykreslovani.vymazPoleLabelu(labelListStopPointName);
    labelVykreslovani.vymazPoleLabelu(labelListFareZoneUpper);
    labelVykreslovani.vymazPoleLabelu(labelListFareZoneLower);
    //obrazovka prestupu
    labelVykreslovani.vymazPoleLabelu(labelListConnectionDestination);
    labelVykreslovani.vymazPoleLabelu(labelListConnectionLine);
    labelVykreslovani.vymazPoleLabelu(labelListConnectionPlatform);
    labelVykreslovani.vymazPoleLabelu(labelListConnectionDeparture);

    timerLabelPageSwitch->stop();
    pageCycleList.clear();
    pageCycleList.push_back(ui->page_hlavni_2);
}


int MainWindow::showReceivedData()
{
    qDebug() <<  Q_FUNC_INFO;

    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_hlavni_2);
    eraseTable(ui->tableWidget_debugStopList);

    displayLabelEraseInformation();
    updateMainScreenDebugLabels();


    if(vehicleState.isVehicleStopRequested)
    {
        stopRequestedActivated();
    }
    else
    {
        stopRequestedDectivated();
    }
    ui->label_currentStopIndex->setText(QString::number(vehicleState.currentStopIndex0+1));


    if(vehicleState.currentStopIndex0<0 )
    {
        popUpMessage("index zastavky je mensi nez 0");
        return 0;
    }


    displayLabelDestination(nazevCile);
    displayLabelLineName(currentDestinationPointList.at(vehicleState.currentStopIndex0),vehicleState.vehicleSubMode);
    displayLabelStopFareZone(currentDestinationPointList,nextDestinationPointList);
    displayLabelViaPoints();

    pageCycleList.clear();

    //strankyKeStridani.push_back(ui->page_hlavni_2);



    if(!xmlParser.existujeNavaznySpoj(nextDestinationPointList))
    {
        qDebug()<<"navazny spoj neni";
        ui->frame_navaznySpoj->hide();
        // ui->horizontalLayout_navaznySpoj;

    }
    else
    {
        QString navaznyCil="";
        QString navaznaLinka="";
        if(xmlParser.udajeNavaznehoSpoje(nextDestinationPointList,navaznaLinka,navaznyCil))
        {
            ui->label_navaznaLinka->setText(navaznaLinka);
            ui->label_navaznyCil->setText(navaznyCil);
            ui->frame_navaznySpoj->show();
        }
    }

    //additional text message

    if(additionalTextMessageText!="")
    {
        displayLabelShowPageSpecialAnnouncement(additionalTextMessageHeadline,additionalTextMessageType,additionalTextMessageText,"");
        pageCycleList.push_back(ui->page_oznameni);
    }
    else
    {
        labelVykreslovani.naplnAnouncementLabel("",ui->label_announcement);
    }

    //konecna

    if(isVehicleOnFinalStop(vehicleState,currentDestinationPointList)&&(!xmlParser.existujeNavaznySpoj(nextDestinationPointList)))
    {
        pageCycleList.push_front(ui->page_konecna);
        displayLabelShowPageFinalStop();
    }
    else
    {
        if(isFareZone==true)
        {
            showPageFareZoneChange(fareZoneChangeFrom,fareZoneChangeTo);
        }
        else
        {
            if(xmlParser.zmenaDat==true)
            {
                displayLabelReturnToStopList();
            }
            pageCycleList.push_front(ui->page_hlavni_2);
            // skryjZmenuPasma();
        }

    }

    if(!currentDestinationPointList.at(vehicleState.currentStopIndex0).stopPoint.connectionList.isEmpty())
    {
        pageCycleList.push_back(ui->page_prestupy);
        displayLabelConnectionList(currentDestinationPointList.at(vehicleState.currentStopIndex0).stopPoint.connectionList);
    }

    //   hlavniVykresliNasledne();

    labelUpdateFormat();
    lcdResizeLabels();
    currentPageIndex=0;
    timerLabelPageSwitch->start();

    debugStopPointListToTable(currentDestinationPointList,false);
    debugStopPointListToTable(nextDestinationPointList,true);

    connectionListToTable(currentDestinationPointList.at(vehicleState.currentStopIndex0).stopPoint.connectionList,ui->tableWidget_connections);

    return 1;
}

void MainWindow::debugStopPointListToTable(QVector<StopPointDestination> seznamZastavek,bool navazny)
{
    if(!navazny)
    {
        eraseTable(ui->tableWidget_debugStopList);
    }

    foreach(StopPointDestination polozka, seznamZastavek)
    {
        debugStopPointToTable(polozka,navazny);
    }
}

void MainWindow::stopRequestedActivated()
{
    ui->label_stopRequested->setText("<b>STOP</b>");

    ui->label_stopRequestedSymbol->show();
}

void MainWindow::stopRequestedDectivated()
{
    ui->label_stopRequested->setText("STOP");
    ui->label_stopRequestedSymbol->hide();
}



void MainWindow::displayLabelLineName(StopPointDestination selectedStopPointDestinationstavka,QString subMode)
{
    qDebug() <<  Q_FUNC_INFO;
    //  labelVykreslovani.naplnCisloLinkyLabel(alias,ui->Llinka);
    qDebug()<<"vypis linky:"<<selectedStopPointDestinationstavka.destination.NameLcd<<" "<<selectedStopPointDestinationstavka.line.lineName<<" vylukova:"<<selectedStopPointDestinationstavka.line.isDiversion ;

    if(cisSubscriber.version()=="2.3")
    {
        displayLabelDrawLineNumber2_4(subMode,selectedStopPointDestinationstavka.line,ui->label_linka, qFloor(ratioPixelPoint*200),false);

    }
    else
    {
        displayLabelDrawLineNumber(subMode,selectedStopPointDestinationstavka.line,ui->label_linka, qFloor(ratioPixelPoint*200),false);

    }
    //  labelVykreslovani.zmensiCisloLinkyLabel(ui->Llinka);

}

void MainWindow::displayLabelDestination(QString nazev)
{
    qDebug() <<  Q_FUNC_INFO;

    labelVykreslovani.naplnNazevCileLabel(nazev,ui->Lcil);
    /* if(cisSubscriber.verze()=="2.3")
    {
       labelVykreslovani.naplnNazevCileLabel(labelVykreslovani.inlineFormatParser.vyparsujText(nazev, ui->Lcil->font().pixelSize(),labelVykreslovani.slozkaPiktogramu), ui->Lcil);

    }
    else
    {

    }
*/
}



void MainWindow::displayLabelStopFareZone(QVector<StopPointDestination> thisStopPointDestinationList, QVector<StopPointDestination> nextStopPointDestinationList)
{
    qDebug() <<  Q_FUNC_INFO;

    //
    displayLabelStopList(thisStopPointDestinationList,nextStopPointDestinationList,vehicleState.currentStopIndex0);

}





void MainWindow::displayLabelStopList(QVector<StopPointDestination> thisStopPointDestinationList,QVector<StopPointDestination> nextStopPointDestinationList, int index)
{
    qDebug() <<  Q_FUNC_INFO;
    //stavSystemu.indexAktZastavky;
    int pocetPoli=labelListStopPointName.count();
    if(thisStopPointDestinationList.isEmpty())
    {
        return ;
    }

    //   zastavky=vektorZastavkaCilZahoditZacatek(zastavky,index);

    thisStopPointDestinationList.remove(0,index);



    for(int i=0;i<pocetPoli;i++)
    {
        StopPointDestination aktualniZastavka;
        bool navaznySpoj=false;
        if(!thisStopPointDestinationList.isEmpty())
        {
            aktualniZastavka=thisStopPointDestinationList.takeFirst();
        }
        else
        {
            if(!nextStopPointDestinationList.isEmpty())
            {
                navaznySpoj=true;
                aktualniZastavka=nextStopPointDestinationList.takeFirst();
            }
            else
            {
                qDebug()<<"pro label "<<i<<" uz nezbyly zastavky";

                return;
            }
        }

        displayLabelStopPoint(aktualniZastavka,navaznySpoj,labelListStopPointName.at(i),labelListFareZoneUpper.at(i),labelListFareZoneLower.at(i));

    }



}


void MainWindow::displayLabelStopPoint(StopPointDestination selectedStopPointDestination, bool isFollowingTrip, QLabel* labelStopName, QLabel* labelFarezoneBottom, QLabel* labelFarezoneTop)
{
    PasmoveDvojiceLcd pasmoveDvojiceLcd;


    if((cisSubscriber.version()=="2.3")||(cisSubscriber.version()=="2.3CZ1.0"))
    {
        //   QString nahradIconPiktogramem(QString vstup);
        //   nazevZastavky->setText(labelVykreslovani.zabalHtmlDoZnacek(labelVykreslovani.nahradIconPiktogramem( aktualniZastavka.stopPoint.NameLcd, nazevZastavky->font().pixelSize(),labelVykreslovani.slozkaPiktogramu )));
        pasmoveDvojiceLcd.roztridPasma2_3(selectedStopPointDestination.stopPoint.fareZoneList);
        labelStopName->setText(labelVykreslovani.inlineFormatParser.parseTextLcd(selectedStopPointDestination.stopPoint.NameLcd, labelStopName->font().pixelSize(),labelVykreslovani.slozkaPiktogramu) );
    }
    else
    {
        pasmoveDvojiceLcd.roztridPasma(selectedStopPointDestination.stopPoint.fareZoneList);
        labelStopName->setText(labelVykreslovani.zabalHtmlDoZnacek(labelVykreslovani.doplnPiktogramyBezZacatkuKonce(selectedStopPointDestination.stopPoint.NameLcd,selectedStopPointDestination.stopPoint.iconList,labelStopName->font().pixelSize() )));
    }


    if(pasmoveDvojiceLcd.pasmaSystemu1.isEmpty())
    {
        labelFarezoneBottom->setText("");

    }
    else
    {
        QString pasmaString1=svgVykreslovani.pasmaDoStringu( pasmoveDvojiceLcd.pasmaSystemu1);
        QString zkratkaSystemuDvojtecka="";
        if (!pasmoveDvojiceLcd.pasmaSystemu2.isEmpty())
        {

            if(!pasmoveDvojiceLcd.pasmaSystemu1.first().system.isEmpty())
            {
                zkratkaSystemuDvojtecka=pasmoveDvojiceLcd.pasmaSystemu1.first().system+":";
            }

        }
        labelFarezoneBottom->setText(zkratkaSystemuDvojtecka+pasmaString1);
        labelFarezoneBottom->setFont(fontLabelFareZoneLarge);
    }

    if(pasmoveDvojiceLcd.pasmaSystemu2.isEmpty())
    {
        labelFarezoneTop->hide();
        labelFarezoneTop->setFont(fontLabelFareZoneLarge);
    }
    else
    {
        QString pasmaString2=svgVykreslovani.pasmaDoStringu( pasmoveDvojiceLcd.pasmaSystemu2);
        labelFarezoneTop->show();

        labelFarezoneTop->setFont(fontLabelFareZoneSmall );
        labelFarezoneBottom->setFont(fontLabelFareZoneSmall );

        if(!pasmoveDvojiceLcd.pasmaSystemu2.first().system.isEmpty())
        {
            labelFarezoneTop->setText(pasmoveDvojiceLcd.pasmaSystemu2.first().system+":"+pasmaString2);
        }
        else
        {
            labelFarezoneTop->setText(pasmaString2);
        }

    }

    if(isFollowingTrip==false)
    {
        labelStopName->setStyleSheet("color:"+barvyLinek.barva_bila_255_255_255+";");
        labelFarezoneTop->setStyleSheet("color:"+barvyLinek.barva_bila_255_255_255+";");
        labelFarezoneBottom->setStyleSheet("color:"+barvyLinek.barva_bila_255_255_255+";");
    }
    else
    {
        labelStopName->setStyleSheet("color:"+barvyLinek.barva_PozadiC_100_100_100+";");
        labelFarezoneTop->setStyleSheet("color:"+barvyLinek.barva_PozadiC_100_100_100+";");
        labelFarezoneBottom->setStyleSheet("color:"+barvyLinek.barva_PozadiC_100_100_100+";");
    }


}




void MainWindow::displayLabelViaPoints()
{
    qDebug() <<  Q_FUNC_INFO;

    /*
    if(currentDestinationPointList.isEmpty())
    {
        ui->label_nacestne->setText("");
        return;
    }
    */

    QString newViapointString=labelVykreslovani.vykresliNacestneZastavkyText(currentDestinationPointList.at(vehicleState.currentStopIndex0).viaPoints, ui->label_nacestne->font().pixelSize(),cisSubscriber.version());



    if(oldViapointString!=newViapointString)
    {
        ui->label_nacestne->setText( newViapointString);
        timerScrollingText->start(intervalScrollingText);        
        oldViapointString=newViapointString;
    }
    else
    {
        if(ui->label_nacestne->text()=="")
        {
            ui->label_nacestne->setText( newViapointString);
        }

    }


}



int MainWindow::setDestinationName()
{
    qDebug() <<  Q_FUNC_INFO;
    // qInfo()<<"\n DoplneniPromennych";


    if ((currentDestinationPointList.size()>stopIndex)&&(stopIndex>=0))
    {
        StopPointDestination aktualniZastavka=currentDestinationPointList.at(stopIndex);

        if((cisSubscriber.version()=="2.3")||(cisSubscriber.version()=="2.3CZ1.0"))
        {
             nazevCile=labelVykreslovani.inlineFormatParser.parseTextLcd(aktualniZastavka.destination.NameLcd,ui->Lcil->font().pixelSize(),labelVykreslovani.slozkaPiktogramu);
        }
        else
        {
            nazevCile=labelVykreslovani.zabalHtmlDoZnacek(labelVykreslovani.doplnPiktogramyBezZacatkuKonce(aktualniZastavka.destination.NameLcd,aktualniZastavka.destination.iconList,ui->Lcil->font().pixelSize()));
        }

    }
    else
    {
        qDebug()<<"indexZastavky je"<<QString::number(stopIndex)<<" velikost globSezZast="<<QString::number(currentDestinationPointList.size());
    }
    qInfo()<<"nazevCile "<<nazevCile;
    return 1;
}

int MainWindow::labelUpdateFormat()
{
    qDebug() <<  Q_FUNC_INFO;



    if (vehicleState.locationState==Vdv301Enumerations::LocationStateAtStop )
    {
        labelSetNextStopBackground(barvyLinek.barva_PozadiB_50_50_50,barvyLinek.barva_Zastavka_180_180_180 );
    }
    else
    {
        labelSetNextStopBackground(barvyLinek.barva_bila_255_255_255,barvyLinek.barva_PozadiB_50_50_50);
    }

    // hlavniAutoformat();
    return 1;

}

MainWindow::~MainWindow()
{
    qDebug() <<  Q_FUNC_INFO;
    delete ui;
}



void MainWindow::on_actiontestPolozka_triggered()
{
    qDebug() <<  Q_FUNC_INFO;

    slotToggleFullscreen();
}


/*


SITOVA CAST, ODPOVIDAC
nejsem autorem




*/




void MainWindow::eraseTable(QTableWidget *tableWidget)
{
    //used to erase tablewidgets without program crash due to signals
    //  https://stackoverflow.com/a/31564541
    qDebug() <<  Q_FUNC_INFO;

    tableWidget->clearSelection();

    // Disconnect all signals from table widget ! important !
    tableWidget->disconnect();

    // Remove all items
    tableWidget->clearContents();

    // Set row count to 0 (remove rows)
    tableWidget->setRowCount(0);

}

void MainWindow::debugServiceListToTable(QVector<QZeroConfService> serviceList)
{
    qDebug() <<  Q_FUNC_INFO;
    eraseTable(ui->tabulkaSubscriberu);


    foreach(QZeroConfService selectedService, serviceList)
    {
        slotDebugServiceToTable(selectedService);
    }
}


void MainWindow::slotDebugServiceToTable(QZeroConfService zcs)
{
    qDebug() <<  Q_FUNC_INFO;
    qint32 row;
    QTableWidgetItem *cell;

    QString nazev=zcs->name();
    QString ipadresa=zcs->ip().toString();
    QString host=zcs->host();
    QString verze=zcs.data()->txt().value("ver");
    int port=zcs->port();

    qDebug() <<"nazev sluzby "<<nazev<<" ip adresa "<<ipadresa<<" port "<<QString::number(port)<<" data" <<verze ;


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


void MainWindow::slotDebugPublisherToTable(QZeroConfService zcs)
{
    qDebug() <<  Q_FUNC_INFO;
    eraseTable(ui->tableWidget_selectedSubscriber);
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

    row = ui->tableWidget_selectedSubscriber->rowCount();
    ui->tableWidget_selectedSubscriber->insertRow(row);
    cell = new QTableWidgetItem(nazev);
    ui->tableWidget_selectedSubscriber->setItem(row, 0, cell);

    cell = new QTableWidgetItem(verze);
    ui->tableWidget_selectedSubscriber->setItem(row, 1, cell);

    cell = new QTableWidgetItem(ipadresa);
    ui->tableWidget_selectedSubscriber->setItem(row, 2, cell);

    cell = new QTableWidgetItem(QString::number(port));
    ui->tableWidget_selectedSubscriber->setItem(row, 3, cell);

    cell = new QTableWidgetItem(host);
    ui->tableWidget_selectedSubscriber->setItem(row, 4, cell);


    ui->tableWidget_selectedSubscriber->resizeColumnsToContents();


    qDebug()<<"sluzbaDoTabulky_konec";

}

void MainWindow::debugStopPointToTable(StopPointDestination selectedStopPointDestination, bool isFollowingTrip)
{
    qDebug() <<  Q_FUNC_INFO;
    qint32 row;
    QTableWidgetItem *cell;


    /*
    qDebug() <<"nazev sluzby "<<nazev<<" ip adresa "<<ipadresa<<" port "<<QString::number(port)<<" data" <<verze ;

 */

    row = ui->tableWidget_debugStopList->rowCount();
    ui->tableWidget_debugStopList->insertRow(row);

    cell = new QTableWidgetItem(InlineFormatParser::parseTextLed(selectedStopPointDestination.stopPoint.NameLcd));

    if(isFollowingTrip)
    {
        cell->setBackground(QColor(240,240,240));
    }
    ui->tableWidget_debugStopList->setItem(row, 0, cell);

    cell = new QTableWidgetItem(InlineFormatParser::parseTextLed(selectedStopPointDestination.line.lineName));
    ui->tableWidget_debugStopList->setItem(row, 1, cell);

    cell = new QTableWidgetItem(InlineFormatParser::parseTextLed(selectedStopPointDestination.destination.NameLcd));
    ui->tableWidget_debugStopList->setItem(row, 2, cell);

    ui->tableWidget_debugStopList->resizeColumnsToContents();

    qDebug()<<"sluzbaDoTabulky_konec";
}

void MainWindow::connectionListToTable(QVector<Connection> connectionList,QTableWidget* tableWidget)
{

    eraseTable(tableWidget);


    foreach(Connection connection, connectionList)
    {
        connectionToTable(connection,tableWidget);
    }
}
void MainWindow::connectionToTable(Connection connection, QTableWidget* tableWidget)
{
    qDebug() <<  Q_FUNC_INFO;
    qint32 row;
    QTableWidgetItem *cell;

    /*
    qDebug() <<"nazev sluzby "<<nazev<<" ip adresa "<<ipadresa<<" port "<<QString::number(port)<<" data" <<verze ;

 */

    row = tableWidget->rowCount();
    tableWidget->insertRow(row);

    cell = new QTableWidgetItem(InlineFormatParser::parseTextLed( connection.line.lineName));

    tableWidget->setItem(row, 0, cell);

    cell = new QTableWidgetItem(connection.destinationName);
    tableWidget->setItem(row, 1, cell);

    cell = new QTableWidgetItem(connection.scheduledDepartureTime.toString("hh:mm") );
    tableWidget->setItem(row, 2, cell);

    cell = new QTableWidgetItem(connection.expectedDepartureTime.toString("hh:mm") );
    tableWidget->setItem(row, 3, cell);

    tableWidget->resizeColumnsToContents();


}


// XXX FIX GlobalDisplayContent while Stop List is not empty!
void MainWindow::slotXmlDoPromenne(QString vstupniXml)
{
    qDebug() <<  Q_FUNC_INFO;


    xmlParser.nactiXML(vstupniXml);


    receivedDataVariablesReset();


    qDebug()<<"timestamp:"<<xmlParser.vyparsujTimestamp(xmlParser.dokument).toString(Qt::ISODate);


    if(cisSubscriber.version()=="1.0")
    {
        if(!xmlParser.VytvorSeznamZastavek1_0(currentDestinationPointList,nextDestinationPointList, stopIndex))
        {
            notOnLine();
            return;
        }
    }
    else if(cisSubscriber.version()=="2.2CZ1.0")
    {
        if(!xmlParser.VytvorSeznamZastavek2_2CZ1_0(currentDestinationPointList,nextDestinationPointList, stopIndex))
        {
            notOnLine();
            return;
        }
    }
    else if(cisSubscriber.version()=="2.3")
    {

        vdv301AllData=xmlParser.parseAllData2_3(xmlParser.dokument,currenVdv301StopPointList);

        if(!xmlParser.VytvorSeznamZastavek2_3(currentDestinationPointList,nextDestinationPointList, stopIndex))
        {
            notOnLine();
            ledUpdateDisplayedInformationFromDisplayContentList2_3(vdv301AllData.globalDisplayContentList);
            return;
        }

    }

    else if(cisSubscriber.version()=="2.3CZ1.0")
    {

        vdv301AllData=xmlParser.parseAllData2_3(xmlParser.dokument,currenVdv301StopPointList);

        if(!xmlParser.VytvorSeznamZastavek2_3(currentDestinationPointList,nextDestinationPointList, stopIndex))
        {
            notOnLine();
            ledUpdateDisplayedInformationFromDisplayContentList2_3(vdv301AllData.globalDisplayContentList);
            return;
        }
        /*
        else
        {
            if(vdv301AllData.globalDisplayContentList.isEmpty())
            {

            }
            else
            {
                ledUpdateDisplayedInformationFromDisplayContentList2_3(vdv301AllData.globalDisplayContentList);
                return;
            }
        }
        */

    }
    else
    {
        displayAbnormalStateScreen("INCORRECT SUBSCRIBER VERSION");
        return;
    }



    xmlParser.nactiVehicleGroup(vehicleState,xmlParser.dokument);

    //additional text message
    xmlParser.nactiAdditionalTextMessage(xmlParser.dokument,additionalTextMessageType,additionalTextMessageHeadline, additionalTextMessageText);

    //zmena tarifniho pasma

    isFareZone= xmlParser.nactiFareZoneChange(xmlParser.dokument,fareZoneChangeFrom,fareZoneChangeTo);


    //instanceXMLparser.nactiXML(globalniSeznamZastavek, &indexZastavky, &pocetZastavek);
    //qInfo()<<globalniSeznamZastavek[4].StopName;
    qInfo()<<stopIndex;
    qInfo()<<"CIl:"<<nazevCile;

    if(stopIndex>=0)
    {
        if( currentDestinationPointList.size()>0)
        {
            if(isInRange(stopIndex,currentDestinationPointList.count()))
            {
                displayNormalOnLineState();
                setDestinationName();
                showReceivedData();
                labelUpdateFormat();

                if(cisSubscriber.version()=="2.3")
                {
                    ledUpdateDisplayedInformationFromDisplayContentList2_3(this->ledUpdateCurrentStopToDisplayContentList2_3(currenVdv301StopPointList,vehicleState));

                }
                else if(cisSubscriber.version()=="2.3CZ1.0")
                {
                    if(vdv301AllData.globalDisplayContentList.isEmpty())
                    {
                        ledUpdateDisplayedInformationFromDisplayContentList2_3(this->ledUpdateCurrentStopToDisplayContentList2_3(currenVdv301StopPointList,vehicleState));
                    }
                    else
                    {
                        ledUpdateDisplayedInformationFromDisplayContentList2_3(vdv301AllData.globalDisplayContentList);
                        return;
                    }

                }
                else
                {
                    this->ledUpdateDisplayedInformation(currentDestinationPointList,vehicleState);
                }


                this->svgVykresleni();
                qInfo()<<"CIl:"<<nazevCile;
            }
            else
            {
                //vyskakovaciOkno("index zastávky: "+QString::number(indexZastavky));

                displayAbnormalStateScreen("STOP INDEX OUT OF RANGE");

            }

            //instanceHttpServeru.prijatoZeServeruTelo="";
        }
        else
        {
            displayAbnormalStateScreen("COULDNT PARSE STOPS");

        }
    }
    else
    {
        displayAbnormalStateScreen("STOP INDEX <0");
    }


    if(cisSubscriber.version()=="2.3")
    {


    }





    //NetworkCleanup();

}

void MainWindow::receivedDataVariablesReset()
{
    currentDestinationPointList.clear();
    nextDestinationPointList.clear();
    debugStopPointListToTable(currentDestinationPointList,false);
}


void MainWindow::displayAbnormalStateScreen(QString displayState)
{
    qDebug()<<Q_FUNC_INFO<<" "<<displayState;
    ui->label_lcd_state->setText(displayState);
    eraseDisplayedInformation();
    ui->stackedWidget_obrazovka->setCurrentWidget(ui->page_version);

}

void MainWindow::notOnLine()
{
    displayAbnormalStateScreen("EMPTY STOP LIST");
}

void MainWindow::displayNormalOnLineState()
{

    ui->stackedWidget_obrazovka->setCurrentWidget(ui->page_hlavni);
}





void MainWindow::on_pushButton_menu_services_clicked()
{
    ui->prepinadloStran->setCurrentWidget(ui->page_seznamSluzeb);
}

void MainWindow::on_pushButton_menu_displayLabel_clicked()
{
    ui->prepinadloStran->setCurrentWidget(ui->page_hlavniObrazovka);
    labelUpdateFormat();
    lcdResizeLabels();
}

void MainWindow::on_pushButton_menu_timer_clicked()
{
    ui->prepinadloStran->setCurrentWidget(ui->page_casovac);
}

void MainWindow::labelSetNextStopBackground(QString barvaPisma,QString barvaPozadi)
{
    qDebug() <<  Q_FUNC_INFO;
    //
    labelVykreslovani.obarviPozadiPristi(barvaPisma,barvaPozadi,ui->frame_spodniRadek);
    svgVykreslovani.obarviPozadiPristi(barvaPisma,barvaPozadi);


    QString stylTextu="color:"+barvaPisma;
    ui->Lnacestna1->setStyleSheet(stylTextu);
    ui->label_pasmo1_1->setStyleSheet(stylTextu);
    ui->label_pasmo1_2->setStyleSheet(stylTextu);


}


void MainWindow::on_pushButton_menu_quit_clicked()
{
    qDebug() <<  Q_FUNC_INFO;

    connect(&cisSubscriber,&CisSubscriber::signalIsUnsubscriptionSuccesful,this,&MainWindow::slotShutdownReady);
    cisSubscriber.unsubscribe();
    //   connect(&cisSubscriber,&IbisIpSubscriber::signalSubscriptionLost ,this,&MainWindow::slotSubscriptionLost);
}

void MainWindow::slotShutdownReady(bool isReady)
{
    if(isReady)
    {
        MainWindow::close();
    }
    else
    {
        popUpMessage(tr("unsubscription was unsuccessful"));
    }
}



void MainWindow::on_pushButton_menu_svg_clicked()
{
    qDebug()<<Q_FUNC_INFO;
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

    if (currentDestinationPointList.length()>0)
    {
        //svgVykreslovac.svgReplaceName("Verlauf2.svg","vystup.txt",globalniSeznamZastavek.last().StopName,globalniSeznamZastavek.at(stavSystemu.indexAktZastavky).StopName,globalniSeznamZastavek.at(stavSystemu.indexAktZastavky+1).StopName,globalniSeznamZastavek.at(stavSystemu.indexAktZastavky+2).StopName);
        svgVykreslovani.aktualizujVse(currentDestinationPointList,vehicleState);
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
    qDebug() <<  Q_FUNC_INFO;
    QGraphicsScene *s = &scene;

    QFile soubor;

    QScopedPointer<QGraphicsSvgItem> svgItem(new QGraphicsSvgItem(fileName));
    svgItem->renderer()->setFramesPerSecond(20);
    if (!svgItem->renderer()->isValid())
        return false;

    s->clear();
    // resetTransform();

    m_svgItem = svgItem.take();

    //m_svgItem = svgItem.take();
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

void MainWindow::on_pushButton_menu_displayLed_clicked()
{
    ui->prepinadloStran->setCurrentWidget(ui->page_led);
    ui->labelFrontBottomRow->setText("");
}


void MainWindow::ledSetTextFront(QString line,QString destinationTop,QString destinationBottom)
{
    qDebug() <<  Q_FUNC_INFO;


    if (destinationBottom!="")
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


    ui->labelFrontTopRow->setText(destinationTop);
    ui->labelFrontBottomRow->setText(destinationBottom);
    ui->labelFrontSingle->setText(destinationTop);

    ledSetLine(ui->labelFrontLine,line);
}


void MainWindow::ledAlignTextOverflow(QLabel* label)
{
    qDebug() <<  Q_FUNC_INFO;
    QFontMetrics metrics(label->font());

    if(metrics.horizontalAdvance(label->text())> label->width())
    {
        label->setAlignment(Qt::AlignLeading|Qt::AlignBottom);
    }
    else
    {
        label->setAlignment(Qt::AlignHCenter|Qt::AlignBottom);
    }
}

void MainWindow::ledSetTextSide(QString line,QString destinationTop,QString destinationBottom)
{
    qDebug() <<  Q_FUNC_INFO;



    if (destinationBottom!="")
    {
        ui->labelSideSingle->setVisible(false);
        ui->labelSideBottomRow->setVisible(true);
        ui->labelSideTopRow->setVisible(true);
    }
    else
    {
        ui->labelSideSingle->setVisible(true);
        ui->labelSideBottomRow->setVisible(false);
        ui->labelSideTopRow->setVisible(false);
    }

    ui->labelSideLine->setText(line);


    ui->labelSideSingle->setText(destinationTop);
    ledAlignTextOverflow(ui->labelSideSingle);

    ui->labelSideTopRow->setText(destinationTop);
    ledAlignTextOverflow(ui->labelSideTopRow);

    ui->labelSideBottomRow->setText(destinationBottom);
    ledAlignTextOverflow(ui->labelSideBottomRow);

    ledSetLine(ui->labelSideLine,line);

}


void MainWindow::ledSetLine(QLabel* label, QString text)
{
    qDebug()<<Q_FUNC_INFO;
    label->setText(text);
    if (text.length()>3)
    {

        label->setFont(fontLed10);
    }
    else
    {
        label->setFont(fontLed8);
    }
    ledAlignTextOverflow(label);
}

void MainWindow::ledSetTextRear(QString line)
{
    qDebug() <<  Q_FUNC_INFO;

    ledSetLine(ui->labelRearLine,line);

}

void MainWindow::ledSetTextInner(QString line,QString destinationTop,QString destinationBottom)
{
    qDebug() <<  Q_FUNC_INFO;
    ui->labelInnerLine->setText(line);
    ui->labelInnerTopRow->setText(destinationTop);
    ui->labelInnerBottomRow->setText(destinationBottom);
}


void MainWindow::ledInitializeFormat()
{
    qDebug() <<  Q_FUNC_INFO;
    /*
    ledNaplnFront("123","čelní horní","čelní dolní");
    ledNaplnSide("456","Boční cíl","Boční nácestné");
    ledNaplnRear("789");
    ledNaplnInner("123","vnitřní cíl", "vnitřní nácesty");
*/

    ui->labelFrontSingle->setFont(fontLed5);
    ui->labelSideSingle->setFont(fontLed5);

    ui->labelFrontTopRow->setFont(fontLed3);
    ui->labelFrontBottomRow->setFont(fontLed3);

    ui->labelSideTopRow->setFont(fontLed1);
    ui->labelSideBottomRow->setFont(fontLed1);

    ui->labelInnerLine->setFont(fontLed3);
    ui->labelInnerBottomRow->setFont(fontLed1);
    ui->labelInnerTopRow->setFont(fontLed1);
    /* font 3v is not size optimised at the moment
    ui->labelInnerBottomRow->setFont(fontLed3v);
    ui->labelInnerTopRow->setFont(fontLed3v);
    */

    if(ui->labelFrontLine->text().length()>3)
    {
        ui->labelFrontLine->setFont(fontLed10);
        ui->labelSideLine->setFont(fontLed10);
        ui->labelRearLine->setFont(fontLed10);
    }
    else
    {
        ui->labelFrontLine->setFont(fontLed8);
        ui->labelSideLine->setFont(fontLed8);
        ui->labelRearLine->setFont(fontLed8);
    }

}

void MainWindow::ledClearDisplays()
{
    qDebug() <<  Q_FUNC_INFO;
    ledSetTextFront("","","");
    ledSetTextSide("","","");
    ledSetTextRear("");
    ledSetTextInner("","", "");
    textyBocniPanelkIteraci.clear();
    textyVnitrniPanelkIteraci.clear();
}

void MainWindow::ledUpdateDisplayedInformation(QVector<StopPointDestination> stopPointList, VehicleState vehicleState )
{
    qDebug() <<  Q_FUNC_INFO;
    if(!isInRange(vehicleState.currentStopIndex0,stopPointList.count()))
    {
        return;
    }

    StopPointDestination aktZast=stopPointList.at(vehicleState.currentStopIndex0);


    if((cisSubscriber.version()=="2.3")||(cisSubscriber.version()=="2.3CZ1.0"))
    {

        ledSetTextFront(labelVykreslovani.inlineFormatParser.parseTextLed(aktZast.line.lineName),labelVykreslovani.inlineFormatParser.parseTextLed(aktZast.destination.NameFront),labelVykreslovani.inlineFormatParser.parseTextLed(aktZast.destination.NameFront2));
        ledSetTextSide(labelVykreslovani.inlineFormatParser.parseTextLed(aktZast.line.lineName),labelVykreslovani.inlineFormatParser.parseTextLed(aktZast.destination.NameSide),"" );
        ledSetTextRear(labelVykreslovani.inlineFormatParser.parseTextLed(aktZast.line.lineName));
        ledSetTextInner(labelVykreslovani.inlineFormatParser.parseTextLed(aktZast.line.lineName),aktZast.destination.NameInner,  labelVykreslovani.inlineFormatParser.parseTextLed(aktZast.stopPoint.NameInner));

        textyBocniPanelkIteraci=ledStopPointToViapointListSide(aktZast);
        textyVnitrniPanelkIteraci=ledStopPointToViapointListInner(aktZast);




    }
    else
    {

        ledSetTextFront(aktZast.line.lineName,aktZast.destination.NameFront,aktZast.destination.NameFront2);
        ledSetTextSide(aktZast.line.lineName,aktZast.destination.NameSide,aktZast.stopPoint.NameSide );
        ledSetTextRear(aktZast.line.lineName);
        ledSetTextInner(aktZast.line.lineName,aktZast.destination.NameInner, aktZast.stopPoint.NameInner);

        textyBocniPanelkIteraci=ledStopPointToViapointListSide(aktZast);
        textyVnitrniPanelkIteraci=ledStopPointToViapointListInner(aktZast);
    }

    ledUpdateDisplaySizes();


}


QVector<Vdv301DisplayContent> MainWindow::ledUpdateCurrentStopToDisplayContentList2_3(QVector<Vdv301StopPoint> &zastavky, VehicleState stav)
{
    //new approach to display viapoint from DisplayContent
    QVector<Vdv301DisplayContent> output;
    qDebug() <<  Q_FUNC_INFO;
    if(!isInRange(stav.currentStopIndex0,zastavky.count()))
    {
        return output;
    }

    Vdv301StopPoint aktZast=zastavky.at(stav.currentStopIndex0);



    output=aktZast.displayContentList;

    return output;

    //   ledUpdateDisplayedInformationFromDisplayContentList2_3(displayContentListAll);
}

void MainWindow::ledUpdateDisplayedInformationFromDisplayContentList2_3(QVector<Vdv301DisplayContent> displayContentListAll )
{
    //new approach to display viapoint from DisplayContent
    qDebug() <<  Q_FUNC_INFO;


    QVector<Vdv301DisplayContent> displayContentListFront;
    QVector<Vdv301DisplayContent> displayContentListSide;
    QVector<Vdv301DisplayContent> displayContentListRear;
    QVector<Vdv301DisplayContent> displayContentListInner;
    QVector<Vdv301DisplayContent> displayContentListLcd; //might be replaced with Inner

    foreach(Vdv301DisplayContent selectedDisplayContent, displayContentListAll)
    {
        switch(selectedDisplayContent.displayContentType)
        {
        case DisplayContentFront:
            displayContentListFront.append(selectedDisplayContent);
            break;
        case DisplayContentSide:
            displayContentListSide.append(selectedDisplayContent);
            break;
        case DisplayContentRear:
            displayContentListRear.append(selectedDisplayContent);
            break;
        case DisplayContentLcd:
            displayContentListLcd.append(selectedDisplayContent);
            break;
        case DisplayContentInner:
            displayContentListInner.append(selectedDisplayContent);
            break;
        case DisplayContentUndefined:
            qDebug()<<"undefined displayContent";
            break;
        default:
            break;


        }

    }

    frontDisplay.displayContentList=displayContentListFront;
    sideDisplay.displayContentList=displayContentListSide;
    rearDisplay.displayContentList=displayContentListRear;


    ledUpdateDisplaySizes();

    frontDisplay.ticker=0;
    sideDisplay.ticker=0;
    rearDisplay.ticker=0;


    tickLedPanels2_3();
    timerLedSideCycleViaPoints->start();

}

void MainWindow::tickLedPanels2_3()
{

    labelVykreslovani.ledDisplaySetDisplayContent(frontDisplay);
    labelVykreslovani.ledDisplaySetDisplayContent(sideDisplay);
    labelVykreslovani.ledDisplaySetDisplayContent(rearDisplay);


}
/*
void MainWindow::ledCycleDisplayContents()
{

}
*/


QVector<QString> MainWindow::ledStopPointToViapointListSide(StopPointDestination selectedStopPointDestination)
{
    qDebug() <<  Q_FUNC_INFO;
    QVector<QString> output;
    output.append("přes:");
    foreach (StopPoint viaPoint,selectedStopPointDestination.viaPoints)
    {
        output.append(viaPoint.NameSide);
        // qDebug()<<"pridavam nacestnou na bocni"<<nacesta.NameSide;
    }
    return output;

}

QVector<QString> MainWindow::ledStopPointToViapointListInner(StopPointDestination selectedStopPointDestination)
{
    qDebug() <<  Q_FUNC_INFO;
    QVector<QString> output;
    output.append("přes:");
    foreach (StopPoint viaPoint,selectedStopPointDestination.viaPoints)
    {
        output.append(viaPoint.NameInner);
        qDebug()<<"pridavam nacestnou na bocni"<<viaPoint.NameSide;
    }
    return output;

}


void MainWindow::ledIterateAllDisplays()
{
    // qDebug()<<"MainWindow::iterujVsechnyPanely()";
    ledIterateSide(textyBocniPanelkIteraci,currentPageIndexLed);
    ledIterateInner(textyVnitrniPanelkIteraci,currentPageIndexLed);




}

void MainWindow::ledIterateSide(QVector<QString> texty, int &iteracniIndex)
{
    // qDebug()<<"MainWindow::iterujBocniPanel";

    if(iteracniIndex<texty.length())
    {
        ui->labelSideBottomRow->setText(texty.at(iteracniIndex));
        ledAlignTextOverflow(ui->labelSideBottomRow);

        //  iteracniIndex++;

    }
    else
    {
        //   iteracniIndex=0;
    }
}

void MainWindow::ledIterateInner(QVector<QString> texty, int &iteracniIndex)
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




void MainWindow::showPageFareZoneChange(QVector<FareZone> zPasem, QVector<FareZone> naPasma)
{
    qDebug() <<  Q_FUNC_INFO;
    displayLabelShowFareZoneChange(zPasem,naPasma);
    svgVykreslovani.zobrazZmenuPasma(zPasem,naPasma);
}

void MainWindow::displayLabelShowFareZoneChange(QVector<FareZone> fromFareZoneList, QVector<FareZone> toFareZoneList)
{
    qDebug() <<  Q_FUNC_INFO;

    ui->stackedWidget_obrazovka->setCurrentWidget(ui->page_hlavni);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_zmenaPasma);

    ui->label_pasmo1->setText(SvgVykreslovani::pasmaDoStringu(FareZone::filterZonesFromSystem(fromFareZoneList,"PID")));
    ui->label_pasmo2->setText(SvgVykreslovani::pasmaDoStringu(FareZone::filterZonesFromSystem(toFareZoneList,"PID")));

    labelVykreslovani.naplnZmenaLabel(labelVykreslovani.vyrobTextZmenyPasma(fromFareZoneList,toFareZoneList),ui->label_zmena);
}


void MainWindow::displayLabelShowPageSpecialAnnouncement(QString title,QString type,QString textCz, QString textEn)
{
    qDebug() <<  Q_FUNC_INFO;
    displayLabelShowAnnoucement(title,type,textCz,textEn);
    svgVykreslovani.zobrazAnnoucement(title,type,textCz,textEn);
}

void MainWindow::displayLabelShowAnnoucement(QString title,QString type,QString textCz, QString textEn)
{
    qDebug() <<  Q_FUNC_INFO;
    labelVykreslovani.naplnAnouncementLabel(textCz,ui->label_announcement);
    ui->stackedWidget_obrazovka->setCurrentWidget(ui->page_hlavni);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_oznameni);

    ui->label_oznTitle->setText(title);
    ui->label_oznType->setText(  labelVykreslovani.textNaPiktogramOznameni(type,100*ratioPixelPoint));
    ui->label_oznTextCs->setText(textCz);
    ui->label_oznTextEn->setText(textEn);

}



void MainWindow::hideAnnouncement()
{
    qDebug() <<  Q_FUNC_INFO;
    displayLabelReturnToStopList();
}

void MainWindow::hideFareZoneChange()
{
    qDebug() <<  Q_FUNC_INFO;
    displayLabelReturnToStopList();
}


void MainWindow::displayLabelReturnToStopList()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->stackedWidget_obrazovka->setCurrentWidget(ui->page_hlavni);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_hlavni_2);
    labelVykreslovani.naplnZmenaLabel("",ui->label_zmena);
}


void MainWindow::displayLabelShowPageFinalStop()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->stackedWidget_obrazovka->setCurrentWidget(ui->page_hlavni);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_konecna);

}


int MainWindow::isVehicleOnFinalStop(VehicleState stav, QVector<StopPointDestination> zastavky)
{

    qDebug() <<  Q_FUNC_INFO;
    if((stav.currentStopIndex0==(zastavky.count()-1))&&(stav.locationState==Vdv301Enumerations::LocationStateAtStop))
    {
        return true;
    }
    return false;
}


int MainWindow::isInRange(int index, int limit)
{
    if((index<limit)&&(index>=0))
    {

        return 1;
    }
    else
    {
        QMessageBox msgBox;
        QString errorMessage="value"+QString::number(index)+" is out of range "+ QString::number(limit);
        msgBox.setText(errorMessage);
        qDebug()<<" errorMessage";
        msgBox.exec();


        return 0;
    }

}


void MainWindow::displayLabelConnectionList(QVector<Connection> connectionList)
{
    qDebug() <<  Q_FUNC_INFO;

    foreach(QFrame* label,labelListConnectionDestination)
    {
        label->hide();
    }

    foreach(QFrame* label,labelListConnectionLine)
    {
        label->hide();
    }

    foreach(QFrame* label,labelListConnectionPlatform)
    {
        label->hide();
    }

    foreach(QFrame* label,labelListConnectionDeparture)
    {
        label->hide();
    }

    labelVykreslovani.vymazPoleLabelu(labelListConnectionDestination);
    labelVykreslovani.vymazPoleLabelu(labelListConnectionLine);
    labelVykreslovani.vymazPoleLabelu(labelListConnectionPlatform);
    labelVykreslovani.vymazPoleLabelu(labelListConnectionDeparture);





    for (int i=0;i<labelVykreslovani.minimum(connectionList.count(), labelListConnectionDestination.count()) ; i++)
    {
        Connection aktualniPrestup=connectionList.at(i);
        labelListConnectionDestination.at(i)->setText(aktualniPrestup.destinationName);
        labelListConnectionDestination.at(i)->show();



        if(cisSubscriber.version()=="2.3")
        {
            displayLabelDrawLineNumber2_4(aktualniPrestup.subMode,aktualniPrestup.line, labelListConnectionLine.at(i), sizeIconConnectionDynamic,true);

        }
        else
        {
            displayLabelDrawLineNumber(aktualniPrestup.subMode,aktualniPrestup.line, labelListConnectionLine.at(i),sizeIconConnectionDynamic,true);
        }


        labelListConnectionPlatform.at(i)->setText(aktualniPrestup.platform );
        labelListConnectionPlatform.at(i)->show();

        labelListConnectionDeparture.at(i)->setText("<b>"+ QString::number( aktualniPrestup.getMinutesToDeparture(QDateTime::currentDateTime() ))+"</b> min.");
        labelListConnectionDeparture.at(i)->show();
    }
}


void MainWindow::displayLabelDrawLineNumber( QString subMode, Line line, QLabel* label, int iconSize,bool isConnection)
{
    qDebug()<<Q_FUNC_INFO;
    QString linkaStyleSheetStandard="font-weight: bold;";

    if(isConnection)
    {
        linkaStyleSheetStandard+="border-radius:6px;padding: 5px; ";
    }


    QString linkaStyleSheetPiktogram="border-radius:6px; padding: 0px; margin: 0px; font-weight: bold;";



    QString nahrazeno=labelVykreslovani.nahradMetro(line.lineName,subMode,iconSize);

    //defaultni seda barva na bile pozadi, neznama kombinace

    StylLinkyOld stylLinky;



    stylLinky.pozadi="background-color:"+barvyLinek.barva_bila_255_255_255+";";


    stylLinky.text="color:"+barvyLinek.barva_PozadiD_150_150_150+";";




    if(nahrazeno==line.lineName)
    {
        stylLinky=barvyLinek.linkaDoStylu(subMode,line);

        label->setStyleSheet(linkaStyleSheetStandard+stylLinky.text+stylLinky.pozadi);
        label->setText(line.lineName);
    }
    else
    {
        label->setStyleSheet(linkaStyleSheetPiktogram);
        label->setText(nahrazeno);
        //   qDebug()<<"nahrazeny retezec metra:"<<nahrazeno;
    }



    label->show();
}

void MainWindow::displayLabelDrawLineNumber2_4( QString subMode, Line line, QLabel* label, int velikostPiktogramu,bool prestup)
{
    qDebug()<<Q_FUNC_INFO;


    QString linkaStyleSheetStandard="font-weight: bold; background-color:#ffffff; padding: 0px; margin: 0px; ";

    if(prestup)
    {
        linkaStyleSheetStandard+="border-radius:6px;padding: 0px; ";
    }


    QString linkaStyleSheetPiktogram="border-radius:6px; padding: 0px; margin: 0px; font-weight: bold;";


    label->setStyleSheet(linkaStyleSheetStandard);

    QString vyslednyText= labelVykreslovani.inlineFormatParser.parseTextLcd(line.lineName, label->font().pixelSize(),labelVykreslovani.slozkaPiktogramu);
    label->setText( vyslednyText);


    qDebug().noquote()<<"obsah pole linky: "<<vyslednyText;
    label->show();
}



void MainWindow::slotDisplayLcdLabelCyclePages()
{
    qDebug() <<  Q_FUNC_INFO<<" counter ma hodnotu "<<currentPageIndex<<" v seznamu je "<<pageCycleList.count();

    if(currentPageIndex==(pageCycleList.count()-1))
    {
        currentPageIndex=0;
    }
    else
    {
        currentPageIndex++;
    }


    if(currentPageIndex<pageCycleList.count())
    {
        ui->stackedWidget_prostredek->setCurrentWidget(pageCycleList.at(currentPageIndex));

    }



}

void MainWindow::slotToggleFullscreen()
{
    qDebug() <<  Q_FUNC_INFO;
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

    ledUpdateDisplaySizes();




}


void MainWindow::lcdResizeLabels()
{
    qDebug() <<  Q_FUNC_INFO;
    this->show();
    ratioPixelPoint=ui->frame_hlavni->height()/1050.0;

    sizeIconConnectionDynamic=qFloor(sizeIconConnection*ratioPixelPoint);


    labelVykreslovani.labelNastavVelikost(ui->Lcil,sizeFontDestination,ratioPixelPoint ); //100
    labelVykreslovani.labelNastavVelikost(ui->label_nacestne,sizeFontViaPoints,ratioPixelPoint); //72

    labelVykreslovani.poleLabelNastavVelikost(labelListStopPointName,sizeFontFollowing,ratioPixelPoint); //100

    labelVykreslovani.poleLabelNastavVelikost(labelListConnectionLine,sizeFontTransferLine,ratioPixelPoint); //48
    labelVykreslovani.poleLabelNastavSirku(labelListConnectionLine,ratioPixelPoint*sizeConnectionFrameWidth); //95
    labelVykreslovani.poleLabelNastavVysku(labelListConnectionLine,ratioPixelPoint*sizeConnectionFrameHeight); //65

    labelVykreslovani.poleLabelNastavVelikost(labelListConnectionDestination,sizeFontTransferDestination,ratioPixelPoint); //36
    labelVykreslovani.poleLabelNastavVelikost(labelListConnectionPlatform,sizeFontTransferDestination,ratioPixelPoint); //36
    labelVykreslovani.poleLabelNastavVelikost(labelListConnectionDeparture,sizeFontTransferDestination,ratioPixelPoint); //36

    labelVykreslovani.labelNastavVelikost(ui->label_hodiny,80,ratioPixelPoint); //80
    labelVykreslovani.labelNastavVelikost(ui->label_textPres,30,ratioPixelPoint); //30
    labelVykreslovani.labelNastavVelikost(ui->label_textVia ,30,ratioPixelPoint); //30
    /*
    labelVykreslovani.labelNastavVelikost(,,);
    labelVykreslovani.labelNastavVelikost(,,);
    labelVykreslovani.labelNastavVelikost(,,);
    labelVykreslovani.labelNastavVelikost(,,);
    */
    labelVykreslovani.zmensiCisloLinkyLabel(ui->label_linka);

}

void MainWindow::on_pushButton_menu_fullscreen_clicked()
{
    slotToggleFullscreen();
}

void MainWindow::slotDeviceParametersToConfigFile()
{
    qDebug()<<Q_FUNC_INFO;

    deviceManagementServiceInternalVariablesToSettingFile();
    constantsToSettingsPage();
    updateMainScreenDebugLabels();
}

void MainWindow::deviceManagementServiceInternalVariablesToSettingFile()
{
    settings.setValue("deviceManagementService/deviceName",deviceManagementService.deviceName());
    settings.setValue("deviceManagementService/deviceManufacturer",deviceManagementService.deviceManufacturer());
    settings.setValue("deviceManagementService/deviceSerialNumber",deviceManagementService.deviceSerialNumber());
    settings.setValue("deviceManagementService/deviceClass",deviceManagementService.deviceClass());
    settings.setValue("deviceManagementService/deviceId",deviceManagementService.deviceId());
    settings.setValue("deviceManagementService/version",deviceManagementService.version());

}


void MainWindow::ledSetWindowSizeDot(QLabel * label, int lengthDotCount, int heightDotCount, float coeficient)
{
    //int koeficient = pomer pixel:pocetDotu
    label->setFixedHeight(float(heightDotCount)*coeficient);
    label->setFixedWidth(float(lengthDotCount)*coeficient);
}


void MainWindow::ledUpdateDisplaySizes()
{
    qDebug()<<Q_FUNC_INFO;

    const int cilSirka=108;
    const int cilVyskaVelky=19;

    const int vyskaHorniRadek=9;
    const int vyskaDolniRadek=10;


    const int linkaSirka=30;
    const int linkaVyska=19;


    const int linkaVnitrniSirka=22;
    const int linkaVnitrniVyska=8;

    const int vyskaVnitrniHorniRadek=8;
    const int vyskaVnitrniDolniRadek=8;

    const int sirkaVnitrniHorniRadek=113;
    const int sirkaVnitrniDolniRadek=135;

    const int cilBocniSirka=82;


    int velikostFontu=fontLed8.pointSize();
    int vyskaLinky=ui->labelFrontLine->height();
    float pomerFontuKvysce=float(velikostFontu)/float(vyskaLinky);

    ratioPixelLed=ui->labelFrontSingle->width() /(float(cilSirka)); //A

    ui->spinBox_frontSignWidth->setValue(ui->labelFrontSingle->width());

    float novaVyskaLinky=float(linkaVyska)*ratioPixelLed;
    float staraVyskaLinky=78.0;

    float novaVelikostFontu=65*(novaVyskaLinky/staraVyskaLinky);


    ui->labelFrontSingle->setFixedHeight(float(cilVyskaVelky)*ratioPixelLed);

    ui->labelFrontBottomRow->setFixedHeight(float(vyskaDolniRadek)*ratioPixelLed);
    ui->labelFrontTopRow->setFixedHeight(float(vyskaHorniRadek)*ratioPixelLed);

    ledSetWindowSizeDot(ui->labelFrontLine,linkaSirka,linkaVyska,ratioPixelLed);

    ledSetWindowSizeDot(ui->labelSideLine,linkaSirka,linkaVyska,ratioPixelLed);
    ledSetWindowSizeDot(ui->labelSideTopRow,cilBocniSirka,vyskaHorniRadek,ratioPixelLed);
    ledSetWindowSizeDot(ui->labelSideBottomRow,cilBocniSirka,vyskaDolniRadek,ratioPixelLed);

    ledSetWindowSizeDot(ui->labelRearLine,linkaSirka,linkaVyska,ratioPixelLed);

    ledSetWindowSizeDot(ui->labelInnerLine,linkaVnitrniSirka,linkaVnitrniVyska,ratioPixelLed);

    ledSetWindowSizeDot(ui->labelInnerTopRow,sirkaVnitrniHorniRadek,vyskaVnitrniHorniRadek,ratioPixelLed);
    ledSetWindowSizeDot(ui->labelInnerBottomRow,sirkaVnitrniDolniRadek,vyskaVnitrniDolniRadek,ratioPixelLed);




    qDebug()<<"pomer vysky: "<<pomerFontuKvysce; //pomer vysky:  0.833333

    fontLed1.setPointSize(novaVelikostFontu);
    fontLed3.setPointSize(novaVelikostFontu);
    fontLed5.setPointSize(novaVelikostFontu);
    fontLed8.setPointSize(novaVelikostFontu);
    fontLed10.setPointSize(novaVelikostFontu);

    ledInitializeFormat();
}

void MainWindow::popUpMessage(QString messageContent)
{
    qDebug() <<  Q_FUNC_INFO;
    QMessageBox msgBox;
    msgBox.setText(messageContent);
    QFont font;
    //font.setBold(true);
    font.setPointSize(30);
    msgBox.setFont(font);
    // msgBox.setStyleSheet("font-size: 30px;");
    msgBox.exec();
}


QVector<StopPointDestination> MainWindow::vektorZastavkaCilZahoditZacatek(QVector<StopPointDestination> vstup, int zacatek)
{
    QVector<StopPointDestination> vystup;
    for(int i=zacatek;i<vstup.count();i++)
    {
        if(i>zacatek)
        {
            vystup.push_back(vstup.at(i));
            // qDebug()<<"orez zastavek:"<<vstup.at(i).stopPoint.NameLcd;
        }

    }
    return vystup;

}

void MainWindow::on_pushButton_unsubscribe_clicked()
{
    cisSubscriber.unsubscribe();

    slotSubscriptionLost();

}





void MainWindow::on_pushButton_menu_refresh_clicked()
{
    //the button is disabled by default
    qDebug() <<  Q_FUNC_INFO;

    //  CustomerInformationServiceSubscriber.odebirano=false ;
    //  CustomerInformationServiceSubscriber.hledejSluzby("_ibisip_http._tcp.",1);
    this->eraseDisplayedInformation();
    slotUpdateServiceTable();
    //xmlDoPromenne(1);


    eraseDisplayedInformation();
    cisSubscriber.newSubscribeRequest();
}


void MainWindow::on_radioButton_stateDefective_clicked()
{
    deviceManagementService.setDeviceStatus(DeviceManagementService::StateDefective);
    deviceManagementService.slotDataUpdate();
}


void MainWindow::on_radioButton_stateWarning_clicked()
{
    deviceManagementService.setDeviceStatus(DeviceManagementService::StateWarning);
    deviceManagementService.slotDataUpdate();
}


void MainWindow::on_radioButton_stateNotAvailable_clicked()
{
    deviceManagementService.setDeviceStatus(DeviceManagementService::StateNotavailable);
    deviceManagementService.slotDataUpdate();
}


void MainWindow::on_radioButton_stateRunning_clicked()
{
    deviceManagementService.setDeviceStatus(DeviceManagementService::StateRunning);
    deviceManagementService.slotDataUpdate();
}


void MainWindow::on_radioButton_stateReadyForShutdown_clicked()
{
    deviceManagementService.setDeviceStatus(DeviceManagementService::StateReadyForShutdown);
    deviceManagementService.slotDataUpdate();
}


void MainWindow::on_pushButton_settings_save_clicked()
{
    settingsWindowToSettingsFile();
}


void MainWindow::on_radioButton_settings_languageCs_clicked()
{
    retranslateUi("cs");
}


void MainWindow::on_radioButton_settings_languageEn_clicked()
{
    retranslateUi("en");
}


void MainWindow::on_spinBox_frontSignWidth_valueChanged(int arg1)
{
    ui->labelFrontSingle->setFixedWidth(ui->spinBox_frontSignWidth->value());
    ledUpdateDisplaySizes();
}

