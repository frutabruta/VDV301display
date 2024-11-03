#ifndef DISPLAYLABELLCD2_3CZ1_0_H
#define DISPLAYLABELLCD2_3CZ1_0_H

#include "displaylabellcd2_3.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301alldata2_3cz1_0.h"

class DisplayLabelLcd2_3CZ1_0 : public DisplayLabelLcd2_3
{
public:
    DisplayLabelLcd2_3CZ1_0();
    using DisplayLabelLcd2_3::displayLabelStopFareZone;
    void displayLabelStopList(Vdv301Trip2_3CZ1_0 firstTrip, Vdv301Trip2_3CZ1_0 secondTrip, int currentStopIndex);
    void displayLabelStopFareZone(Vdv301AllData2_3CZ1_0 allData);
    void displayLabelStopPoint(Vdv301StopPoint2_3CZ1_0 selectedStopPointDestination, bool isFollowingTrip, QLabel *labelStopName, QLabel *labelFarezoneBottom, QLabel *labelFarezoneTop);
public slots:

};

#endif // DISPLAYLABELLCD2_3CZ1_0_H
