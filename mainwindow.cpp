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

    displayLabelLcd.lcdResizeLabels(ui->frame_hlavni->height());

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
}

MainWindow::~MainWindow()
{
    qDebug() <<  Q_FUNC_INFO;
    delete ui;
}

void MainWindow::allConnects()
{
    qDebug() <<  Q_FUNC_INFO;
    connect(&cisSubscriber, &IbisIpSubscriber::signalDataReceived  ,this, &MainWindow::slotXmlToVehicleStateVariables);
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


void MainWindow::updateMainScreenDebugLabels()
{
    ui->label_subscribedVersion->setText(cisSubscriber.version());
    ui->label_deviceClass->setText(deviceManagementService.deviceClass());
    ui->label_deviceID->setText(deviceManagementService.deviceId());

    if(cisSubscriber.version()=="2.3CZ1.0")
    {
        if(!vdv301AllData2_3CZ1_0.tripInformationList.isEmpty())
        {
            ui->label_locationState->setText(Vdv301Enumerations::LocationStateEnumerationToQString(vdv301AllData2_3CZ1_0.tripInformationList.first().locationState));
        }
        else
        {
            ui->label_locationState->setText("");
        }
    }
    else
    {
        if(!vdv301AllData.tripInformationList.isEmpty())
        {
            ui->label_locationState->setText(Vdv301Enumerations::LocationStateEnumerationToQString(vdv301AllData.tripInformationList.first().locationState));
        }
        else         {
            ui->label_locationState->setText("");
        }
    }



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

void MainWindow::deviceManagementServiceInternalVariablesToSettingFile()
{
    settings.setValue("deviceManagementService/deviceName",deviceManagementService.deviceName());
    settings.setValue("deviceManagementService/deviceManufacturer",deviceManagementService.deviceManufacturer());
    settings.setValue("deviceManagementService/deviceSerialNumber",deviceManagementService.deviceSerialNumber());
    settings.setValue("deviceManagementService/deviceClass",deviceManagementService.deviceClass());
    settings.setValue("deviceManagementService/deviceId",deviceManagementService.deviceId());
    settings.setValue("deviceManagementService/version",deviceManagementService.version());

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
    displayLabelLcd.labelDestinationFollowing= ui->label_followingDestination;
    displayLabelLcd.labelLineFollowing= ui->label_followingLine;

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

    if(settings.value("cisSubscriber/structure").toString()=="")
    {
        cisSubscriber.setStructureName("AllData");
    }
    else
    {
        cisSubscriber.setStructureName(settings.value("cisSubscriber/structure").toString());
    }



    menuSwitchTabs(settings.value("window/defaultScreen").toInt());
    if(settings.value("window/fullscreen").toBool()==true)
    {
        slotToggleFullscreen();
    }

}


void MainWindow::menuSwitchTabs(int tabNumber)
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





QString MainWindow::createProgramVersionString()
{
    QDate compilationDate=QLocale("en_US").toDate(QString(__DATE__).simplified(), "MMM d yyyy");
    QTime compilationTime=QTime::fromString(__TIME__,"hh:mm:ss");
    qDebug()<<" date:"<<compilationDate<<" time:"<<compilationTime;
    QString version=compilationDate.toString("yyyyMMdd")+"_"+compilationTime.toString("hhmm");
    return version;
}


void MainWindow::slotDebugServiceToTable(QZeroConfService zcs)
{
    qDebug() <<  Q_FUNC_INFO;
    qint32 row;
    QTableWidgetItem *cell;

    QString name=zcs->name();
    QString ipaddress=zcs->ip().toString();
    QString host=zcs->host();
    QString version=zcs.data()->txt().value("ver");
    int port=zcs->port();

    qDebug() <<"service name "<<name<<" ip address"<<ipaddress<<" port "<<QString::number(port)<<" data" <<version ;


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


    qDebug()<<"sluzbaDoTabulky_konec";

}


void MainWindow::slotDelayedStartup()
{
    qDebug() <<  Q_FUNC_INFO;
    //  CustomerInformationServiceSubscriber.hledejSluzby("_ibisip_http._tcp.",0);
    //  CustomerInformationServiceSubscriber.hledejSluzby("_ibisip_http._tcp.",1);
    //cisSubscriber.novePrihlaseniOdberu();
}

void MainWindow::slotDebugPublisherToTable(QZeroConfService zcs)
{
    qDebug() <<  Q_FUNC_INFO;
    eraseTable(ui->tableWidget_selectedSubscriber);
    qint32 row;
    QTableWidgetItem *cell;

    QString name=zcs->name();
    QString ipAddress=zcs->ip().toString();
    QString host=zcs->host();
    QString version=zcs.data()->txt().value("ver");
    int port=zcs->port();
    /*
    qDebug() <<"nazev sluzby "<<nazev<<" ip adresa "<<ipadresa<<" port "<<QString::number(port)<<" data" <<verze ;

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



int MainWindow::slotEverySecond()
{

    ui->label_remainingSeconds->setText(QString::number(cisSubscriber.timerHeartbeatCheck.remainingTime()/1000) );
    ui->label_isSubscribed->setText(QString::number(cisSubscriber.isSubscriptionActive));

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
    eventDisplayAbnormalStateScreen("NO SUBSCRIPTION");
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




void MainWindow::slotDeviceParametersToConfigFile()
{
    qDebug()<<Q_FUNC_INFO;

    deviceManagementServiceInternalVariablesToSettingFile();
    constantsToSettingsPage();
    updateMainScreenDebugLabels();
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

    displayLabelLcd.pageAdditionalTextMessage=ui->page_additionalTextMessage;
    displayLabelLcd.pageRoute=ui->page_route;

    displayLabelLcd.stackedWidget_middle=ui->stackedWidget_prostredek;
    displayLabelLcd.stackedWidget_onService=ui->stackedWidget_onService;

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
    ui->stackedWidget_onService->setCurrentWidget(ui->page_version);
    displayLabelLcd.displayLabelEraseInformation();
    svgVykreslovani.vymazObrazovku();
    displayLabelLed.ledClearDisplays();
}


void MainWindow::eventEraseDisplayInformation()
{
    qDebug() <<  Q_FUNC_INFO;
    displayLabelLcd.displayLabelEraseInformation();
}

void MainWindow::eventLcdSetMainPage()
{
    qDebug() <<  Q_FUNC_INFO;
    //LCD label
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_hlavni_2);
}

void MainWindow::eventLcdShowFollowingTripDestination(QString followingTripLine,QString followingTripDestination)
{
    qDebug() <<  Q_FUNC_INFO;
    //LABEL LCD
    ui->label_followingLine->setText(followingTripLine);
    ui->label_followingDestination->setText(followingTripDestination);
    ui->frame_navaznySpoj->show();

    //SVG

}


void MainWindow::eventShowPageFareZoneChange(QVector<Vdv301InternationalText> fromFareZones, QVector<Vdv301InternationalText> toFareZones)
{
    qDebug() <<  Q_FUNC_INFO;
    displayLabelShowFareZoneChange(fromFareZones,toFareZones);
    svgVykreslovani.zobrazZmenuPasma(fromFareZones,toFareZones);
}




void MainWindow::eventStopRequestedActivated()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->label_stopRequested->setText("<b>STOP</b>");
    ui->label_stopRequestedSymbol->show();
}

void MainWindow::eventStopRequestedDectivated()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->label_stopRequested->setText("STOP");
    ui->label_stopRequestedSymbol->hide();
}

void MainWindow::eventShowPageSpecialAnnouncement(QString title,QString type,QString textCz, QString textEn)
{
    qDebug() <<  Q_FUNC_INFO;
    displayLabelShowAnnoucement(title,type,textCz,textEn);
    svgVykreslovani.zobrazAnnoucement(title,type,textCz,textEn);
}

void MainWindow::eventShowPageSpecialAnnouncement(QVector<Vdv301InternationalText> additionalTextMessage,QVector<Vdv301InternationalText> additionalTextMessage1,QVector<Vdv301InternationalText> additionalTextMessage2, QVector<Vdv301InternationalText> additionalTextMessage3,QVector<Vdv301InternationalText> additionalTextMessage4)
{
    qDebug() <<  Q_FUNC_INFO;
    displayLabelShowAnnoucement(additionalTextMessage,additionalTextMessage1,additionalTextMessage2,additionalTextMessage3,additionalTextMessage4);
    //   svgVykreslovani.zobrazAnnoucement(title,type,textCz,textEn);
}

void MainWindow::eventDisplayAbnormalStateScreen(QString displayState)
{
    qDebug()<<Q_FUNC_INFO<<" "<<displayState;
    ui->label_lcd_state->setText(displayState);
    eraseDisplayedInformation();
    ui->stackedWidget_onService->setCurrentWidget(ui->page_version);

}

void MainWindow::eventNotOnLine()
{
    qDebug() <<  Q_FUNC_INFO;
    eventDisplayAbnormalStateScreen("NOT ON LINE");
}



void MainWindow::showReceivedDataLedVdv301(QVector<Vdv301DisplayContent> stopDisplayContentList, QVector<Vdv301DisplayContent> globalDisplayContentList)
{
    qDebug()<<Q_FUNC_INFO;

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

    qDebug() <<  Q_FUNC_INFO;

    eventLcdSetMainPage();
    eventEraseDisplayInformation();
    displayLabelLcd.pageCycleList.clear();

    if(vdv301AllData.vehicleInformationGroup.vehicleStopRequested)
    {
        eventStopRequestedActivated();
    }
    else
    {
        eventStopRequestedDectivated();
    }

    ui->label_currentStopIndex->setText(QString::number(vdv301AllData.currentStopIndex));


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
            qDebug()<<"navazny spoj neni";
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
                qDebug()<<"unsupported version";
            }


            displayLabelLcd.pageCycleList.push_front(ui->page_hlavni_2);
            // skryjZmenuPasma();


        }

        if(!currentVdvStopPoint.connectionList.isEmpty())
        {

            displayLabelLcd.pageCycleList.push_back(ui->page_prestupy);
            displayLabelLcd.displayLabelConnectionList(currentVdvStopPoint.connectionList);

            connectionListToTable(currentVdvStopPoint.connectionList,ui->tableWidget_connections);
        }
        else
        {
            eraseTable(ui->tableWidget_connections);
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

    return 1;
}

int MainWindow::showReceivedDataLcdVdv301_2_3CZ1_0(Vdv301AllData2_3CZ1_0 vdv301AllData)
{

    qDebug() <<  Q_FUNC_INFO;

    bool timerOverride=false;

    eventLcdSetMainPage();
    eventEraseDisplayInformation();
    displayLabelLcd.pageCycleList.clear();

    if(vdv301AllData.vehicleInformationGroup.vehicleStopRequested)
    {
        eventStopRequestedActivated();
    }
    else
    {
        eventStopRequestedDectivated();
    }

    ui->label_currentStopIndex->setText(QString::number(vdv301AllData.currentStopIndex));


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
            qDebug()<<"navazny spoj neni";
            ui->frame_navaznySpoj->hide();
        }



        //konecna

        if(vdv301AllData.isVehicleOnFinalStop()&&(!xmlParser2_3CZ1_0.followingTripExists(vdv301AllData.tripInformationList)))
        {
            displayLabelLcd.pageCycleList.push_front(ui->page_konecna);
            displayLabelShowPageFinalStop();
        }
        else
        {
            displayLabelLcd.pageCycleList.push_front(ui->page_hlavni_2);


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
                }*/

            }
            else
            {

                displayLabelLcd.naplnAnouncementLabel("",ui->label_announcement);
                if(xmlParser2_3CZ1_0.dataChanged==true)
                {
                    eventLcdReturnToStopList();
                }
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

        if(!currentVdv301StopPoint.connectionList.isEmpty())
        {

            displayLabelLcd.pageCycleList.push_back(ui->page_prestupy);
            displayLabelLcd.displayLabelConnectionList(currentVdv301StopPoint.connectionList);

            connectionListToTable(currentVdv301StopPoint.connectionList,ui->tableWidget_connections);
        }
        else
        {
            eraseTable(ui->tableWidget_connections);
        }
    }
    else
    {
        popUpMessage("stop index is out of range");
    }


    displayLabelLcd.lcdResizeLabels(ui->frame_hlavni->height());

    lcdLabelCurrentPageIndex=0;
    if(timerOverride)
    {
        displayLabelLcd.timerLabelPageSwitch.stop();
    }
    else
    {
        displayLabelLcd.timerLabelPageSwitch.start();
    }


    return 1;
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
        }
        else
        {
            displayLabelLcd.displayLabelDestinationFollowing(destination);
        }

        if(line.lineNameList.isEmpty())
        {
            displayLabelLcd.displayLabelLineNameFollowing("");
        }
        else
        {
            displayLabelLcd.displayLabelLineNameFollowing(line);
        }
    }
    else
    {
        if(destination.destinationNameList.isEmpty())
        {
            displayLabelLcd.displayLabelDestination("");
        }
        else
        {
            displayLabelLcd.displayLabelDestination(destination);
        }

        if(line.lineNameList.isEmpty())
        {
            displayLabelLcd.displayLabelLineName("");
        }
        else
        {
            displayLabelLcd.displayLabelLineName(line);
        }

        displayLabelLcd.displayLabelViaPoints(displayContentList.first().viaPointList);
    }



    //displayLabelLcd.displayLabelLineName(line);




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




