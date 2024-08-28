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



    displayLabelLcd.slozkaPiktogramu=QCoreApplication::applicationDirPath()+"/icons";

    initilializeFonts();

    initilializeShortcuts();

    loadConstants();
    constantsToSettingsPage();
    updateMainScreenDebugLabels();

    allConnects();



    //ui->prepinadloStran->setCurrentWidget(ui->page_hlavniObrazovka);

    displayLabelFillArray(); //naplni pointery na labely do pole, aby se nimi dalo iterovat
    ledLabelInitialize2_3();
    lcdLabelInitialize2_3();


    labelUpdateFormat();
    displayLabelLcd.lcdResizeLabels(ui->frame_hlavni->height());

    stopRequestedDectivated();

    displayAbnormalStateScreen("NO SUBSCRIPTION");



    cisSubscriber.isSubscriptionActive=false ;

    cisSubscriber.start();

    cisSubscriber.newSubscribeRequest();

    updateMainScreenDebugLabels();



    displayLabelLed.ledInitializeFormat();

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

    timerUpdateSeconds.start(1000); //refresh vterin
    displayLabelLed.timerLedSideCycleViaPoints.start(intervalSideDisplay);



    timerDelayedStart.setInterval(intervalDelayedStart);
    timerDelayedStart.setSingleShot(true);
    timerDelayedStart.start();
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


    displayLabelLed.initializeFonts();

    displayLabelLcd.initializeFonts();

}

void MainWindow::ledLabelInitialize2_3()
{
    displayLabelLed.frontDisplay.lineLabel=ui->labelFrontLine;
    displayLabelLed.frontDisplay.destinationLabel=ui->labelFrontSingle;
    displayLabelLed.frontDisplay.destination1Label=ui->labelFrontTopRow;
    displayLabelLed.frontDisplay.destination2Label=ui->labelFrontBottomRow;
    displayLabelLed.frontDisplay.ticker=0;

    displayLabelLed.sideDisplay.lineLabel=ui->labelSideLine;
    displayLabelLed.sideDisplay.destinationLabel=ui->labelSideSingle;
    displayLabelLed.sideDisplay.destination1Label=ui->labelSideTopRow;
    displayLabelLed.sideDisplay.destination2Label=ui->labelSideBottomRow;
    displayLabelLed.sideDisplay.ticker=0;

    displayLabelLed.rearDisplay.lineLabel=ui->labelRearLine;
    displayLabelLed.rearDisplay.destinationLabel=NULL;
    displayLabelLed.rearDisplay.destination1Label=NULL;
    displayLabelLed.rearDisplay.destination2Label=NULL;
    displayLabelLed.rearDisplay.ticker=0;


    displayLabelLed.innerDisplay.lineLabel=ui->labelInnerLine;
    displayLabelLed.innerDisplay.destinationLabel=NULL;
    displayLabelLed.innerDisplay.destination1Label=ui->labelInnerTopRow;
    displayLabelLed.innerDisplay.destination2Label=ui->labelInnerBottomRow;
    displayLabelLed.rearDisplay.ticker=0;

}

