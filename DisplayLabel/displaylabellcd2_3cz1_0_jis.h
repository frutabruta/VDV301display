#ifndef DISPLAYLABELLCD2_3CZ1_0_JIS_H
#define DISPLAYLABELLCD2_3CZ1_0_JIS_H

#include "displaylabellcd2_3cz1_0.h"

class DisplayLabelStopGroup
{
public:
    DisplayLabelStopGroup(QPointer<QLabel> new_labelStopName, QPointer<QLabel> new_labelFarezoneBottom, QPointer<QLabel> new_labelFarezoneTop);

    QPointer<QLabel> labelStopName;
    QPointer<QLabel> labelFarezoneBottom;
    QPointer<QLabel> labelFarezoneTop;
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
};

class DisplayLabelLcd2_3CZ1_0_Jis : public DisplayLabelLcd2_3CZ1_0
{
public:

    DisplayLabelLcd2_3CZ1_0_Jis();

    QLabel *labelLineConnection=nullptr;
    QLabel *labelDestinationConnection=nullptr;


    QVector<DisplayLabelStopGroup> labelListStopGroup;

    QVector<DisplayLabelStopGroup> labelListStopConnectionGroup;

    QVector<DisplayLabelConnectionGroup> labelListConnectionGroup;

  //  QVector<DisplayLabelConnectionGroup> labelListStopPointNameConnectionNew;



  //  void displayLabelStopList(Vdv301Trip2_3CZ1_0 firstTrip, Vdv301Trip2_3CZ1_0 secondTrip, int currentStopIndex);
    void displayLabelStopFareZone(Vdv301AllData2_3CZ1_0 allData);
    void displayLabelStopListNew(Vdv301Trip2_3CZ1_0 firstTrip, Vdv301Trip2_3CZ1_0 secondTrip, int currentStopIndex, QVector<DisplayLabelStopGroup> labelListStopGroup);
    void displayLabelConnectionList(QVector<Vdv301Connection> connectionList);
    void displayLabelLineName(Vdv301Line vdv301Line);
    void displayLabelLineName(QString lineName);
private:

};

#endif // DISPLAYLABELLCD2_3CZ1_0_JIS_H