void MainWindow::debugStopPointListToTable(QVector<Vdv301StopPoint> seznamZastavek,bool navazny)
{

    if(!navazny)
    {
        eraseTable(ui->tableWidget_debugStopList);
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
        eraseTable(ui->tableWidget_debugStopList);
    }

    foreach(Vdv301StopPoint polozka, seznamZastavek)
    {
        debugStopPointToTable(polozka,navazny);
    }
}



void MainWindow::labelLcdUpdateStopBackground(Vdv301Enumerations::LocationStateEnumeration locationState)
{
    qDebug() <<  Q_FUNC_INFO;



    if (locationState==Vdv301Enumerations::LocationStateAtStop )
    {
        labelSetNextStopBackground(barvyLinek.barva_PozadiB_50_50_50,barvyLinek.barva_Zastavka_180_180_180 );
    }
    else
    {
        labelSetNextStopBackground(barvyLinek.barva_bila_255_255_255,barvyLinek.barva_PozadiB_50_50_50);
    }

}



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
    eraseTable(ui->tableWidget_services);


    foreach(QZeroConfService selectedService, serviceList)
    {
        slotDebugServiceToTable(selectedService);
    }
}



void MainWindow::debugStopPointToTable(Vdv301StopPoint selectedStopPointDestination, bool isFollowingTrip)
{
    qDebug() <<  Q_FUNC_INFO;
    qint32 row;
    QTableWidgetItem *cell;


    /*
    qDebug() <<"nazev sluzby "<<nazev<<" ip adresa "<<ipadresa<<" port "<<QString::number(port)<<" data" <<verze ;

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


    ui->tableWidget_debugStopList->resizeColumnsToContents();


}



void MainWindow::connectionListToTable(QVector<Vdv301Connection> connectionList,QTableWidget* tableWidget)
{

    eraseTable(tableWidget);


    foreach(Vdv301Connection connection, connectionList)
    {
        connectionToTable(connection,tableWidget);
    }
}




void MainWindow::connectionToTable(Vdv301Connection connection, QTableWidget* tableWidget)
{
    qDebug() <<  Q_FUNC_INFO;
    qint32 row;
    QTableWidgetItem *cell;

    /*
    qDebug() <<"nazev sluzby "<<nazev<<" ip adresa "<<ipadresa<<" port "<<QString::number(port)<<" data" <<verze ;

 */

    if(connection.vdv301displayContentList.isEmpty())
    {
        return;
    }
    else
    {
        Vdv301DisplayContent firstDisplayContent=connection.vdv301displayContentList.first();
        row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        QString lineName=InlineFormatParser::parseTextLed(displayLabelLcd.vdv301InternationalTextJoinAll(firstDisplayContent.lineInformation.lineNameList,"\n").text);
        cell = new QTableWidgetItem(lineName);

        tableWidget->setItem(row, 0, cell);

        QString destinationName=InlineFormatParser::parseTextLed(displayLabelLcd.vdv301InternationalTextJoinAll(firstDisplayContent.destination.destinationNameList,"\n").text);
        cell = new QTableWidgetItem(destinationName);
        tableWidget->setItem(row, 1, cell);

        cell = new QTableWidgetItem(connection.scheduledDepartureTime.toString("hh:mm") );
        tableWidget->setItem(row, 2, cell);

        cell = new QTableWidgetItem(connection.expectedDepartureTime.toString("hh:mm") );
        tableWidget->setItem(row, 3, cell);

        tableWidget->resizeColumnsToContents();

    }



}


