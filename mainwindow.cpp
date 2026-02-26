#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "typeconvertor.h"



Q_LOGGING_CATEGORY(MainWindowLog, "MainWindow")


MainWindow::MainWindow(QString configurationFilePath, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    settings(configurationFilePath, QSettings::IniFormat),
    svgVykreslovani(QCoreApplication::applicationDirPath()),
    cisSubscriber("CustomerInformationService","AllData","2.2CZ1.0","_ibisip_http._tcp",48479,"xxx"),//puvodni port 48479, novy 59631
    deviceManagementService("DeviceManagementService","_ibisip_http._tcp",49477,"1.0","_ropid_vdv301display_1_0"), //49477
    golemio("")
{

    logHandler.setRelay(&relay);
    logHandler.setIncludeContextFileLine(false);
    logHandler.install();
    logHandler.setTimestampFormat(QStringLiteral("dd/MM/yyyy hh:mm:ss"));
    logHandler.setCategoryLevels(QStringLiteral("app.net"), 1, 1, 1, 1);

    ui->setupUi(this);
    QString loggingRules="";
    loggingRules+="*=false\n";
    loggingRules+="IbisIpSubscriber=true\n";
    loggingRules+="IbisIpSubscriberOnePublisher=true\n";
    loggingRules+="HttpServerSubscriber=true\n";
    loggingRules+= "*.debug=false\n";

    /*

rules += "*.debug=false\n";
rules += "*.info=true\n";
rules += "*.warning=false\n";
rules += "*.critical=false\n"

*/

    /*
    loggingRules+="DisplayLabel=false\n";
    loggingRules+="DisplayLabelLcd=false\n";
    loggingRules+="DisplayLabelLcd2_3=false\n";
    loggingRules+="DisplayLabelLcd2_3CZ1_0=false\n";
    loggingRules+="DisplayLabelLcd2_3CZ1_0_Jis=false\n";
    loggingRules+="DisplayLabelLed=false\n";
    loggingRules+="InLineFormatParser=false\n";
    loggingRules+="XmlParser=false\n";
    loggingRules+="XmlParser2_3=false\n";
    loggingRules+="MainWindow=false\n";
    loggingRules+="SvgVykreslovani=false\n";
    */




    logHandler.clearCategoryLevels();

    if(logOnStartup)
    {
        QLoggingCategory::setFilterRules(loggingRules);
    }



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

    qCDebug(MainWindowLog)<<"new language:"<<selectedLanguage;

    retranslateUi(selectedLanguage);

    ui->plainTextEdit_debugLogLevel->setPlainText(loggingRules);

    displayLabelLcd.slozkaPiktogramu=QCoreApplication::applicationDirPath()+"/icons";
    displayLabelLcdJis.slozkaPiktogramu=QCoreApplication::applicationDirPath()+"/icons";

    initilializeFonts();

    initilializeShortcuts();

    loadConstants();

    if(blockBonjour)
    {
        setWindowTitle(windowTitle()+" | "+tr("režim bez Bonjour"));
    }

    constantsToSettingsPage();
    updateMainScreenDebugLabels();

    allConnects();



    //ui->prepinadloStran->setCurrentWidget(ui->page_hlavniObrazovka);

    displayLabelFillArray(); //naplni pointery na labely do pole, aby se nimi dalo iterovat
    displayLabelFillArrayJis();
    ledLabelInitialize2_3();
    lcdLabelInitialize2_3();

    displayLabelLcd.timerLabelPageSwitch.setInterval(intervalLcdPageSwitchSeconds*1000);
    displayLabelLcdJis.timerLabelPageSwitch.setInterval(intervalLcdPageSwitchSeconds*1000);

    displayLabelLcd.lcdResizeLabels(ui->frame_hlavni->height());
    //  displayLabelLcdJis.lcdResizeLabels(ui->frame_hlavni->height());

    eventStopRequestedDectivated();

    eventDisplayAbnormalStateScreen("NO SUBSCRIPTION");



    cisSubscriber.isSubscriptionActive=false ;
    cisSubscriber.start();
    cisSubscriber.newSubscribeRequest();

    updateMainScreenDebugLabels();

    displayLabelLed.ledInitializeFormat();

    //
    eraseDisplayedInformation();

    timerUpdateSeconds.start(1000); //refresh vterin
    displayLabelLed.timerLedSideCycleViaPoints.start(intervalSideDisplay);



    timerDelayedStart.setInterval(intervalDelayedStart);
    timerDelayedStart.setSingleShot(true);
    timerDelayedStart.start();

    if(blockBonjour)
    {
        PublisherStruct manualPublisher;
        manualPublisher.hostAddress=QHostAddress::LocalHost;
        manualPublisher.ibisIpVersion=cisSubscriber.version();
        manualPublisher.serviceName="CustomerInformationService";
        manualPublisher.portNumber=47482;

        cisSubscriber.slotAddServiceManual(manualPublisher);
    }


    if(connectionsStandalone)
    {

        connect(&golemio,&Golemio::stazeniHotovo,this,&MainWindow::slotGolemioReady);
        connect(&timerUpdateGolemio,&QTimer::timeout,this,&MainWindow::slotDownloadGolemio);

        timerUpdateGolemio.setInterval(5000);
        timerUpdateGolemio.start();
    }


}

MainWindow::~MainWindow()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    delete ui;
}

void MainWindow::allConnects()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    if(logOnStartup)
    {
      //  connect(&relay, &LoggerRelay::message,this,&MainWindow::slotLogWindowAppend,Qt::QueuedConnection);
        ui->checkBox_debugLogEnable->setChecked(logOnStartup);
    }



    connect(&cisSubscriber, &IbisIpSubscriber::signalDataReceived  ,this, &MainWindow::slotXmlToVehicleStateVariables);
    connect(&cisSubscriber,&IbisIpSubscriber::signalUpdateDeviceList,this,&MainWindow::slotUpdateServiceTable);
    connect(&cisSubscriber.timerHeartbeatCheck,&QTimer::timeout ,this,&MainWindow::slotHeartbeatTimeout);
    connect(&cisSubscriber,&IbisIpSubscriber::signalSubscriptionLost ,this,&MainWindow::slotSubscriptionLost);
    connect(&cisSubscriber,&IbisIpSubscriberOnePublisher::signalSubscriptionSuccessful,this,&MainWindow::slotDebugPublisherToTable);
    connect(&cisSubscriber,&IbisIpSubscriber::signalAddressUpdate,this,&MainWindow::slotDeviceIpUpdated);

    connect(this,&MainWindow::signalStopRefUpdate,this,&MainWindow::slotStopRefUpdate);
    connect(this,&MainWindow::signalVehicleRefUpdate,this,&MainWindow::slotVehicleRefUpdate);


    connect(&deviceManagementService,&DeviceManagementService::signalParametersChanged,this,&MainWindow::slotDeviceParametersToConfigFile);


    connect(&timerUpdateSeconds, &QTimer::timeout, this, &MainWindow::slotEverySecond);



    connect(&displayLabelLcd.timerLabelPageSwitch, &QTimer::timeout, this, &MainWindow::slotDisplayLcdLabelCyclePages);
    connect(&displayLabelLcd.timerScrollingText, &QTimer::timeout, this, &MainWindow::slotMoveScrollingText);
    connect(&displayLabelLcdJis.timerLabelPageSwitch, &QTimer::timeout, this, &MainWindow::slotDisplayLcdLabelCyclePagesJis);
    connect(&displayLabelLcdJis.timerScrollingText, &QTimer::timeout, this, &MainWindow::slotMoveScrollingText);


    connect(&timerDelayedStart, &QTimer::timeout, this, &MainWindow::slotDelayedStartup);

    connect(&displayLabelLed, &DisplayLabelLed::signalFrontDisplayWidthChanged, ui->spinBox_frontSignWidth, &QSpinBox::setValue);
    //ui->spinBox_frontSignWidth->setValue(frontDisplay.destinationLabel->width());
    //emit signalFrontDisplayWidthChanged(frontDisplay.destinationLabel->width());


    if(cisSubscriber.version()=="2.3")
    {
        connect(&displayLabelLed.timerLedSideCycleViaPoints, &QTimer::timeout, &displayLabelLed, &DisplayLabelLed::slotTickLedPanels2_3);

    }
    else if(cisSubscriber.version()=="2.3CZ1.0")
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


bool MainWindow::allDataChanged(Vdv301AllData2_3CZ1_0 oldAllData, Vdv301AllData2_3CZ1_0 newAllData)
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;
    if(oldAllData.currentStopIndex!=newAllData.currentStopIndex)
    {
        qCDebug(MainWindowLog)<<"stop index changed";
        return true;
    }
    else if(oldAllData.tripInformationList.count()!=newAllData.tripInformationList.count())
    {
        qCDebug(MainWindowLog)<<"trip count changed";
        return true;
    }
    else if(oldAllData.tripInformationList.count()>0)
    {
        if(oldAllData.tripInformationList.first().stopPointList.count()!=newAllData.tripInformationList.first().stopPointList.count())
        {
            qCDebug(MainWindowLog)<<"stop point count changed";
            return true;
        }
        if(oldAllData.tripInformationList.first().locationState!=newAllData.tripInformationList.first().locationState)
        {
            qCDebug(MainWindowLog)<<"location state changed";
            return true;
        }
    }
    qCDebug(MainWindowLog)<<"nothing changed";

    return false;
}


void MainWindow::constantsToSettingsPage()
{
    ui->lineEdit_settings_deviceName->setText(deviceManagementService.deviceName());
    ui->lineEdit_settings_deviceManufacturer->setText(deviceManagementService.deviceManufacturer());
    ui->lineEdit_settings_deviceSerialNumber->setText(deviceManagementService.deviceSerialNumber());
    ui->lineEdit_settings_deviceClass->setText(deviceManagementService.deviceClass());
    ui->lineEdit_settings_deviceId->setText(deviceManagementService.deviceId());

    ui->lineEdit_settings_replyPath->setText(cisSubscriber.replyPath());

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


QString MainWindow::createProgramVersionString()
{
    QDate compilationDate=QLocale("en_US").toDate(QString(__DATE__).simplified(), "MMM d yyyy");
    QTime compilationTime=QTime::fromString(__TIME__,"hh:mm:ss");
    qCDebug(MainWindowLog)<<" date:"<<compilationDate<<" time:"<<compilationTime;
    QString version=compilationDate.toString("yyyyMMdd")+"_"+compilationTime.toString("hhmm");
    return version;
}



void MainWindow::debugServiceListToTable(QVector<QZeroConfService> serviceList)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    mainWindowHelper.eraseTable(ui->tableWidget_services);


    foreach(QZeroConfService selectedService, serviceList)
    {
        slotDebugServiceToTable(selectedService);
    }
}



