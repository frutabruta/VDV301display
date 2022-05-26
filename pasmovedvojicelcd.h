#ifndef PASMOVEDVOJICELCD_H
#define PASMOVEDVOJICELCD_H
#include <QObject>
#include "VDV301struktury/pasmo.h"


class PasmoveDvojiceLcd
{
public:
    PasmoveDvojiceLcd();
    Pasmo prvniPasmo;

    QVector<Pasmo> pasmaSystemu1;
    QVector<Pasmo> pasmaSystemu2;


    int roztridPasma(QVector<Pasmo> vstup);

};

#endif // PASMOVEDVOJICELCD_H