// XXX FIX GlobalDisplayContent while Stop List is not empty!
void MainWindow::slotXmlToVehicleStateVariables(QString inputXmlString)
{
    qDebug() <<  Q_FUNC_INFO;


    ui->plainTextEdit_debugReceivedXml->setPlainText(inputXmlString);
    receivedDataVariablesReset();

    //  xmlParser1_0.loadXmlFile(inputXmlString);
    //  qDebug()<<"timestamp:"<<xmlParser1_0.parseTimestamp(xmlParser1_0.receivedDataDomDocument).toString(Qt::ISODate);

    receivedMessagesCounter++;
    ui->label_messageCounter->setText(QString::number(receivedMessagesCounter));

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
            qDebug()<<"unknown structure to parse";
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
            qDebug()<<"unknown structure to parse";
        }

    }

    else if(cisSubscriber.version()=="2.3CZ1.0")
    {
        xmlParser2_3CZ1_0.loadXmlFile(inputXmlString);


        if(cisSubscriber.structureName()=="AllData")
        {
            vdv301AllData2_3CZ1_0=xmlParser2_3CZ1_0.parseAllData2_3CZ1_0(xmlParser2_3CZ1_0.receivedDataDomDocument);

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
            qDebug()<<"unknown structure to parse";
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
            qDebug()<<"unknown structure to show";
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
            qDebug()<<"unknown structure to show";
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
            qDebug()<<"unknown structure to show";
        }
    }
    else
    {
        qDebug()<<"unknown VDV301 version data";
    }


}


