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

Vdv301CurrentDisplayContent2_3CZ1_0 XmlParser2_3CZ1_0::parseCurrentDisplayContent2_3(QDomDocument input)
{
    QDomElement root = input.firstChildElement();
    QDomElement domCurrentDisplayContentData=root.firstChildElement("CurrentDisplayContentData");
    QDomNodeList domDisplayContentList=domCurrentDisplayContentData.elementsByTagName("CurrentDisplayContent");


    Vdv301CurrentDisplayContent2_3CZ1_0 currentDisplayContentData;

    currentDisplayContentData.timeStamp=parseTimestamp(domCurrentDisplayContentData.firstChildElement("TimeStamp").firstChildElement("Value").text());

    for(int i=0;i<domDisplayContentList.count();i++)
    {
        currentDisplayContentData.displayContentList<<domDisplayContentToVdv301DisplayContent(domDisplayContentList.at(i).toElement());
    }

    return currentDisplayContentData;
}

Vdv301AdditionalAnnouncement2_3CZ1_0 XmlParser2_3CZ1_0::domAdditionalAnnouncementToVdv301AdditionalAnnouncement(QDomElement input)
{
    Vdv301AdditionalAnnouncement2_3CZ1_0 additionalAnnouncement;

    additionalAnnouncement.announcementRef=input.firstChildElement("AnnouncementRef").text();

    QDomNodeList domAnnouncementTextList=input.elementsByTagName("AnnouncementText");
    for(int i=0;i<domAnnouncementTextList.count();i++)
    {
        Vdv301InternationalText annoucementText;
        annoucementText.text=domAnnouncementTextList.at(i).firstChildElement("Value").text();
        annoucementText.language=domAnnouncementTextList.at(i).firstChildElement("Language").text();
        additionalAnnouncement.announcementTextList<<annoucementText;
    }

    QDomNodeList domAnnouncementTTSTextList=input.elementsByTagName("AnnouncementTTSText");
    for(int i=0;i<domAnnouncementTTSTextList.count();i++)
    {
        Vdv301InternationalText annoucementTTSText;
        annoucementTTSText.text=domAnnouncementTTSTextList.at(i).firstChildElement("Value").text();
        annoucementTTSText.language=domAnnouncementTTSTextList.at(i).firstChildElement("Language").text();
        additionalAnnouncement.announcementTTSTextList<<annoucementTTSText;
    }


    //immediate

    //periodic

    //farezonechange

    return additionalAnnouncement;
}

Vdv301DisplayContent2_3CZ1_0 XmlParser2_3CZ1_0::domDisplayContentToVdv301DisplayContent(QDomElement selectedDisplayContentDom)
{
    Vdv301DisplayContent2_3CZ1_0 temporaryDisplayContent;
    temporaryDisplayContent.displayContentRef=selectedDisplayContentDom.firstChildElement("DisplayContentRef").text();
    temporaryDisplayContent.displayContentType=Vdv301DisplayContent::qStringToDisplayContentClass(selectedDisplayContentDom.firstChildElement("DisplayContentRef").text());
    //QStringList temporaryDestinationList;
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

    QDomNodeList viaPointDomList=selectedDisplayContentDom.elementsByTagName("ViaPoint");
    for(int k=0;k<viaPointDomList.count();k++)
    {
        temporaryDisplayContent.viaPointList.append(domViaPointToVdv301ViaPoint(viaPointDomList.at(k).toElement()));
    }


    return temporaryDisplayContent;
}

