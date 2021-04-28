#include "xmlparser.h"
#include "VDV301struktury/seznamzastavek.h"
#include "VDV301struktury/cestaudaje.h"
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

int XmlParser::VytvorSeznamZastavek(QVector<SeznamZastavek> &docasnySeznamZst, int &docasnyIndexZastavky, int &docasnyPocetZastavek)
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
        SeznamZastavek docasnaZastavka;
        QDomElement aktZastavkaDOM=root.elementsByTagName("StopPoint").at(i).toElement();
        int poradiZastavky=aktZastavkaDOM.elementsByTagName("StopIndex").at(0).firstChildElement().text().toInt();
        docasnaZastavka.StopName=aktZastavkaDOM.elementsByTagName("StopName").at(0).firstChildElement().text();
        docasnaZastavka.LineName=root.elementsByTagName("DisplayContent").at(0).toElement().elementsByTagName("LineInformation").at(0).toElement().elementsByTagName("LineName").at(0).firstChildElement().text();
        docasnaZastavka.StopIndex=i;
        //docasnaZastavka.nacestne=vyparsujNacestneZastavky(aktZastavkaDOM);
        //docasnaZastavka.nacestna=jeZastavkaNacestna(root.elementsByTagName("StopPoint").at(i).toElement());
        docasnaZastavka.DestinationName=root.elementsByTagName("DisplayContent").at(0).toElement().elementsByTagName("Destination").at(0).toElement().elementsByTagName("DestinationName").at(0).firstChildElement().text();
        qInfo()<< "xml "<<QString::number(poradiZastavky)<<"i "<<QString::number(i) << docasnaZastavka.StopName;
        docasnySeznamZst.push_back(docasnaZastavka);
    }
    if (docasnySeznamZst.size() ==0)
    {
        qDebug()<<"zastavkyNebylyNacteny";
        return 0;
    }

    return 1;
}
QVector<SeznamZastavek> XmlParser::vyparsujNacestneZastavky(QDomElement zastavka)
{
/*
    for()
    {

    }
*/
    QVector<SeznamZastavek> vystup;
    return vystup;
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


void XmlParser::Test()
{
    qDebug()<<" XmlParser::Test";
    qInfo()<<"xmlParserTestPoint2";
}

