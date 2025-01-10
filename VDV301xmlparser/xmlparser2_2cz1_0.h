#ifndef XMLPARSER2_2CZ1_0_H
#define XMLPARSER2_2CZ1_0_H

#include "VDV301subscriber/VDV301DataStructures/stoppointdestination.h"

#include "xmlparser1_0.h"

class XmlParser2_2CZ1_0 : public XmlParser1_0
{
public:
    XmlParser2_2CZ1_0();
    int createStopList2_2CZ1_0(QVector<StopPointDestination> &tempStopPointDestinationList, QVector<StopPointDestination> &tempStopPointDestinationListFollowing, int &docasnyIndexZastavky);
    int parseFareZoneChange(QDomDocument xmlko, QVector<FareZone> &pasmaZ, QVector<FareZone> &pasmaNa);
    int parseAdditionalTextMessage2_2CZ1_0(QDomDocument xmlko, QString &type, QString &headline, QString &text);
private:
    QVector<FareZone> domToFareZoneList2_2CZ1_0(QDomElement domStopPoint);
    int parseStopPointDestinationList2_2CZ1_0(QVector<StopPointDestination> &docasnySeznamZst, QDomElement vstup);
    QVector<StopPoint> domToViaPoints2_2CZ1_0(QDomElement domStopPoint);

};

#endif // XMLPARSER2_2CZ1_0_H
