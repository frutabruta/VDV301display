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

void XmlParser::nactiXML(QString vstup)
{
    qDebug()<<Q_FUNC_INFO;

    if(vstup!=stareXml)
    {
        zmenaDat=true;
        zmenaDat=false;
    }
    else
    {
        zmenaDat=false;
    }

    dokument.setContent(vstup);
    // QString blabla = dokument.toString();


}

int XmlParser::VytvorSeznamZastavek1_0(QVector<StopPointDestination> &docasnySeznamZst,QVector<StopPointDestination> &docasnySeznamZstNavazny, int &docasnyIndexZastavky)
{
    qDebug()<<Q_FUNC_INFO;
    docasnySeznamZst.clear();
    QDomElement root = dokument.firstChildElement();
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
        tripDoSeznamuZastavek1_0(docasnySeznamZst,tripInformation);
        break ;
    case 2:
        qDebug()<<"existuje jeden navazny spoj";
        tripInformation=tripInformationList.at(0).toElement();
        tripDoSeznamuZastavek1_0(docasnySeznamZst,tripInformation);
        tripInformation2=tripInformationList.at(1).toElement();
        tripDoSeznamuZastavek1_0(docasnySeznamZstNavazny,tripInformation2);

        break;

    default:
        qDebug()<<"moc navaznych spoju";
        tripInformation=tripInformationList.at(0).toElement();
        tripDoSeznamuZastavek1_0(docasnySeznamZst,tripInformation);
        tripInformation2=tripInformationList.at(1).toElement();
        tripDoSeznamuZastavek1_0(docasnySeznamZstNavazny,tripInformation2);

        break;

    }



    return 1;
}




QDateTime XmlParser::vyparsujTimestamp(QDomDocument vstupniDokument)
{
    qDebug()<<Q_FUNC_INFO;

    QDateTime timestamp =  QDateTime::fromString(vstupniDokument.firstChildElement("CustomerInformationService.GetAllDataResponse").firstChildElement("AllData").firstChildElement("TimeStamp").firstChildElement("Value").firstChild().nodeValue() ,Qt::ISODate);

    return timestamp;

}


int XmlParser::udajeNavaznehoSpoje(QVector<StopPointDestination> &docasnySeznamZst, QString &linka, QString &cil)
{
    if (docasnySeznamZst.isEmpty())
    {
        return 0;
    }
    linka=docasnySeznamZst.first().line.lineName;
    cil=docasnySeznamZst.first().destination.NameLcd;


    return 1;
}


