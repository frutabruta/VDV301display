#ifndef XMLPARSER_H
#define XMLPARSER_H
//#define MAX_ZAST2 10

#include <QMainWindow>
#include <QObject>
#include <QtXml>
#include "VDV301subscriber/VDV301DataStructures/stoppoint.h"
#include "VDV301subscriber/VDV301DataStructures/stoppointdestination.h"
#include "VDV301subscriber/VDV301DataStructures/vehiclestate.h"
#include "VDV301subscriber/VDV301DataStructures/farezone.h"

#include "VDV301subscriber/VDV301DataStructures/vdv301stoppoint.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301trip.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301alldata.h"

class XmlParser
{
public:
    XmlParser();
    // void nactiXML(QByteArray vstup);
    int linka=0;
    QString cil="";




    // SeznamZastavek docasnySeznamZastavek[] ;
    //SeznamZastavek* docasnySeznamZastavek = new SeznamZastavek[MAX_ZAST2];

    QDomDocument dokument;
    void Test(); //unused

    void nactiXML(QString vstup);

    int nactiVehicleGroup(VehicleState &stav, QDomDocument xmlko);
     int nactiFareZoneChange(QDomDocument xmlko, QVector<FareZone> &pasmaZ, QVector<FareZone> &pasmaNa);
    //int nactiAdditionalTextMessage2_2CZ1_0(QDomDocument xmlko, QString &type, QString &headline, QString &text);
    int vyparsujPasmaZeSeznamu(QDomElement vstup, QVector<FareZone> &pasma);
    QVector<QString> naplnVektorPriznaku(QDomNode vstup, QString nazevElementu);
    int udajeNavaznehoSpoje(QVector<StopPointDestination> &docasnySeznamZst, QString &linka, QString &cil);
    int existujeNavaznySpoj(QVector<StopPointDestination> seznamZastavek);
    QVector<Connection> nactiPrestupy(QDomElement vstup);
    Line priznakyDoLinky(QVector<QString> vstup, Line vstupniLinka);

    QDateTime vyparsujTimestamp(QDomDocument vstupniDokument);

    bool zmenaDat=false;
    static int minutDoOdjezdu(QDateTime aktCas, QDateTime casOdjezdu);  //unused

    //rozdelano
    int VytvorSeznamZastavek1_0(QVector<StopPointDestination> &docasnySeznamZst, QVector<StopPointDestination> &docasnySeznamZstNavazny, int &docasnyIndexZastavky);
    int tripDoSeznamuZastavek1_0(QVector<StopPointDestination> &docasnySeznamZst, QDomElement vstup);
    QVector<StopPoint> vyparsujNacestneZastavky1_0(QDomElement zastavka);
    QVector<FareZone> vyparsujPasma_1_0(QDomElement zastavka);



    Vdv301InternationalText qDomNodeToVdv301InternationalText(QDomNode domNode);
    QVector<Vdv301StopPoint> domStopListToVdv301TripStopList(QDomElement domTrip);
    Vdv301Trip domTripInformationToVdv301Trip(QDomElement input);
    Vdv301StopPoint qDomNodeToStopPointDestination(QDomNode input); //unused
    Vdv301StopPoint domStopPointToVdv301StopPoint(QDomElement domStopPoint);
    Vdv301DisplayContent domDisplayContentToVdv301DisplayContent(QDomElement selectedDisplayContentDom);
    Vdv301VehicleInformationGroup domAllDataToVdv301VehicleInformationGroup(QDomElement input);
private:
     QString stareXml="";
};




#endif // XMLPARSER_H