void MainWindow::debugStopPointToTable(Vdv301StopPoint selectedStopPointDestination, bool isFollowingTrip)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    qint32 row;
    QTableWidgetItem *cell;


    /*
    qCDebug(MainWindowLog) <<"nazev sluzby "<<nazev<<" ip adresa "<<ipadresa<<" port "<<QString::number(port)<<" data" <<verze ;

 */
    row = ui->tableWidget_debugStopList->rowCount();
    ui->tableWidget_debugStopList->insertRow(row);


    if(!selectedStopPointDestination.stopNameList.isEmpty())
    {
        Vdv301InternationalText firstName=selectedStopPointDestination.stopNameList.first();

        QString stopName=InlineFormatParser::parseTextLed(firstName.text);

        cell = new QTableWidgetItem(stopName);

        if(isFollowingTrip)
        {
            cell->setBackground(QColor(240,240,240));
        }

        ui->tableWidget_debugStopList->setItem(row, 0, cell);
    }


    if(!selectedStopPointDestination.displayContentList.isEmpty())
    {
        Vdv301DisplayContent firstDisplayContent=selectedStopPointDestination.displayContentList.first();

        if(!firstDisplayContent.lineInformation.lineNameList.isEmpty())
        {
            cell = new QTableWidgetItem(InlineFormatParser::parseTextLed(firstDisplayContent.lineInformation.lineNameList.first().text));
            ui->tableWidget_debugStopList->setItem(row, 1, cell);
        }

        if(!firstDisplayContent.destination.destinationNameList.isEmpty())
        {
            cell = new QTableWidgetItem(InlineFormatParser::parseTextLed(firstDisplayContent.destination.destinationNameList.first().text));
            ui->tableWidget_debugStopList->setItem(row, 2, cell);
        }

    }

    cell = new QTableWidgetItem(QDateTime::fromString(selectedStopPointDestination.departureScheduled,Qt::ISODate).toString("hh:mm"));
    ui->tableWidget_debugStopList->setItem(row, 3, cell);

    cell = new QTableWidgetItem(QDateTime::fromString(selectedStopPointDestination.departureExpected,Qt::ISODate).toString("hh:mm"));
    ui->tableWidget_debugStopList->setItem(row, 4, cell);

    ui->tableWidget_debugStopList->resizeColumnsToContents();


}

void MainWindow::debugStopPointListToTable(QVector<Vdv301StopPoint> seznamZastavek,bool navazny)
{

    if(!navazny)
    {
        mainWindowHelper.eraseTable(ui->tableWidget_debugStopList);
    }

    foreach(Vdv301StopPoint polozka, seznamZastavek)
    {
        debugStopPointToTable(polozka,navazny);
    }
}

void MainWindow::debugStopPointListToTable(QVector<Vdv301StopPoint2_3CZ1_0> seznamZastavek,bool navazny)
{

    if(!navazny)
    {
        mainWindowHelper.eraseTable(ui->tableWidget_debugStopList);
    }

    foreach(Vdv301StopPoint polozka, seznamZastavek)
    {
        debugStopPointToTable(polozka,navazny);
    }
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



void MainWindow::displayLabelFillArray()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    displayLabelLcd.labelListStopGroup<<DisplayLabelStopGroup(ui->Lnacestna1,ui->label_pasmo1_2, ui->label_pasmo1_1);
    displayLabelLcd.labelListStopGroup<<DisplayLabelStopGroup(ui->Lnacestna2,ui->label_pasmo2_2, ui->label_pasmo2_1);
    displayLabelLcd.labelListStopGroup<<DisplayLabelStopGroup(ui->Lnacestna3,ui->label_pasmo3_2, ui->label_pasmo3_1);
    displayLabelLcd.labelListStopGroup<<DisplayLabelStopGroup(ui->Lnacestna4,ui->label_pasmo4_2, ui->label_pasmo4_1);
    displayLabelLcd.labelListStopGroup<<DisplayLabelStopGroup(ui->Lnacestna5,ui->label_pasmo5_2, ui->label_pasmo5_1);


    displayLabelLcd.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup0_linka,ui->label_prestup0_cil,ui->label_prestup0_odjezd,ui->label_prestup0_nastupiste);
    displayLabelLcd.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup1_linka,ui->label_prestup1_cil,ui->label_prestup1_odjezd,ui->label_prestup1_nastupiste);
    displayLabelLcd.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup2_linka,ui->label_prestup2_cil,ui->label_prestup2_odjezd,ui->label_prestup2_nastupiste);
    displayLabelLcd.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup3_linka,ui->label_prestup3_cil,ui->label_prestup3_odjezd,ui->label_prestup3_nastupiste);
    displayLabelLcd.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup4_linka,ui->label_prestup4_cil,ui->label_prestup4_odjezd,ui->label_prestup4_nastupiste);
    displayLabelLcd.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup5_linka,ui->label_prestup5_cil,ui->label_prestup5_odjezd,ui->label_prestup5_nastupiste);
    displayLabelLcd.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup6_linka,ui->label_prestup6_cil,ui->label_prestup6_odjezd,ui->label_prestup6_nastupiste);
    displayLabelLcd.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup7_linka,ui->label_prestup7_cil,ui->label_prestup7_odjezd,ui->label_prestup7_nastupiste);
    displayLabelLcd.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup8_linka,ui->label_prestup8_cil,ui->label_prestup8_odjezd,ui->label_prestup8_nastupiste);
    displayLabelLcd.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup9_linka,ui->label_prestup9_cil,ui->label_prestup9_odjezd,ui->label_prestup9_nastupiste);
    displayLabelLcd.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup10_linka,ui->label_prestup10_cil,ui->label_prestup10_odjezd,ui->label_prestup10_nastupiste);
    displayLabelLcd.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup11_linka,ui->label_prestup11_cil,ui->label_prestup11_odjezd,ui->label_prestup11_nastupiste);



    displayLabelLcd.pageAdditionalTextMessage=ui->page_additionalTextMessage;
    displayLabelLcd.pageRoute=ui->page_route;

    displayLabelLcd.stackedWidget_middle=ui->stackedWidget_prostredek;
    displayLabelLcd.stackedWidget_onService=ui->stackedWidget_onService;
    displayLabelLcdJis.stackedWidget_onService=ui->stackedWidget_onService_2;

    displayLabelLcd.labelAnnouncementLeft=ui->label_announcementLeft;
    displayLabelLcd.labelAnnouncementRight=ui->label_announcementRight;

    displayLabelLcd.pageFareZoneChange=ui->page_fareZoneChange;
    displayLabelLcd.labelFareZoneAnnouncementLeft=ui->label_fareChangeAnnLeft;
    displayLabelLcd.labelFareZoneAnnouncementRight=ui->label_fareChangeAnnRight;
    displayLabelLcd.labelFareZoneChangeFrom=ui->label_fareZoneChangeFrom;
    displayLabelLcd.labelFareZoneChangeTo=ui->label_fareZoneChangeTo;


    //     displayLabelLcd.labelFareZoneChangeTo=ui->label_fareChangeAnnRight;



    displayLabelLcd.pageLineChange=ui->page_lineChange;
    displayLabelLcd.labelLineChangeAnnouncementLeft=ui->label_lineChangeLeft;
    displayLabelLcd.labelLineChangeAnnouncementRight=ui->label_lineChangeRight;
    displayLabelLcd.labelLineChangeAnnouncementFrom =ui->label_lineFrom;
    displayLabelLcd.labelLineChangeAnnouncementTo=ui->label_lineTo;
}



void MainWindow::displayLabelFillArrayJis()
{
    displayLabelLcdJis.labelListStopGroup<<DisplayLabelStopGroup(ui->Lnacestna1_2,ui->label_pasmo1_4, ui->label_pasmo1_3, ui->label_nastupiste_2, ui->label_stopMinutes1);
    displayLabelLcdJis.labelListStopGroup<<DisplayLabelStopGroup(ui->Lnacestna2_2,ui->label_pasmo2_4, ui->label_pasmo2_3, nullptr, ui->label_stopMinutes2);
    displayLabelLcdJis.labelListStopGroup<<DisplayLabelStopGroup(ui->Lnacestna3_2,ui->label_pasmo3_4, ui->label_pasmo3_3, nullptr, ui->label_stopMinutes3);
    displayLabelLcdJis.labelListStopGroup<<DisplayLabelStopGroup(ui->Lnacestna4_2,ui->label_pasmo4_4, ui->label_pasmo4_3, nullptr, ui->label_stopMinutes4);
    displayLabelLcdJis.labelListStopGroup<<DisplayLabelStopGroup(ui->Lnacestna5_2,ui->label_pasmo5_4, ui->label_pasmo5_3, nullptr, ui->label_stopMinutes5);
    displayLabelLcdJis.labelListStopGroup<<DisplayLabelStopGroup(ui->Lnacestna6_2,ui->label_pasmo6_4, ui->label_pasmo6_3, nullptr, ui->label_stopMinutes6);

    displayLabelLcdJis.labelListStopConnectionGroup<<DisplayLabelStopGroup(ui->Lnacestna1_3,nullptr,nullptr);

    //page 1
    displayLabelLcdJis.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup0_linka_2,ui->label_prestup0_cil_2,ui->label_prestup0_odjezd_2,ui->label_prestup0_nastupiste_2);
    displayLabelLcdJis.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup1_linka_2,ui->label_prestup1_cil_2,ui->label_prestup1_odjezd_2,ui->label_prestup1_nastupiste_2);
    displayLabelLcdJis.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup2_linka_2,ui->label_prestup2_cil_2,ui->label_prestup2_odjezd_2,ui->label_prestup2_nastupiste_2);
    displayLabelLcdJis.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup3_linka_2,ui->label_prestup3_cil_2,ui->label_prestup3_odjezd_2,ui->label_prestup3_nastupiste_2);
    displayLabelLcdJis.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup4_linka_2,ui->label_prestup4_cil_2,ui->label_prestup4_odjezd_2,ui->label_prestup4_nastupiste_2);
    displayLabelLcdJis.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup5_linka_2,ui->label_prestup5_cil_2,ui->label_prestup5_odjezd_2,ui->label_prestup5_nastupiste_2);
    displayLabelLcdJis.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup6_linka_2,ui->label_prestup6_cil_2,ui->label_prestup6_odjezd_2,ui->label_prestup6_nastupiste_2);
    displayLabelLcdJis.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup7_linka_2,ui->label_prestup7_cil_2,ui->label_prestup7_odjezd_2,ui->label_prestup7_nastupiste_2);
    //page 2
    displayLabelLcdJis.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup8_linka_2,ui->label_prestup8_cil_2,ui->label_prestup8_odjezd_2,ui->label_prestup8_nastupiste_2);
    displayLabelLcdJis.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup9_linka_2,ui->label_prestup9_cil_2,ui->label_prestup9_odjezd_2,ui->label_prestup9_nastupiste_2);
    displayLabelLcdJis.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup10_linka_2,ui->label_prestup10_cil_2,ui->label_prestup10_odjezd_2,ui->label_prestup10_nastupiste_2);
    displayLabelLcdJis.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup11_linka_2,ui->label_prestup11_cil_2,ui->label_prestup11_odjezd_2,ui->label_prestup11_nastupiste_2);
    displayLabelLcdJis.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup12_linka_2,ui->label_prestup12_cil_2,ui->label_prestup12_odjezd_2,ui->label_prestup12_nastupiste_2);
    displayLabelLcdJis.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup13_linka_2,ui->label_prestup13_cil_2,ui->label_prestup13_odjezd_2,ui->label_prestup13_nastupiste_2);
    displayLabelLcdJis.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup14_linka_2,ui->label_prestup14_cil_2,ui->label_prestup14_odjezd_2,ui->label_prestup14_nastupiste_2);
    displayLabelLcdJis.labelListConnectionGroup<<DisplayLabelConnectionGroup(ui->label_prestup15_linka_2,ui->label_prestup15_cil_2,ui->label_prestup15_odjezd_2,ui->label_prestup15_nastupiste_2);

    displayLabelLcdJis.pageAdditionalTextMessage=ui->page_additionalTextMessage_2;
    displayLabelLcdJis.pageRoute=ui->page_route_2;

    displayLabelLcdJis.stackedWidget_middle=ui->stackedWidget_prostredek_2;
    displayLabelLcdJis.stackedWidget_onService=ui->stackedWidget_onService_2;

    displayLabelLcdJis.labelAnnouncementLeft=ui->label_announcementLeft_2;
    displayLabelLcdJis.labelAnnouncementRight=ui->label_announcementRight_2;

    displayLabelLcdJis.pageFareZoneChange=ui->page_fareZoneChange_2;
    displayLabelLcdJis.labelFareZoneAnnouncementLeft=ui->label_fareChangeAnnLeft_2;
    displayLabelLcdJis.labelFareZoneAnnouncementRight=ui->label_fareChangeAnnRight_2;
    displayLabelLcdJis.labelFareZoneChangeFrom=ui->label_fareZoneChangeFrom_2;
    displayLabelLcdJis.labelFareZoneChangeTo=ui->label_fareZoneChangeTo_2;

    displayLabelLcdJis.pageLineChange=ui->page_lineChange_2;
    displayLabelLcdJis.labelLineChangeAnnouncementLeft=ui->label_lineChangeLeft_2;
    displayLabelLcdJis.labelLineChangeAnnouncementRight=ui->label_lineChangeRight_2;
    displayLabelLcdJis.labelLineChangeAnnouncementFrom =ui->label_lineFrom_2;
    displayLabelLcdJis.labelLineChangeAnnouncementTo=ui->label_lineTo_2;
}


