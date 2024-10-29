#ifndef DISPLAYLABELLCD2_3_H
#define DISPLAYLABELLCD2_3_H

#include "displaylabellcd.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301alldata.h"

class DisplayLabelLcd2_3 : public DisplayLabelLcd
{
public:
    DisplayLabelLcd2_3();
    using DisplayLabelLcd::displayLabelStopFareZone; // to make previous declarations visible in inherited class
    using DisplayLabelLcd::displayLabelViaPoints;
    using DisplayLabelLcd::displayLabelDestination;

    void displayLabelViaPoints(QVector<Vdv301ViaPoint> viaPoints);
    void displayLabelDestination(Vdv301Destination vdv301Destination);
    void displayLabelStopList(Vdv301Trip firstTrip, Vdv301Trip secondTrip, int currentStopIndex);
    void displayLabelStopFareZone(Vdv301AllData allData);
    void displayLabelStopPoint(Vdv301StopPoint selectedStopPointDestination, bool isFollowingTrip, QLabel *labelStopName, QLabel *labelFarezoneBottom, QLabel *labelFarezoneTop);

};

#endif // DISPLAYLABELLCD2_3_H
