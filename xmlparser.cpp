#include "xmlparser.h"
#include "VDV301struktury/zastavka.h"
#include "VDV301struktury/cestaudaje.h"
#include  "VDV301struktury/pasmo.h"
#include <QDebug>
#include <QMainWindow>




XmlParser::XmlParser()
{
    qDebug()<<"XmlParser::XmlParser";
}

void XmlParser::nactiXML(QString vstup)
{
    qDebug()<<"XmlParser::nactiXML";

    dokument.setContent(vstup);
    QString blabla = dokument.toString();


}

int XmlParser::VytvorSeznamZastavek(QVector<ZastavkaCil> &docasnySeznamZst, int &docasnyIndexZastavky, int &docasnyPocetZastavek)
{
    docasnySeznamZst.clear();
    qDebug()<<"XmlParser::VytvorSeznamZastavek";
    QDomElement root = dokument.firstChildElement();
    qDebug()<<root.tagName();
    if (root.tagName()!="CustomerInformationService.GetAllDataResponse")
    {
        qDebug()<<"vadné XML";
        return 0;
    }
    QDomNodeList nodes = root.elementsByTagName("StopPoint");

    docasnyPocetZastavek= nodes.count();
    docasnyIndexZastavky=root.elementsByTagName("CurrentStopIndex").at(0).firstChildElement().text().toInt();
    for (int i=0; i<nodes.count();i++)
    {

        ZastavkaCil docasnaZastavka;
        QDomElement aktZastavkaDOM=root.elementsByTagName("StopPoint").at(i).toElement();
        int poradiZastavky=aktZastavkaDOM.elementsByTagName("StopIndex").at(0).firstChildElement().text().toInt();
        docasnaZastavka.zastavka.StopName=aktZastavkaDOM.elementsByTagName("StopName").at(0).firstChildElement().text();
        docasnaZastavka.zastavka.NameFront=aktZastavkaDOM.elementsByTagName("StopFrontName").at(0).firstChildElement().text();
        docasnaZastavka.zastavka.NameSide=aktZastavkaDOM.elementsByTagName("StopSideName").at(0).firstChildElement().text();
        docasnaZastavka.zastavka.NameRear=aktZastavkaDOM.elementsByTagName("StopRearName").at(0).firstChildElement().text();
        docasnaZastavka.zastavka.NameInner=aktZastavkaDOM.elementsByTagName("StopInnerName").at(0).firstChildElement().text();
        docasnaZastavka.zastavka.NameLcd=aktZastavkaDOM.elementsByTagName("StopLcdName").at(0).firstChildElement().text();
        docasnaZastavka.linka.LineName=aktZastavkaDOM.elementsByTagName("DisplayContent").at(0).toElement().elementsByTagName("LineInformation").at(0).toElement().elementsByTagName("LineName").at(0).firstChildElement().text();
        docasnaZastavka.zastavka.StopIndex=i;
        docasnaZastavka.nacestneZastavky=vyparsujNacestneZastavky(aktZastavkaDOM);

        QDomElement displayContent=aktZastavkaDOM.elementsByTagName("DisplayContent").at(0).toElement();
        docasnaZastavka.cil.StopName=displayContent.elementsByTagName("Destination").at(0).toElement().elementsByTagName("DestinationName").at(0).firstChildElement().text();
        docasnaZastavka.cil.NameFront=displayContent.elementsByTagName("Destination").at(0).toElement().elementsByTagName("DestinationFrontName").at(0).firstChildElement().text();


        QDomNodeList nazvyCelniPanel=displayContent.elementsByTagName("Destination").at(0).toElement().elementsByTagName("DestinationFrontName");
        if (nazvyCelniPanel.length()>0)
        {
            docasnaZastavka.cil.NameFront=nazvyCelniPanel.at(0).firstChildElement().text();
        }
        if (nazvyCelniPanel.length()>1)
        {
         docasnaZastavka.cil.NameFront2=nazvyCelniPanel.at(1).firstChildElement().text();
        }


        docasnaZastavka.cil.NameSide=displayContent.elementsByTagName("Destination").at(0).toElement().elementsByTagName("DestinationSideName").at(0).firstChildElement().text();
        docasnaZastavka.cil.NameRear=displayContent.elementsByTagName("Destination").at(0).toElement().elementsByTagName("DestinationRearName").at(0).firstChildElement().text();
        docasnaZastavka.cil.NameInner=displayContent.elementsByTagName("Destination").at(0).toElement().elementsByTagName("DestinationInnerName").at(0).firstChildElement().text();
        docasnaZastavka.cil.NameLcd=displayContent.elementsByTagName("Destination").at(0).toElement().elementsByTagName("DestinationLcdName").at(0).firstChildElement().text();




        qInfo()<< "xml "<<QString::number(poradiZastavky)<<"i "<<QString::number(i) << docasnaZastavka.zastavka.StopName<<"cil"<<docasnaZastavka.cil.NameLcd<<"linka "<<docasnaZastavka.linka.LineName ;
        docasnaZastavka.zastavka.seznamPasem=vyparsujPasma_2_2CZ1_0(aktZastavkaDOM);
        docasnySeznamZst.push_back(docasnaZastavka);
    }
    if (docasnySeznamZst.size() ==0)
    {
        qDebug()<<"zastavkyNebylyNacteny";
        return 0;
    }

    return 1;
}
QVector<Zastavka> XmlParser::vyparsujNacestneZastavky(QDomElement zastavka)
{
    qDebug()<<"XmlParser::vyparsujNacestneZastavky";
    QDomNodeList nacesty = zastavka.elementsByTagName("ViaPoint");
    QVector<Zastavka> vectorNacesty;
    for (int i=0;i<nacesty.count();i++)
    {
        Zastavka nacesta;
        QDomNodeList priznaky=nacesty.at(i).toElement().elementsByTagName("ViaPointProperty");
        QDomElement aktNacesta=nacesty.at(i).toElement();
        nacesta.NameLcd=aktNacesta.firstChildElement("PlaceLcdName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.NameInner=aktNacesta.firstChildElement("PlaceInnerName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.NameSide=aktNacesta.firstChildElement("PlaceSideName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.StopName=nacesta.NameLcd;
        for (int j=0;j<priznaky.count();j++)
        {
            QString hodnotaPriznaku=priznaky.at(j).firstChild().nodeValue();
            qDebug()<<"priznak "<<hodnotaPriznaku;


            if(hodnotaPriznaku=="RequestStop")
            {
                nacesta.naZnameni=true;
            }
        }

        vectorNacesty.append(nacesta);
    }

    return vectorNacesty;
}

QVector<Pasmo> XmlParser::vyparsujPasma_2_2CZ1_0(QDomElement zastavka)
{
    qDebug()<<"XmlParser::vyparsujPasma";
    QVector<Pasmo> vystupniVektorPasmo;

    QDomNodeList domPasma = zastavka.elementsByTagName("FareZone");

    for (int i=0;i<domPasma.count();i++)
    {
        Pasmo aktPasmo;
        aktPasmo.system=domPasma.at(i).firstChildElement("FareZoneType").firstChildElement("FareZoneTypeName").firstChildElement("Value").firstChild().nodeValue();
        aktPasmo.nazev=domPasma.at(i).firstChildElement("FareZoneLongName").firstChildElement("Value").firstChild().nodeValue();
        vystupniVektorPasmo.append(aktPasmo);

    }

    return vystupniVektorPasmo;
}
int XmlParser::nactiVehicleGroup(CestaUdaje &stav,QDomDocument xmlko )
{
    qDebug()<<"XmlParser::nactiVehicleGroup";
    QDomElement root = xmlko.firstChildElement();
    qDebug()<<"root name "<<root.nodeName();
    QDomElement allData=root.firstChildElement("AllData");
    qDebug()<<"alldata name "<<allData.nodeName();
    stav.indexAktZastavky=allData.firstChildElement("CurrentStopIndex").firstChildElement().firstChild().nodeValue().toInt();
    stav.VehicleStopRequested=allData.firstChildElement("VehicleStopRequested").firstChildElement("Value").firstChild().nodeValue().toInt();
    stav.locationState=allData.firstChildElement("TripInformation").firstChildElement("LocationState").firstChild().nodeValue();
    qDebug()<<"stopIndex "<<QString::number(stav.indexAktZastavky)<<"stopRequested "<<stav.VehicleStopRequested<<" locState "<<stav.locationState;

    return 1;
}



int XmlParser::nactiAdditionalTextMessage(QDomDocument xmlko, QString &vystup )
{
    qDebug()<<"XmlParser::nactiAdditionalTextMessage";

    vystup="";

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
    QDomElement additionalTextMessageText=additionalTextMessage.firstChildElement("AdditionalTextMessageText");
    QDomElement value=additionalTextMessageText.firstChildElement("Value");
    vystup=value.firstChild().nodeValue();
    qDebug()<<"additional text je "<<vystup;

   /*
    QDomElement root = xmlko.firstChildElement();
    qDebug()<<"root name "<<root.nodeName();
    QDomElement allData=root.firstChildElement("AllData");
    qDebug()<<"alldata name "<<allData.nodeName();
    stav.indexAktZastavky=allData.firstChildElement("CurrentStopIndex").firstChildElement().firstChild().nodeValue().toInt();
    stav.VehicleStopRequested=allData.firstChildElement("VehicleStopRequested").firstChildElement("Value").firstChild().nodeValue().toInt();
    stav.locationState=allData.firstChildElement("TripInformation").firstChildElement("LocationState").firstChild().nodeValue();
    qDebug()<<"stopIndex "<<QString::number(stav.indexAktZastavky)<<"stopRequested "<<stav.VehicleStopRequested<<" locState "<<stav.locationState;
*/

    return 1;
}

int XmlParser::nactiFareZoneChange(QDomDocument xmlko, QVector<Pasmo> &pasmaZ, QVector<Pasmo> &pasmaNa )
{
        //rozepsano
    qDebug()<<"XmlParser::nactiFareZoneChange";


    QDomElement root = xmlko.firstChildElement();
    qDebug()<<"root name "<<root.nodeName();
    QDomElement allData=root.firstChildElement("AllData");
    qDebug()<<"alldata name "<<allData.nodeName();
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




    /*
    stav.indexAktZastavky=allData.firstChildElement("CurrentStopIndex").firstChildElement().firstChild().nodeValue().toInt();
    stav.VehicleStopRequested=allData.firstChildElement("VehicleStopRequested").firstChildElement("Value").firstChild().nodeValue().toInt();
    stav.locationState=allData.firstChildElement("TripInformation").firstChildElement("LocationState").firstChild().nodeValue();
    qDebug()<<"stopIndex "<<QString::number(stav.indexAktZastavky)<<"stopRequested "<<stav.VehicleStopRequested<<" locState "<<stav.locationState;
*/
    return 1;
}



void XmlParser::Test()
{
    qDebug()<<" XmlParser::Test";
    qInfo()<<"xmlParserTestPoint2";
}

