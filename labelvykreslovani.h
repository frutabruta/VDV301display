#ifndef LABELVYKRESLOVANI_H
#define LABELVYKRESLOVANI_H

#include <QMainWindow>
#include <QObject>
#include <QDebug>
#include <QLabel>
#include "VDV301struktury/pasmo.h"
#include "svgvykreslovani.h"
#include <QFont>
class LabelVykreslovani
{

public:
    LabelVykreslovani();


    void naplnZmenaLabel(QString vstup, QLabel *stitek);
    QString vyrobTextZmenyPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma);
    void naplnAnouncementLabel(QString vstup, QLabel *label);
    void obarviPozadiPristi(QString barvaPisma, QString barvaPozadi, QFrame *qframe);
    QString vykresliNacestneZastavkyText(QVector<Zastavka> nacestneZastavky);
    QString doplnPiktogramyBezZacatkuKonce(QString nazevZastavky, QVector<QString> seznamPiktogramu);
    QString zabalHtmlDoZnacek(QString vstup);

    int minimum(int cislo1, int cislo2);
    void vykresliNacestneForce(QVector<ZastavkaCil> globalniSeznamZastavek, CestaUdaje stavSystemu, QLabel *label);
    void zmensiCisloLinkyLabel(QLabel *label);
    void naplnNazevCileLabel(QString vstup, QLabel *label);
    QString nahradMetro(QString linka, QString submode, int vyska);
    void poleLabelNastavVelikost(QVector<QLabel*> labely, int bodovaVelikost, float pomerBodu);
    void labelNastavVelikost(QLabel *label, int bodovaVelikost, float pomerBodu);
    void poleLabelNastavSirku(QVector<QLabel*> seznamLabelu, int sirka);
    void poleLabelNastavVysku(QVector<QLabel*>  seznamLabelu, int vyska);
signals:

};

#endif // LABELVYKRESLOVANI_H
