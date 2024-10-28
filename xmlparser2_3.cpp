#include "xmlparser2_3.h"

XmlParser2_3::XmlParser2_3() {}

QVector<StopPointDestination> XmlParser2_3::domTripToStopPointDestinationList2_3(QDomElement tripDomElement)
{
    qDebug()<<Q_FUNC_INFO;
    QVector<StopPointDestination> stopPointList;

    QDomNodeList stopPointNodeList = tripDomElement.elementsByTagName("StopPoint");

    for (int i=0; i<stopPointNodeList.count();i++)
    {

        StopPointDestination stopPointDestination;
        QDomElement stopPointElement=stopPointNodeList.at(i).toElement();
        int poradiZastavky=stopPointElement.elementsByTagName("StopIndex").at(0).firstChildElement().text().toInt();
        stopPointDestination.stopPoint.StopName=stopPointElement.firstChildElement("StopName").firstChildElement().text();
        stopPointDestination.stopPoint.NameFront=stopPointElement.firstChildElement("StopName").firstChildElement().text();
        stopPointDestination.stopPoint.NameSide=stopPointElement.firstChildElement("StopName").firstChildElement().text();
        stopPointDestination.stopPoint.NameRear=stopPointElement.firstChildElement("StopName").firstChildElement().text();
        stopPointDestination.stopPoint.NameInner=stopPointElement.firstChildElement("StopName").firstChildElement().text();
        stopPointDestination.stopPoint.NameLcd=stopPointElement.firstChildElement("StopName").firstChildElement().text();
        stopPointDestination.line.lineName=stopPointElement.firstChildElement("DisplayContent").firstChildElement("LineInformation").firstChildElement("LineName").firstChildElement().text();


        QVector<QString> propertyValueStringList;

        QDomNodeList linePropertyNodeList=stopPointElement.firstChildElement("DisplayContent").firstChildElement("LineInformation").elementsByTagName("LineProperty");


        for(int j=0; j<linePropertyNodeList.count();j++)
        {
            QString propertyValue=linePropertyNodeList.at(j).firstChild().nodeValue();
            propertyValueStringList.push_back(propertyValue);
            // qDebug()<<"parsuju priznaky:"<<priznak;
        }

        stopPointDestination.line=propertyStringListToLine(propertyValueStringList,stopPointDestination.line);

        QDomNodeList displayContentArray=stopPointElement.elementsByTagName("DisplayContent");

        for (int k=0;k<displayContentArray.length();k++)
        {
            qDebug()<<"selected display content id: "<<QString::number(k);
            QDomNode selectedDisplayContentNode=displayContentArray.at(k);
            QString ref=selectedDisplayContentNode.firstChildElement("DisplayContentRef").firstChildElement("Value").firstChild().nodeValue();
            if(ref=="Front")
            {

                QDomNodeList destinationNameList=selectedDisplayContentNode.toElement().firstChildElement("Destination").elementsByTagName("DestinationName");

                if(destinationNameList.count()>0)
                {
                    stopPointDestination.destination.NameFront=destinationNameList.at(0).firstChildElement("Value").firstChild().nodeValue();

                }
                if(destinationNameList.count()>1)
                {
                    stopPointDestination.destination.NameFront2=destinationNameList.at(1).firstChildElement("Value").firstChild().nodeValue();

                }
            }
            if(ref=="Side")
            {
                stopPointDestination.destination.NameSide=selectedDisplayContentNode.firstChildElement("Destination").firstChildElement("DestinationName").firstChildElement("Value").firstChild().nodeValue();

            }
            if(ref=="Rear")
            {
                stopPointDestination.destination.NameRear=selectedDisplayContentNode.firstChildElement("Destination").firstChildElement("DestinationName").firstChildElement("Value").firstChild().nodeValue();

            }
            if(ref=="Lcd")
            {
                stopPointDestination.destination.NameLcd=selectedDisplayContentNode.firstChildElement("Destination").firstChildElement("DestinationName").firstChildElement("Value").firstChild().nodeValue();
                stopPointDestination.viaPoints=domDisplayContentToViaPointList(selectedDisplayContentNode);
                //   docasnaZastavka.destination.StopName =polozka.firstChildElement("Destination").firstChildElement("DestinationName").firstChildElement().text();

            }


        }

        stopPointDestination.stopPoint.StopIndex=i;


        stopPointDestination.stopPoint.connectionList=domElementToConnectionList(stopPointElement);

        stopPointDestination.stopPoint.iconList= propertyDomToStringList(stopPointElement,"Stop");

        stopPointDestination.stopPoint.fareZoneList=domStopPointToFareZoneList(stopPointElement);
        stopPointList.push_back(stopPointDestination);
        globalStopList2_3.insert(poradiZastavky,stopPointDestination);
    }
    if (stopPointList.size()==0)
    {
        qDebug()<<"no stop were loaded";
    }
    return stopPointList;
}