void MainWindow::showReceivedDataVdv301(Vdv301AllData vdv301AllData)
{
    qDebug()<<Q_FUNC_INFO;

    eraseTable(ui->tableWidget_debugStopList);
    updateMainScreenDebugLabels();

    int tripCount=vdv301AllData.tripInformationList.count();


    if(tripCount==0)
    {
        // empty trip list
        qDebug()<<"empty trip list";
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
    qDebug()<<Q_FUNC_INFO;

    eraseTable(ui->tableWidget_debugStopList);
    updateMainScreenDebugLabels();

    int tripCount=vdv301AllData.tripInformationList.count();


    if(tripCount==0)
    {
        // empty trip list
        qDebug()<<"empty trip list";
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
    qDebug()<<Q_FUNC_INFO;

    eraseTable(ui->tableWidget_debugStopList);
    updateMainScreenDebugLabels();


    QVector<Vdv301DisplayContent> emptyDisplayContentList;

    showReceivedDataLedVdv301(emptyDisplayContentList,vdv301currentDisplayContent.displayContentList );
}

void MainWindow::receivedDataVariablesReset()
{

    currentVdv301StopPointList.clear();

    debugStopPointListToTable(currentVdv301StopPointList,false);
}






void MainWindow::displayNormalOnLineState()
{

    ui->stackedWidget_onService->setCurrentWidget(ui->page_route);
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





void MainWindow::on_pushButton_menu_svg_clicked()
{
    qDebug()<<Q_FUNC_INFO;
    ui->stackedWidget_menuSwitch->setCurrentWidget(ui->page_svg);


    //QSvgRenderer *m_renderer = new QSvgRenderer(QLatin1String("./Verlauf.svg"));

    this->svgRender();
    /*
    ui->graphicsView->setScene(&novaScena);
    ui->graphicsView->update();
    ui->graphicsView->show();
    */

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
        qDebug()<<"seznam zastavek je prazdny";
    }
*/
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






/*
void MainWindow::ledCycleDisplayContents()
{

}
*/



void MainWindow::displayLabelShowFareZoneChange(QVector<Vdv301InternationalText> fromFareZoneList, QVector<Vdv301InternationalText> toFareZoneList)
{
    qDebug() <<  Q_FUNC_INFO;

    ui->stackedWidget_onService->setCurrentWidget(ui->page_route);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_fareZoneChange);

    ui->label_fareZoneChangeFrom->setText(displayLabelLcd.vdv301InternationalTextJoinAll(fromFareZoneList,"\n").text);
    ui->label_fareZoneChangeTo->setText(displayLabelLcd.vdv301InternationalTextJoinAll(toFareZoneList,"\n").text);
    // displayLabelLcd.naplnZmenaLabel(displayLabelLcd.vyrobTextZmenyPasma(fromFareZoneList,toFareZoneList),ui->label_zmena);
}





void MainWindow::displayLabelShowAnnoucement(QString title,QString type,QString textCz, QString textEn)
{
    qDebug() <<  Q_FUNC_INFO;
    displayLabelLcd.naplnAnouncementLabel(textCz,ui->label_announcement);
    ui->stackedWidget_onService->setCurrentWidget(ui->page_route);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_oznameni);

    ui->label_oznTitle->setText(title);
    ui->label_oznType->setText(  displayLabelLcd.textNaPiktogramOznameni(type,100*displayLabelLcd.ratioPixelPoint));
    ui->label_oznTextCs->setText(textCz);
    ui->label_oznTextEn->setText(textEn);

    displayLabelLcd.pageCycleList.push_back(ui->page_oznameni);
}


void MainWindow::displayLabelShowAnnoucement(QVector<Vdv301InternationalText> additionalTextMessageList,QVector<Vdv301InternationalText> additionalTextMessage1List,QVector<Vdv301InternationalText> additionalTextMessage2List, QVector<Vdv301InternationalText> additionalTextMessage3List,QVector<Vdv301InternationalText> additionalTextMessage4List)
{
    qDebug() <<  Q_FUNC_INFO;
    if(!additionalTextMessageList.isEmpty() )
    {
        displayLabelLcd.naplnAnouncementLabel(additionalTextMessageList.first().text,ui->label_announcement);
    }



    displayLabelLcd.displayLabelShowAnnoucement(additionalTextMessageList,additionalTextMessage1List,additionalTextMessage2List,additionalTextMessage3List,additionalTextMessage4List);




}




void MainWindow::eventHideAnnouncement()
{
    qDebug() <<  Q_FUNC_INFO;
    displayLabelReturnToStopList();
}

void MainWindow::eventHideFareZoneChange()
{
    qDebug() <<  Q_FUNC_INFO;
    displayLabelReturnToStopList();
}



void MainWindow::eventLcdReturnToStopList()
{
    //label
    displayLabelReturnToStopList();
    //lcd


}
void MainWindow::displayLabelReturnToStopList()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->stackedWidget_onService->setCurrentWidget(ui->page_route);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_hlavni_2);
    displayLabelLcd.naplnZmenaLabel("",ui->label_zmena);
}


