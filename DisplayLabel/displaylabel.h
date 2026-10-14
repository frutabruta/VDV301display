#ifndef DISPLAYLABEL_H
#define DISPLAYLABEL_H

#include <QMainWindow>
#include <QObject>
#include <QDebug>
#include <QLabel>
#include <QFont>
#include <QFile>
#include <QtMath>
#include <QLoggingCategory>

#include "VDV301subscriber/VDV301DataStructures/farezone.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301displaycontent.h"

#include "inlineformatparser.h"
#include "barvylinek.h"

class LedLabelDisplay
{

public:
    QPointer<QLabel> lineLabel=NULL;
    QPointer<QLabel> destination1Label=NULL;
    QPointer<QLabel> destination2Label=NULL;
    QPointer<QLabel> destinationLabel=NULL;

    int ticker=0;
    QVector<Vdv301DisplayContent> displayContentList;
private:
};

class DisplayLabel : public QObject
{
     Q_OBJECT
public:
    DisplayLabel();

    QString iconDirectory="";
    InlineFormatParser inlineFormatParser;

    BarvyLinek barvyLinek;

    void setAnouncementLabel(QString input, QLabel *label);

    void setNextStopBackground(QString textColor, QString backgroundColor, QFrame *qframe);

    // unused QString doplnPiktogramyBezZacatkuKonce(QString nazevZastavky, QVector<QString> seznamPiktogramu,int vyskaObrazku);
    QString wrapInHtml(QString input);


    // unused  QString metroToIcon(QString linka, QString submode, int vyska);

    void resizeLineLabel(QLabel *label);
    void resizeLabelPointCoeficient(QLabel *label, int pointSize, float scaleCoeficient);
    void resizeLabelListPointCoeficient(QVector<QLabel*> labely, int pointSize, float scaleCoeficient);

   void eraseLabelList(QVector<QLabel*> input);


   QString replaceIconOuterDisplays(QString input);

    // text creation tools
    QVector<Vdv301InternationalText> vdv301InternationalTextJoinByLanguage(QVector<Vdv301InternationalText> internationalTextList, QString separator);
    static Vdv301InternationalText vdv301InternationalTextJoinAll(QVector<Vdv301InternationalText> internationalTextList, QString separator);
    QString iconToHtmlImage(QString input, int iconSize, QString iconDirectory);
    QString fareZoneToQString(QVector<FareZone> fareZoneList);
    QString textToAnnouncementIcon(QString announcementType, int iconSize);
    QString viaPointListToFormattedString(QVector<Vdv301ViaPoint> viaPointList, int velikostPiktogramu);

    // helper functions
    int isInRange(int index, int limit);
    int minimum(int number1, int number2);

    // setters and getters
    void setVdv301version(const QString &newVdv301version);
    QString vdv301version() const;

signals:

private:

protected:
    QString mVdv301version="1.0";

    bool labelSetTextSafe(QLabel *label, QString text);
    bool labelSetVisibleSafe(QLabel *label, bool visibility);
    bool labelSetStylesheetSafe(QLabel *label, QString stylesheet);
};

#endif // DISPLAYLABEL_H
