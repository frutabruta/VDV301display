
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
- 20260205_1707
  - MainWindow
    - complete functions reorder
    - vehicleSubmodeToGolemioType moved to TypeConvertor
- 20260205_1507
  - GolemioClient
    - icon parsing
  - VDV301subscriber
    - reply fix
  - functions moved from MainWindow to new class MainWindowHelper
    - onnectionListToTable(QVector<Vdv301Connection> connectionList, QTableWidget *tableWidget);
    - eraseTable(QTableWidget *tableWidget);
    - connectionListToTable(QVector<ConnectionGolemioV4> connectionList, QTableWidget *tableWidget);
    - connectionToTable(Vdv301Connection connection, QTableWidget *tableWidget);
    - connectionToTable(ConnectionGolemioV4 connection, QTableWidget *tableWidget);
  - function moved to TypeConvertor
    - connectionGolemioV4toConnectionBasic(ConnectionGolemioV4 connectionGolemio);
    - lineToIconJisUnderground(QString routeShortName, int routeType);

- 20260108_1416
  - GolemioClient
    - icons parsing
  - new class TypeConvertor
  - InlineFormatParser::parseTextLcd
    - remove gaps between icons
  - LedLabelDisplay
    - QPointer usage
  - DisplayLabelLcd2_3CZ1_0_Jis::displayLabelConnectionListBasic
    - usage of inlineFormatParser.parseTextLcd
    - empty ptr check
  - MainWindow::slotDownloadGolemio
    - empty stop number check
  - MainWindow::connectionGolemioV4toConnectionBasic
    - added icon
  - Logging rules set using a plaintextEdit on Debug tab
  - VDV301subscriber
    - response handling rewrite 

- 20251129_0134
  - VDV301subscriber
    - added qCDebug implementation
  - SvgVykreslovani
    - added qCDebug implementation
  - XmlParser
    - added qCDebug implementation
    
- 20251118_1429
  - VDV301subscriber
    - fixed replyPath
  - VDV301publisher
    - fixed Qt5 support
    
- 20251104_0203
  - set golemio type from received vehicleMode
    - new function MainWindow::vehicleSubmodeToGolemioType
    - MainWindow::showReceivedDataVdv301_2_3CZ1_0
      - set golemioVehicleType
- 20251103_1714
  - switched to QtCreator 18.0.0 (change of .ui file syntax)
  - changed layout of settings page
  - settings.ini
    - added app/blockBonjour
    - added golemio/useTestServer
  - added golemio test server settings
  - added golemio key line text edits
  - updated translations

- 20251031_1717
  - displayLabelStopListNew
    - added parameter to invert text color when AtStop or BeforeStop
- 20251030_1638
  - added block bonjour functionality
  - MainWindow::slotDownloadGolemio()
    - start golemioTimer
  - MainWindow::slotEverySecond
    - added page count updates
  - MainWindow::slotGolemioReady
    - updates display 
  - line resize temporary fix
  - fixed new data check for Vdv301 2.3CZ1.0 and page switching

- 20251028_1925
  - Vdv301publisher and Vdv301subscriber
    - Vdv301DataStructures Trip == operator fix
  - Connections header table fix
  - MainWindow::showReceivedDataLcdVdv301_2_3CZ1_0 
    - standalone Connections fix

- 20251028_0134
  - added standalone mode to download connection directly from GolemioClient and bypass connections from AllData
  - added ConnectionBasic to DisplayLabelLcd2_3CZ1_0_Jis 
  - settings.ini
    - new parameter app/connectionsStandalone
  - MainWindow::slotDebugPublisherToTable
    - now uses PublisherStruct


- 20251027_2101
  - VDV301publisher
    - added serviceNamePostfix
  - added module GolemioClient (not used yet)
  - usage of labelListStopGroup
    - DisplayLabelLcd
    - DisplayLabelLcd2_3
    - DisplayLabelLcd2_3CZ1_0    
  - DisplayLabelStopGroup
    - moved to DisplayLabelLcd2_3.cpp
  - DisplayLabelConnectionGroup
    - moved to DisplayLabelLcd2_3.cpp

