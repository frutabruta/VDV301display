#include "xmlparser2_2cz1_0.h"


XmlParser2_2CZ1_0::XmlParser2_2CZ1_0()
{}



int XmlParser2_2CZ1_0::createStopList2_2CZ1_0(QVector<StopPointDestination> &docasnySeznamZst,QVector<StopPointDestination> &docasnySeznamZstNavazny, int &docasnyIndexZastavky)
{
    qDebug()<<Q_FUNC_INFO;
    docasnySeznamZst.clear();
    QDomElement root = receivedDataDomDocument.firstChildElement();
    qDebug()<<root.tagName();
    if (root.tagName()!="CustomerInformationService.GetAllDataResponse")
    {
        qDebug()<<"vadné XML";
        return 0;
    }


    QDomElement tripInformation;//=allData.firstChildElement("TripInformation");
    QDomElement tripInformation2;
    docasnyIndexZastavky=root.elementsByTagName("CurrentStopIndex").at(0).firstChildElement().text().toInt()-1; //převod indexování od 1 (VDV301) na indexování od 0 ( C++ pole)

    QDomNodeList tripInformationList=root.elementsByTagName("TripInformation");


    switch(tripInformationList.count())
    {
    case 0:
        qDebug()<<"seznam tripu je prazdny";
        return 0;
        break;
    case 1:
        tripInformation=tripInformationList.at(0).toElement();
        parseStopPointDestinationList2_2CZ1_0(docasnySeznamZst,tripInformation);
        break ;
    case 2:
        qDebug()<<"existuje jeden navazny spoj";
        tripInformation=tripInformationList.at(0).toElement();
        parseStopPointDestinationList2_2CZ1_0(docasnySeznamZst,tripInformation);
        tripInformation2=tripInformationList.at(1).toElement();
        parseStopPointDestinationList2_2CZ1_0(docasnySeznamZstNavazny,tripInformation2);

        break;

    default:
        qDebug()<<"moc navaznych spoju";
        tripInformation=tripInformationList.at(0).toElement();
        parseStopPointDestinationList2_2CZ1_0(docasnySeznamZst,tripInformation);
        tripInformation2=tripInformationList.at(1).toElement();
        parseStopPointDestinationList2_2CZ1_0(docasnySeznamZstNavazny,tripInformation2);

        break;

    }



    return 1;
}