QVector<StopPoint> XmlParser2_3::domDisplayContentToViaPointList(QDomNode displayContent)
{
    qDebug()<<Q_FUNC_INFO;
    QDomNodeList viaPointNodeList = displayContent.toElement().elementsByTagName("ViaPoint");
    QVector<StopPoint> viaPointList;
    for (int i=0;i<viaPointNodeList.count();i++)
    {


        StopPoint viaPoint;
        QDomElement viaPointElement=viaPointNodeList.at(i).toElement();
        viaPoint.NameLcd=viaPointElement.firstChildElement("PlaceName").firstChildElement("Value").firstChild().nodeValue();
        viaPoint.NameInner=viaPointElement.firstChildElement("PlaceName").firstChildElement("Value").firstChild().nodeValue();
        viaPoint.NameSide=viaPointElement.firstChildElement("PlaceName").firstChildElement("Value").firstChild().nodeValue();
        viaPoint.StopName=viaPoint.NameLcd;

        /*
        QDomNodeList priznaky=nacesty.at(i).toElement().elementsByTagName("ViaPointProperty");
        nacesta.seznamPiktogramu= naplnVektorPriznaku(aktNacesta,"ViaPoint");
        for (int j=0;j<priznaky.count();j++)
        {
            QString hodnotaPriznaku=priznaky.at(j).firstChild().nodeValue();
            qDebug()<<"priznak "<<hodnotaPriznaku;


            if(hodnotaPriznaku=="RequestStop")
            {
                nacesta.naZnameni=true;
            }
        }
*/

        viaPointList.append(viaPoint);
    }

    return viaPointList;
}


QVector<FareZone> XmlParser2_3::domStopPointToFareZoneList(QDomElement stopPointElement)
{
    qDebug()<<Q_FUNC_INFO;
    QVector<FareZone> output;

    QDomNodeList fareZoneNodeList = stopPointElement.elementsByTagName("FareZone");

    for (int i=0;i<fareZoneNodeList.count();i++)
    {
        FareZone selectedFareZone;
        //  aktPasmo.system=domPasma.at(i).firstChildElement("Value").firstChildElement("FareZoneTypeName").firstChildElement("Value").firstChild().nodeValue();
        selectedFareZone.name=fareZoneNodeList.at(i).firstChildElement("Value").firstChild().nodeValue();
        output.append(selectedFareZone);

    }

    return output;
}


Vdv301AllData XmlParser2_3::parseAllData2_3(QDomDocument input, QVector<Vdv301StopPoint> &testStopList)
{
    QDomElement root = input.firstChildElement();
    QDomElement domAllData=root.firstChildElement("AllData");
    QDomNodeList domTripList=domAllData.elementsByTagName("TripInformation");
    QVector<Vdv301Trip> tripList;
    Vdv301AllData vdv301AllData;

    QString vehicleRef=domAllData.firstChildElement("VehicleRef").firstChildElement("Value").text();
    vdv301AllData.vehicleRef=vehicleRef;

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


    QDomNodeList displayContentsDom=input.elementsByTagName("GlobalDisplayContent");
    for(int j=0;j<displayContentsDom.count();j++)
    {
        QDomElement selectedDisplayContentDom=displayContentsDom.at(j).toElement();
        vdv301AllData.globalDisplayContentList<<domDisplayContentToVdv301DisplayContent(selectedDisplayContentDom);

    }

    return vdv301AllData;
}



int XmlParser2_3::receivedDocumentToStopPointList2_3(QVector<StopPointDestination> &stopPointDestinationList,QVector<StopPointDestination> &stopPointDestinationListFollowing, int &currentStopIndex)
{
    qDebug()<<Q_FUNC_INFO;
    stopPointDestinationList.clear();
    QDomElement root = receivedDataDomDocument.firstChildElement();
    qDebug()<<root.tagName();
    if (root.tagName()!="CustomerInformationService.GetAllDataResponse")
    {
        qDebug()<<"invalid XML";
        return 0;
    }


    QDomElement tripInformation;//=allData.firstChildElement("TripInformation");
    QDomElement tripInformation2;
    currentStopIndex=root.elementsByTagName("CurrentStopIndex").at(0).firstChildElement().text().toInt()-1; //převod indexování od 1 (VDV301) na indexování od 0 ( C++ pole)

    QDomNodeList tripInformationList=root.elementsByTagName("TripInformation");


    switch(tripInformationList.count())
    {
    case 0:
        qDebug()<<"triplist is empty";
        return 0;
        break;
    case 1:
        tripInformation=tripInformationList.at(0).toElement();
        stopPointDestinationList=domTripToStopPointDestinationList2_3(tripInformation);
        break ;
    case 2:
        qDebug()<<"one following trip exists";
        tripInformation=tripInformationList.at(0).toElement();
        stopPointDestinationList=domTripToStopPointDestinationList2_3(tripInformation);
        tripInformation2=tripInformationList.at(1).toElement();
        stopPointDestinationListFollowing=domTripToStopPointDestinationList2_3(tripInformation2);

        break;

    default:
        qDebug()<<"too many following trips";
        tripInformation=tripInformationList.at(0).toElement();
        stopPointDestinationList=domTripToStopPointDestinationList2_3(tripInformation);
        tripInformation2=tripInformationList.at(1).toElement();
        stopPointDestinationListFollowing=domTripToStopPointDestinationList2_3(tripInformation2);

        break;

    }


    return 1;
}




