# VDV301display


Ctrl+F fullscreen mode
F1-F8 přepínání položek v menu

Pokud existuje soubor fullscreen.txt, spustí se aplikace v režimu celé obrazovky.
Obsah souboru určuje, na jaké obrazovce se program spustí (1 na první obrazovce apod.)

Logování do souboru: 
logování funguje, pokud existuje soubor E:/LogFile.log

## Changelog
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