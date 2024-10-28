#include "xmlparser.h"
#include "VDV301subscriber/VDV301DataStructures/stoppoint.h"
#include "VDV301subscriber/VDV301DataStructures/vehiclestate.h"
#include "VDV301subscriber/VDV301DataStructures/farezone.h"

#include <QDebug>
#include <QMainWindow>




XmlParser::XmlParser()
{
    qDebug()<<Q_FUNC_INFO;
}

void XmlParser::loadXmlFile(QString input)
{
    qDebug()<<Q_FUNC_INFO;

    if(input!=previousXmlData)
    {
        dataChanged=true;
    }
    else
    {
        dataChanged=false;
    }

    receivedDataDomDocument.setContent(input);
    // QString blabla = dokument.toString();


}

int XmlParser::createStopList1_0(QVector<StopPointDestination> &tempStopList,QVector<StopPointDestination> &tempStopListFollowing, int &tempStopIndex)
{
    qDebug()<<Q_FUNC_INFO;
    tempStopList.clear();
    QDomElement root = receivedDataDomDocument.firstChildElement();
    qDebug()<<root.tagName();
    if (root.tagName()!="CustomerInformationService.GetAllDataResponse")
    {
        qDebug()<<"invalid XML";
        return 0;
    }


    QDomElement tripInformation;//=allData.firstChildElement("TripInformation");
    QDomElement tripInformation2;
    tempStopIndex=root.elementsByTagName("CurrentStopIndex").at(0).firstChildElement().text().toInt()-1; //převod indexování od 1 (VDV301) na indexování od 0 ( C++ pole)

    QDomNodeList tripInformationList=root.elementsByTagName("TripInformation");


    switch(tripInformationList.count())
    {
    case 0:
        qDebug()<<"tripList is empty";
        return 0;
        break;
    case 1:
        tripInformation=tripInformationList.at(0).toElement();
        tripToStoplist1_0(tempStopList,tripInformation);
        break ;
    case 2:
        qDebug()<<"one following trip exists";
        tripInformation=tripInformationList.at(0).toElement();
        tripToStoplist1_0(tempStopList,tripInformation);
        tripInformation2=tripInformationList.at(1).toElement();
        tripToStoplist1_0(tempStopListFollowing,tripInformation2);

        break;

    default:
        qDebug()<<"too many following trips";
        tripInformation=tripInformationList.at(0).toElement();
        tripToStoplist1_0(tempStopList,tripInformation);
        tripInformation2=tripInformationList.at(1).toElement();
        tripToStoplist1_0(tempStopListFollowing,tripInformation2);

        break;

    }



    return 1;
}




QDateTime XmlParser::parseTimestamp(QDomDocument vstupniDokument)
{
    qDebug()<<Q_FUNC_INFO;

    QDateTime timestamp =  QDateTime::fromString(vstupniDokument.firstChildElement("CustomerInformationService.GetAllDataResponse").firstChildElement("AllData").firstChildElement("TimeStamp").firstChildElement("Value").firstChild().nodeValue() ,Qt::ISODate);

    return timestamp;

}


int XmlParser::followingTripLineDestination(QVector<StopPointDestination> &tempStopPointDestinationList, QString &lineText, QString &destinationText)
{
    if (tempStopPointDestinationList.isEmpty())
    {
        return 0;
    }
    lineText=tempStopPointDestinationList.first().line.lineName;
    destinationText=tempStopPointDestinationList.first().destination.NameLcd;


    return 1;
}