void MainWindow::displayLabelReturnToStopList()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    lcdLabelCurrentPageIndex=0;
    ui->stackedWidget_onService->setCurrentWidget(ui->page_route);
    displayLabelLcd.stackedWidget_middle->setCurrentWidget(ui->page_hlavni_2);


    lcdLabelCurrentPageIndexJis=0;
    ui->stackedWidget_onService_2->setCurrentWidget(ui->page_route_2);
    displayLabelLcdJis.stackedWidget_middle->setCurrentWidget(ui->page_hlavni_3);

    displayLabelLcd.naplnZmenaLabel("",ui->label_zmena);
}



void MainWindow::displayLabelShowFareZoneChange(QVector<Vdv301InternationalText> fromFareZoneList, QVector<Vdv301InternationalText> toFareZoneList)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    ui->stackedWidget_onService->setCurrentWidget(ui->page_route);
    displayLabelLcd.stackedWidget_middle->setCurrentWidget(ui->page_fareZoneChange);

    ui->stackedWidget_onService_2->setCurrentWidget(ui->page_route_2);
    displayLabelLcdJis.stackedWidget_middle->setCurrentWidget(ui->page_fareZoneChange_2);

    ui->label_fareZoneChangeFrom->setText(displayLabelLcd.vdv301InternationalTextJoinAll(fromFareZoneList,"\n").text);
    ui->label_fareZoneChangeTo->setText(displayLabelLcd.vdv301InternationalTextJoinAll(toFareZoneList,"\n").text);



    //ADD JIS VERSION!

    // displayLabelLcd.naplnZmenaLabel(displayLabelLcd.vyrobTextZmenyPasma(fromFareZoneList,toFareZoneList),ui->label_zmena);
}





void MainWindow::displayLabelShowAnnoucement(QString title,QString type,QString textCz, QString textEn)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    updateLabelAnnouncement(textCz);
    ui->stackedWidget_onService->setCurrentWidget(ui->page_route);
    displayLabelLcd.stackedWidget_middle->setCurrentWidget(ui->page_oznameni);

    ui->stackedWidget_onService_2->setCurrentWidget(ui->page_route_2);
    displayLabelLcdJis.stackedWidget_middle->setCurrentWidget(ui->page_oznameni_2);

    ui->label_oznTitle->setText(title);
    ui->label_oznType->setText(  displayLabelLcd.textNaPiktogramOznameni(type,100*displayLabelLcd.ratioPixelPoint));
    ui->label_oznTextCs->setText(textCz);
    ui->label_oznTextEn->setText(textEn);


    ui->label_oznTitle_2->setText(title);
    ui->label_oznType_2->setText(  displayLabelLcd.textNaPiktogramOznameni(type,100*displayLabelLcd.ratioPixelPoint));
    ui->label_oznTextCs_2->setText(textCz);
    ui->label_oznTextEn_2->setText(textEn);

    displayLabelLcd.pageCycleList.push_back(ui->page_oznameni);
    displayLabelLcdJis.pageCycleList.push_back(ui->page_oznameni_2);

    //ADD JIS VERSION!
}


void MainWindow::displayLabelShowAnnoucement(QVector<Vdv301InternationalText> additionalTextMessageList,QVector<Vdv301InternationalText> additionalTextMessage1List,QVector<Vdv301InternationalText> additionalTextMessage2List, QVector<Vdv301InternationalText> additionalTextMessage3List,QVector<Vdv301InternationalText> additionalTextMessage4List)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    if(!additionalTextMessageList.isEmpty() )
    {
        updateLabelAnnouncement(additionalTextMessageList.first().text);
    }

    displayLabelLcd.displayLabelShowAnnoucement(additionalTextMessageList,additionalTextMessage1List,additionalTextMessage2List,additionalTextMessage3List,additionalTextMessage4List);
}


void MainWindow::displayLabelShowPageFinalStop()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    ui->stackedWidget_onService->setCurrentWidget(ui->page_route);
    displayLabelLcd.stackedWidget_middle->setCurrentWidget(ui->page_konecna);

    ui->stackedWidget_onService_2->setCurrentWidget(ui->page_route_2);
    displayLabelLcdJis.stackedWidget_middle->setCurrentWidget(ui->page_konecna_2);
}



void MainWindow::eraseDisplayedInformation()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    ui->stackedWidget_onService->setCurrentWidget(ui->page_version);
    ui->stackedWidget_onService_2->setCurrentWidget(ui->page_version_2);
    displayLabelLcd.displayLabelEraseInformation();
    displayLabelLcdJis.displayLabelEraseInformation();
    svgVykreslovani.vymazObrazovku();
    displayLabelLed.ledClearDisplays();
}

void MainWindow::eventDisplayAbnormalStateScreen(QString displayState)
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO<<" "<<displayState;
    ui->label_lcd_state->setText(displayState);
    ui->label_lcd_state_2->setText(displayState);
    eraseDisplayedInformation();
    //  ui->stackedWidget_onService->setCurrentWidget(ui->page_version);

}


void MainWindow::eventEraseDisplayInformation()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    eraseDisplayedInformation();
    //displayLabelLcd.displayLabelEraseInformation();
}

void MainWindow::eventHideAnnouncement()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    eventLcdSetMainPage();
}

void MainWindow::eventHideFareZoneChange()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    eventLcdSetMainPage();
}

void MainWindow::eventLcdSetMainPage()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    //LCD label
    displayLabelReturnToStopList();

    //SVG
    //unused
}

void MainWindow::eventLcdShowFollowingTripDestination(QString followingTripLine,QString followingTripDestination)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    //LABEL LCD
    ui->label_followingLine->setText(followingTripLine);
    ui->label_followingDestination->setText(followingTripDestination);
    ui->frame_navaznySpoj->show();

    //SVG

}




void MainWindow::eventLcdReturnToStopList()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    //label
    displayLabelReturnToStopList();

    //svg
    //unused
}


void MainWindow::eventNotOnLine()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    eventDisplayAbnormalStateScreen("NOT ON LINE");
}


void MainWindow::eventShowPageFareZoneChange(QVector<Vdv301InternationalText> fromFareZones, QVector<Vdv301InternationalText> toFareZones)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    displayLabelShowFareZoneChange(fromFareZones,toFareZones);
    svgVykreslovani.zobrazZmenuPasma(fromFareZones,toFareZones);
}


void MainWindow::eventShowPageSpecialAnnouncement(QString title,QString type,QString textCz, QString textEn)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    displayLabelShowAnnoucement(title,type,textCz,textEn);
    svgVykreslovani.zobrazAnnoucement(title,type,textCz,textEn);
}

void MainWindow::eventShowPageSpecialAnnouncement(QVector<Vdv301InternationalText> additionalTextMessage,QVector<Vdv301InternationalText> additionalTextMessage1,QVector<Vdv301InternationalText> additionalTextMessage2, QVector<Vdv301InternationalText> additionalTextMessage3,QVector<Vdv301InternationalText> additionalTextMessage4)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    displayLabelShowAnnoucement(additionalTextMessage,additionalTextMessage1,additionalTextMessage2,additionalTextMessage3,additionalTextMessage4);
    //   svgVykreslovani.zobrazAnnoucement(title,type,textCz,textEn);
}



void MainWindow::eventStopRequestedActivated()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    ui->label_stopRequested->setText("<b>STOP</b>");

    ui->label_stopRequestedSymbol->show();
    ui->label_stopRequestedSymbol_2->show();
}

void MainWindow::eventStopRequestedDectivated()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    ui->label_stopRequested->setText("STOP");


    ui->label_stopRequestedSymbol->hide();
    ui->label_stopRequestedSymbol_2->hide();
}





QString MainWindow::golemioRequestCompose(QString aswId, QString vehicleRef, int vehicleType)
{
    QString output="?aswId=";
    output+=aswId;
    output+="&vehicleRegistrationNumber=";
    output+=vehicleRef;
    output+="&routeType=";
    output+=QString::number(vehicleType);

    return output;
}

void MainWindow::golemioUpdateVariables()
{
    if(golemioUseTestServer)
    {
        golemio.setKlic(golemioKeyTest.toUtf8());
        golemio.setAdresa(golemioAddressTest);
    }
    else
    {
        golemio.setKlic(golemioKey.toUtf8());
        golemio.setAdresa(golemioAddress);
    }
}




void MainWindow::handleDisplayContentInner(QVector<Vdv301DisplayContent> displayContentList, bool following)
{
    if(displayContentList.isEmpty())
    {
        return;
    }

    //handles only one row of destination and one displaycontent per class. Switching will be in future revisions

    Vdv301DisplayContent firstDisplayContent=displayContentList.first();


    Vdv301Destination destination=firstDisplayContent.destination;
    Vdv301Line line=firstDisplayContent.lineInformation;


    if(following)
    {
        if(destination.destinationNameList.isEmpty())
        {
            displayLabelLcd.displayLabelDestinationFollowing("");
            displayLabelLcdJis.displayLabelDestinationFollowing("");
        }
        else
        {
            displayLabelLcd.displayLabelDestinationFollowing(destination);
            displayLabelLcdJis.displayLabelDestinationFollowing(destination);

        }

        if(line.lineNameList.isEmpty())
        {
            displayLabelLcd.displayLabelLineNameFollowing("");
            displayLabelLcdJis.displayLabelLineNameFollowing("");

        }
        else
        {
            displayLabelLcd.displayLabelLineNameFollowing(line);
            displayLabelLcdJis.displayLabelLineNameFollowing(line);
        }
    }
    else
    {
        if(destination.destinationNameList.isEmpty())
        {
            displayLabelLcd.displayLabelDestination("");
            displayLabelLcdJis.displayLabelDestination("");
        }
        else
        {
            displayLabelLcd.displayLabelDestination(destination);
            displayLabelLcdJis.displayLabelDestination(destination);
        }

        if(line.lineNameList.isEmpty())
        {
            displayLabelLcd.displayLabelLineName("");
            displayLabelLcdJis.displayLabelLineName("");
        }
        else
        {
            displayLabelLcd.displayLabelLineName(line);
            displayLabelLcdJis.displayLabelLineName(line);
        }

        displayLabelLcd.displayLabelViaPoints(displayContentList.first().viaPointList);
        displayLabelLcdJis.displayLabelViaPoints(displayContentList.first().viaPointList);
    }

}


