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
#include "VDV301subscriber/VDV301DataStructures/vdv301vehicleinformationgroup.h"

class XmlParser
{
public:
    XmlParser();

    QDomDocument receivedDataDomDocument;
    void Test(); //unused
    
    void loadXmlFile(QString input);
    
    int domDocumentVehicleGroupToVehicleState(VehicleState &vehicleState, QDomDocument xmlDocument);
   //  int nactiFareZoneChange(QDomDocument xmlko, QVector<FareZone> &pasmaZ, QVector<FareZone> &pasmaNa);
    //int nactiAdditionalTextMessage2_2CZ1_0(QDomDocument xmlko, QString &type, QString &headline, QString &text);
    //int vyparsujPasmaZeSeznamu(QDomElement vstup, QVector<FareZone> &pasma);
     QVector<QString> propertyDomToStringList(QDomNode domNode, QString elementName);
    int followingTripLineDestination(QVector<StopPointDestination> &tempStopPointDestinationList, QString &lineText, QString &destinationText);
     int followingConnectionExists(QVector<StopPointDestination> followingStopPointDestinationList);
    QVector<Connection> domElementToConnectionList(QDomElement connectionsElement);
     Line propertyStringListToLine(QVector<QString> propertyStringList, Line inputLine);
    
    QDateTime parseTimestamp(QDomDocument vstupniDokument);
     
     bool dataChanged=false;
   // static int minutDoOdjezdu(QDateTime aktCas, QDateTime casOdjezdu);  //unused

    //rozdelano
    int createStopList1_0(QVector<StopPointDestination> &tempStopList, QVector<StopPointDestination> &tempStopListFollowing, int &tempStopIndex);
    int tripToStoplist1_0(QVector<StopPointDestination> &tempStopList, QDomElement domInput);
    QVector<StopPoint> domStopPointToViaPointsVector(QDomElement stopPointElement);
    QVector<FareZone> stopPointElementToFareZoneList1_0(QDomElement stopPointElement);



    Vdv301InternationalText qDomNodeToVdv301InternationalText(QDomNode domNode);
    QVector<Vdv301StopPoint> domStopListToVdv301TripStopList(QDomElement domTrip);

    Vdv301Trip domTripInformationToVdv301Trip(QDomElement input);
    Vdv301StopPoint qDomNodeToStopPointDestination(QDomNode input); //unused
    Vdv301StopPoint domStopPointToVdv301StopPoint(QDomElement domStopPoint);
    Vdv301DisplayContent domDisplayContentToVdv301DisplayContent(QDomElement selectedDisplayContentDom);
    Vdv301VehicleInformationGroup domAllDataToVdv301VehicleInformationGroup(QDomElement input);
private:
    QString previousXmlData="";
};




#endif // XMLPARSER_H