int XmlParser::tripDoSeznamuZastavek1_0(QVector<StopPointDestination> &docasnySeznamZst, QDomElement vstup)
{
    qDebug()<<Q_FUNC_INFO;

    QDomNodeList nodes = vstup.elementsByTagName("StopPoint");


    for (int i=0; i<nodes.count();i++)
    {

        StopPointDestination docasnaZastavka;
        QDomElement aktZastavkaDOM=nodes.at(i).toElement();
        int poradiZastavky=aktZastavkaDOM.elementsByTagName("StopIndex").at(0).firstChildElement().text().toInt();
        docasnaZastavka.stopPoint.StopName=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.stopPoint.NameFront=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.stopPoint.NameSide=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.stopPoint.NameRear=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.stopPoint.NameInner=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.stopPoint.NameLcd=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.line.lineName=aktZastavkaDOM.firstChildElement("DisplayContent").firstChildElement("LineInformation").firstChildElement("LineName").firstChildElement().text();

        QVector<QString> priznakyStringy;

        QDomNodeList seznamPriznakuElements=aktZastavkaDOM.firstChildElement("DisplayContent").firstChildElement("LineInformation").elementsByTagName("LineProperty");


        for(int j=0; j<seznamPriznakuElements.count();j++)
        {
            QString priznak=seznamPriznakuElements.at(j).firstChild().nodeValue();
            priznakyStringy.push_back(priznak);
            // qDebug()<<"parsuju priznaky:"<<priznak;
        }
        docasnaZastavka.line=priznakyDoLinky(priznakyStringy,docasnaZastavka.line);

        docasnaZastavka.stopPoint.StopIndex=i;
        docasnaZastavka.viaPoints=vyparsujNacestneZastavky1_0(aktZastavkaDOM);
        docasnaZastavka.stopPoint.connectionList=nactiPrestupy(aktZastavkaDOM);

        QDomElement displayContent=aktZastavkaDOM.firstChildElement("DisplayContent");
        QDomElement dDestination=displayContent.firstChildElement("Destination");
        docasnaZastavka.destination.StopName=dDestination.firstChildElement("DestinationName").text();
        docasnaZastavka.destination.NameFront=dDestination.firstChildElement("DestinationName").firstChildElement().text();
        docasnaZastavka.destination.iconList=naplnVektorPriznaku(displayContent.elementsByTagName("Destination").at(0),"Destination");

        QDomNodeList nazvyCelniPanel=dDestination.elementsByTagName("DestinationName");
        if (nazvyCelniPanel.length()>0)
        {
            docasnaZastavka.destination.NameFront=nazvyCelniPanel.at(0).firstChildElement().text();
        }
        if (nazvyCelniPanel.length()>1)
        {
            docasnaZastavka.destination.NameFront2=nazvyCelniPanel.at(1).firstChildElement().text();
        }
        docasnaZastavka.stopPoint.iconList= naplnVektorPriznaku(aktZastavkaDOM,"Stop");


        docasnaZastavka.destination.NameSide=dDestination.firstChildElement("DestinationName").firstChildElement().text();
        docasnaZastavka.destination.NameRear=dDestination.firstChildElement("DestinationName").firstChildElement().text();
        docasnaZastavka.destination.NameInner=dDestination.firstChildElement("DestinationName").firstChildElement().text();
        docasnaZastavka.destination.NameLcd=dDestination.firstChildElement("DestinationName").firstChildElement().text();

        //    qInfo()<< "xml "<<QString::number(poradiZastavky)<<"i "<<QString::number(i) << docasnaZastavka.stopPoint.StopName<<"cil"<<docasnaZastavka.destination.NameLcd<<"linka "<<docasnaZastavka.line.LineName<<" nocni "<<docasnaZastavka.line.isNight ;
        docasnaZastavka.stopPoint.fareZoneList=vyparsujPasma_1_0(aktZastavkaDOM);
        docasnySeznamZst.push_back(docasnaZastavka);
    }
    if (docasnySeznamZst.size() ==0)
    {
        qDebug()<<"zastavkyNebylyNacteny";
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
        QDomElement aktZastavkaDOM=nodes.at(i).toElement();

        //////////////////////////////////////////////////
        //new approach
        tripStopPointList<<domStopPointToVdv301StopPoint(aktZastavkaDOM);
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

QVector<QString> XmlParser::naplnVektorPriznaku(QDomNode vstup,QString nazevElementu)
{
    // qDebug()<<"XmlParser::naplnVektorPriznaku";
    QVector<QString> vystup;

    StopPoint nacesta;
    QDomNodeList priznaky=vstup.toElement().elementsByTagName(nazevElementu+"Property");
    // qDebug()<<"naplnVektor Zastavka ma tolik priznaku:"<<priznaky.count();

    for (int j=0;j<priznaky.count();j++)
    {
        QString hodnotaPriznaku=priznaky.at(j).firstChild().nodeValue();
        //     qDebug()<<"priznak "<<hodnotaPriznaku;
        vystup.push_back(hodnotaPriznaku);
    }
    return vystup;
}






QVector<StopPoint> XmlParser::vyparsujNacestneZastavky1_0(QDomElement zastavka)
{
    qDebug()<<Q_FUNC_INFO;
    QDomNodeList nacesty = zastavka.elementsByTagName("ViaPoint");
    QVector<StopPoint> vectorNacesty;
    for (int i=0;i<nacesty.count();i++)
    {
        StopPoint nacesta;
        // QDomNodeList priznaky=nacesty.at(i).toElement().elementsByTagName("ViaPointProperty");
        QDomElement aktNacesta=nacesty.at(i).toElement();
        nacesta.NameLcd=aktNacesta.firstChildElement("PlaceName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.NameInner=aktNacesta.firstChildElement("PlaceName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.NameSide=aktNacesta.firstChildElement("PlaceName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.StopName=nacesta.NameLcd;

        /*
        nacesta.seznamPiktogramu= naplnVektorPriznaku(aktNacesta,"ViaPoint");
        for (int j=0;j<priznaky.count();j++)
        {
            QString hodnotaPriznaku=priznaky.at(j).firstChild().nodeValue();
            qDebug()<<"priznak "<<hodnotaPriznaku;


            if(hodnotaPriznaku=="RequestStop")
            {
                nacesta.naZnameni=true;
            }
        }*/

        vectorNacesty.append(nacesta);
    }

    return vectorNacesty;
}



QVector<FareZone> XmlParser::vyparsujPasma_1_0(QDomElement zastavka)
{
    qDebug()<<Q_FUNC_INFO;
    QVector<FareZone> vystupniVektorPasmo;

    QDomNodeList domPasma = zastavka.elementsByTagName("FareZone");

    for (int i=0;i<domPasma.count();i++)
    {
        FareZone aktPasmo;
        aktPasmo.system="";
        aktPasmo.name=domPasma.at(i).firstChildElement("Value").firstChild().nodeValue();
        vystupniVektorPasmo.append(aktPasmo);

    }

    return vystupniVektorPasmo;
}


int XmlParser::nactiVehicleGroup(VehicleState &stav,QDomDocument xmlko )
{
    qDebug()<<Q_FUNC_INFO;
    QDomElement root = xmlko.firstChildElement();
    qDebug()<<"root name "<<root.nodeName();
    QDomElement allData=root.firstChildElement("AllData");
    qDebug()<<"alldata name "<<allData.nodeName();
    stav.currentStopIndex0=allData.firstChildElement("CurrentStopIndex").firstChildElement().firstChild().nodeValue().toInt()-1; //-1
    stav.isVehicleStopRequested=allData.firstChildElement("VehicleStopRequested").firstChildElement("Value").firstChild().nodeValue().toInt();
    stav.locationState=Vdv301Enumerations::LocationStateEnumerationFromQString(allData.firstChildElement("TripInformation").firstChildElement("LocationState").firstChild().nodeValue());
    stav.vehicleMode=allData.firstChildElement("MyOwnVehicleMode").firstChildElement("PtMainMode").firstChild().nodeValue();
    stav.vehicleSubMode=allData.firstChildElement("MyOwnVehicleMode").firstChildElement(stav.vehicleMode).firstChild().nodeValue();
    qDebug()<<"stopIndex "<<QString::number(stav.currentStopIndex0)<<"stopRequested "<<stav.isVehicleStopRequested<<" locState "<<stav.locationState;

    return 1;
}






void XmlParser::Test()
{
    qDebug()<<Q_FUNC_INFO;
    qInfo()<<"xmlParserTestPoint2";
}



int XmlParser::existujeNavaznySpoj(QVector<StopPointDestination> seznamZastavek)
{
    if (seznamZastavek.isEmpty())
    {
        return false;
    }
    return true;


}



QVector<Connection> XmlParser::nactiPrestupy(QDomElement vstup)
{
    //rozepsano
    qDebug()<<Q_FUNC_INFO;
    QVector<Connection> vystup;

    QDomNodeList elementyPrestupu=vstup.elementsByTagName("Connection") ;

    for (int i=0;i<elementyPrestupu.count();i++)
    {
        Connection aktualniPrestup;
        QDomElement aktualniElement=elementyPrestupu.at(i).toElement();
        aktualniPrestup.connectionProperty=aktualniElement.firstChildElement("ConnectionProperty").firstChild().nodeValue();

        aktualniPrestup.connectionType=aktualniElement.firstChildElement("ConnectionType").firstChild().nodeValue();

        QDomElement displayContent=aktualniElement.firstChildElement("DisplayContent");
        QDomElement lineInformation=displayContent.firstChildElement("LineInformation");

        aktualniPrestup.line.lineName=lineInformation.firstChildElement("LineName").firstChildElement("Value").firstChild().nodeValue();
        aktualniPrestup.line.lineNumber=lineInformation.firstChildElement("LineNumber").firstChildElement("Value").firstChild().nodeValue();

        aktualniPrestup.destinationName=displayContent.firstChildElement("Destination").firstChildElement("DestinationName").firstChildElement("Value").firstChild().nodeValue();
        aktualniPrestup.expectedDepartureTime=QDateTime::fromString( aktualniElement.firstChildElement("ExpectedDepartureTime").firstChildElement("Value").firstChild().nodeValue(),Qt::ISODate);

        aktualniPrestup.scheduledDepartureTime=QDateTime::fromString( aktualniElement.firstChildElement("ScheduledDepartureTime").firstChildElement("Value").firstChild().nodeValue(),Qt::ISODate);

        QDateTime timestamp = aktualniPrestup.expectedDepartureTime;
        // timestamp.setTimeSpec(Qt::UTC); // mark the timestamp as UTC (but don't convert it)
        //  timestamp = timestamp.toLocalTime(); // convert to local time

        /*
        QString vysledek= QString::number(-timestamp.secsTo(QDateTime::currentDateTime())/60)+" min." ;
        aktualniPrestup.expectedDepartureTime=vysledek;
    */
        // aktualniPrestup.departureTime=timestamp.toString("hh:mm");

        aktualniPrestup.platform=aktualniElement.firstChildElement("Platform").firstChildElement("Value").firstChild().nodeValue();

        QDomElement connectionMode=aktualniElement.firstChildElement("ConnectionMode");
        aktualniPrestup.mainMode=connectionMode.firstChildElement("PtMainMode").firstChild().nodeValue();
        aktualniPrestup.subMode=connectionMode.firstChildElement(aktualniPrestup.mainMode).firstChild().nodeValue();

        QVector<QString> priznakyStringy;

        QDomNodeList seznamPriznakuElements=aktualniElement.elementsByTagName("LineProperty");

        for(int j=0; j<seznamPriznakuElements.count();j++)
        {
            QString priznak=seznamPriznakuElements.at(j).firstChild().nodeValue();
            priznakyStringy.push_back(priznak);
        }
        aktualniPrestup.line=priznakyDoLinky(priznakyStringy,aktualniPrestup.line);

        //    qDebug()<<"XmlParser::nactiPrestupy "<<aktualniPrestup.connectionProperty<<" "<<aktualniPrestup.line.LineName<<" "<<aktualniPrestup.destinationName<<" "<<aktualniPrestup.expectedDepartureTime<<" "<<aktualniPrestup.mainMode<<" "<<aktualniPrestup.subMode<<" "<<aktualniPrestup.platform<<" replacement "<<aktualniPrestup.line.isReplacement;

        vystup.push_back(aktualniPrestup);
    }
    return vystup;
}


Line XmlParser::priznakyDoLinky(QVector<QString> vstup, Line vstupniLinka)
{
    qDebug()<<Q_FUNC_INFO;
    // qDebug()<<"linka je nocni:"<<vstupniLinka.isNight;
    foreach(QString textPriznak,vstup)
    {
        //  qDebug()<<"priznakLinky: "<<textPriznak;
        if(textPriznak=="Night")
        {
            vstupniLinka.isNight=true;
            //  qDebug()<<"linka je nocni";
        }
        if(textPriznak=="Day")
        {
            vstupniLinka.isNight=false;
        }
        if(textPriznak=="Diversion")
        {
            vstupniLinka.isDiversion=true;
        }
        if(textPriznak=="Replacement")
        {
            vstupniLinka.isReplacement=true;
            qDebug()<<"linak je nahradni";
        }
        if(textPriznak=="Special")
        {
            vstupniLinka.isSpecial=true;
        }
        if(textPriznak=="WheelChair")
        {
            vstupniLinka.isWheelchair=true;
        }
        /*
        if(textPriznak=="")
        {
            vstupniLinka.=true;
        }
        */
    }
    // qDebug()<<"linka je nocni:"<<vstupniLinka.isNight;
    return vstupniLinka;

}