void MainWindow::handleDisplayContentFront(QVector<Vdv301DisplayContent> displayContentList)
{

}


void MainWindow::handleDisplayContentSide(QVector<Vdv301DisplayContent> displayContentList)
{

}


void MainWindow::handleDisplayContentRear(QVector<Vdv301DisplayContent> displayContentList)
{

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
    displayLabelLcdJis.initializeFonts();
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

int MainWindow::isInRange(int index, int limit, QString functionName)
{
    if((index<limit)&&(index>=0))
    {

        return 1;
    }
    else
    {
        QMessageBox msgBox;
        QString errorMessage="value"+QString::number(index)+" is out of range "+ QString::number(limit)+" function:"+functionName;
        msgBox.setText(errorMessage);
        qCDebug(MainWindowLog)<<" errorMessage";
        msgBox.exec();


        return 0;
    }

}

void MainWindow::labelLcdUpdateStopBackground(Vdv301Enumerations::LocationStateEnumeration locationState)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;



    if ((locationState==Vdv301Enumerations::LocationStateAtStop)||(locationState==Vdv301Enumerations::LocationStateBeforeStop))
    {
        labelSetNextStopBackground(barvyLinek.barva_PozadiB_50_50_50,barvyLinek.barva_Zastavka_180_180_180 );
        labelSetNextStopBackgroundJis("rgb(29,29,27)", "rgb(200,200,200)");
    }
    else
    {
        labelSetNextStopBackground(barvyLinek.barva_bila_255_255_255,barvyLinek.barva_PozadiB_50_50_50);
        labelSetNextStopBackgroundJis(barvyLinek.barva_bila_255_255_255,"rgb(54,54,53)");
    }

}


void MainWindow::labelSetNextStopBackground(QString barvaPisma,QString barvaPozadi)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    //
    displayLabelLcd.obarviPozadiPristi(barvaPisma,barvaPozadi,ui->frame_spodniRadek);
    displayLabelLcdJis.obarviPozadiPristi(barvaPisma,barvaPozadi,ui->frame_spodniRadek_2);
    svgVykreslovani.obarviPozadiPristi(barvaPisma,barvaPozadi);


    QString stylTextu="color:"+barvaPisma;
    ui->Lnacestna1->setStyleSheet(stylTextu);
    ui->label_pasmo1_1->setStyleSheet(stylTextu);
    ui->label_pasmo1_2->setStyleSheet(stylTextu);


}


void MainWindow::labelSetNextStopBackgroundJis(QString barvaPisma,QString barvaPozadi)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    //
    displayLabelLcdJis.obarviPozadiPristi(barvaPisma,barvaPozadi,ui->frame_spodniRadek_2);

    QString stylTextu="color:"+barvaPisma;
    ui->Lnacestna1_2->setStyleSheet(stylTextu);
    ui->label_pasmo1_3->setStyleSheet(stylTextu);
    ui->label_pasmo1_4->setStyleSheet(stylTextu);


}


void MainWindow::lcdLabelInitialize2_3()
{
    displayLabelLcd.labelDestination=ui->Lcil;
    displayLabelLcd.labelLine=ui->label_linka;
    displayLabelLcd.labelViaPointsScrolling=ui->label_nacestne;
    displayLabelLcd.labelClock=ui->label_hodiny;
    displayLabelLcd.frameFollowingTrip=ui->frame_navaznySpoj;
    displayLabelLcd.labelDestinationFollowing= ui->label_followingDestination;
    displayLabelLcd.labelLineFollowing= ui->label_followingLine;


    displayLabelLcdJis.labelDestination=ui->Lcil_2;
    displayLabelLcdJis.labelLine=ui->label_linka_2;

    displayLabelLcdJis.labelLineConnection=ui->label_linka_3;
    displayLabelLcdJis.labelPlatformConnection=ui->label_nastupiste_2;
    //displayLabelLcdJis.labelDestinationConnection=nullptr;


    displayLabelLcdJis.labelViaPointsScrolling=ui->label_nacestne_2;
    displayLabelLcdJis.labelClock=ui->label_hodiny_2;
    //displayLabelLcdJis.frameFollowingTrip=ui->frame_navaznySpoj_;
    //displayLabelLcdJis.labelDestinationFollowing= ui->label_followingDestination;
    //displayLabelLcdJis.labelLineFollowing= ui->label_followingLine;

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
    displayLabelLed.rearDisplay.destinationLabel=nullptr;
    displayLabelLed.rearDisplay.destination1Label=nullptr;
    displayLabelLed.rearDisplay.destination2Label=nullptr;
    displayLabelLed.rearDisplay.ticker=0;


    displayLabelLed.innerDisplay.lineLabel=ui->labelInnerLine;
    displayLabelLed.innerDisplay.destinationLabel=nullptr;
    displayLabelLed.innerDisplay.destination1Label=ui->labelInnerTopRow;
    displayLabelLed.innerDisplay.destination2Label=ui->labelInnerBottomRow;
    displayLabelLed.rearDisplay.ticker=0;

}



void MainWindow::loadConstants()
{
    blockBonjour=settings.value("app/blockBonjour").toBool();

    deviceManagementService.setDeviceName(settings.value("deviceManagementService/deviceName").toString());
    deviceManagementService.setDeviceManufacturer(settings.value("deviceManagementService/deviceManufacturer").toString());
    deviceManagementService.setDeviceSerialNumber(settings.value("deviceManagementService/deviceSerialNumber").toString());
    deviceManagementService.setDeviceClass(settings.value("deviceManagementService/deviceClass").toString());
    deviceManagementService.setDeviceId(settings.value("deviceManagementService/deviceId").toString());
    deviceManagementService.setSwVersion(createProgramVersionString());
    deviceManagementService.setPortNumber(settings.value("deviceManagementService/port").toInt() ); //47477
    deviceManagementService.setVersion(settings.value("deviceManagementService/version").toString());


    deviceManagementService.blockBonjour=blockBonjour;

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
        displayLabelLcdJis.setVdv301version(vdv301version);
    }
    else
    {
        popUpMessage(tr("version ")+vdv301version+tr(" is not supported!"));
    }
    cisSubscriber.setPortNumber(settings.value("cisSubscriber/port").toUInt());

    if(settings.value("cisSubscriber/structure").toString()=="")
    {
        cisSubscriber.setStructureName("AllData");
    }
    else
    {
        cisSubscriber.setStructureName(settings.value("cisSubscriber/structure").toString());
    }

    cisSubscriber.setReplyPath(settings.value("cisSubscriber/replyPath").toString());
    cisSubscriber.blockBonjour=blockBonjour;

    useJis=settings.value("graphics/useJisGraphics").toBool();
    if(settings.value("graphics/lcdPageSwitchTimer").toInt()!=0)
    {
        intervalLcdPageSwitchSeconds=settings.value("graphics/lcdPageSwitchTimer").toInt();
        ui->spinBox_pageSwitchDuration->setValue(intervalLcdPageSwitchSeconds);
    }




    ui->checkBox_settings_useJis->setChecked(useJis);

    menuSwitchTabs(settings.value("window/defaultScreen").toInt());
    if(settings.value("window/fullscreen").toBool()==true)
    {
        slotToggleFullscreen();
    }

    connectionsStandalone=settings.value("app/connectionsStandalone").toBool();
    ui->checkBox_settings_useGolemioConnections->setChecked(connectionsStandalone);


    golemioAddress=settings.value("golemio/address").toString();
    golemioAddressTest=settings.value("golemio/addressTest").toString();


    golemioKey=settings.value("golemio/key").toString().toUtf8();
    ui->lineEdit_settings_golemio_apiKey->setText(golemioKey);

    golemioKeyTest=settings.value("golemio/keyTest").toString().toUtf8();
    ui->lineEdit_settings_golemio_rabinKey->setText(golemioKeyTest);

    golemioParametry=settings.value("golemio/parameters").toString();
    golemio.setParametry(golemioParametry);

    golemioUseTestServer=settings.value("golemio/useTestServer").toBool();
    ui->checkBox_settings_golemioTestServer->setChecked(golemioUseTestServer);


    golemioUpdateVariables();
}

void MainWindow::menuSwitchTabs(int tabNumber)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO<<" "<<tabNumber;

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



void MainWindow::messageToTable(Vdv301AllData2_3CZ1_0 input)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    qint32 row;
    QTableWidgetItem *cell;

    QString timeStamp=QTime::currentTime().toString("hh:mm:ss.zzz");
    QString currentStopIndex=QString::number(input.currentStopIndex);
    QString tripCount=QString::number(input.tripInformationList.count());
    QString stopCount="";
    QString locationState="";
    QString announcement="";
    QString connectionCount="";
    QString stopRequested=QString::number(input.vehicleInformationGroup.vehicleStopRequested);

    if(!input.tripInformationList.isEmpty())
    {
        Vdv301Trip2_3CZ1_0 selectedTrip=input.tripInformationList.first();


        stopCount=QString::number(selectedTrip.stopPointList.count());
        locationState=Vdv301Enumerations::LocationStateEnumerationToQString(selectedTrip.locationState);
        if(!selectedTrip.additionalTextMessageList.isEmpty() )
        {
            announcement=   input.tripInformationList.first().additionalTextMessageList.first().text;
        }

        if(!selectedTrip.stopPointList.isEmpty())
        {
            if(isInRange(input.currentStopIndex-1,selectedTrip.stopPointList.count(),Q_FUNC_INFO))
            {
                Vdv301StopPoint2_3CZ1_0 selectedStopPoint=selectedTrip.stopPointList.at(input.currentStopIndex-1);
                connectionCount=QString::number(selectedStopPoint.connectionList.count());
            }

        }

    }


    row = ui->tableWidget_logMessages->rowCount();
    ui->tableWidget_logMessages->insertRow(row);
    cell = new QTableWidgetItem(timeStamp);
    ui->tableWidget_logMessages->setItem(row, 0, cell);

    cell = new QTableWidgetItem(currentStopIndex);
    ui->tableWidget_logMessages->setItem(row, 1, cell);

    cell = new QTableWidgetItem(tripCount);
    ui->tableWidget_logMessages->setItem(row, 2, cell);

    cell = new QTableWidgetItem(stopCount);
    ui->tableWidget_logMessages->setItem(row, 3, cell);

    cell = new QTableWidgetItem(locationState);
    ui->tableWidget_logMessages->setItem(row, 4, cell);

    cell = new QTableWidgetItem(connectionCount);
    ui->tableWidget_logMessages->setItem(row, 5, cell);

    cell = new QTableWidgetItem(stopRequested);
    ui->tableWidget_logMessages->setItem(row, 6, cell);

    cell = new QTableWidgetItem(announcement.replace("\n",""));
    ui->tableWidget_logMessages->setItem(row, 7, cell);


    ui->tableWidget_logMessages->resizeColumnsToContents();
    if(ui->checkBox_logMessageAutoscroll->isChecked())
    {
        ui->tableWidget_logMessages->scrollToBottom();
    }


}

void MainWindow::on_checkBox_debugLogEnable_stateChanged(int arg1)
{
    if(arg1)
    {
        connect(&relay, &LoggerRelay::message,this,&MainWindow::slotLogWindowAppend,Qt::QueuedConnection);
    }
    else
    {
        disconnect(&relay, &LoggerRelay::message,this,&MainWindow::slotLogWindowAppend);
    }
}

void MainWindow::on_checkBox_settings_useGolemioConnections_stateChanged(int arg1)
{
    connectionsStandalone=arg1;
    settings.setValue("app/connectionsStandalone",connectionsStandalone);
}


