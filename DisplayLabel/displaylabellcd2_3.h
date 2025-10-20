#ifndef DISPLAYLABELLCD2_3_H
#define DISPLAYLABELLCD2_3_H


#include "displaylabellcd.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301alldata.h"

class DisplayLabelLcd2_3 : public DisplayLabelLcd
{
public:
    DisplayLabelLcd2_3();
    using DisplayLabelLcd::displayLabelDestination;
    using DisplayLabelLcd::displayLabelDestinationFollowing;

    using DisplayLabelLcd::displayLabelLineName;
    using DisplayLabelLcd::displayLabelLineNameFollowing;

    void displayLabelViaPoints(QVector<Vdv301ViaPoint> viaPoints);
    void displayLabelDestination(Vdv301Destination vdv301Destination);
    void displayLabelStopList(Vdv301Trip firstTrip, Vdv301Trip secondTrip, int currentStopIndex);
    void displayLabelStopFareZone(Vdv301AllData allData);
    void displayLabelStopPoint(Vdv301StopPoint selectedStopPointDestination, bool isFollowingTrip, QLabel *labelStopName, QLabel *labelFarezoneBottom, QLabel *labelFarezoneTop);

    void displayLabelConnectionList(QVector<Vdv301Connection> connectionList);
    void displayLabelDestinationFollowing(Vdv301Destination vdv301Destination);
    QVector<Vdv301DisplayContent> filterVdv301DisplayContentByClass(QVector<Vdv301DisplayContent> displayContentList, DisplayContentClass displayContentType);
    void displayLabelLineName(Vdv301Line vdv301Line);
    void displayLabelLineNameFollowing(Vdv301Line vdv301Line);
};

#endif // DISPLAYLABELLCD2_3_H
