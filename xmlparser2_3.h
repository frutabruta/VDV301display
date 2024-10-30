#ifndef XMLPARSER2_3_H
#define XMLPARSER2_3_H

#include "xmlparser.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301alldata.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301trip.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301vehicleinformationgroup.h"

class XmlParser2_3 : public XmlParser
{
public:
    XmlParser2_3();


    QMap<int,StopPointDestination> globalStopList2_3;

    QVector<StopPointDestination> domTripToStopPointDestinationList2_3(QDomElement tripDomElement);
    QVector<StopPoint> domDisplayContentToViaPointList(QDomElement displayContent);
    QVector<FareZone> domStopPointToFareZoneList(QDomElement stopPointElement);
    Vdv301AllData parseAllData2_3(QDomDocument input, QVector<Vdv301StopPoint> &testStopList);
    int receivedDocumentToStopPointList2_3(QVector<StopPointDestination> &stopPointDestinationList, QVector<StopPointDestination> &stopPointDestinationListFollowing, int &docasnyIndexZastavky);


    Vdv301InternationalText qDomNodeToVdv301InternationalText(QDomNode domNode);
    QVector<Vdv301StopPoint> domStopListToVdv301TripStopList(QDomElement domTrip);
    Vdv301Trip domTripInformationToVdv301Trip(QDomElement input);
    Vdv301StopPoint qDomNodeToStopPointDestination(QDomNode input); //unused
    Vdv301StopPoint domStopPointToVdv301StopPoint(QDomElement domStopPoint);
    Vdv301DisplayContent domDisplayContentToVdv301DisplayContent(QDomElement selectedDisplayContentDom);
    Vdv301VehicleInformationGroup domAllDataToVdv301VehicleInformationGroup(QDomElement input);

    Vdv301ViaPoint domViaPointToVdv301ViaPoint(QDomElement domViaPoint);
    Vdv301Connection domElementToVdv301Connection(QDomElement connectionElement);
};

#endif // XMLPARSER2_3_H