Vdv301VehicleInformationGroup XmlParser2_3::domAllDataToVdv301VehicleInformationGroup(QDomElement input)
{
    Vdv301VehicleInformationGroup output;

    output.doorState=Vdv301Enumerations::DoorOpenStateEnumerationFromQString(input.firstChildElement("DoorState").text());
    //output.tripState=
    //output.exitSide=
    //output.inPanic=
    //output.routeDeviation
    output.vehicleMode=input.firstChildElement("MyOwnVehicleMode").firstChildElement("PtMainMode").firstChild().nodeValue();
    output.vehicleSubMode=input.firstChildElement("MyOwnVehicleMode").firstChildElement(output.vehicleMode).firstChild().nodeValue();
    output.vehicleStopRequested=input.firstChildElement("VehicleStopRequested").firstChildElement("Value").firstChild().nodeValue().toInt();


    return output;
}

Vdv301Trip XmlParser2_3::domTripInformationToVdv301Trip( QDomElement input)
{
    Vdv301Trip trip;
    trip.tripRef=input.firstChildElement("TripRef").text();
    trip.stopPointList=domStopListToVdv301TripStopList(input);
    trip.locationState=Vdv301Enumerations::LocationStateEnumerationFromQString(input.firstChildElement("LocationState").text());
    return trip;
}




QVector<Vdv301StopPoint> XmlParser2_3::domStopListToVdv301TripStopList( QDomElement domTrip)
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


Vdv301StopPoint XmlParser2_3::domStopPointToVdv301StopPoint( QDomElement domStopPoint)
{
    Vdv301StopPoint temporaryStopPoint;
    temporaryStopPoint.stopIndex=domStopPoint.elementsByTagName("StopIndex").at(0).firstChildElement().text().toInt();
    temporaryStopPoint.stopRef=domStopPoint.firstChildElement("StopRef").firstChildElement().text();
    QDomNodeList stopPointNameListDom=domStopPoint.elementsByTagName("StopName");
    for(int j=0;j<stopPointNameListDom.count();j++)
    {
        temporaryStopPoint.stopNameList<<qDomNodeToVdv301InternationalText(stopPointNameListDom.at(j));
    }


    //displayContentApproach
    QDomNodeList displayContentsDom=domStopPoint.elementsByTagName("DisplayContent");
    for(int j=0;j<displayContentsDom.count();j++)
    {
        QDomElement selectedDisplayContentDom=displayContentsDom.at(j).toElement();


        temporaryStopPoint.displayContentList<<domDisplayContentToVdv301DisplayContent(selectedDisplayContentDom);

    }

    temporaryStopPoint.departureScheduled=domStopPoint.firstChildElement("ScheduledDepartureTime").firstChildElement("Value").text();
    temporaryStopPoint.departureExpected=domStopPoint.firstChildElement("ExpectedDepartureTime").firstChildElement("Value").text();

    QDomNodeList temporaryFareZoneList=domStopPoint.elementsByTagName("FareZone");
    for(int l=0;l<temporaryFareZoneList.count();l++)
    {
        temporaryStopPoint.fareZoneList<<temporaryFareZoneList.at(l).firstChildElement("Value").text();
    }

    return temporaryStopPoint;
}

Vdv301DisplayContent XmlParser2_3::domDisplayContentToVdv301DisplayContent(QDomElement selectedDisplayContentDom)
{
    Vdv301DisplayContent temporaryDisplayContent;
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

    return temporaryDisplayContent;
}



/*
Vdv301Destination XmlParser::qDomNodeListToVdv301Destination(QDomNodeList input)
{

}
*/


Vdv301InternationalText XmlParser2_3::qDomNodeToVdv301InternationalText(QDomNode domNode)
{
    Vdv301InternationalText output;
    output.text=domNode.firstChildElement("Value").text();
    output.language=domNode.firstChildElement("Language").text();

    return output;
}
