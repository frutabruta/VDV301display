#ifndef DISPLAYLABELLED_H
#define DISPLAYLABELLED_H

#include "displaylabel.h"

#include <QTimer>
#include "VDV301subscriber/VDV301DataStructures/vdv301stoppoint.h"

class DisplayLabelLed : public DisplayLabel
{
    Q_OBJECT
public:
    DisplayLabelLed();

    QTimer timerLedSideCycleViaPoints ;


    LedLabelDisplay frontDisplay;
    LedLabelDisplay sideDisplay;
    LedLabelDisplay rearDisplay;
    LedLabelDisplay innerDisplay;

    QVector<QString> textyBocniPanelkIteraci;
    QVector<QString> textyVnitrniPanelkIteraci;

     int currentPageIndexLed=0;

    //LED fonts
    QFont fontLed1;
    QFont fontLed3;
    QFont fontLed3v;
    QFont fontLed5;
    QFont fontLed8;
    QFont fontLed10;

    float ratioPixelLed=4.105;


    QVector<Vdv301DisplayContent> ledUpdateCurrentStopToDisplayContentList2_3(QVector<Vdv301StopPoint> &zastavky, VehicleState stav);
    void ledUpdateDisplayedInformationFromDisplayContentList2_3(QVector<Vdv301DisplayContent> displayContentListAll);

    QVector<QString> ledStopPointToViapointListSide(StopPointDestination selectedStopPointDestination);
    QVector<QString> ledStopPointToViapointListInner(StopPointDestination selectedStopPointDestination);

    void ledIterateSide(QVector<QString> texty, int &iteracniIndex);
    void ledIterateInner(QVector<QString> texty, int &iteracniIndex);
    void ledAlignTextOverflow(QLabel *label);
    void ledSetTextSide(QString line, QString destinationTop, QString destinationBottom);
    void ledSetLine(QLabel *label, QString text);
    void ledSetTextRear(QString line);
    void ledSetTextInner(QString line, QString destinationTop, QString destinationBottom);
    void ledInitializeFormat();
    void ledUpdateDisplaySizes();
    void ledSetWindowSizeDot(QLabel *label, int lengthDotCount, int heightDotCount, float coeficient);
    void initializeFonts();
    void ledClearDisplays();
    void ledSetTextFront(QString line, QString destinationTop, QString destinationBottom);
    void ledUpdateDisplayedInformation(QVector<StopPointDestination> stopPointList, VehicleState vehicleState);
public slots:
    void slotTickLedPanels2_3();
    void slotLedIterateAllDisplays();
signals:
    void signalFrontDisplayWidthChanged(int value);
};

#endif // DISPLAYLABELLED_H