int XmlParser::tripToStoplist1_0(QVector<StopPointDestination> &tempStopList, QDomElement domInput)
{
    qDebug()<<Q_FUNC_INFO;

    QDomNodeList nodes = domInput.elementsByTagName("StopPoint");


    for (int i=0; i<nodes.count();i++)
    {

        StopPointDestination tempStopPointDestination;
        QDomElement aktZastavkaDOM=nodes.at(i).toElement();
        int stopIndex=aktZastavkaDOM.elementsByTagName("StopIndex").at(0).firstChildElement().text().toInt();
        tempStopPointDestination.stopPoint.StopName=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        tempStopPointDestination.stopPoint.NameFront=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        tempStopPointDestination.stopPoint.NameSide=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        tempStopPointDestination.stopPoint.NameRear=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        tempStopPointDestination.stopPoint.NameInner=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        tempStopPointDestination.stopPoint.NameLcd=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        tempStopPointDestination.line.lineName=aktZastavkaDOM.firstChildElement("DisplayContent").firstChildElement("LineInformation").firstChildElement("LineName").firstChildElement().text();

        QVector<QString> stopPropertyStringList;

        QDomNodeList stopPropertyDomList=aktZastavkaDOM.firstChildElement("DisplayContent").firstChildElement("LineInformation").elementsByTagName("LineProperty");


        for(int j=0; j<stopPropertyDomList.count();j++)
        {
            QString stopProperty=stopPropertyDomList.at(j).firstChild().nodeValue();
            stopPropertyStringList.push_back(stopProperty);
            // qDebug()<<"parsuju priznaky:"<<priznak;
        }
        tempStopPointDestination.line=propertyStringListToLine(stopPropertyStringList,tempStopPointDestination.line);

        tempStopPointDestination.stopPoint.StopIndex=i;
        tempStopPointDestination.viaPoints=domStopPointToViaPointsVector(aktZastavkaDOM);
        tempStopPointDestination.stopPoint.connectionList=domElementToConnectionList(aktZastavkaDOM);

        QDomElement displayContent=aktZastavkaDOM.firstChildElement("DisplayContent");
        QDomElement dDestination=displayContent.firstChildElement("Destination");
        tempStopPointDestination.destination.StopName=dDestination.firstChildElement("DestinationName").text();
        tempStopPointDestination.destination.NameFront=dDestination.firstChildElement("DestinationName").firstChildElement().text();
        tempStopPointDestination.destination.iconList=propertyDomToStringList(displayContent.elementsByTagName("Destination").at(0),"Destination");

        QDomNodeList stopNameFrontDomList=dDestination.elementsByTagName("DestinationName");
        if (stopNameFrontDomList.length()>0)
        {
            tempStopPointDestination.destination.NameFront=stopNameFrontDomList.at(0).firstChildElement().text();
        }
        if (stopNameFrontDomList.length()>1)
        {
            tempStopPointDestination.destination.NameFront2=stopNameFrontDomList.at(1).firstChildElement().text();
        }
        tempStopPointDestination.stopPoint.iconList= propertyDomToStringList(aktZastavkaDOM,"Stop");


        tempStopPointDestination.destination.NameSide=dDestination.firstChildElement("DestinationName").firstChildElement().text();
        tempStopPointDestination.destination.NameRear=dDestination.firstChildElement("DestinationName").firstChildElement().text();
        tempStopPointDestination.destination.NameInner=dDestination.firstChildElement("DestinationName").firstChildElement().text();
        tempStopPointDestination.destination.NameLcd=dDestination.firstChildElement("DestinationName").firstChildElement().text();

        //    qInfo()<< "xml "<<QString::number(poradiZastavky)<<"i "<<QString::number(i) << docasnaZastavka.stopPoint.StopName<<"cil"<<docasnaZastavka.destination.NameLcd<<"linka "<<docasnaZastavka.line.LineName<<" nocni "<<docasnaZastavka.line.isNight ;
        tempStopPointDestination.stopPoint.fareZoneList=stopPointElementToFareZoneList1_0(aktZastavkaDOM);
        tempStopList.push_back(tempStopPointDestination);
    }
    if (tempStopList.size() ==0)
    {
        qDebug()<<"no stops found";
        return 0;
    }
    return 1;
}




Vdv301VehicleInformationGroup XmlParser::domAllDataToVdv301VehicleInformationGroup(QDomElement input)
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

Vdv301Trip XmlParser::domTripInformationToVdv301Trip( QDomElement input)
{
    Vdv301Trip trip;
    trip.tripRef=input.firstChildElement("TripRef").text();
    trip.stopPointList=domStopListToVdv301TripStopList(input);
    trip.locationState=Vdv301Enumerations::LocationStateEnumerationFromQString(input.firstChildElement("LocationState").text());
    return trip;
}

QVector<Vdv301StopPoint> XmlParser::domStopListToVdv301TripStopList( QDomElement domTrip)
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


Vdv301StopPoint XmlParser::domStopPointToVdv301StopPoint( QDomElement domStopPoint)
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

Vdv301DisplayContent XmlParser::domDisplayContentToVdv301DisplayContent(QDomElement selectedDisplayContentDom)
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


Vdv301InternationalText XmlParser::qDomNodeToVdv301InternationalText(QDomNode domNode)
{
    Vdv301InternationalText output;
    output.text=domNode.firstChildElement("Value").text();
    output.language=domNode.firstChildElement("Language").text();

    return output;
}

