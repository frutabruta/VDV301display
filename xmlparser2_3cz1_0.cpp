#include "xmlparser2_3cz1_0.h"

XmlParser2_3CZ1_0::XmlParser2_3CZ1_0() {}



Vdv301AllData2_3CZ1_0 XmlParser2_3CZ1_0::parseAllData2_3CZ1_0(QDomDocument input)
{
    QDomElement root = input.firstChildElement();
    QDomElement domAllData=root.firstChildElement("AllData");
    QDomNodeList domTripList=domAllData.elementsByTagName("TripInformation");
    QVector<Vdv301Trip2_3CZ1_0> tripList;
    Vdv301AllData2_3CZ1_0 vdv301AllData;

    vdv301AllData.timeStamp=parseTimestamp(domAllData.firstChildElement("TimeStamp").firstChildElement("Value").text());
    vdv301AllData.vehicleRef=domAllData.firstChildElement("VehicleRef").firstChildElement("Value").text();


    for(int i=0;i<domTripList.count();i++)
    {
        tripList.append(domTripInformationToVdv301Trip(domTripList.at(i).toElement()));
    }

    vdv301AllData.tripInformationList.append(tripList);

    vdv301AllData.vehicleInformationGroup=domAllDataToVdv301VehicleInformationGroup(domAllData);

    vdv301AllData.currentStopIndex=domAllData.firstChildElement("CurrentStopIndex").firstChildElement("Value").text().toInt();
    QDomNodeList displayContentsDom=input.elementsByTagName("GlobalDisplayContent");
    for(int j=0;j<displayContentsDom.count();j++)
    {
        QDomElement selectedDisplayContentDom=displayContentsDom.at(j).toElement();
        vdv301AllData.globalDisplayContentList<<domDisplayContentToVdv301DisplayContent(selectedDisplayContentDom);

    }

    return vdv301AllData;
}



Vdv301Trip2_3CZ1_0 XmlParser2_3CZ1_0::domTripInformationToVdv301Trip( QDomElement input)
{
    Vdv301Trip2_3CZ1_0 trip;
    trip.tripRef=input.firstChildElement("TripRef").text();
    trip.stopPointList=domStopListToVdv301TripStopList(input);
    trip.locationState=Vdv301Enumerations::LocationStateEnumerationFromQString(input.firstChildElement("LocationState").text());

    trip.fareZoneChange=domFareZoneChangeToVdv301FareZoneChange(input.firstChildElement("FareZoneChange"));

    return trip;
}


Vdv301FareZoneChange2_3CZ1_0 XmlParser2_3CZ1_0::domFareZoneChangeToVdv301FareZoneChange( QDomElement input)
{
    Vdv301FareZoneChange2_3CZ1_0 fareZoneChange;

    QDomNodeList domFromFareZone=input.firstChildElement("FromFareZones").elementsByTagName("FareZone");
    for(int i=0; i<domFromFareZone.count();i++)
    {
        fareZoneChange.fromFareZone<<qDomNodeToVdv301InternationalText(domFromFareZone.at(i));
    }

    QDomNodeList domToFareZone=input.firstChildElement("ToFareZones").elementsByTagName("FareZone");

    for(int i=0; i<domToFareZone.count();i++)
    {
        fareZoneChange.toFareZone<<qDomNodeToVdv301InternationalText(domToFareZone.at(i));
    }

    if((!fareZoneChange.fromFareZone.isEmpty())||(!fareZoneChange.toFareZone.isEmpty()))
    {
        fareZoneChange.active=true;
    }
    return fareZoneChange;
}