void MainWindow::on_checkBox_settings_golemioTestServer_stateChanged(int arg1)
{
    golemioUseTestServer=arg1;
    settings.setValue("golemio/useTestServer",golemioUseTestServer);

    golemioUpdateVariables();
}


void MainWindow::on_checkBox_settings_useJis_stateChanged(int arg1)
{
    useJis=arg1;
    settings.setValue("graphics/useJisGraphics",useJis);
}


void MainWindow::on_pushButton_debugConvertInline_clicked()
{
    displayLabelLcd.labelSetTextBgInline(ui->label_debugInLineOutput,ui->plainTextEdit_debugInLineInput->toPlainText());
    ui->plainTextEdit_debugInLineOutput->setPlainText(ui->label_debugInLineOutput->text());

}

void MainWindow::on_pushButton_debugLogClear_clicked()
{
    ui->plainTextEdit_debugLogContent->clear();
}

void MainWindow::on_pushButton_debugLogLevel_clicked()
{
    QLoggingCategory::setFilterRules(ui->plainTextEdit_debugLogLevel->toPlainText());
}




void MainWindow::on_pushButton_debugShowHtml_clicked()
{
    ui->label_debugInLineOutput->setText(ui->plainTextEdit_debugInLineOutput->toPlainText());
}


void MainWindow::on_pushButton_menu_displayLabel_clicked()
{
    if(useJis)
    {
        ui->stackedWidget_menuSwitch->setCurrentWidget(ui->page_labelDisplayJis);
    }
    else
    {
        ui->stackedWidget_menuSwitch->setCurrentWidget(ui->page_labelDisplay);
    }

    displayLabelLcd.lcdResizeLabels(ui->frame_hlavni->height());
}


void MainWindow::on_pushButton_menu_displayLed_clicked()
{
    ui->stackedWidget_menuSwitch->setCurrentWidget(ui->page_led);
    ui->labelFrontBottomRow->setText("");
}




void MainWindow::on_pushButton_menu_fullscreen_clicked()
{
    slotToggleFullscreen();
}

void MainWindow::on_pushButton_menu_quit_clicked()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    if(cisSubscriber.isSubscriptionActive)
    {
        connect(&cisSubscriber,&CisSubscriber::signalIsUnsubscriptionSuccesful,this,&MainWindow::slotShutdownReady);
        cisSubscriber.unsubscribe();
    }
    else
    {
        slotShutdownReady(true);
    }

    //   connect(&cisSubscriber,&IbisIpSubscriber::signalSubscriptionLost ,this,&MainWindow::slotSubscriptionLost);
}


void MainWindow::on_pushButton_menu_refresh_clicked()
{
    //the button is disabled by default
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    //  CustomerInformationServiceSubscriber.odebirano=false ;
    //  CustomerInformationServiceSubscriber.hledejSluzby("_ibisip_http._tcp.",1);
    this->eraseDisplayedInformation();
    slotUpdateServiceTable(); //xmlDoPromenne(1);


    eraseDisplayedInformation();
    cisSubscriber.newSubscribeRequest();
}

void MainWindow::on_pushButton_menu_services_clicked()
{
    ui->stackedWidget_menuSwitch->setCurrentWidget(ui->page_settings);
}

void MainWindow::on_pushButton_menu_svg_clicked()
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;
    ui->stackedWidget_menuSwitch->setCurrentWidget(ui->page_svg);


    //QSvgRenderer *m_renderer = new QSvgRenderer(QLatin1String("./Verlauf.svg"));

    this->svgRender();
    /*
    ui->graphicsView->setScene(&novaScena);
    ui->graphicsView->update();
    ui->graphicsView->show();
    */

}

void MainWindow::on_pushButton_menu_timer_clicked()
{
    ui->stackedWidget_menuSwitch->setCurrentWidget(ui->page_timer);
}



void MainWindow::on_pushButton_messageLogReset_clicked()
{
    mainWindowHelper.eraseTable(ui->tableWidget_logMessages);
}

void MainWindow::on_pushButton_settings_save_clicked()
{
    settingsWindowToSettingsFile();
}

void MainWindow::on_pushButton_unsubscribe_clicked()
{
    cisSubscriber.unsubscribe();

    slotSubscriptionLost();

}

void MainWindow::on_radioButton_settings_languageCs_clicked()
{
    retranslateUi("cs");
}


void MainWindow::on_radioButton_settings_languageEn_clicked()
{
    retranslateUi("en");
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




void MainWindow::on_spinBox_frontSignWidth_valueChanged(int arg1)
{
    ui->labelFrontSingle->setFixedWidth(ui->spinBox_frontSignWidth->value());
    displayLabelLed.ledUpdateDisplaySizes();
}


void MainWindow::on_spinBox_pageSwitchDuration_valueChanged(int arg1)
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO<<" "<<arg1;
    intervalLcdPageSwitchSeconds=arg1;
    displayLabelLcd.timerLabelPageSwitch.setInterval(intervalLcdPageSwitchSeconds*1000);
    displayLabelLcdJis.timerLabelPageSwitch.setInterval(intervalLcdPageSwitchSeconds*1000);
}



void MainWindow::popUpMessage(QString messageContent)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    QMessageBox msgBox;
    msgBox.setText(messageContent);
    QFont font;
    //font.setBold(true);
    font.setPointSize(30);
    msgBox.setFont(font);
    // msgBox.setStyleSheet("font-size: 30px;");
    msgBox.exec();
}


void MainWindow::receivedDataVariablesReset()
{
    currentVdv301StopPointList.clear();

    debugStopPointListToTable(currentVdv301StopPointList,false);

    mainWindowHelper.eraseTable(ui->tableWidget_connections);
}




void MainWindow::retranslateUi(QString language)
{
    QTranslator translator;

    qApp->removeTranslator(&translator);
    if(translator.load(":/lang_"+language+".qm"))
    {
        qApp->installTranslator(&translator);
        qCDebug(MainWindowLog)<<"language change";
        ui->retranslateUi(this);
    }
    else
    {
        popUpMessage(tr("language file not found"));
    }
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

    settings.setValue("cisSubscriber/replyPath",ui->lineEdit_settings_replyPath->text());

    settings.setValue("graphics/lcdPageSwitchTimer",intervalLcdPageSwitchSeconds);

    settings.setValue("app/connectionsStandalone",connectionsStandalone);

    golemioKey=ui->lineEdit_settings_golemio_apiKey->text();
    golemioKeyTest=ui->lineEdit_settings_golemio_rabinKey->text();

    settings.setValue("golemio/key",golemioKey);
    settings.setValue("golemio/keyTest",golemioKeyTest);
    settings.setValue("golemio/useTestServer",golemioUseTestServer);
    golemioUpdateVariables();
}





void MainWindow::showReceivedDataLedVdv301(QVector<Vdv301DisplayContent> stopDisplayContentList, QVector<Vdv301DisplayContent> globalDisplayContentList)
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;

    if(globalDisplayContentList.isEmpty())
    {
        displayLabelLed.ledUpdateDisplayedInformationFromDisplayContentList2_3(stopDisplayContentList);
    }
    else
    {
        displayLabelLed.ledUpdateDisplayedInformationFromDisplayContentList2_3(globalDisplayContentList);

    }


}

int MainWindow::showReceivedDataLcdVdv301(Vdv301AllData vdv301AllData)
{

    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    eventLcdSetMainPage();
    eventEraseDisplayInformation();
    displayLabelLcd.pageCycleList.clear();
    displayLabelLcdJis.pageCycleList.clear();

    if(vdv301AllData.vehicleInformationGroup.vehicleStopRequested)
    {
        eventStopRequestedActivated();
    }
    else
    {
        eventStopRequestedDectivated();
    }

    updateLabelCurrentStopindex(QString::number(vdv301AllData.currentStopIndex));


    if(vdv301AllData.currentStopIndex<1 )
    {
        popUpMessage("stop index is smaller than 0");
        return 0;
    }
    else if(vdv301AllData.currentStopIndex<1 )
    {
        popUpMessage("stop index is 0");
        return 0;
    }
    else if(isInRange(vdv301AllData.currentStopIndex-1,vdv301AllData.tripInformationList.first().stopPointList.count(),Q_FUNC_INFO))
    {
        Vdv301Trip currentVdv301trip=vdv301AllData.tripInformationList.first();
        Vdv301StopPoint currentVdvStopPoint=currentVdv301trip.stopPointList.at(vdv301AllData.currentStopIndex-1);


        //   displayLabelLcd.displayLabelViaPoints(currentDestinationPointList,vehicleState);

        labelLcdUpdateStopBackground(currentVdv301trip.locationState);

        QVector<Vdv301DisplayContent> displayContentListInterior=displayLabelLcd.filterVdv301DisplayContentByClass(currentVdvStopPoint.displayContentList,DisplayContentInterior);
        QVector<Vdv301DisplayContent> displayContentListLcd=displayLabelLcd.filterVdv301DisplayContentByClass(currentVdvStopPoint.displayContentList,DisplayContentLcd);


        if(displayContentListLcd.isEmpty())
        {
            handleDisplayContentInner(displayContentListInterior,false);
        }
        else
        {
            handleDisplayContentInner(displayContentListLcd,false);
        }
        if(cisSubscriber.version()=="1.0")
        {
            handleDisplayContentInner(currentVdvStopPoint.displayContentList,false);
        }

        displayLabelLcd.displayLabelStopFareZone(vdv301AllData);



        if(xmlParser2_3.followingTripExists(vdv301AllData.tripInformationList))
        {
            Vdv301Trip nextVdv301trip=vdv301AllData.tripInformationList.at(1);
            if(!nextVdv301trip.stopPointList.isEmpty())
            {
                Vdv301StopPoint firstVdv301StopPointOfNextTrip=nextVdv301trip.stopPointList.first();


                QVector<Vdv301DisplayContent> displayContentListInteriorNext=displayLabelLcd.filterVdv301DisplayContentByClass(firstVdv301StopPointOfNextTrip.displayContentList,DisplayContentInterior);
                QVector<Vdv301DisplayContent> displayContentListLcdNext=displayLabelLcd.filterVdv301DisplayContentByClass(firstVdv301StopPointOfNextTrip.displayContentList,DisplayContentLcd);

                /*
                  if(displayContentListLcdNext.isEmpty())
                  {
                      handleDisplayContentInner(displayContentListInteriorNext,false);
                  }
                  else
                  {
                      handleDisplayContentInner(displayContentListLcdNext,false);
                  }*/

                if(displayContentListLcdNext.isEmpty())
                {
                    handleDisplayContentInner(displayContentListInteriorNext,true);
                }
                else
                {
                    handleDisplayContentInner(displayContentListLcdNext,true);
                }
            }

        }
        else
        {
            qCDebug(MainWindowLog)<<"navazny spoj neni";
            ui->frame_navaznySpoj->hide();
        }

        //konecna

        if(vdv301AllData.isVehicleOnFinalStop()&&(!xmlParser2_3.followingTripExists(vdv301AllData.tripInformationList)))
        {
            displayLabelLcd.pageCycleList.push_front(ui->page_konecna);
            displayLabelShowPageFinalStop();
        }
        else
        {


            if(cisSubscriber.version()=="1.0")
            {
                if(xmlParser1_0.dataChanged==true)
                {
                    eventLcdReturnToStopList();
                }
            }
            else if(cisSubscriber.version()=="2.3")
            {
                if(xmlParser2_3.dataChanged==true)
                {
                    eventLcdReturnToStopList();
                }
            }
            else
            {
                qCDebug(MainWindowLog)<<"unsupported version";
            }


            displayLabelLcd.pageCycleList.push_front(ui->page_hlavni_2);
            // skryjZmenuPasma();


        }
        if(!connectionsStandalone)
        {
            if(!currentVdvStopPoint.connectionList.isEmpty())
            {
                mainWindowHelper.connectionListToTable(currentVdvStopPoint.connectionList,ui->tableWidget_connections);

                displayLabelLcd.pageCycleList.push_back(ui->page_prestupy);
                displayLabelLcd.displayLabelConnectionList(currentVdvStopPoint.connectionList);

                displayLabelLcdJis.pageCycleList.push_back(ui->page_prestupy_2M);
                displayLabelLcdJis.displayLabelConnectionList(currentVdvStopPoint.connectionList);
            }
            else
            {
                mainWindowHelper.eraseTable(ui->tableWidget_connections);
            }
        }

    }
    else
    {
        popUpMessage("stop index is out of range");
    }

    //additional text message
    /*
    if(additionalTextMessageText!="")
    {
        eventShowPageSpecialAnnouncement(additionalTextMessageHeadline,additionalTextMessageType,additionalTextMessageText,"");

    }
    else
    {
        displayLabelLcd.naplnAnouncementLabel("",ui->label_announcement);
    }
*/

    displayLabelLcd.lcdResizeLabels(ui->frame_hlavni->height());
    lcdLabelCurrentPageIndex=0;

    displayLabelLcd.timerLabelPageSwitch.start();
    displayLabelLcdJis.timerLabelPageSwitch.start();

    return 1;
}