QVector<QString> XmlParser::propertyDomToStringList(QDomNode domNode,QString elementName)
{
    QVector<QString> output;

    QDomNodeList propertyNodes=domNode.toElement().elementsByTagName(elementName+"Property");
    // qDebug()<<"naplnVektor Zastavka ma tolik priznaku:"<<priznaky.count();

    for (int j=0;j<propertyNodes.count();j++)
    {
        QString propertyValue=propertyNodes.at(j).firstChild().nodeValue();
        //     qDebug()<<"priznak "<<hodnotaPriznaku;
        output.push_back(propertyValue);
    }
    return output;
}






QVector<StopPoint> XmlParser::domStopPointToViaPointsVector(QDomElement stopPointElement)
{
    qDebug()<<Q_FUNC_INFO;
    QDomNodeList viaPointDomList = stopPointElement.elementsByTagName("ViaPoint");
    QVector<StopPoint> viaPointList;
    for (int i=0;i<viaPointDomList.count();i++)
    {
        StopPoint viaPoint;
        QDomElement selectedViaPointElement=viaPointDomList.at(i).toElement();
        viaPoint.NameLcd=selectedViaPointElement.firstChildElement("PlaceName").firstChildElement("Value").firstChild().nodeValue();
        viaPoint.NameInner=selectedViaPointElement.firstChildElement("PlaceName").firstChildElement("Value").firstChild().nodeValue();
        viaPoint.NameSide=selectedViaPointElement.firstChildElement("PlaceName").firstChildElement("Value").firstChild().nodeValue();
        viaPoint.StopName=viaPoint.NameLcd;
        viaPointList.append(viaPoint);
    }

    return viaPointList;
}



QVector<FareZone> XmlParser::stopPointElementToFareZoneList1_0(QDomElement stopPointElement)
{
    qDebug()<<Q_FUNC_INFO;
    QVector<FareZone> output;

    QDomNodeList fareZoneNodeList = stopPointElement.elementsByTagName("FareZone");

    for (int i=0;i<fareZoneNodeList.count();i++)
    {
        FareZone selectedFareZone;
        selectedFareZone.system="";
        selectedFareZone.name=fareZoneNodeList.at(i).firstChildElement("Value").firstChild().nodeValue();
        output.append(selectedFareZone);

    }

    return output;
}


int XmlParser::domDocumentVehicleGroupToVehicleState(VehicleState &vehicleState,QDomDocument xmlDocument )
{
    qDebug()<<Q_FUNC_INFO;
    QDomElement root = xmlDocument.firstChildElement();
    qDebug()<<"root name "<<root.nodeName();
    QDomElement allData=root.firstChildElement("AllData");
    qDebug()<<"alldata name "<<allData.nodeName();
    vehicleState.currentStopIndex0=allData.firstChildElement("CurrentStopIndex").firstChildElement().firstChild().nodeValue().toInt()-1; //-1
    vehicleState.isVehicleStopRequested=allData.firstChildElement("VehicleStopRequested").firstChildElement("Value").firstChild().nodeValue().toInt();
    vehicleState.locationState=Vdv301Enumerations::LocationStateEnumerationFromQString(allData.firstChildElement("TripInformation").firstChildElement("LocationState").firstChild().nodeValue());
    vehicleState.vehicleMode=allData.firstChildElement("MyOwnVehicleMode").firstChildElement("PtMainMode").firstChild().nodeValue();
    vehicleState.vehicleSubMode=allData.firstChildElement("MyOwnVehicleMode").firstChildElement(vehicleState.vehicleMode).firstChild().nodeValue();
    qDebug()<<"stopIndex "<<QString::number(vehicleState.currentStopIndex0)<<"stopRequested "<<vehicleState.isVehicleStopRequested<<" locState "<<vehicleState.locationState;

    return 1;
}






void XmlParser::Test()
{
    qDebug()<<Q_FUNC_INFO;
    qInfo()<<"xmlParserTestPoint2";
}



int XmlParser::followingConnectionExists(QVector<StopPointDestination> followingStopPointDestinationList)
{
    if (followingStopPointDestinationList.isEmpty())
    {
        return false;
    }
    return true;


}



