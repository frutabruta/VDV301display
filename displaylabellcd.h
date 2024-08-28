#ifndef DISPLAYLABELLCD_H
#define DISPLAYLABELLCD_H

#include "displaylabel.h"

class DisplayLabelLcd : public DisplayLabel
{
public:
    DisplayLabelLcd();

    //variables
    QString oldViapointString="";


    QTimer timerScrollingText;
    QTimer timerLabelPageSwitch;

    int scrollingTextOffset=0;


    //LCD fonts
    QFont fontLabelFareZoneLarge;
    QFont fontLabelFareZoneSmall;

    //display labels
    QLabel *labelDestination=NULL;
    QLabel *labelLine=NULL;
    QLabel *labelViaPointsScrolling=NULL;
    QLabel *labelClock=NULL;



    //vektory Labelu Hlavni
    QVector<QLabel*> labelListStopPointName;
    QVector<QLabel*> labelListFareZoneUpper;
    QVector<QLabel*> labelListFareZoneLower;

    QVector<QLabel*> labelListConnectionLine;
    QVector<QLabel*> labelListConnectionDestination;
    QVector<QLabel*> labelListConnectionDeparture;
    QVector<QLabel*> labelListConnectionPlatform;

    QFrame *frameFollowingTrip=NULL;

     QVector<QWidget*> pageCycleList;

    void initializeFonts();
    void displayLabelStopPoint(StopPointDestination selectedStopPointDestination, bool isFollowingTrip, QLabel *labelStopName, QLabel *labelFarezoneBottom, QLabel *labelFarezoneTop);
    void displayLabelDestination(QString nazev);
    void displayLabelConnectionList(QVector<Connection> connectionList);
    void displayLabelDrawLineNumber(QString subMode, Line line, QLabel *label, int iconSize, bool isConnection);
    void displayLabelDrawLineNumber2_4(QString subMode, Line line, QLabel *label, int velikostPiktogramu, bool prestup);
    void displayLabelEraseInformation();
    void displayLabelLineName(StopPointDestination selectedStopPointDestinationstavka, QString subMode);
    void displayLabelStopFareZone(QVector<StopPointDestination> thisStopPointDestinationList, QVector<StopPointDestination> nextStopPointDestinationList, VehicleState vehicleState);
    void displayLabelStopList(QVector<StopPointDestination> thisStopPointDestinationList, QVector<StopPointDestination> nextStopPointDestinationList, int index);
    void displayLabelViaPoints(QVector<StopPointDestination> currentDestinationPointList, VehicleState vehicleState);


    //constants
    const int sizeFontDestination=100;
    const int sizeFontViaPoints=72;
    const int sizeFontFollowing=100;

    const int sizeFontTransferLine=48;
    const int sizeFontTransferDestination=36;

    const int sizeIconConnection=65;
    int sizeIconConnectionDynamic=20;
    const int sizeConnectionFrameWidth=95;
    const int sizeConnectionFrameHeight=65;

    const int intervalScrollingText=20;

    const int intervalSwitchPages=10000;


    float ratioPixelPoint=1080.0/1050.0;




    void slotMoveScrollingText(QVector<StopPointDestination> currentDestinationPointList, VehicleState vehicleState);
    void lcdResizeLabels(int frameHeight);
    void slotDisplayLcdLabelCyclePages();
};

#endif // DISPLAYLABELLCD_H