int MainWindow::showReceivedDataLcdVdv301_2_3CZ1_0(Vdv301AllData2_3CZ1_0 vdv301AllData)
{

    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    bool timerOverride=false;


    //  eventEraseDisplayInformation();

    displayLabelLcd.pageCycleList.clear();
    displayLabelLcdJis.pageCycleList.clear();

    //   eventLcdSetMainPage();


    if(vdv301AllData.vehicleInformationGroup.vehicleStopRequested)
    {
        eventStopRequestedActivated();
    }
    else
    {
        eventStopRequestedDectivated();
    }

    updateLabelCurrentStopindex(QString::number(vdv301AllData.currentStopIndex));


    if(vdv301AllData.currentStopIndex<1 )
    {
        popUpMessage("stop index is smaller than 0");
        return 0;
    }
    else if(vdv301AllData.currentStopIndex<1 )
    {
        popUpMessage("stop index is 0");
        return 0;
    }
    else if(isInRange(vdv301AllData.currentStopIndex-1,vdv301AllData.tripInformationList.first().stopPointList.count(),Q_FUNC_INFO))
    {
        Vdv301Trip2_3CZ1_0 currentVdv301trip=vdv301AllData.tripInformationList.first();
        Vdv301StopPoint2_3CZ1_0 currentVdv301StopPoint=currentVdv301trip.stopPointList.at(vdv301AllData.currentStopIndex-1);


        //   displayLabelLcd.displayLabelViaPoints(currentDestinationPointList,vehicleState);

        labelLcdUpdateStopBackground(currentVdv301trip.locationState);




        QVector<Vdv301DisplayContent> displayContentListInterior=displayLabelLcd.filterVdv301DisplayContentByClass(currentVdv301StopPoint.displayContentList,DisplayContentInterior);
        QVector<Vdv301DisplayContent> displayContentListLcd=displayLabelLcd.filterVdv301DisplayContentByClass(currentVdv301StopPoint.displayContentList,DisplayContentLcd);


        if(displayContentListLcd.isEmpty())
        {
            handleDisplayContentInner(displayContentListInterior,false);
        }
        else
        {
            handleDisplayContentInner(displayContentListLcd,false);
        }

        displayLabelLcd.displayLabelStopFareZone(vdv301AllData);
        displayLabelLcdJis.displayLabelStopFareZone(vdv301AllData);


        if(xmlParser2_3CZ1_0.followingTripExists(vdv301AllData.tripInformationList))
        {
            Vdv301Trip2_3CZ1_0 nextVdv301trip=vdv301AllData.tripInformationList.at(1);
            if(!nextVdv301trip.stopPointList.isEmpty())
            {
                Vdv301StopPoint2_3CZ1_0 firstVdv301StopPointOfNextTrip=nextVdv301trip.stopPointList.first();
                //replace

                QVector<Vdv301DisplayContent> displayContentListInteriorNext=displayLabelLcd.filterVdv301DisplayContentByClass(firstVdv301StopPointOfNextTrip.displayContentList,DisplayContentInterior);
                QVector<Vdv301DisplayContent> displayContentListLcdNext=displayLabelLcd.filterVdv301DisplayContentByClass(firstVdv301StopPointOfNextTrip.displayContentList,DisplayContentLcd);

                /*
                  if(displayContentListLcdNext.isEmpty())
                  {
                      handleDisplayContentInner(displayContentListInteriorNext,false);
                  }
                  else
                  {
                      handleDisplayContentInner(displayContentListLcdNext,false);
                  }*/

                if(displayContentListLcdNext.isEmpty())
                {
                    handleDisplayContentInner(displayContentListInteriorNext,true);
                }
                else
                {
                    handleDisplayContentInner(displayContentListLcdNext,true);
                }
            }



        }
        else
        {
            qCDebug(MainWindowLog)<<"navazny spoj neni";
            ui->frame_navaznySpoj->hide();
        }



        //konecna

        if(vdv301AllData.isVehicleOnFinalStop()&&(!xmlParser2_3CZ1_0.followingTripExists(vdv301AllData.tripInformationList)))
        {
            displayLabelLcd.pageCycleList.push_front(ui->page_konecna);
            displayLabelLcdJis.pageCycleList.push_front(ui->page_konecna_2);
            displayLabelShowPageFinalStop();
        }
        else
        {
            displayLabelLcd.pageCycleList.push_front(ui->page_hlavni_2);
            displayLabelLcdJis.pageCycleList.push_front(ui->page_hlavni_3);


            if(!currentVdv301trip.additionalTextMessageList.isEmpty())
            {
                eventShowPageSpecialAnnouncement(currentVdv301trip.additionalTextMessageList,currentVdv301trip.additionalTextMessage1List,currentVdv301trip.additionalTextMessage2List,currentVdv301trip.additionalTextMessage3List,currentVdv301trip.additionalTextMessage4List);
                /*
                if(!currentVdv301trip.additionalTextMessage4List.isEmpty())
                {
                    if(currentVdv301trip.additionalTextMessage4List.first().text=="FareZoneChange")
                    {
                         timerOverride=true;
                        eventShowPageFareZoneChange(currentVdv301trip.additionalTextMessage2List,currentVdv301trip.additionalTextMessage3List);
                    }
                    else if(currentVdv301trip.additionalTextMessage4List.first().text=="LineChange")
                    {
                        //eventshowline change
                    }
                }
                else
                {
                    timerOverride=true;
                    eventShowPageSpecialAnnouncement(currentVdv301trip.additionalTextMessageList,currentVdv301trip.additionalTextMessage1List,currentVdv301trip.additionalTextMessage2List,currentVdv301trip.additionalTextMessage3List,currentVdv301trip.additionalTextMessage4List);
                }
                */

            }
            else
            {
                updateLabelAnnouncement("");
                if(allDataChanged(vdv301AllData,vdv301AllData2_3CZ1_0_previous))
                {
                    qCDebug(MainWindowLog)<<"all data changed";
                    eventLcdReturnToStopList();
                    displayLabelLcd.timerLabelPageSwitch.start();
                    displayLabelLcdJis.timerLabelPageSwitch.start();
                }
                else
                {
                    if(!displayLabelLcd.timerLabelPageSwitch.isActive())
                    {
                        displayLabelLcd.timerLabelPageSwitch.start();
                    }
                    if(!displayLabelLcdJis.timerLabelPageSwitch.isActive())
                    {
                        displayLabelLcdJis.timerLabelPageSwitch.start();
                    }
                }
                /*
                if(xmlParser2_3CZ1_0.dataChanged==true)
                {
                    eventLcdReturnToStopList();
                }
                */
            }

            /*
                if(!currentVdv301trip.additionalAnnouncementList.isEmpty())
                {

                    Vdv301AdditionalAnnouncement2_3CZ1_0 firstAnnouncement=currentVdv301trip.additionalAnnouncementList.first();
                    if(!firstAnnouncement.announcementTextList.isEmpty())
                    {
                        eventShowPageSpecialAnnouncement("","",firstAnnouncement.announcementTextList.first().text ,"");
                    }


                }
                else
                {

                    displayLabelLcd.naplnAnouncementLabel("",ui->label_announcement);
                    if(xmlParser1_0.dataChanged==true)
                    {
                        eventLcdReturnToStopList();
                    }
                }

            */

            // skryjZmenuPasma();

        }


        if(connectionsStandalone)
        {


            if(!golemioConnections.isEmpty())
            {
                mainWindowHelper.connectionListToTable(golemioConnections,ui->tableWidget_connections);

                //displayLabelLcd.pageCycleList.push_back(ui->page_prestupy);
                //displayLabelLcd.displayLabelConnectionListBasic(currentVdv301StopPoint.connectionList);

                QVector<ConnectionBasic> basicConnections;
                foreach (ConnectionGolemioV4 connection, golemioConnections ) {
                    basicConnections<<TypeConvertor::connectionGolemioV4toConnectionBasic(connection);
                }

                displayLabelLcdJis.pageCycleList.push_back(ui->page_prestupy_2M);
                displayLabelLcdJis.displayLabelConnectionListBasic(basicConnections);
            }
            else
            {
                mainWindowHelper.eraseTable(ui->tableWidget_connections);
            }
        }
        else
        {
            if(!currentVdv301StopPoint.connectionList.isEmpty())
            {
                mainWindowHelper.connectionListToTable(currentVdv301StopPoint.connectionList,ui->tableWidget_connections);

                displayLabelLcd.pageCycleList.push_back(ui->page_prestupy);
                displayLabelLcd.displayLabelConnectionList(currentVdv301StopPoint.connectionList);

                displayLabelLcdJis.pageCycleList.push_back(ui->page_prestupy_2M);
                displayLabelLcdJis.displayLabelConnectionList(currentVdv301StopPoint.connectionList);

            }
            else
            {
                mainWindowHelper.eraseTable(ui->tableWidget_connections);
            }
        }




    }
    else
    {
        popUpMessage("stop index is out of range");
    }


    displayLabelLcd.lcdResizeLabels(ui->frame_hlavni->height());

    // lcdLabelCurrentPageIndex=0;





    /*
    else
    {
        displayLabelLcd.timerLabelPageSwitch.start();
        displayLabelLcdJis.timerLabelPageSwitch.start();
    }
*/

    vdv301AllData2_3CZ1_0_previous=vdv301AllData;
    return 1;
}





