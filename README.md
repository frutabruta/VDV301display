
# VDV301display

Ctrl+F fullscreen mode
F1-F8 menu switching

Setting are in file nastaveni.ini


Logging to file: 
Debug logs are stored in  E:/LogFile.log, if the file exists.

Program can be launched with parameter to change settings location.

--config FILEPATH parameter

- Planned features
    - debug window with VDV301subscriber log

## Changelog
- 20250110_1543
    - XmlParser classes moved to separate folder (prepared to become a submodule in future revisions)
    - MainWindow::updateMainScreenDebugLabels
        - locationState enumeration fix fo r2.3CZ1.0
    - added received messages counter to debug tab 
    - Vdv301publisher
        - fixes not connected with VDV301Display

- 20250101_2309
    - split XmlParser1_0 and XmlParser
    - all XmlParser classes public/private/protected reevaluation
- 20241213_1829
    - debug window clear connections when connection list is empty
- 20241212_2017
    - following Trip destination display fix (2.3 and 2.3CZ1.0)
    - new function DisplayLabelLcd::displayLabelDestinationFollowing
    - new function DisplayLabelLcd::displayLabelLineNameFollowing
    - DisplayLabelLcd
        - new variable QLabel *labelDestinationFollowing
        - new variable QLabel *labelLineFollowing
    
    - new function DisplayLabelLcd2_3::displayLabelLineName(Vdv301Line vdv301Line)
    - new function DisplayLabelLcd2_3::displayLabelLineNameFollowing(Vdv301Line vdv301Line)
    - new function DisplayLabelLcd2_3::displayLabelDestinationFollowing(Vdv301Destination vdv301Destination)
    - new function DisplayLabelLcd2_3::filterVdv301DisplayContentByClass(QVector<Vdv301DisplayContent> displayContentList, DisplayContentClass displayContentType)
    - MainWindow::showReceivedDataLcdVdv301(Vdv301AllData vdv301AllData)
        - fixed following trip display (line+destination)
    - MainWindow::showReceivedDataLcdVdv301_2_3CZ1_0(Vdv301AllData2_3CZ1_0 vdv301AllData)
        - fixed following trip display (line+destination)
    
- 20241206_1802
    - MainWindow
        - displayContentInner changed to Interior
    - Vdv301publisher
        - displayContentInner changed to Interior
    - Vdv301subscriber
        - displayContentInner changed to Interior
- 20241206_1604
    - 2.3CZ1.0
        - fixed color change of next stop background during AtTheStop state
    - XmlParser2_3CZ1_0::domTripInformationToVdv301Trip
        - parse RunNumber
    - XmlParser2_3CZ1_0::domStopPointToVdv301StopPoint
        - parse GlobalStopRef
    - Vdv301publisher
        - new version (changes non-related to VDV301display)
    - Vdv301subscriber
        - VDV301DataStructures
            - new function AllData isOnLastStop
    

- 20241103_2140
    - 2.3CZ1.0 show farezone change
    - 2.3CZ1.0 external displays fix
    - MainWindow
        - new functions
            - eventShowPageFareZoneChange(QVector<Vdv301InternationalText> fromFareZones, QVector<Vdv301InternationalText> toFareZones)
            - displayLabelShowFareZoneChange(QVector<Vdv301InternationalText> fromFareZoneList, QVector<Vdv301InternationalText> toFareZoneList);
    - XmlParser2_3CZ1_0
        - new function
            - domFareZoneChangeToVdv301FareZoneChange(QDomElement input);
- 20241103_1745
    - new class DisplayLabelLcd2_3CZ1_0
        - displayLabelStopList
        - displayLabelStopFareZone
        - displayLabelStopPoint
    - MainWindow
        - eventNotOnLine
            - changed text from EMPTY STOP LIST to NOT ON LINE
        - new function MainWindow::showReceivedDataLcdVdv301_2_3CZ1_0
        - new function MainWindow::debugStopPointListToTable(QVector<Vdv301StopPoint2_3CZ1_0> seznamZastavek,bool navazny)
        - new function showReceivedDataVdv301_2_3CZ1_0(Vdv301AllData2_3CZ1_0 vdv301AllData)
        - slotXmlToVehicleStateVariables
            - 2.3CZ1.0 fixes
    - XmlParser2_3CZ1_0
        - new functions
            - QVector<Vdv301StopPoint2_3CZ1_0> domStopListToVdv301TripStopList(QDomElement domTrip);
            - Vdv301Trip2_3CZ1_0 domTripInformationToVdv301Trip(QDomElement input);
            - Vdv301StopPoint2_3CZ1_0 domStopPointToVdv301StopPoint(QDomElement domStopPoint);
            - Vdv301AllData2_3CZ1_0 parseAllData2_3CZ1_0(QDomDocument input);
            - bool followingTripExists(QVector<Vdv301Trip2_3CZ1_0> vdv301tripList);