int XmlParser2_2CZ1_0::parseStopPointDestinationList2_2CZ1_0(QVector<StopPointDestination> &docasnySeznamZst, QDomElement vstup)
{
    qDebug()<<Q_FUNC_INFO;

    QDomNodeList nodes = vstup.elementsByTagName("StopPoint");


    for (int i=0; i<nodes.count();i++)
    {

        StopPointDestination docasnaZastavka;
        QDomElement aktZastavkaDOM=nodes.at(i).toElement();
        int poradiZastavky=aktZastavkaDOM.elementsByTagName("StopIndex").at(0).firstChildElement().text().toInt();
        docasnaZastavka.stopPoint.StopName=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.stopPoint.NameFront=aktZastavkaDOM.firstChildElement("StopFrontName").firstChildElement().text();
        docasnaZastavka.stopPoint.NameSide=aktZastavkaDOM.firstChildElement("StopSideName").firstChildElement().text();
        docasnaZastavka.stopPoint.NameRear=aktZastavkaDOM.firstChildElement("StopRearName").firstChildElement().text();
        docasnaZastavka.stopPoint.NameInner=aktZastavkaDOM.firstChildElement("StopInnerName").firstChildElement().text();
        docasnaZastavka.stopPoint.NameLcd=aktZastavkaDOM.firstChildElement("StopLcdName").firstChildElement().text();
        docasnaZastavka.line.lineName=aktZastavkaDOM.firstChildElement("DisplayContent").firstChildElement("LineInformation").firstChildElement("LineName").firstChildElement().text();

        QVector<QString> priznakyStringy;

        QDomNodeList seznamPriznakuElements=aktZastavkaDOM.firstChildElement("DisplayContent").firstChildElement("LineInformation").elementsByTagName("LineProperty");


        for(int j=0; j<seznamPriznakuElements.count();j++)
        {
            QString priznak=seznamPriznakuElements.at(j).firstChild().nodeValue();
            priznakyStringy.push_back(priznak);
            // qDebug()<<"parsuju priznaky:"<<priznak;
        }
        docasnaZastavka.line=propertyStringListToLine(priznakyStringy,docasnaZastavka.line);

        docasnaZastavka.stopPoint.StopIndex=i;
        docasnaZastavka.viaPoints=domToViaPoints2_2CZ1_0(aktZastavkaDOM);
        docasnaZastavka.stopPoint.connectionList=domElementToConnectionList(aktZastavkaDOM);

        QDomElement displayContent=aktZastavkaDOM.firstChildElement("DisplayContent");
        QDomElement dDestination=displayContent.firstChildElement("Destination");
        docasnaZastavka.destination.StopName=dDestination.firstChildElement("DestinationName").text();
        docasnaZastavka.destination.NameFront=dDestination.firstChildElement("DestinationFrontName").firstChildElement().text();
        docasnaZastavka.destination.iconList=propertyDomToStringList(displayContent.elementsByTagName("Destination").at(0),"Destination");

        QDomNodeList nazvyCelniPanel=dDestination.elementsByTagName("DestinationFrontName");
        if (nazvyCelniPanel.length()>0)
        {
            docasnaZastavka.destination.NameFront=nazvyCelniPanel.at(0).firstChildElement().text();
        }
        if (nazvyCelniPanel.length()>1)
        {
            docasnaZastavka.destination.NameFront2=nazvyCelniPanel.at(1).firstChildElement().text();
        }
        docasnaZastavka.stopPoint.iconList= propertyDomToStringList(aktZastavkaDOM,"Stop");


        docasnaZastavka.destination.NameSide=dDestination.firstChildElement("DestinationSideName").firstChildElement().text();
        docasnaZastavka.destination.NameRear=dDestination.firstChildElement("DestinationRearName").firstChildElement().text();
        docasnaZastavka.destination.NameInner=dDestination.firstChildElement("DestinationInnerName").firstChildElement().text();
        docasnaZastavka.destination.NameLcd=dDestination.firstChildElement("DestinationLcdName").firstChildElement().text();

        //    qInfo()<< "xml "<<QString::number(poradiZastavky)<<"i "<<QString::number(i) << docasnaZastavka.stopPoint.StopName<<"cil"<<docasnaZastavka.destination.NameLcd<<"linka "<<docasnaZastavka.line.LineName<<" nocni "<<docasnaZastavka.line.isNight ;
        docasnaZastavka.stopPoint.fareZoneList=domToFareZoneList2_2CZ1_0(aktZastavkaDOM);
        docasnySeznamZst.push_back(docasnaZastavka);
    }
    if (docasnySeznamZst.size() ==0)
    {
        qDebug()<<"zastavkyNebylyNacteny";
        return 0;
    }
    return 1;
}




QVector<FareZone> XmlParser2_2CZ1_0::domToFareZoneList2_2CZ1_0(QDomElement domStopPoint)
{
    qDebug()<<Q_FUNC_INFO;
    QVector<FareZone> vystupniVektorPasmo;

    QDomNodeList domPasma = domStopPoint.elementsByTagName("FareZone");

    for (int i=0;i<domPasma.count();i++)
    {
        FareZone aktPasmo;
        aktPasmo.system=domPasma.at(i).firstChildElement("FareZoneType").firstChildElement("FareZoneTypeName").firstChildElement("Value").firstChild().nodeValue();
        aktPasmo.name=domPasma.at(i).firstChildElement("FareZoneLongName").firstChildElement("Value").firstChild().nodeValue();
        vystupniVektorPasmo.append(aktPasmo);

    }

    return vystupniVektorPasmo;
}



