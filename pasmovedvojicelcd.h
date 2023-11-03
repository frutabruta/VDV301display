#ifndef PASMOVEDVOJICELCD_H
#define PASMOVEDVOJICELCD_H
#include <QObject>


#include "VDV301DataStructures/farezone.h"


class PasmoveDvojiceLcd
{
public:
    PasmoveDvojiceLcd();
    FareZone prvniPasmo;

    QVector<FareZone> pasmaSystemu1;
    QVector<FareZone> pasmaSystemu2;


    int roztridPasma(QVector<FareZone> vstup);

    int roztridPasma2_3(QVector<FareZone> vstup);
};

#endif // PASMOVEDVOJICELCD_H
