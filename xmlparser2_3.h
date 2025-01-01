#ifndef XMLPARSER2_3_H
#define XMLPARSER2_3_H

#include "xmlparser.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301alldata.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301trip.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301vehicleinformationgroup.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301vehicleinformationgroup.h"

class XmlParser2_3 : public XmlParser
{
public:
    XmlParser2_3();

    Vdv301AllData parseAllData2_3(QDomDocument input, QVector<Vdv301StopPoint> &testStopList);
    bool followingTripExists(QVector<Vdv301Trip> vdv301tripList);

protected:
    Vdv301InternationalText qDomNodeToVdv301InternationalText(QDomNode domNode);
    Vdv301DisplayContent domDisplayContentToVdv301DisplayContent(QDomElement selectedDisplayContentDom);
    Vdv301VehicleInformationGroup domAllDataToVdv301VehicleInformationGroup(QDomElement input);
    Vdv301Connection domElementToVdv301Connection(QDomElement connectionElement);

private:
    QVector<Vdv301StopPoint> domStopListToVdv301TripStopList(QDomElement domTrip);
    Vdv301Trip domTripInformationToVdv301Trip(QDomElement input);
    Vdv301StopPoint domStopPointToVdv301StopPoint(QDomElement domStopPoint);
    Vdv301ViaPoint domViaPointToVdv301ViaPoint(QDomElement domViaPoint);






};

#endif // XMLPARSER2_3_H
