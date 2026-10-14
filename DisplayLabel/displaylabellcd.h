#ifndef DISPLAYLABELLCD_H
#define DISPLAYLABELLCD_H

#include <QStackedWidget>

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
    QLabel *labelDestination=nullptr;
    QLabel *labelDestinationFollowing=nullptr;
    QLabel *labelLine=nullptr;
    QLabel *labelLineFollowing=nullptr;
    QLabel *labelViaPointsScrolling=nullptr;
    QLabel *labelClock=nullptr;


    //announcement labels
    //display labels
    QLabel *labelAnnouncementLeft=nullptr;
    QLabel *labelAnnouncementRight=nullptr;

    QLabel *labelFareZoneAnnouncementLeft=nullptr;
    QLabel *labelFareZoneAnnouncementRight=nullptr;


    QLabel *labelFareZoneChangeFrom=nullptr;
    QLabel *labelFareZoneChangeTo=nullptr;


    QLabel *labelLineChangeAnnouncementLeft=nullptr;
    QLabel *labelLineChangeAnnouncementRight=nullptr;


    QLabel *labelLineChangeAnnouncementFrom=nullptr;
    QLabel *labelLineChangeAnnouncementTo=nullptr;

    QWidget *pageAdditionalTextMessage=nullptr;
    QWidget *pageFareZoneChange=nullptr;
    QWidget *pageLineChange=nullptr;
    QWidget *pageRoute=nullptr;



    //vektory Labelu Hlavni
 //   QVector<QLabel*> labelListStopPointName;
 //   QVector<QLabel*> labelListFareZoneUpper;
  //  QVector<QLabel*> labelListFareZoneLower;

//    QVector<QLabel*> labelListConnectionLine;
  //  QVector<QLabel*> labelListConnectionDestination;
  //  QVector<QLabel*> labelListConnectionDeparture;
  //  QVector<QLabel*> labelListConnectionPlatform;

    QFrame *frameFollowingTrip=nullptr;

    QStackedWidget *stackedWidget_onService=nullptr;
    QStackedWidget *stackedWidget_middle=nullptr;




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