- 20251019_2142
  - MainWindow
    - added labelSetNextStopBackgroundJis
    - added allDataChanged to compare if alldata changed and page switching should be reseted
    - intervalLcdPageSwitchSeconds
      - added option to save and set page switching interval
    - added interval countdown 
    - MainWindow::slotEverySecond
      - JIS time fix 
    - MainWindow::slotDisplayLcdLabelCyclePagesJis()
        - complete rework
    - MainWindow::eventDisplayAbnormalStateScreen
      - JIS fix
    - MainWindow::showReceivedDataLcdVdv301_2_3CZ1_0
      - page switching rework
    - MainWindow::labelLcdUpdateStopBackground
      - JIS fix
    - new function MainWindow::labelSetNextStopBackgroundJis
  - ui 
    - added message counter to home screen
  - settings.ini
    - added parameter graphics/lcdPageSwitchTimer
  - added InlineFormatParser::parseTextLcdJis to disable line colouring with JIS graphics

  - DisplayLabelLcd
    - NULL -> nullptr
  - DisplayLabelLcd2_3
    - NULL -> nullptr
    - qCDebug implementation
  - DisplayLabelLcd2_3CZ1_0_Jis  
    - NULL -> nullptr
    - qCDebug implementation
    - show platform at connections screen
    - DisplayLabelLcd2_3CZ1_0_Jis::displayLabelDrawLineNumber2_4
      - to fix of colours of JIS graphics line number
    - DisplayLabelStopGroup
      - added labelPlatform
    - DisplayLabelLcd2_3CZ1_0
      - NULL -> nullptr
    
    


- 20251007_1535
  - ui
    - added option to change psge switch time (not stored in settings.ini)
  - added QLoggingCategory
    - InlineFormatParser
    - DisplayLabel
    - DisplayLabelLcd
    - DisplayLabelLed
    - MainWindow
  - VDV301subscriber
    - not sending subscribe request with empty IP


- 20251006_1546
  - move all DisplayLabel files to a separate folder
- 20251006_1525
  - ui
    - JIS graphics
      - Stop Request sign now works
      - added 6th stop
    - fixed stretches
    - moved debug frame
  - settings.ini
    - added option to save useJis state 

- 20251006_1150
  - new class DisplayLabelLcd2_3CZ1_0_Jis with label group architecture
    - DisplayLabelStopGroup::DisplayLabelStopGroup
    - DisplayLabelStopGroup::eraseContent
    - DisplayLabelConnectionGroup::eraseContent
    - DisplayLabelConnectionGroup::labelSetTextSafe
    - DisplayLabelLcd2_3CZ1_0_Jis::displayLabelLineName
    - DisplayLabelLcd2_3CZ1_0_Jis::displayLabelStopListNew
  - DisplayLabelLcd2_3CZ1_0::displayLabelStopPoint 
    - null pointer fix
  - ui
    - reworked JIS layout
    - line and next stop now working
    - added connections to total number of 8
  - MainWindow
    - added MainWindow::slotDisplayLcdLabelCyclePagesJis
    - fixes to allow correct switching of JIS pages



- 20250926_1732
  - VDV301subscriber
    - added replyPath support
    - null pointer fixed 

  - VDV301publisher
    - HttpService::slotDumpRequestContent
    - added support for  replyPath including /
    - fixed else if statement to prevent response clash
  
  - DisplayLabel
    - DisplayLabel::labelSetStylesheetSafe
    - DisplayLabelLcd::displayLabelDrawLineNumber2_4
      - empty pointer checks
    - DisplayLabelLcd2_3::displayLabelDestinationFollowing
      - empty pointer checks
    - DisplayLabelLcd2_3CZ1_0::displayLabelStopList
      - empty pointer checks
    - DisplayLabelLcd2_3CZ1_0::displayLabelStopPoint
      - empty pointer checks
        
  - added option to set replyPath (cisSubscriber/replyPath in settings.ini)
  - MainWindow
    - JIS preparations
  
