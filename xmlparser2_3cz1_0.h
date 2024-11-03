#ifndef XMLPARSER2_3CZ1_0_H
#define XMLPARSER2_3CZ1_0_H

#include "xmlparser2_3.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301trip2_3cz1_0.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301alldata2_3cz1_0.h"
class XmlParser2_3CZ1_0 : public XmlParser2_3
{
public:
    XmlParser2_3CZ1_0();
    QVector<Vdv301StopPoint2_3CZ1_0> domStopListToVdv301TripStopList(QDomElement domTrip);
    Vdv301Trip2_3CZ1_0 domTripInformationToVdv301Trip(QDomElement input);
    Vdv301StopPoint2_3CZ1_0 domStopPointToVdv301StopPoint(QDomElement domStopPoint);
    Vdv301AllData2_3CZ1_0 parseAllData2_3CZ1_0(QDomDocument input);
    bool followingTripExists(QVector<Vdv301Trip2_3CZ1_0> vdv301tripList);
};

#endif // XMLPARSER2_3CZ1_0_H
