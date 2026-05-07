#ifndef DISPLAYLABELLCD2_3CZ1_0_H
#define DISPLAYLABELLCD2_3CZ1_0_H

#include "displaylabellcd2_3.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301alldata2_3cz1_0.h"

class DisplayLabelLcd2_3CZ1_0 : public DisplayLabelLcd2_3
{
public:
    DisplayLabelLcd2_3CZ1_0();
    using DisplayLabelLcd2_3::displayLabelStopFareZone;
    void displayLabelStopList(Vdv301Trip2_3CZ1_0 firstTrip, Vdv301Trip2_3CZ1_0 secondTrip, int currentStopIndex, QVector<DisplayLabelStopGroup> labelListStopGroup);
    void displayLabelStopFareZone(Vdv301AllData2_3CZ1_0 allData);
    void displayLabelStopPoint(Vdv301StopPoint2_3CZ1_0 selectedStopPointDestination, bool isFollowingTrip, QLabel *labelStopName, QLabel *labelFarezoneBottom, QLabel *labelFarezoneTop, bool invert=false);
    void displayLabelShowAnnoucement(QVector<Vdv301InternationalText> additionalTextMessageList, QVector<Vdv301InternationalText> additionalTextMessage1List, QVector<Vdv301InternationalText> additionalTextMessage2List, QVector<Vdv301InternationalText> additionalTextMessage3List, QVector<Vdv301InternationalText> additionalTextMessage4List);
    bool labelSetTextBgInline(QLabel *label, QString text, bool ignoreBackground = false );
    using DisplayLabelLcd2_3::filterVdv301DisplayContentByClass;
    QVector<Vdv301DisplayContent2_3CZ1_0> filterVdv301DisplayContentByClass(QVector<Vdv301DisplayContent2_3CZ1_0> displayContentList, DisplayContentClass displayContentType);
public slots:

};

#endif // DISPLAYLABELLCD2_3CZ1_0_H
