#ifndef DISPLAYLABELLCD2_3CZ1_0_JIS_H
#define DISPLAYLABELLCD2_3CZ1_0_JIS_H

#include "displaylabellcd2_3cz1_0.h"


class ConnectionBasic
{
public:
    QString lineName="";
    QString destinationName="";
    QString platform="";
    QString departureTime="";
};


class DisplayLabelLcd2_3CZ1_0_Jis : public DisplayLabelLcd2_3CZ1_0
{
public:
    DisplayLabelLcd2_3CZ1_0_Jis();

    QPointer<QLabel> labelLineConnection=nullptr;
    QPointer<QLabel> labelDestinationConnection=nullptr;
    QPointer<QLabel> labelPlatformConnection=nullptr;
    QPointer<QLabel> labelViaPointMinutes=nullptr;

    bool hideNegativeMinutes=true;

    void displayLabelStopFareZone(Vdv301AllData2_3CZ1_0 allData);
    void displayLabelStopListNew(Vdv301Trip2_3CZ1_0 firstTrip, Vdv301Trip2_3CZ1_0 secondTrip, int currentStopIndex, QVector<DisplayLabelStopGroup> labelListStopGroup, bool invertFirstStop=false);
    void displayLabelConnectionList(QVector<Vdv301Connection> connectionList);
    void displayLabelLineName(Vdv301Line vdv301Line);
    void displayLabelLineName(QString lineName);
    void displayLabelDrawLineNumber2_4(QString lineName, QLabel *label, int velikostPiktogramu, bool prestup);
    void displayLabelConnectionListBasic(QVector<ConnectionBasic> connectionList);
    void displayLabelViaPoints(QVector<Vdv301ViaPoint> viaPoints);

    QVector<Vdv301ViaPoint> viaPointList;
    int viaPointListIterator=0;

    QTimer timerViaPoint;

public slots:
    void slotViapointTick();
    
protected:
QString viaPointToQString(Vdv301ViaPoint viaPoint, int velikostPiktogramu);    
};

#endif // DISPLAYLABELLCD2_3CZ1_0_JIS_H