void MainWindow::showReceivedDataVdv301(Vdv301AllData vdv301AllData)
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;

    mainWindowHelper.eraseTable(ui->tableWidget_debugStopList);
    mainWindowHelper.eraseTable(ui->tableWidget_connections);
    updateMainScreenDebugLabels();

    int tripCount=vdv301AllData.tripInformationList.count();

    updateLabelCurrentStopindex(QString::number(vdv301AllData.currentStopIndex));


    if(tripCount==0)
    {
        // empty trip list
        qCDebug(MainWindowLog)<<"empty trip list";
    }
    else if(tripCount>0)
    {
        debugStopPointListToTable(vdv301AllData.tripInformationList.at(0).stopPointList,false);
        if(tripCount>1)
        {
            debugStopPointListToTable(vdv301AllData.tripInformationList.at(1).stopPointList,true);
        }

        if(vdv301AllData.currentStopIndex>0)
        {
            if( vdv301AllData.tripInformationList.first().stopPointList.size()>0)
            {

                if(isInRange(vdv301AllData.currentStopIndex-1,vdv301AllData.tripInformationList.first().stopPointList.count(),Q_FUNC_INFO))
                {
                    //normal state on route


                    showReceivedDataLcdVdv301(vdv301AllData);
                    //showReceivedDataLed();

                    // svgRender();
                }
                else
                {
                    eventDisplayAbnormalStateScreen("STOP INDEX OUT OF RANGE");
                }

                //instanceHttpServeru.prijatoZeServeruTelo="";
            }
            else
            {
                eventDisplayAbnormalStateScreen("COULDNT PARSE STOPS");
            }
        }
        else
        {
            eventDisplayAbnormalStateScreen("STOP INDEX <=0");
        }
    }
}



void MainWindow::showReceivedDataVdv301_2_3CZ1_0(Vdv301AllData2_3CZ1_0 vdv301AllData)
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;

    mainWindowHelper.eraseTable(ui->tableWidget_debugStopList);
    mainWindowHelper.eraseTable(ui->tableWidget_connections);
    updateMainScreenDebugLabels();

    int tripCount=vdv301AllData.tripInformationList.count();

    golemioVehicleType=TypeConvertor::vehicleSubmodeToGolemioType(vdv301AllData.vehicleInformationGroup.vehicleMode);
    emit signalVehicleRefUpdate(vdv301AllData.vehicleRef);

    if(tripCount==0)
    {
        // empty trip list
        qCDebug(MainWindowLog)<<"empty trip list";
        QVector<Vdv301DisplayContent> emptyDisplayContentList;
        showReceivedDataLedVdv301(emptyDisplayContentList,vdv301AllData.globalDisplayContentList );

    }
    else if(tripCount>0)
    {
        Vdv301Trip2_3CZ1_0 currentVdv301Trip=vdv301AllData.tripInformationList.first();
        debugStopPointListToTable(currentVdv301Trip.stopPointList,false);
        if(tripCount>1)
        {

            debugStopPointListToTable(vdv301AllData.tripInformationList.at(1).stopPointList,true);
        }

        if(vdv301AllData.currentStopIndex>0)
        {
            if( currentVdv301Trip.stopPointList.size()>0)
            {

                if(isInRange(vdv301AllData.currentStopIndex-1,currentVdv301Trip.stopPointList.count(),Q_FUNC_INFO))
                {
                    //normal state on route
                    Vdv301StopPoint2_3CZ1_0 currentVdv301StopPoint=currentVdv301Trip.stopPointList.at(vdv301AllData.currentStopIndex-1);
                    emit signalStopRefUpdate(currentVdv301StopPoint.stopRef);

                    showReceivedDataLcdVdv301_2_3CZ1_0(vdv301AllData);
                    showReceivedDataLedVdv301(currentVdv301StopPoint.displayContentList,vdv301AllData.globalDisplayContentList );

                    // svgRender();
                }
                else
                {
                    eventDisplayAbnormalStateScreen("STOP INDEX OUT OF RANGE");
                }

                //instanceHttpServeru.prijatoZeServeruTelo="";
            }
            else
            {
                eventDisplayAbnormalStateScreen("COULDNT PARSE STOPS");
            }
        }
        else
        {
            eventDisplayAbnormalStateScreen("STOP INDEX <=0");
        }
    }
}




void MainWindow::showReceivedDataVdv301_2_3CZ1_0(Vdv301CurrentDisplayContent vdv301currentDisplayContent)
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;

    mainWindowHelper.eraseTable(ui->tableWidget_debugStopList);
    updateMainScreenDebugLabels();


    QVector<Vdv301DisplayContent> emptyDisplayContentList;

    showReceivedDataLedVdv301(emptyDisplayContentList,vdv301currentDisplayContent.displayContentList );
}







void MainWindow::slotDebugServiceToTable(QZeroConfService zcs)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    qint32 row;
    QTableWidgetItem *cell;

    QString name=zcs->name();
    QString ipaddress=zcs->ip().toString();
    QString host=zcs->host();
    QString version=zcs.data()->txt().value("ver");
    int port=zcs->port();

    qCDebug(MainWindowLog) <<"service name "<<name<<" ip address"<<ipaddress<<" port "<<QString::number(port)<<" data" <<version ;


    row = ui->tableWidget_services->rowCount();
    ui->tableWidget_services->insertRow(row);
    cell = new QTableWidgetItem(name);
    ui->tableWidget_services->setItem(row, 0, cell);

    cell = new QTableWidgetItem(version);
    ui->tableWidget_services->setItem(row, 1, cell);

    cell = new QTableWidgetItem(ipaddress);
    ui->tableWidget_services->setItem(row, 2, cell);

    cell = new QTableWidgetItem(QString::number(port));
    ui->tableWidget_services->setItem(row, 3, cell);

    cell = new QTableWidgetItem(host);
    ui->tableWidget_services->setItem(row, 4, cell);


    ui->tableWidget_services->resizeColumnsToContents();


    qCDebug(MainWindowLog)<<"sluzbaDoTabulky_konec";

}




void MainWindow::slotDebugPublisherToTable(PublisherStruct publisher)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    mainWindowHelper.eraseTable(ui->tableWidget_selectedSubscriber);
    qint32 row;
    QTableWidgetItem *cell;

    QString name=publisher.serviceName;
    QString ipAddress=publisher.hostAddress.toString();
    QString host=publisher.hostname;
    QString version=publisher.ibisIpVersion;
    int port=publisher.portNumber;
    /*
    qCDebug(MainWindowLog) <<"nazev sluzby "<<nazev<<" ip adresa "<<ipadresa<<" port "<<QString::number(port)<<" data" <<verze ;

 */

    row = ui->tableWidget_selectedSubscriber->rowCount();
    ui->tableWidget_selectedSubscriber->insertRow(row);
    cell = new QTableWidgetItem(name);
    ui->tableWidget_selectedSubscriber->setItem(row, 0, cell);

    cell = new QTableWidgetItem(version);
    ui->tableWidget_selectedSubscriber->setItem(row, 1, cell);

    cell = new QTableWidgetItem(ipAddress);
    ui->tableWidget_selectedSubscriber->setItem(row, 2, cell);

    cell = new QTableWidgetItem(QString::number(port));
    ui->tableWidget_selectedSubscriber->setItem(row, 3, cell);

    cell = new QTableWidgetItem(host);
    ui->tableWidget_selectedSubscriber->setItem(row, 4, cell);


    ui->tableWidget_selectedSubscriber->resizeColumnsToContents();

    eventDisplayAbnormalStateScreen("SUBSCRIBED");
}

void MainWindow::slotDelayedStartup()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    //  CustomerInformationServiceSubscriber.hledejSluzby("_ibisip_http._tcp.",0);
    //  CustomerInformationServiceSubscriber.hledejSluzby("_ibisip_http._tcp.",1);
    //cisSubscriber.novePrihlaseniOdberu();
}

void MainWindow::slotDeviceIpUpdated(QHostAddress input)
{
    ui->label_subscriptionDeviceIp->setText(input.toString());
}


void MainWindow::slotDeviceParametersToConfigFile()
{
    qCDebug(MainWindowLog)<<Q_FUNC_INFO;

    deviceManagementServiceInternalVariablesToSettingFile();
    constantsToSettingsPage();
    updateMainScreenDebugLabels();
}

// move to displayLAbelLcd???
void MainWindow::slotDisplayLcdLabelCyclePages()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO<<" counter ma hodnotu "<<lcdLabelCurrentPageIndex<<" v seznamu je "<<displayLabelLcd.pageCycleList.count();

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

void MainWindow::slotDisplayLcdLabelCyclePagesJis()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO<<" counter ma hodnotu "<<lcdLabelCurrentPageIndexJis<<" v seznamu je "<<displayLabelLcdJis.pageCycleList.count();

    lcdLabelCurrentPageIndexJis++;

    if(lcdLabelCurrentPageIndexJis>=(displayLabelLcdJis.pageCycleList.count()))
    {
        lcdLabelCurrentPageIndexJis=0;
        qCDebug(MainWindowLog)<<"counter reset";
    }
    /*
    else
    {
        lcdLabelCurrentPageIndexJis++;
    }
*/

    ui->label_jisPageCount->setText(QString::number(lcdLabelCurrentPageIndexJis+1)+"/"+QString::number(displayLabelLcdJis.pageCycleList.count()));


    if(lcdLabelCurrentPageIndexJis<displayLabelLcdJis.pageCycleList.count())
    {
        qCDebug(MainWindowLog)<<"page "+QString::number(lcdLabelCurrentPageIndexJis)+" is in range";
        displayLabelLcdJis.stackedWidget_middle->setCurrentWidget(displayLabelLcdJis.pageCycleList.at(lcdLabelCurrentPageIndexJis));
    }
    else
    {
        qCDebug(MainWindowLog)<<"page out of range";
    }
}



bool MainWindow::slotDownloadGolemio()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    if(!golemioStopRef.isEmpty())
    {
        golemioParametry=golemioRequestCompose(golemioStopRef,golemioVehicleRef,golemioVehicleType);
        golemio.startDataDownload(golemioParametry);
        timerUpdateGolemio.start();
    }
    else
    {
        qCDebug(MainWindowLog)<<"invalid stopRef";
    }

    return true;
}



int MainWindow::slotEverySecond()
{

    ui->label_remainingSeconds->setText(QString::number(cisSubscriber.timerHeartbeatCheck.remainingTime()/1000) );
    ui->label_isSubscribed->setText(QString::number(cisSubscriber.isSubscriptionActive));
    ui->label_jisSwitchTimer->setText(QString::number(floor(displayLabelLcdJis.timerLabelPageSwitch.remainingTime()/1000)));
    ui->label_jisPageCount->setText(QString::number(lcdLabelCurrentPageIndexJis+1)+"/"+QString::number(displayLabelLcdJis.pageCycleList.count()));

    if(showTimeColon==true)
    {
        ui->label_hodiny->setText(QTime::currentTime().toString("hh:mm") );
        ui->label_hodiny_2->setText(QTime::currentTime().toString("hh:mm") );
        showTimeColon=false;
    }
    else
    {
        ui->label_hodiny->setText(QTime::currentTime().toString("hh mm") );
        ui->label_hodiny_2->setText(QTime::currentTime().toString("hh mm") );
        showTimeColon=true;
    }

    return 1;
}


void MainWindow::slotGolemioReady()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    golemio.naplnVstupDokument(golemio.stazenaData);
    golemioConnections=golemio.parseDomDocumentDepartures();
    golemioStops=golemio.parseDomDocumentStops();
    golemioInfotexts=golemio.parseDomDocumentInfotexts();

    /* if(filterConnections)
    {
        //   prestupy=xmlMpvParser.vyfiltrujPrestupy(prestupy,stavSystemu.aktlinka);
    }*/
    qCDebug(MainWindowLog)<<"pocet Prestupu ve vektoru: "<<golemioConnections.count();

    mainWindowHelper.connectionListToTable(golemioConnections,ui->tableWidget_connections);

    showReceivedDataVdv301_2_3CZ1_0(vdv301AllData2_3CZ1_0);
}


void MainWindow::slotHeartbeatTimeout()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

}