- 20250901_1638
  - MainWindow::messageToTable(Vdv301AllData2_3CZ1_0 input)
    - added tripcount
  - fixed debug windows connections not resetting
  - fixed not logging of message when the triplist is empty
  - changed debug message font to monospace

- 20250829_1123
  - added beforeStop to MainWindow::labelLcdUpdateStopBackground 
  
- 20250828_1926
  - VDV301publisher
    - color rules fix
  - MainWindow
    - added message log window for 2.3CZ1.0
- 20250827_1912
  - added locationState, currentStopIndex and announcement labels to debug window
  - added departure times to stop debug window
  - removed maximum window size limit to fix resizing issues

- 20250630_1558
  - QUIT button fix when subscription is not active
  
- 20250630_1520
  - VDV301publisher
    - TicketValidation service drafts
  - VDV301subscriber
    - updated data structures
  - updated translations

- 20250520_1319
  - fixed Vdv301Datastructures VDV301CurrentDisplayContent dependency

- 20250424_2304
  - VDV301subscriber
    - refactored version of DevMGMT subscriber
  - removed DisplayLabelLcd::displayLabelDrawLineNumber (last dependency on VehicleState variable)
- 20250405_2146
  - complete purge of 2.2CZ1.0 support and all VehicleState variable dependent code
  
- 20250404_1944
  - 1.0 now parsed using Vdv301 data structures

- 20250404_1837
  - XmlParser fixes of departure time
  - **last version to support parsing 1.0 to VehicleState variables**  

- 20250404_0039
  - renamed VehicleState 1.0 parser to XmlParser1_0

- 20250403_2149
  - option to subscribe CurrentDisplayContent
  - Vdv301publisher
      - Vdv301DataStructures
        - added Vdv301CurrentDisplayContent
  - Vdv301subscriber
    - IbisIpSubscriber::structureName added setter and getter    

  - MainWindow
    - added window for received XML file
    - added settings option to choose subscription structure
    - new function showReceivedDataVdv301_2_3CZ1_0(Vdv301CurrentDisplayContent vdv301currentDisplayContent)
    
  - new function XmlParser2_3::parseCurrentDisplayContent2_3
  - settings.ini updated to support CurrentDisplayContent option

- 20250316_2359
  - InlineFormatParser::parseTextLcdRecursive
    - removed barva attribute
    - removed replacement symbol from icon
  - InlineFormatParser::getDirectParent
    - new function
  - MainWindow
    - modified FareZone change and LineChange layout to expand and removed padding/margin to remove gaps in background color
    
- 20250314_1857
  - DisplayLabelLcd2_3CZ1_0::displayLabelShowAnnoucement
    - reworked to support fare zone change etc.

- 20250312_2102
  - VDV301Publisher
    - Vdv301DataStructures
      - stoppoint neozn and zast
  - VDV301Subscriber
    - Vdv301DataStructures
      - stoppoint neozn and zast
  - DisplayLabelLcd2_3CZ1_0::displayLabelShowAnnoucement
  - InlineFormatParser
    - added coloring of whole label if the text is enclosed in color tag
  - MainWindow
    - added button to test HTML formatted text on a label 

- 20250227_1726
  - Vdv301publisher
    - additionalMessage1-9
  - Vdv301subscriber
    - additionalMessage1-9
  - MainWindow
    - added new page for additionalTextMessage
      - support for icon inclusion
  - new function DisplayLabelLcd2_3CZ1_0::displayLabelShowAnnoucement
  - new function XmlParser2_3::qDomNodeListToVdv301InternationalTextList
  - XmlParser additionalMessage1-9 parsing functions
    
- 20250308_1901
  - MainWindow
    - divided debug menu to three tabs
      - subscription
      - data
      - inline formatting tester
  - support for in-line formatting in additionalTextMessage
    - support for b, icon, font, color
    - fix needed to remove alternative icon text

- 20250221_1824
  - MainWindow::handleDisplayContentInner
    - fix viaPoints with following trip
- 20250117_1834
  - MainWindow::showReceivedDataLcdVehicleState()
    - 2.2CZ1.0 specialAnnouncement fix
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