#include "xmlparser1_0.h"

XmlParser1_0::XmlParser1_0() {}



Vdv301AllData XmlParser1_0::parseAllData1_0(QDomDocument input, QVector<Vdv301StopPoint> &testStopList)
{
    QDomElement root = input.firstChildElement();
    QDomElement domAllData=root.firstChildElement("AllData");
    QDomNodeList domTripList=domAllData.elementsByTagName("TripInformation");
    QVector<Vdv301Trip> tripList;
    Vdv301AllData vdv301AllData;

    vdv301AllData.timeStamp=parseTimestamp(domAllData.firstChildElement("TimeStamp").firstChildElement("Value").text());
    vdv301AllData.vehicleRef=domAllData.firstChildElement("VehicleRef").firstChildElement("Value").text();

    for(int i=0;i<domTripList.count();i++)
    {
        tripList.append(domTripInformationToVdv301Trip(domTripList.at(i).toElement()));
    }

    vdv301AllData.tripInformationList.append(tripList);

    if(!tripList.isEmpty())
    {
        testStopList=tripList.first().stopPointList;
    }

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

Vdv301CurrentDisplayContent XmlParser1_0::parseCurrentDisplayContent1_0(QDomDocument input)
{
    QDomElement root = input.firstChildElement();
    QDomElement domCurrentDisplayContentData=root.firstChildElement("CurrentDisplayContentData");
    QDomNodeList domDisplayContentList=domCurrentDisplayContentData.elementsByTagName("CurrentDisplayContent");


    Vdv301CurrentDisplayContent currentDisplayContentData;

    currentDisplayContentData.timeStamp=parseTimestamp(domCurrentDisplayContentData.firstChildElement("TimeStamp").firstChildElement("Value").text());

    for(int i=0;i<domDisplayContentList.count();i++)
    {
        currentDisplayContentData.displayContentList<<domDisplayContentToVdv301DisplayContent(domDisplayContentList.at(i).toElement());
    }

    return currentDisplayContentData;
}




Vdv301VehicleInformationGroup XmlParser1_0::domAllDataToVdv301VehicleInformationGroup(QDomElement input)
{
    Vdv301VehicleInformationGroup output;
    // RouteDeviation" type="RouteDeviationEnumeration">
    output.routeDeviation=Vdv301Enumerations::RouteDeviationEnumerationFromQString(input.firstChildElement("DoorState").text());
    // DoorState" type="DoorOpenStateEnumeration" minOccurs="0">
    output.doorState=Vdv301Enumerations::DoorOpenStateEnumerationFromQString(input.firstChildElement("DoorState").text());

    // InPanic" type="IBIS-IP.boolean" minOccurs="0">
    output.inPanic=input.firstChildElement("InPanic").firstChildElement("Value").firstChild().nodeValue().toInt() ;
    // VehicleStopRequested" type="IBIS-IP.boolean" minOccurs="0">


    output.vehicleStopRequested=qDomElementValueToBool( input.firstChildElement("VehicleStopRequested")); //.firstChildElement("Value").firstChild().nodeValue().toInt();
    //     output.vehicleStopRequested=input.firstChildElement("VehicleStopRequested").firstChildElement("Value").firstChild().nodeValue().toInt();

    // ExitSide" type="ExitSideEnumeration" minOccurs="0">
 //   output.exitSide=input.firstChildElement("ExitSide").firstChild().nodeValue();

        // MovingDirectionForward" type="IBIS-IP.boolean" minOccurs="0">
    // VehicleMode" type="VehicleModeEnumeration" minOccurs="0"/>

    return output;
}

Vdv301Trip XmlParser1_0::domTripInformationToVdv301Trip( QDomElement input)
{
    Vdv301Trip trip;
    trip.tripRef=input.firstChildElement("TripRef").text();
    trip.stopPointList=domStopListToVdv301TripStopList(input);
    trip.locationState=Vdv301Enumerations::LocationStateEnumerationFromQString(input.firstChildElement("LocationState").text());
    return trip;
}




QVector<Vdv301StopPoint> XmlParser1_0::domStopListToVdv301TripStopList( QDomElement domTrip)
{

    qDebug()<<Q_FUNC_INFO;
    QVector<Vdv301StopPoint> tripStopPointList;


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


Vdv301StopPoint XmlParser1_0::domStopPointToVdv301StopPoint( QDomElement domStopPoint)
{
    Vdv301StopPoint temporaryStopPoint;
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

    // DepartureScheduled minOccurs="0"
    temporaryStopPoint.departureScheduled=domStopPoint.firstChildElement("DepartureScheduled").firstChildElement("Value").text();

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
        temporaryStopPoint.fareZoneList<<temporaryFareZoneList.at(l).firstChildElement("Value").text();
    }

    return temporaryStopPoint;
}

Vdv301DisplayContent XmlParser1_0::domDisplayContentToVdv301DisplayContent(QDomElement selectedDisplayContentDom)
{
    Vdv301DisplayContent temporaryDisplayContent;


    //DisplayContentRef" type="IBIS-IP.NMTOKEN" minOccurs="0">
    temporaryDisplayContent.displayContentRef=selectedDisplayContentDom.firstChildElement("DisplayContentRef").text();
    temporaryDisplayContent.displayContentType=Vdv301DisplayContent::qStringToDisplayContentClass(selectedDisplayContentDom.firstChildElement("DisplayContentRef").text());

    //LineInformation" type="LineInformationStructure">
    QDomElement lineInformationDom=selectedDisplayContentDom.firstChildElement("LineInformation");
    Vdv301Line temporaryLine;
    temporaryLine.lineRef=lineInformationDom.firstChildElement("LineRef").firstChildElement("Value").text();

    QDomNodeList lineNameListDom=lineInformationDom.elementsByTagName("LineName");
    for(int k=0;k<lineNameListDom.count();k++)
    {
        Vdv301InternationalText temporaryLineName = qDomNodeToVdv301InternationalText(lineNameListDom.at(k));
        temporaryLine.lineNameList.append(temporaryLineName);
    }
    temporaryLine.lineNumber=lineInformationDom.firstChildElement("LineNumber").firstChildElement("Value").text();


    temporaryDisplayContent.lineInformation=temporaryLine;

    //Destination" type="DestinationStructure">
    QDomNode destinationDom=selectedDisplayContentDom.firstChildElement("Destination");
    Vdv301Destination temporaryDestination;
    temporaryDestination.destinationRef=destinationDom.firstChildElement("DestinationRef").text();

    QDomNodeList destinationNameListDom=selectedDisplayContentDom.elementsByTagName("DestinationName");

    for(int k=0;k<destinationNameListDom.count();k++)
    {
        QDomElement temporaryDestinationName=destinationNameListDom.at(k).toElement();
        temporaryDestination.destinationNameList<<qDomNodeToVdv301InternationalText(destinationNameListDom.at(k));
    }
    temporaryDisplayContent.destination=temporaryDestination;

    //ViaPoint" type="ViaPointStructure" minOccurs="0" maxOccurs="unbounded">
    QDomNodeList viaPointDomList=selectedDisplayContentDom.elementsByTagName("ViaPoint");
    for(int k=0;k<viaPointDomList.count();k++)
    {
        temporaryDisplayContent.viaPointList.append(domViaPointToVdv301ViaPoint(viaPointDomList.at(k).toElement()));
    }

    //AdditionalInformation" type="InternationalTextType" minOccurs="0" maxOccurs="unbounded">
    //"DisplayPolicyGroup" minOccurs="0">


    return temporaryDisplayContent;
}


Vdv301ViaPoint XmlParser1_0::domViaPointToVdv301ViaPoint( QDomElement domViaPoint)
{
    Vdv301ViaPoint temporaryViaPoint;
    temporaryViaPoint.viaPointRef=domViaPoint.firstChildElement("ViaPointRef").firstChildElement().text();

    QDomNodeList viaPointNameListDom=domViaPoint.elementsByTagName("PlaceName");
    for(int j=0;j<viaPointNameListDom.count();j++)
    {
        temporaryViaPoint.placeNameList<<qDomNodeToVdv301InternationalText(viaPointNameListDom.at(j));
    }

    return temporaryViaPoint;
}


Vdv301Connection XmlParser1_0::domElementToVdv301Connection(QDomElement connectionElement)
{
    //rozepsano
    qDebug()<<Q_FUNC_INFO;


    Vdv301Connection output;

    //StopRef" type="IBIS-IP.NMTOKEN">
    //ConnectionRef" type="IBIS-IP.NMTOKEN">
    //ConnectionType" type="ConnectionTypeEnumeration">
    //DisplayContent" type="DisplayContentStructure">
    QDomNodeList displayContentList=connectionElement.elementsByTagName("DisplayContent");

    for (int j = 0; j < displayContentList.count(); ++j)
    {
        output.vdv301displayContentList<<domDisplayContentToVdv301DisplayContent(displayContentList.at(j).toElement());
    }

    //Platform" type="IBIS-IP.string" minOccurs="0">
    output.platform=connectionElement.firstChildElement("Platform").firstChildElement("Value").text();
    //ConnectionState" type="ConnectionStateEnumeration" minOccurs="0">
    //TransportMode" type="VehicleStructure" minOccurs="0">
    //ExpectedDepatureTime" type="IBIS-IP.dateTime" minOccurs="0">
    output.expectedDepartureTime=parseTimestamp(connectionElement.firstChildElement("ExpectedDepatureTime").firstChildElement("Value").text());




    /*
    QDomElement connectionMode=connectionElement.firstChildElement("ConnectionMode");
    output.mainMode=connectionMode.firstChildElement("PtMainMode").firstChild().nodeValue();
    output.subMode=connectionMode.firstChildElement(output.mainMode).firstChild().nodeValue();
*/
    return output;
}


bool XmlParser1_0::followingTripExists(QVector<Vdv301Trip> vdv301tripList)
{
    if (vdv301tripList.count()>1)
    {
        return true;
    }
    return false;


}

/*
Vdv301Destination XmlParser::qDomNodeListToVdv301Destination(QDomNodeList input)
{

}
*/


Vdv301InternationalText XmlParser1_0::qDomNodeToVdv301InternationalText(QDomNode domNode)
{
    Vdv301InternationalText output;
    output.text=domNode.firstChildElement("Value").text();
    output.language=domNode.firstChildElement("Language").text();

    return output;
}


QVector<Vdv301InternationalText> XmlParser1_0::qDomNodeListToVdv301InternationalTextList(QDomNodeList domNodeList)
{
    QVector<Vdv301InternationalText> output;
    for(int i=0;i<domNodeList.count();i++)
    {
        output<<Vdv301InternationalText(domNodeList.at(i).firstChildElement("Value").text(),domNodeList.at(i).firstChildElement("Language").text());
    }
    return output;
}