- 20241103_1315
    - XmlParser2_3
        - removed legacy funtions
            - domTripToStopPointDestinationList2_3
            - domDisplayContentToViaPointList
            - receivedDocumentToStopPointList2_3
    - MainWindow
        - showReceivedDataLcdVdv301
            - removed all VehicleState dependencies
        - slotXmlToVehicleStateVariables
            - removed all VehicleState dependencies from 2.3 and 2.3CZ1.0 sections
        - isInRange
            - added function name parameter to find issues more easily
    - removed unused includes from CIS publisher
    - VDV301subscriber
        - VDV301DataStructures
            - added Vdv301Connection related variables
    - VDV301publisher
        - XmlCommon
            - removed unused includes
            - QtZeroConf newer version
- 20241031_1755
    - MainWindow 2.3 show connections fix
        - new functions
            - connectionListToTable(QVector<Vdv301Connection> connectionList,QTableWidget* tableWidget)
            - connectionToTable(Vdv301Connection connection, QTableWidget* tableWidget)
            - isVehicleOnFinalStop(Vdv301AllData allData)
        - showReceivedDataLcdVdv301(Vdv301AllData vdv301AllData)
            - reduction of old data structure usage
    - DisplayLabelLcd2_3
        - new function displayLabelConnectionList(QVector<Vdv301Connection> connectionList)
    - XmlParser
        - followingConnectionExists renamed to followingTripExists
    - XmlParser2_3
        - new function followingTripExists(QVector<Vdv301Trip> vdv301tripList) 

    
- 20241030_1755
    - VDV301subscriber
        - new version with 2.3CZ1.0 VDV301DataStructures
    - XmlParser2_3
        - XmlParser2_3::domStopPointToVdv301StopPoint
            - Connections fix
            - platform fix
            - added XML element desctiptions
        - new function XmlParser2_3::domElementToVdv301Connection
        
- 20241030_0007
    - major rewrite to display VDV301 2.3CZ1_0 data directly from Vdv301alldata structure without using VehicleState 
        - DisplayLabel
            - new functions 
                - vykresliNacestneZastavkyText
                - vdv301InternationalTextJoinByLanguage
                - vdv301InternationalTextJoinAll
                - pasmaDoStringu
            - now independent on svgVykreslovani
        - DisplayLabelLcd
            - new function
                - displayLabelLineName(QString lineName)
            - changed attributes of displayLabelDrawLineNumber2_4
        - DisplayLabelLcd2_3
            - new class using Vdv301 structures
        - MainWindow
            - added specific Vdv301functions
            - several functions rename
        - XmlParser
            - new function
                - parseTimestamp(QString input)
        - XmlParser2_3
            - new function
                - domViaPointToVdv301ViaPoint
    - known issues
        - viaPoint cycle on LED panels doesn't work
- 20241028_1733
    - MainWindow
        - removed non-existent function from header file
- 20241028_1714
    - XmlParser
        - functions moved to XmlParser2_3
            - domTripInformationToVdv301Trip(QDomElement input);
            - qDomNodeToStopPointDestination(QDomNode input); //unused
            - domStopPointToVdv301StopPoint(QDomElement domStopPoint);
            - domDisplayContentToVdv301DisplayContent(QDomElement selectedDisplayContentDom);
            - domAllDataToVdv301VehicleInformationGroup(QDomElement input);
    - - XmlParser2_3
        - functions names translated to English
- 20241028_1626
    - MainWindow
        - showReceivedData renamed to showReceivedDataVehicleState
        - new WIP functions
            - showReceivedDataVdv301
            - debugStopPointListToTable
            - debugStopPointToTable
    - XmlParser
        - function and variable names translated to English
        - xml changed fix
        - nonexisting functions removed from header
    - XmlParser2_2CZ1_0
        - usage of renamed functions
    - XmlParser2_3
        - usage of renamed functions

- 20241023_1638
    - MainWindow elements translations
