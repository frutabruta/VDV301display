#ifndef XMLPARSER1_0OLD_H
#define XMLPARSER1_0OLD_H

#include "xmlparser.h"
#include "VDV301subscriber/VDV301DataStructures/farezone.h"
#include "VDV301subscriber/VDV301DataStructures/vehiclestate.h"

class XmlParser1_0old : public XmlParser
{
public:
    XmlParser1_0old();
    int followingTripLineDestination(QVector<StopPointDestination> &tempStopPointDestinationList, QString &lineText, QString &destinationText);
    int followingTripExists(QVector<StopPointDestination> followingStopPointDestinationList);
    int domDocumentVehicleGroupToVehicleState(VehicleState &vehicleState, QDomDocument xmlDocument);
    int createStopList1_0(QVector<StopPointDestination> &tempStopList, QVector<StopPointDestination> &tempStopListFollowing, int &tempStopIndex);

protected:
    Line propertyStringListToLine(QVector<QString> propertyStringList, Line inputLine);
    QVector<Connection> domElementToConnectionList(QDomElement connectionsElement);

private:
    int tripToStoplist1_0(QVector<StopPointDestination> &tempStopList, QDomElement domInput);
    QVector<FareZone> stopPointElementToFareZoneList1_0(QDomElement stopPointElement);
    QVector<StopPoint> domStopPointToViaPointsVector(QDomElement stopPointElement);

};

#endif // XMLPARSER1_0OLD_H