void MainWindow::lcdLabelInitialize2_3()
{
    displayLabelLcd.labelDestination=ui->Lcil;
    displayLabelLcd.labelLine=ui->label_linka;
    displayLabelLcd.labelViaPointsScrolling=ui->label_nacestne;
    displayLabelLcd.labelClock=ui->label_hodiny;
    displayLabelLcd.frameFollowingTrip=ui->frame_navaznySpoj;

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
        displayLabelLed.setVdv301version(vdv301version);
        displayLabelLcd.setVdv301version(vdv301version);
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


    connect(&timerUpdateSeconds, &QTimer::timeout, this, &MainWindow::slotEverySecond);



    connect(&displayLabelLcd.timerLabelPageSwitch, &QTimer::timeout, this, &MainWindow::slotDisplayLcdLabelCyclePages);
    connect(&displayLabelLcd.timerScrollingText, &QTimer::timeout, this, &MainWindow::slotMoveScrollingText);
    connect(&timerDelayedStart, &QTimer::timeout, this, &MainWindow::slotDelayedStartup);

    connect(&displayLabelLed, &DisplayLabelLed::signalFrontDisplayWidthChanged, ui->spinBox_frontSignWidth, &QSpinBox::setValue);
    //ui->spinBox_frontSignWidth->setValue(frontDisplay.destinationLabel->width());
    //emit signalFrontDisplayWidthChanged(frontDisplay.destinationLabel->width());


    if(cisSubscriber.version()=="2.3")
    {
        connect(&displayLabelLed.timerLedSideCycleViaPoints, &QTimer::timeout, &displayLabelLed, &DisplayLabelLed::slotTickLedPanels2_3);

    }
    else
    {
        connect(&displayLabelLed.timerLedSideCycleViaPoints, &QTimer::timeout, &displayLabelLed, &DisplayLabelLed::slotLedIterateAllDisplays);
    }

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
    displayLabelLcd.labelListStopPointName.push_back(ui->Lnacestna1);
    displayLabelLcd.labelListStopPointName.push_back(ui->Lnacestna2);
    displayLabelLcd.labelListStopPointName.push_back(ui->Lnacestna3);
    displayLabelLcd.labelListStopPointName.push_back(ui->Lnacestna4);
    displayLabelLcd.labelListStopPointName.push_back(ui->Lnacestna5);

    displayLabelLcd.labelListFareZoneUpper.push_back(ui->label_pasmo1_1);
    displayLabelLcd.labelListFareZoneUpper.push_back(ui->label_pasmo2_1);
    displayLabelLcd.labelListFareZoneUpper.push_back(ui->label_pasmo3_1);
    displayLabelLcd.labelListFareZoneUpper.push_back(ui->label_pasmo4_1);
    displayLabelLcd.labelListFareZoneUpper.push_back(ui->label_pasmo5_1);

    displayLabelLcd.labelListFareZoneLower.push_back(ui->label_pasmo1_2);
    displayLabelLcd.labelListFareZoneLower.push_back(ui->label_pasmo2_2);
    displayLabelLcd.labelListFareZoneLower.push_back(ui->label_pasmo3_2);
    displayLabelLcd.labelListFareZoneLower.push_back(ui->label_pasmo4_2);
    displayLabelLcd.labelListFareZoneLower.push_back(ui->label_pasmo5_2);


    displayLabelLcd.labelListConnectionDestination .push_back(ui->label_prestup0_cil);
    displayLabelLcd.labelListConnectionDestination.push_back(ui->label_prestup1_cil);
    displayLabelLcd.labelListConnectionDestination.push_back(ui->label_prestup2_cil);
    displayLabelLcd.labelListConnectionDestination.push_back(ui->label_prestup3_cil);
    displayLabelLcd.labelListConnectionDestination.push_back(ui->label_prestup4_cil);
    displayLabelLcd.labelListConnectionDestination.push_back(ui->label_prestup5_cil);
    displayLabelLcd.labelListConnectionDestination.push_back(ui->label_prestup6_cil);
    displayLabelLcd.labelListConnectionDestination.push_back(ui->label_prestup7_cil);
    displayLabelLcd.labelListConnectionDestination.push_back(ui->label_prestup8_cil);
    displayLabelLcd.labelListConnectionDestination.push_back(ui->label_prestup9_cil);
    displayLabelLcd.labelListConnectionDestination.push_back(ui->label_prestup10_cil);
    displayLabelLcd.labelListConnectionDestination.push_back(ui->label_prestup11_cil);

    displayLabelLcd.labelListConnectionLine.push_back(ui->label_prestup0_linka);
    displayLabelLcd.labelListConnectionLine.push_back(ui->label_prestup1_linka);
    displayLabelLcd.labelListConnectionLine.push_back(ui->label_prestup2_linka);
    displayLabelLcd.labelListConnectionLine.push_back(ui->label_prestup3_linka);
    displayLabelLcd.labelListConnectionLine.push_back(ui->label_prestup4_linka);
    displayLabelLcd.labelListConnectionLine.push_back(ui->label_prestup5_linka);
    displayLabelLcd.labelListConnectionLine.push_back(ui->label_prestup6_linka);
    displayLabelLcd.labelListConnectionLine.push_back(ui->label_prestup7_linka);
    displayLabelLcd.labelListConnectionLine.push_back(ui->label_prestup8_linka);
    displayLabelLcd.labelListConnectionLine.push_back(ui->label_prestup9_linka);
    displayLabelLcd.labelListConnectionLine.push_back(ui->label_prestup10_linka);
    displayLabelLcd.labelListConnectionLine.push_back(ui->label_prestup11_linka);

    displayLabelLcd.labelListConnectionDeparture.push_back(ui->label_prestup0_odjezd);
    displayLabelLcd.labelListConnectionDeparture.push_back(ui->label_prestup1_odjezd);
    displayLabelLcd.labelListConnectionDeparture.push_back(ui->label_prestup2_odjezd);
    displayLabelLcd.labelListConnectionDeparture.push_back(ui->label_prestup3_odjezd);
    displayLabelLcd.labelListConnectionDeparture.push_back(ui->label_prestup4_odjezd);
    displayLabelLcd.labelListConnectionDeparture.push_back(ui->label_prestup5_odjezd);
    displayLabelLcd.labelListConnectionDeparture.push_back(ui->label_prestup6_odjezd);
    displayLabelLcd.labelListConnectionDeparture.push_back(ui->label_prestup7_odjezd);
    displayLabelLcd.labelListConnectionDeparture.push_back(ui->label_prestup8_odjezd);
    displayLabelLcd.labelListConnectionDeparture.push_back(ui->label_prestup9_odjezd);
    displayLabelLcd.labelListConnectionDeparture.push_back(ui->label_prestup10_odjezd);
    displayLabelLcd.labelListConnectionDeparture.push_back(ui->label_prestup11_odjezd);

    displayLabelLcd.labelListConnectionPlatform.push_back(ui->label_prestup0_nastupiste);
    displayLabelLcd.labelListConnectionPlatform.push_back(ui->label_prestup1_nastupiste);
    displayLabelLcd.labelListConnectionPlatform.push_back(ui->label_prestup2_nastupiste);
    displayLabelLcd.labelListConnectionPlatform.push_back(ui->label_prestup3_nastupiste);
    displayLabelLcd.labelListConnectionPlatform.push_back(ui->label_prestup4_nastupiste);
    displayLabelLcd.labelListConnectionPlatform.push_back(ui->label_prestup5_nastupiste);
    displayLabelLcd.labelListConnectionPlatform.push_back(ui->label_prestup6_nastupiste);
    displayLabelLcd.labelListConnectionPlatform.push_back(ui->label_prestup7_nastupiste);
    displayLabelLcd.labelListConnectionPlatform.push_back(ui->label_prestup8_nastupiste);
    displayLabelLcd.labelListConnectionPlatform.push_back(ui->label_prestup9_nastupiste);
    displayLabelLcd.labelListConnectionPlatform.push_back(ui->label_prestup10_nastupiste);
    displayLabelLcd.labelListConnectionPlatform.push_back(ui->label_prestup11_nastupiste);

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
    displayLabelLcd.displayLabelEraseInformation();
    svgVykreslovani.vymazObrazovku();
    displayLabelLed.ledClearDisplays();
}




