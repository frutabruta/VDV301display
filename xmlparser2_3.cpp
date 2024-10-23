#include "xmlparser2_3.h"

XmlParser2_3::XmlParser2_3() {}



int XmlParser2_3::tripDoSeznamuZastavek2_3(QVector<StopPointDestination> &docasnySeznamZst, QDomElement vstup)
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

        QDomNodeList displayContentArray=aktZastavkaDOM.elementsByTagName("DisplayContent");

        for (int k=0;k<displayContentArray.length();k++)
        {
            qDebug()<<"aktualniDisplayContent: "<<QString::number(k);
            QDomNode aktualniDisplayContent=displayContentArray.at(k);
            QString ref=aktualniDisplayContent.firstChildElement("DisplayContentRef").firstChildElement("Value").firstChild().nodeValue();
            if(ref=="Front")
            {

                QDomNodeList destinationNameList=aktualniDisplayContent.toElement().firstChildElement("Destination").elementsByTagName("DestinationName");

                if(destinationNameList.count()>0)
                {
                    docasnaZastavka.destination.NameFront=destinationNameList.at(0).firstChildElement("Value").firstChild().nodeValue();

                }
                if(destinationNameList.count()>1)
                {
                    docasnaZastavka.destination.NameFront2=destinationNameList.at(1).firstChildElement("Value").firstChild().nodeValue();

                }
            }
            if(ref=="Side")
            {
                docasnaZastavka.destination.NameSide=aktualniDisplayContent.firstChildElement("Destination").firstChildElement("DestinationName").firstChildElement("Value").firstChild().nodeValue();

            }
            if(ref=="Rear")
            {
                docasnaZastavka.destination.NameRear=aktualniDisplayContent.firstChildElement("Destination").firstChildElement("DestinationName").firstChildElement("Value").firstChild().nodeValue();

            }
            if(ref=="Lcd")
            {
                docasnaZastavka.destination.NameLcd=aktualniDisplayContent.firstChildElement("Destination").firstChildElement("DestinationName").firstChildElement("Value").firstChild().nodeValue();
                docasnaZastavka.viaPoints=vyparsujNacestneZastavky2_3(aktualniDisplayContent);
                //   docasnaZastavka.destination.StopName =polozka.firstChildElement("Destination").firstChildElement("DestinationName").firstChildElement().text();

            }


        }

        docasnaZastavka.stopPoint.StopIndex=i;


        docasnaZastavka.stopPoint.connectionList=nactiPrestupy(aktZastavkaDOM);

        docasnaZastavka.stopPoint.iconList= naplnVektorPriznaku(aktZastavkaDOM,"Stop");

        // QDomElement displayContent=aktZastavkaDOM.firstChildElement("DisplayContent");
        // QDomElement dDestination=displayContent.firstChildElement("Destination");
        //   docasnaZastavka.destination.StopName=dDestination.firstChildElement("DestinationName").text();
        //     docasnaZastavka.destination.NameFront=dDestination.firstChildElement("DestinationFrontName").firstChildElement().text();

        // XXXXX   docasnaZastavka.destination.seznamPiktogramu=naplnVektorPriznaku(displayContent.elementsByTagName("Destination").at(0),"Destination");

        /*
        QDomNodeList nazvyCelniPanel=dDestination.elementsByTagName("DestinationFrontName");
        if (nazvyCelniPanel.length()>0)
        {
            docasnaZastavka.destination.NameFront=nazvyCelniPanel.at(0).firstChildElement().text();
        }
        if (nazvyCelniPanel.length()>1)
        {
            docasnaZastavka.destination.NameFront2=nazvyCelniPanel.at(1).firstChildElement().text();
        }
        docasnaZastavka.stopPoint.seznamPiktogramu= naplnVektorPriznaku(aktZastavkaDOM,"Stop");
*/

        /*
        docasnaZastavka.destination.NameSide=dDestination.firstChildElement("DestinationSideName").firstChildElement().text();
        docasnaZastavka.destination.NameRear=dDestination.firstChildElement("DestinationRearName").firstChildElement().text();
        docasnaZastavka.destination.NameInner=dDestination.firstChildElement("DestinationInnerName").firstChildElement().text();
        docasnaZastavka.destination.NameLcd=dDestination.firstChildElement("DestinationLcdName").firstChildElement().text();
*/


        //    qInfo()<< "xml "<<QString::number(poradiZastavky)<<"i "<<QString::number(i) << docasnaZastavka.stopPoint.StopName<<"cil"<<docasnaZastavka.destination.NameLcd<<"linka "<<docasnaZastavka.line.LineName<<" nocni "<<docasnaZastavka.line.isNight ;
        docasnaZastavka.stopPoint.fareZoneList=vyparsujPasma_2_3(aktZastavkaDOM);
        docasnySeznamZst.push_back(docasnaZastavka);
        globalStopList2_3.insert(poradiZastavky,docasnaZastavka);
    }
    if (docasnySeznamZst.size()==0)
    {
        qDebug()<<"zastavkyNebylyNacteny";
        return 0;
    }
    return 1;
}