QVector<Connection> XmlParser::domElementToConnectionList(QDomElement connectionsElement)
{
    //rozepsano
    qDebug()<<Q_FUNC_INFO;
    QVector<Connection> output;

    QDomNodeList connectionNodeList=connectionsElement.elementsByTagName("Connection") ;

    for (int i=0;i<connectionNodeList.count();i++)
    {
        Connection selectedConnection;
        QDomElement selectedConnectionElement=connectionNodeList.at(i).toElement();
        selectedConnection.connectionProperty=selectedConnectionElement.firstChildElement("ConnectionProperty").firstChild().nodeValue();

        selectedConnection.connectionType=selectedConnectionElement.firstChildElement("ConnectionType").firstChild().nodeValue();

        QDomElement displayContent=selectedConnectionElement.firstChildElement("DisplayContent");
        QDomElement lineInformation=displayContent.firstChildElement("LineInformation");

        selectedConnection.line.lineName=lineInformation.firstChildElement("LineName").firstChildElement("Value").firstChild().nodeValue();
        selectedConnection.line.lineNumber=lineInformation.firstChildElement("LineNumber").firstChildElement("Value").firstChild().nodeValue();

        selectedConnection.destinationName=displayContent.firstChildElement("Destination").firstChildElement("DestinationName").firstChildElement("Value").firstChild().nodeValue();
        selectedConnection.expectedDepartureTime=QDateTime::fromString( selectedConnectionElement.firstChildElement("ExpectedDepartureTime").firstChildElement("Value").firstChild().nodeValue(),Qt::ISODate);

        selectedConnection.scheduledDepartureTime=QDateTime::fromString( selectedConnectionElement.firstChildElement("ScheduledDepartureTime").firstChildElement("Value").firstChild().nodeValue(),Qt::ISODate);

        QDateTime timestamp = selectedConnection.expectedDepartureTime;
        // timestamp.setTimeSpec(Qt::UTC); // mark the timestamp as UTC (but don't convert it)
        //  timestamp = timestamp.toLocalTime(); // convert to local time


        selectedConnection.platform=selectedConnectionElement.firstChildElement("Platform").firstChildElement("Value").firstChild().nodeValue();

        QDomElement connectionMode=selectedConnectionElement.firstChildElement("ConnectionMode");
        selectedConnection.mainMode=connectionMode.firstChildElement("PtMainMode").firstChild().nodeValue();
        selectedConnection.subMode=connectionMode.firstChildElement(selectedConnection.mainMode).firstChild().nodeValue();

        QVector<QString> linePropertyStringList;

        QDomNodeList linePropertyElementList=selectedConnectionElement.elementsByTagName("LineProperty");

        for(int j=0; j<linePropertyElementList.count();j++)
        {
            QString propertyValue=linePropertyElementList.at(j).firstChild().nodeValue();
            linePropertyStringList.push_back(propertyValue);
        }
        selectedConnection.line=propertyStringListToLine(linePropertyStringList,selectedConnection.line);

        //    qDebug()<<"XmlParser::nactiPrestupy "<<aktualniPrestup.connectionProperty<<" "<<aktualniPrestup.line.LineName<<" "<<aktualniPrestup.destinationName<<" "<<aktualniPrestup.expectedDepartureTime<<" "<<aktualniPrestup.mainMode<<" "<<aktualniPrestup.subMode<<" "<<aktualniPrestup.platform<<" replacement "<<aktualniPrestup.line.isReplacement;

        output.push_back(selectedConnection);
    }
    return output;
}


Line XmlParser::propertyStringListToLine(QVector<QString> propertyStringList, Line inputLine)
{
    qDebug()<<Q_FUNC_INFO;
    // qDebug()<<"linka je nocni:"<<vstupniLinka.isNight;
    foreach(QString selectedPropertyString,propertyStringList)
    {
        //  qDebug()<<"priznakLinky: "<<textPriznak;
        if(selectedPropertyString=="Night")
        {
            inputLine.isNight=true;
            //  qDebug()<<"linka je nocni";
        }
        if(selectedPropertyString=="Day")
        {
            inputLine.isNight=false;
        }
        if(selectedPropertyString=="Diversion")
        {
            inputLine.isDiversion=true;
        }
        if(selectedPropertyString=="Replacement")
        {
            inputLine.isReplacement=true;
            qDebug()<<"line is replacement";
        }
        if(selectedPropertyString=="Special")
        {
            inputLine.isSpecial=true;
        }
        if(selectedPropertyString=="WheelChair")
        {
            inputLine.isWheelchair=true;
        }
        /*
        if(selectedPropertyString=="XXX")
        {
            inputLine.XXX=true;
        }
        */
    }

    return inputLine;

}



