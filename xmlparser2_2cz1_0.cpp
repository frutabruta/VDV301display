#include "xmlparser2_2cz1_0.h"


XmlParser2_2CZ1_0::XmlParser2_2CZ1_0()
{}



int XmlParser2_2CZ1_0::VytvorSeznamZastavek2_2CZ1_0(QVector<StopPointDestination> &docasnySeznamZst,QVector<StopPointDestination> &docasnySeznamZstNavazny, int &docasnyIndexZastavky)
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
        tripDoSeznamuZastavek2_2CZ1_0(docasnySeznamZst,tripInformation);
        break ;
    case 2:
        qDebug()<<"existuje jeden navazny spoj";
        tripInformation=tripInformationList.at(0).toElement();
        tripDoSeznamuZastavek2_2CZ1_0(docasnySeznamZst,tripInformation);
        tripInformation2=tripInformationList.at(1).toElement();
        tripDoSeznamuZastavek2_2CZ1_0(docasnySeznamZstNavazny,tripInformation2);

        break;

    default:
        qDebug()<<"moc navaznych spoju";
        tripInformation=tripInformationList.at(0).toElement();
        tripDoSeznamuZastavek2_2CZ1_0(docasnySeznamZst,tripInformation);
        tripInformation2=tripInformationList.at(1).toElement();
        tripDoSeznamuZastavek2_2CZ1_0(docasnySeznamZstNavazny,tripInformation2);

        break;

    }



    return 1;
}


int XmlParser2_2CZ1_0::tripDoSeznamuZastavek2_2CZ1_0(QVector<StopPointDestination> &docasnySeznamZst, QDomElement vstup)
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
        docasnaZastavka.line=priznakyDoLinky(priznakyStringy,docasnaZastavka.line);

        docasnaZastavka.stopPoint.StopIndex=i;
        docasnaZastavka.viaPoints=vyparsujNacestneZastavky2_2CZ1_0(aktZastavkaDOM);
        docasnaZastavka.stopPoint.connectionList=nactiPrestupy(aktZastavkaDOM);

        QDomElement displayContent=aktZastavkaDOM.firstChildElement("DisplayContent");
        QDomElement dDestination=displayContent.firstChildElement("Destination");
        docasnaZastavka.destination.StopName=dDestination.firstChildElement("DestinationName").text();
        docasnaZastavka.destination.NameFront=dDestination.firstChildElement("DestinationFrontName").firstChildElement().text();
        docasnaZastavka.destination.iconList=naplnVektorPriznaku(displayContent.elementsByTagName("Destination").at(0),"Destination");

        QDomNodeList nazvyCelniPanel=dDestination.elementsByTagName("DestinationFrontName");
        if (nazvyCelniPanel.length()>0)
        {
            docasnaZastavka.destination.NameFront=nazvyCelniPanel.at(0).firstChildElement().text();
        }
        if (nazvyCelniPanel.length()>1)
        {
            docasnaZastavka.destination.NameFront2=nazvyCelniPanel.at(1).firstChildElement().text();
        }
        docasnaZastavka.stopPoint.iconList= naplnVektorPriznaku(aktZastavkaDOM,"Stop");


        docasnaZastavka.destination.NameSide=dDestination.firstChildElement("DestinationSideName").firstChildElement().text();
        docasnaZastavka.destination.NameRear=dDestination.firstChildElement("DestinationRearName").firstChildElement().text();
        docasnaZastavka.destination.NameInner=dDestination.firstChildElement("DestinationInnerName").firstChildElement().text();
        docasnaZastavka.destination.NameLcd=dDestination.firstChildElement("DestinationLcdName").firstChildElement().text();

        //    qInfo()<< "xml "<<QString::number(poradiZastavky)<<"i "<<QString::number(i) << docasnaZastavka.stopPoint.StopName<<"cil"<<docasnaZastavka.destination.NameLcd<<"linka "<<docasnaZastavka.line.LineName<<" nocni "<<docasnaZastavka.line.isNight ;
        docasnaZastavka.stopPoint.fareZoneList=vyparsujPasma_2_2CZ1_0(aktZastavkaDOM);
        docasnySeznamZst.push_back(docasnaZastavka);
    }
    if (docasnySeznamZst.size() ==0)
    {
        qDebug()<<"zastavkyNebylyNacteny";
        return 0;
    }
    return 1;
}




QVector<FareZone> XmlParser2_2CZ1_0::vyparsujPasma_2_2CZ1_0(QDomElement zastavka)
{
    qDebug()<<Q_FUNC_INFO;
    QVector<FareZone> vystupniVektorPasmo;

    QDomNodeList domPasma = zastavka.elementsByTagName("FareZone");

    for (int i=0;i<domPasma.count();i++)
    {
        FareZone aktPasmo;
        aktPasmo.system=domPasma.at(i).firstChildElement("FareZoneType").firstChildElement("FareZoneTypeName").firstChildElement("Value").firstChild().nodeValue();
        aktPasmo.name=domPasma.at(i).firstChildElement("FareZoneLongName").firstChildElement("Value").firstChild().nodeValue();
        vystupniVektorPasmo.append(aktPasmo);

    }

    return vystupniVektorPasmo;
}



QVector<StopPoint> XmlParser2_2CZ1_0::vyparsujNacestneZastavky2_2CZ1_0(QDomElement zastavka)
{
    qDebug()<<Q_FUNC_INFO;
    QDomNodeList nacesty = zastavka.elementsByTagName("ViaPoint");
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


        nacesta.iconList= naplnVektorPriznaku(aktNacesta,"ViaPoint");
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



int XmlParser2_2CZ1_0::nactiFareZoneChange(QDomDocument xmlko, QVector<FareZone> &pasmaZ, QVector<FareZone> &pasmaNa )
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
    pasmaZ=vyparsujPasma_2_2CZ1_0(fromFareZones);

    QDomElement toFareZones=fareZoneChange.firstChildElement("ToFareZones");
    pasmaNa=vyparsujPasma_2_2CZ1_0(toFareZones);

    qDebug()<<"pocet pasem Z "<<pasmaZ.count()<<" pocet pasem DO "<<pasmaNa.count();
    return 1;
}


int XmlParser2_2CZ1_0::nactiAdditionalTextMessage2_2CZ1_0(QDomDocument xmlko, QString &type ,QString &headline,QString &text )
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
