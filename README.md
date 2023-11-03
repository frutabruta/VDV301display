# VDV301display

Ctrl+F fullscreen mode
F1-F8 menu switching

Setting are in file nastaveni.ini


Logging to file: 
Debug logs are stored in  E:/LogFile.log, if the file exists.

Program can be launched with parameter to change settings location.

--config FILEPATH parameter

## Changelog
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