Vdv301StopPoint2_3CZ1_0 XmlParser2_3CZ1_0::domStopPointToVdv301StopPoint( QDomElement domStopPoint)
{
    Vdv301StopPoint2_3CZ1_0 temporaryStopPoint;
    // StopIndex
    temporaryStopPoint.stopIndex=domStopPoint.firstChildElement("StopIndex").firstChildElement("Value").text().toInt();
    // StopRef
    temporaryStopPoint.stopRef=domStopPoint.firstChildElement("StopRef").firstChildElement().text();
    // StopName
    QDomNodeList stopPointNameListDom=domStopPoint.elementsByTagName("StopName");
    for(int j=0;j<stopPointNameListDom.count();j++)
    {
        temporaryStopPoint.stopNameList<<qDomNodeToVdv301InternationalText(stopPointNameListDom.at(j));
    }
    // StopAlternativeName
    QDomNodeList stopPointAlternativeNameListDom=domStopPoint.elementsByTagName("StopAlternativeName");
    for(int j=0;j<stopPointAlternativeNameListDom.count();j++)
    {
        temporaryStopPoint.stopAlternativeNameList<<qDomNodeToVdv301InternationalText(stopPointAlternativeNameListDom.at(j));
    }
    // Platform minOccurs="0"
    temporaryStopPoint.platform=domStopPoint.firstChildElement("Platform").firstChildElement("Value").text();

    // DisplayContent
    QDomNodeList displayContentsDom=domStopPoint.elementsByTagName("DisplayContent");
    for(int j=0;j<displayContentsDom.count();j++)
    {
        QDomElement selectedDisplayContentDom=displayContentsDom.at(j).toElement();


        temporaryStopPoint.displayContentList<<domDisplayContentToVdv301DisplayContent(selectedDisplayContentDom);

    }

    // StopAnnouncement minOccurs="0" not implemented

    // ArrivalScheduled minOccurs="0"
    temporaryStopPoint.arrivalScheduled=domStopPoint.firstChildElement("ArrivalScheduled").firstChildElement("Value").text();

    // ArrivalExpected minOccurs="0"
    temporaryStopPoint.arrivalExpected=domStopPoint.firstChildElement("ArrivalExpected").firstChildElement("Value").text();

    // DepartureScheduled minOccurs="0"
    temporaryStopPoint.departureScheduled=domStopPoint.firstChildElement("DepartureScheduled").firstChildElement("Value").text();

    // DepartureExpected minOccurs="0"
    temporaryStopPoint.departureExpected=domStopPoint.firstChildElement("DepartureExpected").firstChildElement("Value").text();

    // RecordedArrivalTime minOccurs="0"
    // DistanceToNextStop minOccurs="0"
    // Connection minOccurs="0"
    QDomNodeList connectionListDom=domStopPoint.elementsByTagName("Connection");
    for(int j=0;j<connectionListDom.count();j++)
    {
        temporaryStopPoint.connectionList<<domElementToVdv301Connection(connectionListDom.at(j).toElement());
    }

    // FareZone minOccurs="0"
    QDomNodeList temporaryFareZoneList=domStopPoint.elementsByTagName("FareZone");
    for(int l=0;l<temporaryFareZoneList.count();l++)
    {
        temporaryStopPoint.fareZoneList<<qDomNodeToVdv301InternationalText(temporaryFareZoneList.at(l));
    }

    return temporaryStopPoint;
}



QVector<Vdv301StopPoint2_3CZ1_0> XmlParser2_3CZ1_0::domStopListToVdv301TripStopList( QDomElement domTrip)
{

    qDebug()<<Q_FUNC_INFO;
    QVector<Vdv301StopPoint2_3CZ1_0> tripStopPointList;


    QDomNodeList nodes = domTrip.elementsByTagName("StopPoint");

    for (int i=0; i<nodes.count();i++)
    {
        QDomElement selectedStopDom=nodes.at(i).toElement();

        //////////////////////////////////////////////////
        //new approach
        tripStopPointList<<domStopPointToVdv301StopPoint(selectedStopDom);
        /////////////////////////////////////////////


    }
    if (tripStopPointList.size()==0)
    {
        qDebug()<<"no stop points have been parsed";
    }


    return tripStopPointList;

}


bool XmlParser2_3CZ1_0::followingTripExists(QVector<Vdv301Trip2_3CZ1_0> vdv301tripList)
{
    if (vdv301tripList.count()>1)
    {
        return true;
    }
    return false;


}
