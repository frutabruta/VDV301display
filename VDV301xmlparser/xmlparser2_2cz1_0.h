#ifndef XMLPARSER2_2CZ1_0_H
#define XMLPARSER2_2CZ1_0_H

#include "VDV301subscriber/VDV301DataStructures/stoppointdestination.h"
#include "VDV301subscriber/VDV301DataStructures/vehiclestate.h"
#include "xmlparser.h"

class XmlParser2_2CZ1_0 : public XmlParser
{
public:
    XmlParser2_2CZ1_0();
    int createStopList2_2CZ1_0(QVector<StopPointDestination> &tempStopPointDestinationList, QVector<StopPointDestination> &tempStopPointDestinationListFollowing, int &docasnyIndexZastavky);
    int parseFareZoneChange(QDomDocument xmlko, QVector<FareZone> &pasmaZ, QVector<FareZone> &pasmaNa);
    int parseAdditionalTextMessage2_2CZ1_0(QDomDocument xmlko, QString &type, QString &headline, QString &text);
    int domDocumentVehicleGroupToVehicleState(VehicleState &vehicleState, QDomDocument xmlDocument);
    int followingTripExists(QVector<StopPointDestination> followingStopPointDestinationList);
    int followingTripLineDestination(QVector<StopPointDestination> &tempStopPointDestinationList, QString &lineText, QString &destinationText);
private:
    QVector<FareZone> domToFareZoneList2_2CZ1_0(QDomElement domStopPoint);
    int parseStopPointDestinationList2_2CZ1_0(QVector<StopPointDestination> &docasnySeznamZst, QDomElement vstup);
    QVector<StopPoint> domToViaPoints2_2CZ1_0(QDomElement domStopPoint);

    QVector<Connection> domElementToConnectionList(QDomElement connectionsElement);
    Line propertyStringListToLine(QVector<QString> propertyStringList, Line inputLine);

};

#endif // XMLPARSER2_2CZ1_0_H
