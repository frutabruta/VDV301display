
#include "xmlparser1_0old.h"

XmlParser1_0old::XmlParser1_0old() {}



int XmlParser1_0old::createStopList1_0(QVector<StopPointDestination> &tempStopList,QVector<StopPointDestination> &tempStopListFollowing, int &tempStopIndex)
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



int XmlParser1_0old::tripToStoplist1_0(QVector<StopPointDestination> &tempStopList, QDomElement domInput)
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


QVector<FareZone> XmlParser1_0old::stopPointElementToFareZoneList1_0(QDomElement stopPointElement)
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

int XmlParser1_0old::followingTripLineDestination(QVector<StopPointDestination> &tempStopPointDestinationList, QString &lineText, QString &destinationText)
{
    if (tempStopPointDestinationList.isEmpty())
    {
        return 0;
    }
    lineText=tempStopPointDestinationList.first().line.lineName;
    destinationText=tempStopPointDestinationList.first().destination.NameLcd;


    return 1;
}




int XmlParser1_0old::followingTripExists(QVector<StopPointDestination> followingStopPointDestinationList)
{
    if (followingStopPointDestinationList.isEmpty())
    {
        return false;
    }
    return true;


}


int XmlParser1_0old::domDocumentVehicleGroupToVehicleState(VehicleState &vehicleState,QDomDocument xmlDocument )
{
    qDebug()<<Q_FUNC_INFO;
    QDomElement root = xmlDocument.firstChildElement();
    qDebug()<<"root name "<<root.nodeName();
    QDomElement allData=root.firstChildElement("AllData");
    qDebug()<<"alldata name "<<allData.nodeName();
    vehicleState.currentStopIndex0=allData.firstChildElement("CurrentStopIndex").firstChildElement().firstChild().nodeValue().toInt()-1; //-1
    vehicleState.isVehicleStopRequested=allData.firstChildElement("VehicleStopRequested").firstChildElement("Value").firstChild().nodeValue().toInt();
    vehicleState.locationState=Vdv301Enumerations::LocationStateEnumerationFromQString(allData.firstChildElement("TripInformation").firstChildElement("LocationState").firstChild().nodeValue());
    // vehicleState.vehicleMode=allData.firstChildElement("MyOwnVehicleMode").firstChildElement("PtMainMode").firstChild().nodeValue();
    //  vehicleState.vehicleSubMode=allData.firstChildElement("MyOwnVehicleMode").firstChildElement(vehicleState.vehicleMode).firstChild().nodeValue();
    qDebug()<<"stopIndex "<<QString::number(vehicleState.currentStopIndex0)<<"stopRequested "<<vehicleState.isVehicleStopRequested<<" locState "<<vehicleState.locationState;

    return 1;
}


QVector<StopPoint> XmlParser1_0old::domStopPointToViaPointsVector(QDomElement stopPointElement)
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




Line XmlParser1_0old::propertyStringListToLine(QVector<QString> propertyStringList, Line inputLine)
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


QVector<Connection> XmlParser1_0old::domElementToConnectionList(QDomElement connectionsElement)
{
    //rozepsano
    qDebug()<<Q_FUNC_INFO;
    QVector<Connection> output;

    QDomNodeList connectionNodeList=connectionsElement.elementsByTagName("Connection") ;

    for (int i=0;i<connectionNodeList.count();i++)
    {
        Connection selectedConnection;
        QDomElement selectedConnectionElement=connectionNodeList.at(i).toElement();

        // StopRef" type="IBIS-IP.NMTOKEN">
        // ConnectionRef" type="IBIS-IP.NMTOKEN">
        // ConnectionType" type="ConnectionTypeEnumeration">
        selectedConnection.connectionType=selectedConnectionElement.firstChildElement("ConnectionType").firstChild().nodeValue();

        // DisplayContent" type="DisplayContentStructure">

        QDomElement displayContent=selectedConnectionElement.firstChildElement("DisplayContent");
        QDomElement lineInformation=displayContent.firstChildElement("LineInformation");

        selectedConnection.line.lineName=lineInformation.firstChildElement("LineName").firstChildElement("Value").firstChild().nodeValue();
        selectedConnection.line.lineNumber=lineInformation.firstChildElement("LineNumber").firstChildElement("Value").firstChild().nodeValue();

        selectedConnection.destinationName=displayContent.firstChildElement("Destination").firstChildElement("DestinationName").firstChildElement("Value").firstChild().nodeValue();

        QVector<QString> linePropertyStringList;

        QDomNodeList linePropertyElementList=selectedConnectionElement.elementsByTagName("LineProperty");

        for(int j=0; j<linePropertyElementList.count();j++)
        {
            QString propertyValue=linePropertyElementList.at(j).firstChild().nodeValue();
            linePropertyStringList.push_back(propertyValue);
        }
        selectedConnection.line=propertyStringListToLine(linePropertyStringList,selectedConnection.line);


        // Platform" type="IBIS-IP.string" minOccurs="0">
        selectedConnection.platform=selectedConnectionElement.firstChildElement("Platform").firstChildElement("Value").firstChild().nodeValue();


        // ConnectionState" type="ConnectionStateEnumeration" minOccurs="0">
        // TransportMode" type="VehicleStructure" minOccurs="0">
        // ExpectedDepatureTime" type="IBIS-IP.dateTime" minOccurs="0">
        selectedConnection.expectedDepartureTime=QDateTime::fromString( selectedConnectionElement.firstChildElement("ExpectedDepatureTime").firstChildElement("Value").firstChild().nodeValue(),Qt::ISODate);



        selectedConnection.connectionProperty=selectedConnectionElement.firstChildElement("ConnectionProperty").firstChild().nodeValue();

        //   selectedConnection.scheduledDepartureTime=QDateTime::fromString( selectedConnectionElement.firstChildElement("ScheduledDepartureTime").firstChildElement("Value").firstChild().nodeValue(),Qt::ISODate);

        QDateTime timestamp = selectedConnection.expectedDepartureTime;

        QDomElement connectionMode=selectedConnectionElement.firstChildElement("ConnectionMode");
     //   selectedConnection.mainMode=connectionMode.firstChildElement("PtMainMode").firstChild().nodeValue();
    //    selectedConnection.subMode=connectionMode.firstChildElement(selectedConnection.mainMode).firstChild().nodeValue();

        output.push_back(selectedConnection);
    }
    return output;
}


