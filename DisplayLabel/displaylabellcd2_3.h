#ifndef DISPLAYLABELLCD2_3_H
#define DISPLAYLABELLCD2_3_H


#include "displaylabellcd.h"
#include "VDV301subscriber/VDV301DataStructures/vdv301alldata.h"

class DisplayLabelStopGroup
{
public:
    DisplayLabelStopGroup(QPointer<QLabel> new_labelStopName, QPointer<QLabel> new_labelFarezoneBottom, QPointer<QLabel> new_labelFarezoneTop, QPointer<QLabel> new_labelPlatform=nullptr, QPointer<QLabel> new_labelMinutes=nullptr);

    QPointer<QLabel> labelStopName;
    QPointer<QLabel> labelFarezoneBottom;
    QPointer<QLabel> labelFarezoneTop;
    QPointer<QLabel> labelPlatform;
    QPointer<QLabel> labelMinutes;
    void eraseContent();
    bool labelSetTextSafe(QLabel *label, QString text);
};

class DisplayLabelConnectionGroup
{
public:
    DisplayLabelConnectionGroup(QPointer<QLabel> new_labelConnectionLine, QPointer<QLabel> new_labelConnectionDestination, QPointer<QLabel> new_labelConnectionDeparture,QPointer<QLabel> new_labelConnectionPlatform);

    QPointer<QLabel> labelConnectionLine;
    QPointer<QLabel> labelConnectionDestination;
    QPointer<QLabel> labelConnectionDeparture;
    QPointer<QLabel> labelConnectionPlatform;


    bool labelSetTextSafe(QLabel *label, QString text);
    void eraseContent();
    bool labelSetVisibleSafe(QLabel *label, bool visibility);
};

class DisplayLabelLcd2_3 : public DisplayLabelLcd
{
public:
    DisplayLabelLcd2_3();
    using DisplayLabelLcd::displayLabelDestination;
    using DisplayLabelLcd::displayLabelDestinationFollowing;

    using DisplayLabelLcd::displayLabelLineName;
    using DisplayLabelLcd::displayLabelLineNameFollowing;


    QVector<DisplayLabelStopGroup> labelListStopGroup;

    QVector<DisplayLabelStopGroup> labelListStopConnectionGroup;

    QVector<DisplayLabelConnectionGroup> labelListConnectionGroup;

    void displayLabelViaPoints(QVector<Vdv301ViaPoint> viaPoints);
    void displayLabelDestination(Vdv301Destination vdv301Destination);
    void displayLabelStopList(Vdv301Trip firstTrip, Vdv301Trip secondTrip, int currentStopIndex, QVector<DisplayLabelStopGroup> labelListStopGroup);
    void displayLabelStopFareZone(Vdv301AllData allData);
    void displayLabelStopPoint(Vdv301StopPoint selectedStopPointDestination, bool isFollowingTrip, QLabel *labelStopName, QLabel *labelFarezoneBottom, QLabel *labelFarezoneTop);

    void displayLabelConnectionList(QVector<Vdv301Connection> connectionList);
    void displayLabelDestinationFollowing(Vdv301Destination vdv301Destination);
    QVector<Vdv301DisplayContent> filterVdv301DisplayContentByClass(QVector<Vdv301DisplayContent> displayContentList, DisplayContentClass displayContentType);
    void displayLabelLineName(Vdv301Line vdv301Line);
    void displayLabelLineNameFollowing(Vdv301Line vdv301Line);
    QString arrivalTimeDifferenceToText(QDateTime earlierTime, QDateTime laterTime, QString postFix);
};

#endif // DISPLAYLABELLCD2_3_H
