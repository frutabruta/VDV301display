# VDV301display

Ctrl+F fullscreen mode
F1-F8 menu switching

Setting are in file nastaveni.ini


Logging to file: 
Debug logs are stored in  E:/LogFile.log, if the file exists.

Program can be launched with parameter to change settings location.

--config FILEPATH parameter

## Changelog
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