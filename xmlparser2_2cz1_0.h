#ifndef XMLPARSER2_2CZ1_0_H
#define XMLPARSER2_2CZ1_0_H


#include "xmlparser.h"

class XmlParser2_2CZ1_0 : public XmlParser
{
public:
    XmlParser2_2CZ1_0();
    QVector<FareZone> vyparsujPasma_2_2CZ1_0(QDomElement zastavka);
    int tripDoSeznamuZastavek2_2CZ1_0(QVector<StopPointDestination> &docasnySeznamZst, QDomElement vstup);
    int VytvorSeznamZastavek2_2CZ1_0(QVector<StopPointDestination> &docasnySeznamZst, QVector<StopPointDestination> &docasnySeznamZstNavazny, int &docasnyIndexZastavky);
    QVector<StopPoint> vyparsujNacestneZastavky2_2CZ1_0(QDomElement zastavka);
    int nactiFareZoneChange(QDomDocument xmlko, QVector<FareZone> &pasmaZ, QVector<FareZone> &pasmaNa);
    int nactiAdditionalTextMessage2_2CZ1_0(QDomDocument xmlko, QString &type, QString &headline, QString &text);
};

#endif // XMLPARSER2_2CZ1_0_H
