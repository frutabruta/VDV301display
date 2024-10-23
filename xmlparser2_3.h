#ifndef XMLPARSER2_3_H
#define XMLPARSER2_3_H

#include "xmlparser.h"

class XmlParser2_3 : public XmlParser
{
public:
    XmlParser2_3();

    QMap<int,StopPointDestination> globalStopList2_3;

    int tripDoSeznamuZastavek2_3(QVector<StopPointDestination> &docasnySeznamZst, QDomElement vstup);
    QVector<StopPoint> vyparsujNacestneZastavky2_3(QDomNode displayContent);
    QVector<FareZone> vyparsujPasma_2_3(QDomElement zastavka);
    Vdv301AllData parseAllData2_3(QDomDocument input, QVector<Vdv301StopPoint> &testStopList);
    int VytvorSeznamZastavek2_3(QVector<StopPointDestination> &docasnySeznamZst, QVector<StopPointDestination> &docasnySeznamZstNavazny, int &docasnyIndexZastavky);
};

#endif // XMLPARSER2_3_H
