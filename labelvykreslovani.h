#ifndef LABELVYKRESLOVANI_H
#define LABELVYKRESLOVANI_H

#include <QMainWindow>
#include <QObject>
#include <QDebug>
#include <QLabel>
#include <QFont>
#include <QFile>
#include <QtMath>

#include "VDV301DataStructures/farezone.h"
#include "svgvykreslovani.h"
#include "inlineformatparser.h"


class LabelVykreslovani
{

public:
    LabelVykreslovani();

    QString slozkaPiktogramu="";
    InlineFormatParser inlineFormatParser;


    void naplnZmenaLabel(QString vstup, QLabel *stitek);
    QString vyrobTextZmenyPasma(QVector<FareZone> zPasem, QVector<FareZone> naPasma);
    void naplnAnouncementLabel(QString vstup, QLabel *label);
    void obarviPozadiPristi(QString barvaPisma, QString barvaPozadi, QFrame *qframe);
    QString vykresliNacestneZastavkyText(QVector<StopPoint> nacestneZastavky, int velikostPiktogramu, QString verze);
    QString doplnPiktogramyBezZacatkuKonce(QString nazevZastavky, QVector<QString> seznamPiktogramu,int vyskaObrazku);
    QString zabalHtmlDoZnacek(QString vstup);

    int minimum(int cislo1, int cislo2);
    void vykresliNacestneForce(QVector<StopPointDestination> globalniSeznamZastavek, VehicleState stavSystemu, QLabel *label, QString verze);
    void zmensiCisloLinkyLabel(QLabel *label);
    void naplnNazevCileLabel(QString vstup, QLabel *label);
    QString nahradMetro(QString linka, QString submode, int vyska);
    void poleLabelNastavVelikost(QVector<QLabel*> labely, int bodovaVelikost, float pomerBodu);
    void labelNastavVelikost(QLabel *label, int bodovaVelikost, float pomerBodu);
    void poleLabelNastavSirku(QVector<QLabel*> seznamLabelu, int sirka);
    void poleLabelNastavVysku(QVector<QLabel*>  seznamLabelu, int vyska);
    QString textNaPiktogramOznameni(QString announcementType, int vyskaObrazku);
    void vymazPoleLabelu(QVector<QLabel*> vstup);
    QString nahradIconPiktogramem(QString vstup, int vyskaObrazku, QString slozka);


    QString replaceIconOuterDisplays(QString vstup);
signals:

};

#endif // LABELVYKRESLOVANI_H