QVector<StopPoint> XmlParser2_2CZ1_0::domToViaPoints2_2CZ1_0(QDomElement domStopPoint)
{
    qDebug()<<Q_FUNC_INFO;
    QDomNodeList nacesty = domStopPoint.elementsByTagName("ViaPoint");
    QVector<StopPoint> vectorNacesty;
    for (int i=0;i<nacesty.count();i++)
    {
        StopPoint nacesta;
        QDomNodeList priznaky=nacesty.at(i).toElement().elementsByTagName("ViaPointProperty");
        QDomElement aktNacesta=nacesty.at(i).toElement();
        nacesta.NameLcd=aktNacesta.firstChildElement("PlaceLcdName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.NameInner=aktNacesta.firstChildElement("PlaceInnerName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.NameSide=aktNacesta.firstChildElement("PlaceSideName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.StopName=nacesta.NameLcd;
        
        
        nacesta.iconList= propertyDomToStringList(aktNacesta,"ViaPoint");
        for (int j=0;j<priznaky.count();j++)
        {
            QString hodnotaPriznaku=priznaky.at(j).firstChild().nodeValue();
            qDebug()<<"priznak "<<hodnotaPriznaku;


            if(hodnotaPriznaku=="RequestStop")
            {
                nacesta.onRequest=true;
            }
        }

        vectorNacesty.append(nacesta);
    }

    return vectorNacesty;
}



int XmlParser2_2CZ1_0::parseFareZoneChange(QDomDocument xmlko, QVector<FareZone> &pasmaZ, QVector<FareZone> &pasmaNa )
{
    //rozepsano
    qDebug()<<Q_FUNC_INFO;

    QDomElement root = xmlko.firstChildElement();
    QDomElement allData=root.firstChildElement("AllData");
    QDomElement tripInformation=allData.firstChildElement("TripInformation");
    QDomElement fareZoneChange=tripInformation.firstChildElement("FareZoneChange");
    if (fareZoneChange.isNull())
    {
        qDebug()<<"element FareZoneChange není vyplněn";
        return 0;
    }

    QDomElement fromFareZones=fareZoneChange.firstChildElement("FromFareZones");
    pasmaZ=domToFareZoneList2_2CZ1_0(fromFareZones);

    QDomElement toFareZones=fareZoneChange.firstChildElement("ToFareZones");
    pasmaNa=domToFareZoneList2_2CZ1_0(toFareZones);

    qDebug()<<"pocet pasem Z "<<pasmaZ.count()<<" pocet pasem DO "<<pasmaNa.count();
    return 1;
}


int XmlParser2_2CZ1_0::parseAdditionalTextMessage2_2CZ1_0(QDomDocument xmlko, QString &type ,QString &headline,QString &text )
{
    qDebug()<<Q_FUNC_INFO;
    QDomElement root = xmlko.firstChildElement();

    qDebug()<<"root name "<<root.nodeName();
    QDomElement allData=root.firstChildElement("AllData");

    if (allData.isNull())
    {
        qDebug()<<"element alldata neni k dispozici";
        return 0;
    }

    qDebug()<<"alldata name "<<allData.nodeName();

    QDomElement tripInformation=allData.firstChildElement("TripInformation");

    QDomElement additionalTextMessage=tripInformation.firstChildElement("AdditionalTextMessage");
    type=additionalTextMessage.firstChildElement("AdditionalTextMessageType").firstChildElement("Value").firstChild().nodeValue();
    headline=additionalTextMessage.firstChildElement("AdditionalTextMessageHeadline").firstChildElement("Value").firstChild().nodeValue();
    text=additionalTextMessage.firstChildElement("AdditionalTextMessageText").firstChildElement("Value").firstChild().nodeValue();

    qDebug()<<"additional text je "<<type<<" "<<headline<<" "<<text;


    return 1;
}



QVector<Connection> XmlParser2_2CZ1_0::domElementToConnectionList(QDomElement connectionsElement)
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
        selectedConnection.expectedDepartureTime=QDateTime::fromString( selectedConnectionElement.firstChildElement("ExpectedDepartureTime").firstChildElement("Value").firstChild().nodeValue(),Qt::ISODate);
        selectedConnection.scheduledDepartureTime=QDateTime::fromString( selectedConnectionElement.firstChildElement("ScheduledDepartureTime").firstChildElement("Value").firstChild().nodeValue(),Qt::ISODate);



        selectedConnection.connectionProperty=selectedConnectionElement.firstChildElement("ConnectionProperty").firstChild().nodeValue();

       
        QDateTime timestamp = selectedConnection.expectedDepartureTime;

        QDomElement connectionMode=selectedConnectionElement.firstChildElement("ConnectionMode");
        selectedConnection.mainMode=connectionMode.firstChildElement("PtMainMode").firstChild().nodeValue();
        selectedConnection.subMode=connectionMode.firstChildElement(selectedConnection.mainMode).firstChild().nodeValue();

        output.push_back(selectedConnection);
    }
    return output;
}



Line XmlParser2_2CZ1_0::propertyStringListToLine(QVector<QString> propertyStringList, Line inputLine)
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



int XmlParser2_2CZ1_0::domDocumentVehicleGroupToVehicleState(VehicleState &vehicleState,QDomDocument xmlDocument )
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


int XmlParser2_2CZ1_0::followingTripExists(QVector<StopPointDestination> followingStopPointDestinationList)
{
    if (followingStopPointDestinationList.isEmpty())
    {
        return false;
    }
    return true;


}


int XmlParser2_2CZ1_0::followingTripLineDestination(QVector<StopPointDestination> &tempStopPointDestinationList, QString &lineText, QString &destinationText)
{
    if (tempStopPointDestinationList.isEmpty())
    {
        return 0;
    }
    lineText=tempStopPointDestinationList.first().line.lineName;
    destinationText=tempStopPointDestinationList.first().destination.NameLcd;


    return 1;
}


