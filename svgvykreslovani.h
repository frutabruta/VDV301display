#ifndef SVGVYKRESLOVANI_H
#define SVGVYKRESLOVANI_H
#include <QWidget>
#include <QDomDocument>
#include <VDV301struktury/zastavka.h>
#include <VDV301struktury/zastavkacil.h>
#include "VDV301struktury/cestaudaje.h"

class SvgVykreslovani
{
public:
    SvgVykreslovani();
    bool svgReplaceName(QString souborVstup, QString souborVystup, QString cil, QString zst0, QString zst1, QString zst2);
    bool individualniNahrazeni(QDomDocument &xmlDocument, QString hledaneId, QString novaHodnota);
    QVector<ZastavkaCil> vytvorNasledujiciZastavky(QVector<ZastavkaCil> vsechnyZastavky, int index, int limit);
    QDomDocument vymazZastavky(QDomDocument xmlDocument);
    QDomDocument vykresliZastavky(QDomDocument xmlDocument, QVector<ZastavkaCil> nasledujiciZastavky);
    int aktualizujVse(QVector<ZastavkaCil> zastavky, CestaUdaje stav);
    int qDomDocumentDoSouboru(QString cestaVystupnihoSouboru, QDomDocument vstupniDom);
   // QVector<ZastavkaCil> vytvorNacestneZastavky(QVector<ZastavkaCil> vsechnyZastavky, int index);
    static QString pasmaDoStringu(QVector<Pasmo> seznamPasem);


    QString vykresliNacestneZastavkyText(QVector<Zastavka> nacestneZastavky);
private:

    QDomDocument souborDoQDomDocument(QString cesta);
    QDomDocument vykresliCil(QDomDocument xmlDocument, QVector<ZastavkaCil> globalniZastavky, CestaUdaje stav);
    QDomDocument vykresliLinku(QDomDocument xmlDocument, QVector<ZastavkaCil> globalniZastavky, CestaUdaje stav);
    QDomDocument vykresliNacestneZastavky(QDomDocument xmlDocument, QVector<Zastavka> nacestneZastavky);

};

#endif // SVGVYKRESLOVANI_H