- 20241023_1231
    - XmlParser split into classes:
        - XmlParser (1.0)
        - XmlParser2_2CZ1_0
        - XmlParser2_3
        - XmlParser2_3CZ1_0
    - DisplayLabel
        - new functions
            - labelSetTextSafe
            - labelSetVisibleSafe
        - deleted functions
            - naplnNazevCileLabel
    - DisplayLabelLcd
        - displayLabelDrawLineNumber
            - null label protection
        - displayLabelEraseInformation 
            - null label protection
        - displayLabelViaPoints
            - null label protection
    - MainWindow
        - showReceivedData
            - fix of debug stop table delete
        - slotXmlDoPromenne
            - reorder function calls by functions
        - usage of different XmlParser versions
    - known issues
        - 2.3 version doesn't escape icons in following trip destination label 
- 20240913_1908
    - Vdv301publisher
        - empty triplist out of range fix
    - DisplayLabel
        - DisplayLabel::vykresliNacestneZastavkyText
            - viapoint icon fix for version 2.3CZ1.0
- 20240828_1621
    - MainWindow
        - functions reorder
        - event functions to achieve  abstraction between SVG and Label displays
- 20240828_1621
    - functions related to display of content moved to separate classes
        - DisplayLabelLcd
        - DisplayLabelLed
    - labelVykreslovani renamed to DisplayLabel
    - known issues
        - lcd label doesn't delete information change when not on trip

- 20240826_1624
    - MainWindow
        - variables and function translation to English
- 20240823_1759
    - GlobalDisplayContent basics
    - removed submodule VDV301DataStructures, now used from Vdv301Subscriber
    - XmlParser
        - new functions            
            - DomNodeToStopPointDestination
            - domStopPointToVdv301StopPoint
            - domDisplayContentToVdv301DisplayContent
            - domAllDataToVdv301VehicleInformationGroup
        - parseAllData2_3
            - now returs Vdv301AllData 
    - MainWindow
        - changes to comply with type change of locationState from QString to Vdv301Enumerations
        - new variable vdv301AllData

        - ledLabelInitialize2_3()
            - sideDisplay.destinationLabel fix
        - 2.3CZ1.0 aded to supported versions
        - MainWindow::allConnects()
            - disabled ledDisplaySetDisplayContent to avoid unexpected LED display redraw
        - MainWindow::displayLabelStopPoint
            - adapted to version 2.3CZ1.0
        - MainWindow::doplneniPromennych()
            - adapted to version 2.3CZ1.0
        - MainWindow::slotXmlDoPromenne
            - adapted to version 2.3CZ1.0
        - MainWindow::ledNaplnSide()
            - added option for single line destination (new label added to UI)
        - MainWindow::ledInicializujVirtualniPanely()
            - labelSideSingle font 5
        - MainWindow::ledUpdateDisplayedInformation
            - adapted to version 2.3CZ1.0
        - new function MainWindow::ledUpdateCurrentStopToDisplayContentList2_3 
        - new function MainWindow::ledUpdateDisplayedInformationFromDisplayContentList2_3
        - deleted function MainWindow::ledUpdateDisplayedInformation2_3
    - UI
        - added new label labelSideSingle
    - VDV301publisher 
        - added GlobalDisplayContent functions
    - Vdv301subscriber
        - Vdv301DataStructures
            - DoorOpenStateEnumerationFromQString


- 20240621_1620
    - hlavni.svg update
    - new function MainWindow::on_spinBox_frontSignWidth_valueChanged
        - the LED displays scale can be manually changed
- 20240617_1636
    - VDV301DataStructures
        - added arrivalTime
        - VehicleState cleanup
    - VDV301publisher 
        - 2_3 removed ZoneChange from AllData to comply with the original VDV301 XSD
- 20240607_1835
    - VDV301publisher
        - examples added
    - VDV301subscriber
        - examples added
- 20240509_1530
    - added icon
    - VDV301publisher
        - escape > fixed

- 20240419_1854
    - nastaveni.ini renamed to settings.ini
    - deviceManagementService1_0 renamed to deviceManagementService
    - VDV301publisher
        - merge 2.3 display content fix, mVersion
        - globalVersion renamed to mVersion
    - MainWindow::updateMainScreenDebugLabels
        - now contains all actions to update labels on the debug bar on the main screen
    - MainWindow::eraseDisplayedInformation()
        - display version screen fixed
    
- 20240418_1443
    - VDV301subscriber
        - correct subscribe request address when multiple network interfaces are used 
- 20240215_1208
    - new settings window, saving selected options to settings file
        - new functions
            - constantsToSettingsPage
            - settingsWindowToSettingsFile
            - deviceManagementServiceInternalVariablesToSettingFile
        - slot slotParametryZarizeniDoConfigu renamed to slotDeviceParametersToConfigFile
        - content of DeviceId changes automatically after receiving setId request
    - ui language change in one click
    - menu ui elements rename