int MainWindow::showReceivedData()
{
    qDebug() <<  Q_FUNC_INFO;



    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_hlavni_2);
    eraseTable(ui->tableWidget_debugStopList);

    displayLabelLcd.displayLabelEraseInformation();
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


    displayLabelLcd.displayLabelDestination(nazevCile);
    displayLabelLcd.displayLabelLineName(currentDestinationPointList.at(vehicleState.currentStopIndex0),vehicleState.vehicleSubMode);
    displayLabelLcd.displayLabelStopFareZone(currentDestinationPointList,nextDestinationPointList,vehicleState);
    displayLabelLcd.displayLabelViaPoints(currentDestinationPointList,vehicleState);

    displayLabelLcd.pageCycleList.clear();

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
        displayLabelLcd.pageCycleList.push_back(ui->page_oznameni);
    }
    else
    {
        displayLabelLcd.naplnAnouncementLabel("",ui->label_announcement);
    }

    //konecna

    if(isVehicleOnFinalStop(vehicleState,currentDestinationPointList)&&(!xmlParser.existujeNavaznySpoj(nextDestinationPointList)))
    {
        displayLabelLcd.pageCycleList.push_front(ui->page_konecna);
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
            displayLabelLcd.pageCycleList.push_front(ui->page_hlavni_2);
            // skryjZmenuPasma();
        }

    }

    if(!currentDestinationPointList.at(vehicleState.currentStopIndex0).stopPoint.connectionList.isEmpty())
    {
        displayLabelLcd.pageCycleList.push_back(ui->page_prestupy);
        displayLabelLcd.displayLabelConnectionList(currentDestinationPointList.at(vehicleState.currentStopIndex0).stopPoint.connectionList);
    }

    //   hlavniVykresliNasledne();

    labelUpdateFormat();
    displayLabelLcd.lcdResizeLabels(ui->frame_hlavni->height());
    lcdLabelCurrentPageIndex=0;
    displayLabelLcd.timerLabelPageSwitch.start();

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






