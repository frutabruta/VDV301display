#ifndef XMLPARSER_H
#define XMLPARSER_H
#define MAX_ZAST2 10

#include <QMainWindow>
#include <QObject>
#include <QtXml>
#include "VDV301struktury/zastavka.h"
#include "VDV301struktury/zastavkacil.h"
#include "VDV301struktury/cestaudaje.h"
#include "VDV301struktury/prestup.h"
class XmlParser
{
public:
    XmlParser();
   // void nactiXML(QByteArray vstup);
    int linka=0;
    QString cil="";
   // SeznamZastavek docasnySeznamZastavek[] ;
    //SeznamZastavek* docasnySeznamZastavek = new SeznamZastavek[MAX_ZAST2];

    QDomDocument dokument;
    void Test();

    void nactiXML(QString vstup);

    int nactiVehicleGroup(CestaUdaje &stav, QDomDocument xmlko);
    int VytvorSeznamZastavek(QVector<ZastavkaCil> &docasnySeznamZst, QVector<ZastavkaCil> &docasnySeznamZstNavazny, int &docasnyIndexZastavky, int &docasnyPocetZastavek);
    int nactiFareZoneChange(QDomDocument xmlko, QVector<Pasmo> &pasmaZ, QVector<Pasmo> &pasmaNa);
    int nactiAdditionalTextMessage(QDomDocument xmlko, QString &type, QString &headline, QString &text);
    int vyparsujPasmaZeSeznamu(QDomElement vstup, QVector<Pasmo> &pasma);
    QVector<QString> naplnVektorPriznaku(QDomNode vstup, QString nazevElementu);
    int tripDoSeznamuZastavek(QVector<ZastavkaCil> &docasnySeznamZst, QDomElement vstup, int &docasnyPocetZastavek);
    int udajeNavaznehoSpoje(QVector<ZastavkaCil> &docasnySeznamZst, QString &linka, QString &cil);
    int existujeNavaznySpoj(QVector<ZastavkaCil> seznamZastavek);
    QVector<Prestup> nactiPrestupy(QDomElement vstup);
    Linka priznakyDoLinky(QVector<QString> vstup, Linka vstupniLinka);

    QDateTime vyparsujTimestamp(QDomDocument vstupniDokument);

    bool zmenaDat=false;
    static int minutDoOdjezdu(QDateTime aktCas, QDateTime casOdjezdu);
private:
    QVector<Zastavka> vyparsujNacestneZastavky(QDomElement zastavka);
    QVector<Pasmo> vyparsujPasma_2_2CZ1_0(QDomElement zastavka);
    QString stareXml="";
};




#endif // XMLPARSER_H