QVector<StopPoint> XmlParser2_3::vyparsujNacestneZastavky2_3(QDomNode displayContent)
{
    qDebug()<<Q_FUNC_INFO;
    QDomNodeList nacesty = displayContent.toElement().elementsByTagName("ViaPoint");
    QVector<StopPoint> vectorNacesty;
    for (int i=0;i<nacesty.count();i++)
    {


        StopPoint nacesta;
        QDomElement aktNacesta=nacesty.at(i).toElement();
        nacesta.NameLcd=aktNacesta.firstChildElement("PlaceName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.NameInner=aktNacesta.firstChildElement("PlaceName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.NameSide=aktNacesta.firstChildElement("PlaceName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.StopName=nacesta.NameLcd;

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

        vectorNacesty.append(nacesta);
    }

    return vectorNacesty;
}


QVector<FareZone> XmlParser2_3::vyparsujPasma_2_3(QDomElement zastavka)
{
    qDebug()<<Q_FUNC_INFO;
    QVector<FareZone> vystupniVektorPasmo;

    QDomNodeList domPasma = zastavka.elementsByTagName("FareZone");

    for (int i=0;i<domPasma.count();i++)
    {
        FareZone aktPasmo;
        //  aktPasmo.system=domPasma.at(i).firstChildElement("Value").firstChildElement("FareZoneTypeName").firstChildElement("Value").firstChild().nodeValue();
        aktPasmo.name=domPasma.at(i).firstChildElement("Value").firstChild().nodeValue();
        vystupniVektorPasmo.append(aktPasmo);

    }

    return vystupniVektorPasmo;
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



int XmlParser2_3::VytvorSeznamZastavek2_3(QVector<StopPointDestination> &docasnySeznamZst,QVector<StopPointDestination> &docasnySeznamZstNavazny, int &docasnyIndexZastavky)
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
        tripDoSeznamuZastavek2_3(docasnySeznamZst,tripInformation);
        break ;
    case 2:
        qDebug()<<"existuje jeden navazny spoj";
        tripInformation=tripInformationList.at(0).toElement();
        tripDoSeznamuZastavek2_3(docasnySeznamZst,tripInformation);
        tripInformation2=tripInformationList.at(1).toElement();
        tripDoSeznamuZastavek2_3(docasnySeznamZstNavazny,tripInformation2);

        break;

    default:
        qDebug()<<"moc navaznych spoju";
        tripInformation=tripInformationList.at(0).toElement();
        tripDoSeznamuZastavek2_3(docasnySeznamZst,tripInformation);
        tripInformation2=tripInformationList.at(1).toElement();
        tripDoSeznamuZastavek2_3(docasnySeznamZstNavazny,tripInformation2);

        break;

    }


    return 1;
}