- 
    - VDV301DataStructures
        - Vdv301Trip added
        - default value for vehicleState fixed
    - VDV301publisher
        - 2.3 out of service fix
    - VDV301subscriber
        - deviceManagementService v2.2 subscriber

- 20240131_1615
    -   VDV301DataStructures
        -   Vdv301 specific structures (required by XmlPArser)
    - VDV301publisher
        - displayContent destination viaPoints
        - device status changeable
        - unsubscribe response false
    - LabelVykreslovani
        - viapoint now don't stop scrolling again on every new message if the content of scrolling viapoints is the same
    - MainWindow
        - QFontDatabase now uses static functions (older approach is now depracated in Qt6)
        - stopButton state reading and display
        - radiobuttons to set device state (running, warning, defective etc.)
        - Connections list in debug menu

- 20240104_1657
    - VDV301subscriber
        - unsubscription fix
        - HTTP status check
    - VDV301publisher
        - unsubscription fix
- 20231218_2011
    - VDV301subscriber
        - now reacts to successful/unsuccessful Unsubscription
    - QUIT button now performs Unsubscription and closes application only if Unsubscription is successful
- 20231218_1910
    - translations
        - added option to change UI language in nastaveni.ini
        - added translation files in resources
        - default language in MainWindow editor is now English
    - InlineFormatParser::vyparsujText renamed to InlineFormatParser::parseTextLcd
    - InlineFormatParser::vyparsujTextLed renamed to InlineFormatParser::parseTextLed
    - XmlParser
        - added import of scheduledDepartureTime to connections
    - UI
        - added list of downloaded connections
  

- 20231214_1723
    - VDV301publisher
        - cancel subscription
    - VDV301subscriber
        - cancel subscription
        - setPortNumber fix
    - InlineFormatParser
        - parser for LED screens
    - added unsubscribe button


- 20231108_0022
    - VDV301publisher
        - 2.4 functions renamed to 2.3
    - VDV301subscriber
        - 2.4 functions renamed to 2.3
        - fix of DNS-SD service name update (leading to unsuccessful subscription)
    - new Out of Service screen
        - display system status when not on line
    - default config nastaveni.ini
        - added available options to select CIS version
- 20231103_1633
    - VDV301publisher
        - new version
    - VDV301subscriber
        - mServiceName fix
    - fixed default color of line to black on white background
    - parsing of 1.0 FareZones

- 20231030_1914
    - VDV301publisher
        - GetDeviceConfiguration fix
        - partial translation of main classes to english

- 20231018_1106
    - VDV301subscriber
        - translated to english
        - empty IP fix
        - using QZeroConf::serviceUpdated
    - VDV301publisher
        - translated to english
    - VDV301DataStructures
        - translated to english
    - XmlParser
        - removal of unused functions parameters
    - partial translation of other classes
     

- 20230925_1035
    - change of configuration by launching the program from console using --config FILEPATH parameter
    - deleted function LabelVykreslovani::zpracujIconNew 
    - last version with source code in Czech
- 20230907_1753
   
    - BarvyLinek
        - new class to handle line coloring  
    - InlineFormatParser
        - new class to parse in-line formating (icon and color tags)
    - VDV301publisher
        - new version
    - VDV301struktury
        - new version
    - VDV301subscriber
        - fix subscribe version    
    - XmlParser
        - new function XmlParser::VytvorSeznamZastavek2_4
        
    - copy-to-program folder
    - modification of start sequence
        - MainWindow::inicializaceKlavesovychZkratek()
        - MainWindow::inicializaceFontu()
    - configuration
        - check of supported VDV301version
    - deletion of publishers table when the subscription is inactive
    - implementation of inline formatting to destination, line and following stops
    - fix of bus stop advancing with stop index change  
    - removal of excessive font folder
    - removal of excessive SVG files
     

## Old Changelog (CZ) 
- 20230704_1806
    - změna vystému vykreslení zastávek na hlavní obrazovce
    - kontrolní seznam zastávek na záložce F5 časovač
    - výpis právě odebírané služby
    - barvy odděleny do barvylinek.h

- 20230612_1129
    - po opravách lze zkompilovat s Qt 6.5.0
- 20230608_1558
    - přidána kompatibilita s VDV301 1.0
    - volba verze CustomerInformationService přes nastaveni.ini
    - automatické zvětšování virtuálních LED panelů