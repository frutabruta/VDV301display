#ifndef SVGVYKRESLOVANI_H
#define SVGVYKRESLOVANI_H
#include <QWidget>
#include <QDomDocument>

class SvgVykreslovani
{
public:
    SvgVykreslovani();
    bool svgReplaceName(QString souborVstup, QString souborVystup, QString cil, QString zst0, QString zst1, QString zst2);
    bool individualniNahrazeni(QDomDocument &xmlDocument, QString hledaneId, QString novaHodnota);
};

#endif // SVGVYKRESLOVANI_H
