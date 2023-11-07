#ifndef XMLPARSER_H
#define XMLPARSER_H
//#define MAX_ZAST2 10

#include <QMainWindow>
#include <QObject>
#include <QtXml>
#include "VDV301DataStructures/stoppoint.h"
#include "VDV301DataStructures/stoppointdestination.h"
#include "VDV301DataStructures/vehiclestate.h"
#include "VDV301DataStructures/farezone.h"

class XmlParser
{
public:
    XmlParser();
    // void nactiXML(QByteArray vstup);
    int linka=0;
    QString cil="";

    QMap<int,StopPointDestination> globalStopList2_3;

    // SeznamZastavek docasnySeznamZastavek[] ;
    //SeznamZastavek* docasnySeznamZastavek = new SeznamZastavek[MAX_ZAST2];

    QDomDocument dokument;
    void Test();

    void nactiXML(QString vstup);

    int nactiVehicleGroup(VehicleState &stav, QDomDocument xmlko);
    int VytvorSeznamZastavek2_2CZ1_0(QVector<StopPointDestination> &docasnySeznamZst, QVector<StopPointDestination> &docasnySeznamZstNavazny, int &docasnyIndexZastavky);
    int nactiFareZoneChange(QDomDocument xmlko, QVector<FareZone> &pasmaZ, QVector<FareZone> &pasmaNa);
    int nactiAdditionalTextMessage(QDomDocument xmlko, QString &type, QString &headline, QString &text);
    int vyparsujPasmaZeSeznamu(QDomElement vstup, QVector<FareZone> &pasma);
    QVector<QString> naplnVektorPriznaku(QDomNode vstup, QString nazevElementu);
    int tripDoSeznamuZastavek2_2CZ1_0(QVector<StopPointDestination> &docasnySeznamZst, QDomElement vstup);
    int udajeNavaznehoSpoje(QVector<StopPointDestination> &docasnySeznamZst, QString &linka, QString &cil);
    int existujeNavaznySpoj(QVector<StopPointDestination> seznamZastavek);
    QVector<Connection> nactiPrestupy(QDomElement vstup);
    Line priznakyDoLinky(QVector<QString> vstup, Line vstupniLinka);

    QDateTime vyparsujTimestamp(QDomDocument vstupniDokument);

    bool zmenaDat=false;
    static int minutDoOdjezdu(QDateTime aktCas, QDateTime casOdjezdu);

    //rozdelano
    int VytvorSeznamZastavek1_0(QVector<StopPointDestination> &docasnySeznamZst, QVector<StopPointDestination> &docasnySeznamZstNavazny, int &docasnyIndexZastavky);
    int tripDoSeznamuZastavek1_0(QVector<StopPointDestination> &docasnySeznamZst, QDomElement vstup);
    QVector<StopPoint> vyparsujNacestneZastavky1_0(QDomElement zastavka);
    QVector<FareZone> vyparsujPasma_1_0(QDomElement zastavka);

    int tripDoSeznamuZastavek2_3(QVector<StopPointDestination> &docasnySeznamZst, QDomElement vstup);
    int VytvorSeznamZastavek2_3(QVector<StopPointDestination> &docasnySeznamZst, QVector<StopPointDestination> &docasnySeznamZstNavazny, int &docasnyIndexZastavky);


private:
    QVector<StopPoint> vyparsujNacestneZastavky2_2CZ1_0(QDomElement zastavka);
    QVector<StopPoint> vyparsujNacestneZastavky2_3(QDomNode displayContent);
    QVector<FareZone> vyparsujPasma_2_2CZ1_0(QDomElement zastavka);
    QVector<FareZone> vyparsujPasma_2_3(QDomElement zastavka);
    QString stareXml="";
};




#endif // XMLPARSER_H
