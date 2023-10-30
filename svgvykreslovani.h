#ifndef SVGVYKRESLOVANI_H
#define SVGVYKRESLOVANI_H
#include <QWidget>
#include <QDomDocument>

#include "VDV301DataStructures/stoppoint.h"
#include "VDV301DataStructures/stoppointdestination.h"
#include "VDV301DataStructures/vehiclestate.h"

class SvgVykreslovani
{
public:
    SvgVykreslovani(QString cesta);
    QString interniCestaSlozkaSvg="";
    bool svgReplaceName(QString souborVstup, QString souborVystup, QString cil, QString zst0, QString zst1, QString zst2);
    bool individualniNahrazeni(QDomDocument &xmlDocument, QString hledaneId, QString novaHodnota);
    QVector<StopPointDestination> vytvorNasledujiciZastavky(QVector<StopPointDestination> vsechnyZastavky, int index, int limit);
    QDomDocument vymazZastavky(QDomDocument xmlDocument);
    QDomDocument vykresliZastavky(QDomDocument xmlDocument, QVector<StopPointDestination> nasledujiciZastavky);
    int aktualizujVse(QVector<StopPointDestination> zastavky, VehicleState stav);
    int qDomDocumentDoSouboru(QString cestaVystupnihoSouboru, QDomDocument vstupniDom);
   // QVector<StopPointDestination> vytvorNacestneZastavky(QVector<StopPointDestination> vsechnyZastavky, int index);
    static QString pasmaDoStringu(QVector<FareZone> seznamPasem);


    QString vykresliNacestneZastavkyText(QVector<StopPoint> nacestneZastavky);
    void zobrazZmenuPasma(QVector<FareZone> zPasem, QVector<FareZone> naPasma);
    void obarviPozadiPristi(QString barvaPisma, QString barvaPozadi);
    void vymazObrazovku();
    void zobrazAnnoucement(QString title, QString type, QString textCz, QString textEn);
private:

    QDomDocument souborDoQDomDocument(QString cesta);
    QDomDocument vykresliCil(QDomDocument xmlDocument, QVector<StopPointDestination> globalniZastavky, VehicleState stav);
    QDomDocument vykresliLinku(QDomDocument xmlDocument, QVector<StopPointDestination> globalniZastavky, VehicleState stav);
    QDomDocument vykresliNacestneZastavky(QDomDocument xmlDocument, QVector<StopPoint> nacestneZastavky);

};

#endif // SVGVYKRESLOVANI_H
