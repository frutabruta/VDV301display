#ifndef SVGVYKRESLOVANI_H
#define SVGVYKRESLOVANI_H
#include <QWidget>
#include <QDomDocument>
#include <VDV301struktury/seznamzastavek.h>
#include "VDV301struktury/cestaudaje.h"

class SvgVykreslovani
{
public:
    SvgVykreslovani();
    bool svgReplaceName(QString souborVstup, QString souborVystup, QString cil, QString zst0, QString zst1, QString zst2);
    bool individualniNahrazeni(QDomDocument &xmlDocument, QString hledaneId, QString novaHodnota);
    QVector<SeznamZastavek> vytvorNasledujiciZastavky(QVector<SeznamZastavek> vsechnyZastavky, int index, int limit);
    QDomDocument vymazZastavky(QDomDocument xmlDocument);
    QDomDocument vykresliZastavky(QDomDocument xmlDocument, QVector<SeznamZastavek> nasledujiciZastavky);
    int aktualizujVse(QVector<SeznamZastavek> zastavky, CestaUdaje stav);
    int qDomDocumentDoSouboru(QString cestaVystupnihoSouboru, QDomDocument vstupniDom);
private:
    QString pasmaDoStringu(QVector<Pasmo> seznamPasem);
    QDomDocument souborDoQDomDocument(QString cesta);
    QDomDocument vykresliCil(QDomDocument xmlDocument, QVector<SeznamZastavek> globalniZastavky, CestaUdaje stav);
    QDomDocument vykresliLinku(QDomDocument xmlDocument, QVector<SeznamZastavek> globalniZastavky, CestaUdaje stav);
    QDomDocument vykresliNacestneZastavky(QDomDocument xmlDocument, QVector<SeznamZastavek> nacestneZastavky);
    QVector<SeznamZastavek> vytvorNacestneZastavky(QVector<SeznamZastavek> vsechnyZastavky, int index);
};

#endif // SVGVYKRESLOVANI_H
