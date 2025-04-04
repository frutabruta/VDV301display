#ifndef XMLPARSER2_3_H
#define XMLPARSER2_3_H

#include "xmlparser1_0.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301alldata.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301currentdisplaycontent.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301trip.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301vehicleinformationgroup.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301vehicleinformationgroup.h"

class XmlParser2_3 : public XmlParser1_0
{
public:
    XmlParser2_3();

    Vdv301AllData parseAllData2_3(QDomDocument input, QVector<Vdv301StopPoint> &testStopList);
    Vdv301CurrentDisplayContent parseCurrentDisplayContent2_3(QDomDocument input);

    bool followingTripExists(QVector<Vdv301Trip> vdv301tripList);    
protected:
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