int MainWindow::setDestinationName()
{
    qDebug() <<  Q_FUNC_INFO;
    // qInfo()<<"\n DoplneniPromennych";


    if ((currentDestinationPointList.size()>stopIndex)&&(stopIndex>=0))
    {
        StopPointDestination aktualniZastavka=currentDestinationPointList.at(stopIndex);

        if((cisSubscriber.version()=="2.3")||(cisSubscriber.version()=="2.3CZ1.0"))
        {
            nazevCile=displayLabelLcd.inlineFormatParser.parseTextLcd(aktualniZastavka.destination.NameLcd,ui->Lcil->font().pixelSize(),displayLabelLcd.slozkaPiktogramu);
        }
        else
        {
            nazevCile=displayLabelLcd.zabalHtmlDoZnacek(displayLabelLcd.doplnPiktogramyBezZacatkuKonce(aktualniZastavka.destination.NameLcd,aktualniZastavka.destination.iconList,ui->Lcil->font().pixelSize()));
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
            displayLabelLed.ledUpdateDisplayedInformationFromDisplayContentList2_3(vdv301AllData.globalDisplayContentList);
            return;
        }

    }

    else if(cisSubscriber.version()=="2.3CZ1.0")
    {

        vdv301AllData=xmlParser.parseAllData2_3(xmlParser.dokument,currenVdv301StopPointList);

        if(!xmlParser.VytvorSeznamZastavek2_3(currentDestinationPointList,nextDestinationPointList, stopIndex))
        {
            notOnLine();
            displayLabelLed.ledUpdateDisplayedInformationFromDisplayContentList2_3(vdv301AllData.globalDisplayContentList);
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
                    displayLabelLed.ledUpdateDisplayedInformationFromDisplayContentList2_3(displayLabelLed.ledUpdateCurrentStopToDisplayContentList2_3(currenVdv301StopPointList,vehicleState));

                }
                else if(cisSubscriber.version()=="2.3CZ1.0")
                {
                    if(vdv301AllData.globalDisplayContentList.isEmpty())
                    {
                        displayLabelLed.ledUpdateDisplayedInformationFromDisplayContentList2_3(displayLabelLed.ledUpdateCurrentStopToDisplayContentList2_3(currenVdv301StopPointList,vehicleState));
                    }
                    else
                    {
                        displayLabelLed.ledUpdateDisplayedInformationFromDisplayContentList2_3(vdv301AllData.globalDisplayContentList);
                        return;
                    }

                }
                else
                {
                    displayLabelLed.ledUpdateDisplayedInformation(currentDestinationPointList,vehicleState);
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
    displayLabelLcd.lcdResizeLabels(ui->frame_hlavni->height());
}

void MainWindow::on_pushButton_menu_timer_clicked()
{
    ui->prepinadloStran->setCurrentWidget(ui->page_casovac);
}

void MainWindow::labelSetNextStopBackground(QString barvaPisma,QString barvaPozadi)
{
    qDebug() <<  Q_FUNC_INFO;
    //
    displayLabelLcd.obarviPozadiPristi(barvaPisma,barvaPozadi,ui->frame_spodniRadek);
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






/*
void MainWindow::ledCycleDisplayContents()
{

}
*/




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

    displayLabelLcd.naplnZmenaLabel(displayLabelLcd.vyrobTextZmenyPasma(fromFareZoneList,toFareZoneList),ui->label_zmena);
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
    displayLabelLcd.naplnAnouncementLabel(textCz,ui->label_announcement);
    ui->stackedWidget_obrazovka->setCurrentWidget(ui->page_hlavni);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_oznameni);

    ui->label_oznTitle->setText(title);
    ui->label_oznType->setText(  displayLabelLcd.textNaPiktogramOznameni(type,100*displayLabelLcd.ratioPixelPoint));
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
    displayLabelLcd.naplnZmenaLabel("",ui->label_zmena);
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

    displayLabelLed.ledUpdateDisplaySizes();




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
    displayLabelLed.ledUpdateDisplaySizes();
}



void MainWindow::slotMoveScrollingText()
{
    int textWidthPixels=displayLabelLcd.labelViaPointsScrolling->width();
    int stepSize=1;

    if(textWidthPixels<ui->scrollArea->width() )
    {
        return;
    }
    // qDebug()<<"delka beziciho textu "<< delkaTextu << " posun rotovani: "<<posunRotovani;

    displayLabelLcd.scrollingTextOffset-=stepSize;

    if (abs(displayLabelLcd.scrollingTextOffset)>textWidthPixels)
    {
        displayLabelLcd.scrollingTextOffset=0;
        displayLabelLcd.vykresliNacestneForce(currentDestinationPointList,vehicleState,displayLabelLcd.labelViaPointsScrolling,displayLabelLcd.vdv301version());
    }

    else

    {
        ui->scrollAreaWidgetContents->scroll(-stepSize,0);
    }

}

// move to displayLAbelLcd???
void MainWindow::slotDisplayLcdLabelCyclePages()
{
    qDebug() <<  Q_FUNC_INFO<<" counter ma hodnotu "<<lcdLabelCurrentPageIndex<<" v seznamu je "<<displayLabelLcd.pageCycleList.count();

    if(lcdLabelCurrentPageIndex==(displayLabelLcd.pageCycleList.count()-1))
    {
        lcdLabelCurrentPageIndex=0;
    }
    else
    {
        lcdLabelCurrentPageIndex++;
    }


    if(lcdLabelCurrentPageIndex<displayLabelLcd.pageCycleList.count())
    {
        ui->stackedWidget_prostredek->setCurrentWidget(displayLabelLcd.pageCycleList.at(lcdLabelCurrentPageIndex));

    }



}