void MainWindow::displayLabelShowPageFinalStop()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->stackedWidget_onService->setCurrentWidget(ui->page_route);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_konecna);

}




/*
bool MainWindow::isVehicleOnFinalStop(Vdv301AllData allData)
{

    qDebug() <<  Q_FUNC_INFO;

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

    qDebug() <<  Q_FUNC_INFO;

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
        qDebug()<<" errorMessage";
        msgBox.exec();


        return 0;
    }

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



void MainWindow::on_actiontestPolozka_triggered()
{
    qDebug() <<  Q_FUNC_INFO;

    slotToggleFullscreen();
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

void MainWindow::on_pushButton_menu_services_clicked()
{
    ui->stackedWidget_menuSwitch->setCurrentWidget(ui->page_settings);
}

void MainWindow::on_pushButton_menu_displayLabel_clicked()
{
    ui->stackedWidget_menuSwitch->setCurrentWidget(ui->page_labelDisplay);

    displayLabelLcd.lcdResizeLabels(ui->frame_hlavni->height());
}

void MainWindow::on_pushButton_menu_timer_clicked()
{
    ui->stackedWidget_menuSwitch->setCurrentWidget(ui->page_timer);
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


/* can be rebuilt for VDV301structures
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

}*/

void MainWindow::on_pushButton_debugConvertInline_clicked()
{
    displayLabelLcd.labelSetTextBgInline(ui->label_debugInLineOutput,ui->plainTextEdit_debugInLineInput->toPlainText());
    ui->plainTextEdit_debugInLineOutput->setPlainText(ui->label_debugInLineOutput->text());

}


void MainWindow::on_pushButton_debugShowHtml_clicked()
{
    ui->label_debugInLineOutput->setText(ui->plainTextEdit_debugInLineOutput->toPlainText());
}

