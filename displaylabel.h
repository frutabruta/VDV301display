#ifndef DISPLAYLABEL_H
#define DISPLAYLABEL_H

#include <QMainWindow>
#include <QObject>
#include <QDebug>
#include <QLabel>
#include <QFont>
#include <QFile>
#include <QtMath>

#include "VDV301subscriber/VDV301DataStructures/farezone.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301displaycontent.h"
#include "svgvykreslovani.h"
#include "inlineformatparser.h"
#include "barvylinek.h"

class LedLabelDisplay
{

public:
    QLabel* lineLabel=NULL;
    QLabel* destination1Label=NULL;
    QLabel* destination2Label=NULL;
    QLabel* destinationLabel=NULL;

    int ticker=0;
    QVector<Vdv301DisplayContent> displayContentList;
private:
};

class DisplayLabel : public QObject
{
     Q_OBJECT
public:
    DisplayLabel();

    QString slozkaPiktogramu="";
    InlineFormatParser inlineFormatParser;



    BarvyLinek barvyLinek;


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

    QString nahradMetro(QString linka, QString submode, int vyska);
    void poleLabelNastavVelikost(QVector<QLabel*> labely, int bodovaVelikost, float pomerBodu);
    void labelNastavVelikost(QLabel *label, int bodovaVelikost, float pomerBodu);
    void poleLabelNastavSirku(QVector<QLabel*> seznamLabelu, int sirka);
    void poleLabelNastavVysku(QVector<QLabel*>  seznamLabelu, int vyska);
    QString textNaPiktogramOznameni(QString announcementType, int vyskaObrazku);
    void vymazPoleLabelu(QVector<QLabel*> vstup);
    QString nahradIconPiktogramem(QString vstup, int vyskaObrazku, QString slozka);


    QString replaceIconOuterDisplays(QString vstup);
    void ledWriteToDisplay(LedLabelDisplay display, QString linka, QString horniRadek, QString dolniRadek);
    void ledDisplaySetDisplayContent(LedLabelDisplay &selectedDisplay);
    int isInRange(int index, int limit);
    QString fareZoneListToQString(QVector<FareZone> seznamPasem);
    void setVdv301version(const QString &newVdv301version);

    QString vdv301version() const;

signals:

private:

protected:
    QString mVdv301version="1.0";

    bool labelSetTextSafe(QLabel *label, QString text);
    bool labelSetVisibleSafe(QLabel *label, bool visibility);
};

#endif // DISPLAYLABEL_H
