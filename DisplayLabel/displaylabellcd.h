#ifndef DISPLAYLABELLCD_H
#define DISPLAYLABELLCD_H

#include <QStackedWidget>
#include <QLoggingCategory>

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
    QLabel *labelDestinationFollowing=NULL;
    QLabel *labelLine=NULL;
    QLabel *labelLineFollowing=NULL;
    QLabel *labelViaPointsScrolling=NULL;
    QLabel *labelClock=NULL;


    //announcement labels
    //display labels
    QLabel *labelAnnouncementLeft=NULL;
    QLabel *labelAnnouncementRight=NULL;

    QLabel *labelFareZoneAnnouncementLeft=NULL;
    QLabel *labelFareZoneAnnouncementRight=NULL;


    QLabel *labelFareZoneChangeFrom=NULL;
    QLabel *labelFareZoneChangeTo=NULL;


    QLabel *labelLineChangeAnnouncementLeft=NULL;
    QLabel *labelLineChangeAnnouncementRight=NULL;


    QLabel *labelLineChangeAnnouncementFrom=NULL;
    QLabel *labelLineChangeAnnouncementTo=NULL;

    QWidget *pageAdditionalTextMessage=NULL;
    QWidget *pageFareZoneChange=NULL;
    QWidget *pageLineChange=NULL;
    QWidget *pageRoute=NULL;



    //vektory Labelu Hlavni
    QVector<QLabel*> labelListStopPointName;
    QVector<QLabel*> labelListFareZoneUpper;
    QVector<QLabel*> labelListFareZoneLower;

    QVector<QLabel*> labelListConnectionLine;
    QVector<QLabel*> labelListConnectionDestination;
    QVector<QLabel*> labelListConnectionDeparture;
    QVector<QLabel*> labelListConnectionPlatform;

    QFrame *frameFollowingTrip=NULL;

    QStackedWidget *stackedWidget_onService=NULL;
    QStackedWidget *stackedWidget_middle=NULL;




     QVector<QWidget*> pageCycleList;

    void initializeFonts();
    void displayLabelDestination(QString nazev);
    void displayLabelDestinationFollowing(QString nazev);

    void displayLabelDrawLineNumber2_4(QString lineName, QLabel *label, int velikostPiktogramu, bool prestup);
    void displayLabelEraseInformation();
    void displayLabelLineName(QString lineName);


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

    void lcdResizeLabels(int frameHeight);
    void slotDisplayLcdLabelCyclePages();


    void displayLabelLineNameFollowing(QString lineName);
};

#endif // DISPLAYLABELLCD_H