Vdv301Trip2_3CZ1_0 XmlParser2_3CZ1_0::domTripInformationToVdv301Trip( QDomElement input)
{
    Vdv301Trip2_3CZ1_0 trip;
    trip.tripRef=input.firstChildElement("TripRef").text();
    trip.stopPointList=domStopListToVdv301TripStopList(input);
    trip.locationState=Vdv301Enumerations::LocationStateEnumerationFromQString(input.firstChildElement("LocationState").text());

    trip.fareZoneChange=domFareZoneChangeToVdv301FareZoneChange(input.firstChildElement("FareZoneChange"));
    trip.runNumber=input.firstChildElement("RunNumber").firstChildElement("Value").text();


    trip.additionalTextMessageList=qDomNodeListToVdv301InternationalTextList(input.elementsByTagName("AdditionalTextMessage"));
    trip.additionalTextMessage1List=qDomNodeListToVdv301InternationalTextList(input.elementsByTagName("AdditionalTextMessage1"));
    trip.additionalTextMessage2List=qDomNodeListToVdv301InternationalTextList(input.elementsByTagName("AdditionalTextMessage2"));
    trip.additionalTextMessage3List=qDomNodeListToVdv301InternationalTextList(input.elementsByTagName("AdditionalTextMessage3"));
    trip.additionalTextMessage4List=qDomNodeListToVdv301InternationalTextList(input.elementsByTagName("AdditionalTextMessage4"));
    trip.additionalTextMessage5List=qDomNodeListToVdv301InternationalTextList(input.elementsByTagName("AdditionalTextMessage5"));
    trip.additionalTextMessage6List=qDomNodeListToVdv301InternationalTextList(input.elementsByTagName("AdditionalTextMessage6"));
    trip.additionalTextMessage7List=qDomNodeListToVdv301InternationalTextList(input.elementsByTagName("AdditionalTextMessage7"));
    trip.additionalTextMessage8List=qDomNodeListToVdv301InternationalTextList(input.elementsByTagName("AdditionalTextMessage8"));
    trip.additionalTextMessage9List=qDomNodeListToVdv301InternationalTextList(input.elementsByTagName("AdditionalTextMessage9"));


    QDomNodeList domAdditionalAnnouncementList=input.elementsByTagName("AdditionalAnnouncement");
    for(int i = 0; i<domAdditionalAnnouncementList.count();i++ )
    {
        trip.additionalAnnouncementList<<domAdditionalAnnouncementToVdv301AdditionalAnnouncement(domAdditionalAnnouncementList.at(i).toElement());
    }


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
    // GlobalStopRef
    temporaryStopPoint.globalStopRef=domStopPoint.firstChildElement("GlobalStopRef").firstChildElement().text();
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

Vdv301ViaPoint2_3CZ1_0 XmlParser2_3CZ1_0::domViaPointToVdv301ViaPoint( QDomElement domViaPoint)
{
    Vdv301ViaPoint2_3CZ1_0 temporaryViaPoint;
    temporaryViaPoint.viaPointRef=domViaPoint.firstChildElement("ViaPointRef").firstChildElement().text();

    QDomNodeList viaPointNameListDom=domViaPoint.elementsByTagName("PlaceName");
    for(int j=0;j<viaPointNameListDom.count();j++)
    {
        temporaryViaPoint.placeNameList<<qDomNodeToVdv301InternationalText(viaPointNameListDom.at(j));
    }

    // ArrivalScheduled minOccurs="0"
    temporaryViaPoint.arrivalScheduled=domViaPoint.firstChildElement("ArrivalScheduled").firstChildElement("Value").text();

    // ArrivalExpected minOccurs="0"
    temporaryViaPoint.arrivalExpected=domViaPoint.firstChildElement("ArrivalExpected").firstChildElement("Value").text();

    // DepartureScheduled minOccurs="0"
    temporaryViaPoint.departureScheduled=domViaPoint.firstChildElement("DepartureScheduled").firstChildElement("Value").text();

    // DepartureExpected minOccurs="0"
    temporaryViaPoint.departureExpected=domViaPoint.firstChildElement("DepartureExpected").firstChildElement("Value").text();


    return temporaryViaPoint;
}


bool XmlParser2_3CZ1_0::followingTripExists(QVector<Vdv301Trip2_3CZ1_0> vdv301tripList)
{
    if (vdv301tripList.count()>1)
    {
        return true;
    }
    return false;


}