void MainWindow::slotLogWindowAppend(const QString &text)
{
    ui->plainTextEdit_debugLogContent->appendPlainText(text);
}



void MainWindow::slotMoveScrollingText()
{
    int textWidthPixels=displayLabelLcd.labelViaPointsScrolling->width();
    int stepSize=1;

    if(textWidthPixels<ui->scrollArea->width() )
    {
        return;
    }
    // qCDebug(MainWindowLog)<<"delka beziciho textu "<< delkaTextu << " posun rotovani: "<<posunRotovani;

    displayLabelLcd.scrollingTextOffset-=stepSize;

    if (abs(displayLabelLcd.scrollingTextOffset)>textWidthPixels)
    {
        displayLabelLcd.scrollingTextOffset=0;
    }

    else
    {
        ui->scrollAreaWidgetContents->scroll(-stepSize,0);
    }

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

void MainWindow::slotStopRefUpdate(QString stopRef)
{
    if(golemioStopRef!=stopRef)
    {
        golemioStopRef=stopRef;
        ui->label_debugStopRef->setText(golemioStopRef);
        slotDownloadGolemio();
    }
}



void MainWindow::slotSubscriptionLost()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    mainWindowHelper.eraseTable(ui->tableWidget_selectedSubscriber);
    receivedDataVariablesReset();
    eventDisplayAbnormalStateScreen("NO SUBSCRIPTION");
}





void MainWindow::slotToggleFullscreen()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
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

    //displayLabelLed.ledUpdateDisplaySizes(); //pada kdyz je odkomentovano




}





void MainWindow::slotUpdateServiceTable()
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
    debugServiceListToTable(cisSubscriber.serviceList);
}

void MainWindow::slotVehicleRefUpdate(QString vehicleRef)
{
    if(golemioVehicleRef!=vehicleRef)
    {
        golemioVehicleRef=vehicleRef;
        ui->label_debugVehicleRef->setText(golemioVehicleRef);
        slotDownloadGolemio();
    }
}


// XXX FIX GlobalDisplayContent while Stop List is not empty!
void MainWindow::slotXmlToVehicleStateVariables(QString inputXmlString)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;


    ui->plainTextEdit_debugReceivedXml->setPlainText(inputXmlString);
    receivedDataVariablesReset();

    //  xmlParser1_0.loadXmlFile(inputXmlString);
    //  qCDebug(MainWindowLog)<<"timestamp:"<<xmlParser1_0.parseTimestamp(xmlParser1_0.receivedDataDomDocument).toString(Qt::ISODate);

    receivedMessagesCounter++;
    ui->label_messageCounter->setText(QString::number(receivedMessagesCounter));
    ui->label_messageCounter2->setText(QString::number(receivedMessagesCounter));




    if(cisSubscriber.version()=="1.0")
    {
        xmlParser1_0.loadXmlFile(inputXmlString);


        if(cisSubscriber.structureName()=="AllData")
        {
            vdv301AllData=xmlParser1_0.parseAllData1_0(xmlParser1_0.receivedDataDomDocument,currentVdv301StopPointList);

            if(vdv301AllData.tripInformationList.isEmpty())
            {
                eventNotOnLine();
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
        else if (cisSubscriber.structureName()=="CurrentDisplayContent")
        {
            vdv301currentDisplayContent=xmlParser1_0.parseCurrentDisplayContent1_0(xmlParser1_0.receivedDataDomDocument);
        }
        else
        {
            qCDebug(MainWindowLog)<<"unknown structure to parse";
        }
    }


    else if(cisSubscriber.version()=="2.3")
    {
        xmlParser2_3.loadXmlFile(inputXmlString);

        if(cisSubscriber.structureName()=="AllData")
        {
            vdv301AllData=xmlParser2_3.parseAllData2_3(xmlParser2_3.receivedDataDomDocument,currentVdv301StopPointList);

            if(vdv301AllData.tripInformationList.isEmpty())
            {
                eventNotOnLine();
                displayLabelLed.ledUpdateDisplayedInformationFromDisplayContentList2_3(vdv301AllData.globalDisplayContentList);
                return;
            }
        }
        else if (cisSubscriber.structureName()=="CurrentDisplayContent")
        {
            vdv301currentDisplayContent=xmlParser2_3.parseCurrentDisplayContent2_3(xmlParser2_3.receivedDataDomDocument);

        }
        else
        {
            qCDebug(MainWindowLog)<<"unknown structure to parse";
        }

    }

    else if(cisSubscriber.version()=="2.3CZ1.0")
    {
        xmlParser2_3CZ1_0.loadXmlFile(inputXmlString);


        if(cisSubscriber.structureName()=="AllData")
        {
            //vdv301AllData2_3CZ1_0_previous=vdv301AllData2_3CZ1_0;
            vdv301AllData2_3CZ1_0=xmlParser2_3CZ1_0.parseAllData2_3CZ1_0(xmlParser2_3CZ1_0.receivedDataDomDocument);
            updateLabelCurrentStopindex(QString::number(vdv301AllData2_3CZ1_0.currentStopIndex));

            if(ui->checkBox_logMessages->isChecked())
            {
                messageToTable(vdv301AllData2_3CZ1_0);
            }

            if(vdv301AllData2_3CZ1_0.tripInformationList.isEmpty())
            {
                eventNotOnLine();
                displayLabelLed.ledUpdateDisplayedInformationFromDisplayContentList2_3(vdv301AllData2_3CZ1_0.globalDisplayContentList);
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
        else if (cisSubscriber.structureName()=="CurrentDisplayContent")
        {
            vdv301currentDisplayContent=xmlParser2_3CZ1_0.parseCurrentDisplayContent2_3(xmlParser2_3CZ1_0.receivedDataDomDocument);
        }
        else
        {
            qCDebug(MainWindowLog)<<"unknown structure to parse";
        }


    }

    else
    {
        eventDisplayAbnormalStateScreen("INCORRECT SUBSCRIBER VERSION");
        return;
    }




    if(cisSubscriber.version()=="2.3")
    {
        if(cisSubscriber.structureName()=="AllData")
        {
            showReceivedDataVdv301(vdv301AllData);
        }
        else if(cisSubscriber.structureName()=="CurrentDisplayContent")
        {
            //showReceivedDataVdv301(vdv301currentDisplayContent);
        }
        else
        {
            qCDebug(MainWindowLog)<<"unknown structure to show";
        }

    }
    else if(cisSubscriber.version()=="2.3CZ1.0")
    {
        if(cisSubscriber.structureName()=="AllData")
        {

            showReceivedDataVdv301_2_3CZ1_0(vdv301AllData2_3CZ1_0);

        }
        else if(cisSubscriber.structureName()=="CurrentDisplayContent")
        {
            showReceivedDataVdv301_2_3CZ1_0(vdv301currentDisplayContent);
        }
        else
        {
            qCDebug(MainWindowLog)<<"unknown structure to show";
        }


        //showReceivedDataLedVdv301(vdv301AllData);

    }
    else if(cisSubscriber.version()=="1.0")
    {
        if(cisSubscriber.structureName()=="AllData")
        {
            showReceivedDataVdv301(vdv301AllData);
        }
        else if(cisSubscriber.structureName()=="CurrentDisplayContent")
        {
            //showReceivedDataVdv301(vdv301currentDisplayContent);
        }
        else
        {
            qCDebug(MainWindowLog)<<"unknown structure to show";
        }
    }
    else
    {
        qCDebug(MainWindowLog)<<"unknown VDV301 version data";
    }


}



bool MainWindow::svgOpenFile(const QString &fileName)
{
    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;
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




//zkpirovano z svgviewer demo

bool MainWindow::svgRender()
{
    /*
    if (currentDestinationPointList.length()>0)
    {
        //svgVykreslovac.svgReplaceName("Verlauf2.svg","vystup.txt",globalniSeznamZastavek.last().StopName,globalniSeznamZastavek.at(stavSystemu.indexAktZastavky).StopName,globalniSeznamZastavek.at(stavSystemu.indexAktZastavky+1).StopName,globalniSeznamZastavek.at(stavSystemu.indexAktZastavky+2).StopName);
        //svgVykreslovani.aktualizujVse(currentDestinationPointList,vehicleState);
    }
    else
    {
        qCDebug(MainWindowLog)<<"seznam zastavek je prazdny";
    }
*/
    int vysledek=svgOpenFile(QCoreApplication::applicationDirPath()+"/vystup.svg");
    qCDebug(MainWindowLog)<<"vysledek otevirani SVG je"<<QString::number(vysledek);

    return true;
}










/*
bool MainWindow::isVehicleOnFinalStop(Vdv301AllData allData)
{

    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    if(allData.tripInformationList.isEmpty())
    {
        return false;
    }

    if(allData.tripInformationList.first().stopPointList.isEmpty())
    {
        return false;
    }

    if(allData.currentStopIndex<1)
    {
        return false;
    }

    if((allData.currentStopIndex==(allData.tripInformationList.first().stopPointList.count()))&&(allData.tripInformationList.first().locationState==Vdv301Enumerations::LocationStateAtStop))
    {
        return true;
    }
    return false;
}
*/
/*
bool MainWindow::isVehicleOnFinalStop(Vdv301AllData2_3CZ1_0 allData)
{

    qCDebug(MainWindowLog) <<  Q_FUNC_INFO;

    if(allData.tripInformationList.isEmpty())
    {
        return false;
    }

    if(allData.tripInformationList.first().stopPointList.isEmpty())
    {
        return false;
    }

    if(allData.currentStopIndex<1)
    {
        return false;
    }

    if((allData.currentStopIndex==(allData.tripInformationList.first().stopPointList.count()))&&(allData.tripInformationList.first().locationState==Vdv301Enumerations::LocationStateAtStop))
    {
        return true;
    }
    return false;
}

*/









void MainWindow::updateLabelAnnouncement(QString announcementText)
{
    displayLabelLcd.naplnAnouncementLabel(announcementText,ui->label_announcement);


    // ui->label_debugAnnouncement->setText(announcementText);
    ui->label_debugAnnouncement->setText(announcementText);
}
void MainWindow::updateLabelCurrentStopindex(QString currentStopIndex)
{
    ui->label_debugCurrentStopIndex->setText(currentStopIndex);
    ui->label_currentStopIndex->setText(currentStopIndex);
}

void MainWindow::updateLabelLocationState(QString locationState)
{
    ui->label_debugLocationState->setText(locationState);
    ui->label_locationState->setText(locationState);
}




void MainWindow::updateMainScreenDebugLabels()
{
    ui->label_subscribedVersion->setText(cisSubscriber.version());
    ui->label_deviceClass->setText(deviceManagementService.deviceClass());
    ui->label_deviceID->setText(deviceManagementService.deviceId());

    if(cisSubscriber.version()=="2.3CZ1.0")
    {
        if(!vdv301AllData2_3CZ1_0.tripInformationList.isEmpty())
        {
            updateLabelLocationState(Vdv301Enumerations::LocationStateEnumerationToQString(vdv301AllData2_3CZ1_0.tripInformationList.first().locationState));
        }
        else
        {
            updateLabelLocationState("");
        }
    }
    else
    {
        if(!vdv301AllData.tripInformationList.isEmpty())
        {
            updateLabelLocationState(Vdv301Enumerations::LocationStateEnumerationToQString(vdv301AllData.tripInformationList.first().locationState));
        }
        else         {
            updateLabelLocationState("");
        }
    }



    ui->label_build->setText(createProgramVersionString());
    ui->label_lcd_version->setText(createProgramVersionString());
    ui->label_build->setTextInteractionFlags(Qt::TextSelectableByMouse);
}
