#include "displaylabellcd2_3cz1_0_jis.h"

DisplayLabelLcd2_3CZ1_0_Jis::DisplayLabelLcd2_3CZ1_0_Jis() {

}


DisplayLabelStopGroup::DisplayLabelStopGroup(QPointer<QLabel> new_labelStopName, QPointer<QLabel> new_labelFarezoneBottom, QPointer<QLabel> new_labelFarezoneTop)
{
    labelStopName=new_labelStopName;
    labelFarezoneBottom=new_labelFarezoneBottom;
    labelFarezoneTop=new_labelFarezoneTop;
}

void DisplayLabelStopGroup::eraseContent()
{
    labelSetTextSafe(labelStopName,"");
    labelSetTextSafe(labelFarezoneBottom,"");
    labelSetTextSafe(labelFarezoneTop,"");
}

bool DisplayLabelStopGroup::labelSetTextSafe(QLabel *label, QString text)
{
    if(label==NULL)
    {
        qDebug()<<Q_FUNC_INFO<<" failed";
        return false;
    }

    else
    {
        label->setText(text);
    }
    return true;
}




DisplayLabelConnectionGroup::DisplayLabelConnectionGroup(QPointer<QLabel> new_labelConnectionLine, QPointer<QLabel> new_labelConnectionDestination, QPointer<QLabel> new_labelConnectionDeparture, QPointer<QLabel> new_labelConnectionPlatform)
{
    labelConnectionLine=new_labelConnectionLine;
    labelConnectionDestination=new_labelConnectionDestination;
    labelConnectionDeparture=new_labelConnectionDeparture;
    labelConnectionPlatform=new_labelConnectionPlatform;
}


void DisplayLabelConnectionGroup::eraseContent()
{
    labelSetTextSafe(labelConnectionLine,"");
    labelSetTextSafe(labelConnectionDestination,"");
    labelSetTextSafe(labelConnectionDeparture,"");
    labelSetTextSafe(labelConnectionPlatform,"");
}

bool DisplayLabelConnectionGroup::labelSetTextSafe(QLabel *label, QString text)
{
    if(label==NULL)
    {
        qDebug()<<Q_FUNC_INFO<<" failed";
        return false;
    }

    else
    {
        label->setText(text);
    }
    return true;
}


/*

void DisplayLabelLcd2_3CZ1_0_Jis::displayLabelStopList(Vdv301Trip2_3CZ1_0 firstTrip, Vdv301Trip2_3CZ1_0 secondTrip, int currentStopIndex)
{
    qDebug() <<  Q_FUNC_INFO;

    int pocetPoli=labelListStopPointName.count();
    if(firstTrip.stopPointList.isEmpty())
    {
        return ;
    }

    firstTrip.stopPointList.remove(0,currentStopIndex-1);

    for(int i=0;i<pocetPoli;i++)
    {
        Vdv301StopPoint2_3CZ1_0 aktualniZastavka;
        bool navaznySpoj=false;
        QLabel* labelStopName=nullptr;
        //  QLabel* labelStopNameConnection=nullptr;
        QLabel* labelFarezoneBottom=nullptr;
        QLabel* labelFarezoneTop=nullptr;


        if(!labelListStopPointName.isEmpty())
        {
            labelStopName=labelListStopPointName.value(i);
        }


        if(!labelListFareZoneLower.isEmpty())
        {
            labelFarezoneBottom=labelListFareZoneLower.value(i);
        }

        if(!labelListFareZoneUpper.isEmpty())
        {
            labelFarezoneTop=labelListFareZoneUpper.value(i);
        }

        if(!firstTrip.stopPointList.isEmpty())
        {
            aktualniZastavka=firstTrip.stopPointList.takeFirst();
        }
        else
        {
            if(!secondTrip.stopPointList.isEmpty())
            {
                navaznySpoj=true;
                aktualniZastavka=secondTrip.stopPointList.takeFirst();
            }
            else
            {
                qDebug()<<"pro label "<<i<<" uz nezbyly zastavky";

                return;
            }
        }

        displayLabelStopPoint(aktualniZastavka,navaznySpoj,labelStopName,labelFarezoneTop,labelFarezoneBottom);
        // displayLabelStopPoint(aktualniZastavka,navaznySpoj,labelStopNameConnection,nullptr,nullptr);
    }
}


*/

void DisplayLabelLcd2_3CZ1_0_Jis::displayLabelLineName(Vdv301Line vdv301Line)
{
    qDebug() <<  Q_FUNC_INFO;


    if(vdv301Line.lineNameList.isEmpty())
    {
        displayLabelLineName("");
    }
    else
    {
        displayLabelLineName(vdv301Line.lineNameList.first().text);
    }
}

void DisplayLabelLcd2_3CZ1_0_Jis::displayLabelLineName(QString lineName)
{
    qDebug() <<  Q_FUNC_INFO;
    displayLabelDrawLineNumber2_4(lineName,labelLine, qFloor(ratioPixelPoint*200),false);
    displayLabelDrawLineNumber2_4(lineName,labelLineConnection, qFloor(ratioPixelPoint*200),false);
}



void DisplayLabelLcd2_3CZ1_0_Jis::displayLabelStopListNew(Vdv301Trip2_3CZ1_0 firstTrip, Vdv301Trip2_3CZ1_0 secondTrip, int currentStopIndex,  QVector<DisplayLabelStopGroup> labelListStopGroup)
{
    qDebug() <<  Q_FUNC_INFO;

    Vdv301Trip2_3CZ1_0 firstTripCopy=firstTrip;
    Vdv301Trip2_3CZ1_0 secondTripCopy=secondTrip;

    if(firstTripCopy.stopPointList.isEmpty())
    {
        return ;
    }

    firstTripCopy.stopPointList.remove(0,currentStopIndex-1);

    qDebug()<<"number of labels: "<<labelListStopGroup.count();

    for(DisplayLabelStopGroup &selectedGroup : labelListStopGroup)
    {
        Vdv301StopPoint2_3CZ1_0 aktualniZastavka;
        bool navaznySpoj=false;


        if(!firstTripCopy.stopPointList.isEmpty())
        {
            aktualniZastavka=firstTripCopy.stopPointList.takeFirst();
        }
        else
        {
            if(!secondTripCopy.stopPointList.isEmpty())
            {
                navaznySpoj=true;
                aktualniZastavka=secondTripCopy.stopPointList.takeFirst();
            }
            else
            {
                qDebug()<<"pro label uz nezbyly zastavky";
                selectedGroup.eraseContent();
            }
        }

        displayLabelStopPoint(aktualniZastavka,navaznySpoj,selectedGroup.labelStopName,selectedGroup.labelFarezoneTop,selectedGroup.labelFarezoneBottom);


    }


}


void DisplayLabelLcd2_3CZ1_0_Jis::displayLabelStopFareZone(Vdv301AllData2_3CZ1_0 allData)
{
    qDebug() <<  Q_FUNC_INFO;

    Vdv301Trip2_3CZ1_0 firstTrip;
    Vdv301Trip2_3CZ1_0 followingTrip;

    if(allData.tripInformationList.isEmpty())
    {

    }
    else
    {
        firstTrip=allData.tripInformationList.at(0);
        if(allData.tripInformationList.count()>1)
        {
            followingTrip=allData.tripInformationList.at(1);
        }
    }

    displayLabelStopListNew(firstTrip,followingTrip,allData.currentStopIndex, labelListStopGroup);
    displayLabelStopListNew(firstTrip,followingTrip,allData.currentStopIndex, labelListStopConnectionGroup);


}







void DisplayLabelLcd2_3CZ1_0_Jis::displayLabelConnectionList(QVector<Vdv301Connection> connectionList)
{
    qDebug() <<  Q_FUNC_INFO;

    QVector<Vdv301Connection> connectionListCopy=connectionList;
    /*

    foreach(QFrame* label,labelListConnectionDestination)
    {
        label->hide();
    }

    foreach(QFrame* label,labelListConnectionLine)
    {
        label->hide();
    }

    foreach(QFrame* label,labelListConnectionPlatform)
    {
        label->hide();
    }

    foreach(QFrame* label,labelListConnectionDeparture)
    {
        label->hide();
    }

    vymazPoleLabelu(labelListConnectionDestination);
    vymazPoleLabelu(labelListConnectionLine);
    vymazPoleLabelu(labelListConnectionPlatform);
    vymazPoleLabelu(labelListConnectionDeparture);

    */

    for(DisplayLabelConnectionGroup &selectedGroup : labelListConnectionGroup)
    {
        if(!connectionListCopy.isEmpty())
        {
            Vdv301Connection selectedConnection=connectionListCopy.takeFirst();


            if(!selectedConnection.vdv301displayContentList.isEmpty() )
            {
                Vdv301DisplayContent firstDisplayContent=selectedConnection.vdv301displayContentList.first();

                labelSetTextSafe(selectedGroup.labelConnectionDestination,vdv301InternationalTextJoinAll(firstDisplayContent.destination.destinationNameList,"\n").text);
                // labelListConnectionDestination.at(i)->setText();
                // labelListConnectionDestination.at(i)->show();

                displayLabelDrawLineNumber2_4(vdv301InternationalTextJoinAll(firstDisplayContent.lineInformation.lineNameList,"\n").text, selectedGroup.labelConnectionLine, sizeIconConnectionDynamic,true);

                // labelListConnectionPlatform.at(i)->setText( );
                //  labelListConnectionPlatform.at(i)->show();

                labelSetTextSafe(selectedGroup.labelConnectionPlatform,selectedConnection.platform);

                QString departureTime="";
                if( selectedConnection.getMinutesToDeparture(QDateTime::currentDateTime())<1)
                {
                    departureTime="&lt;1";
                }
                else
                {
                    departureTime=QString::number( selectedConnection.getMinutesToDeparture(QDateTime::currentDateTime()));
                }

                labelSetTextSafe(selectedGroup.labelConnectionDeparture,"<b>"+ departureTime+"</b> min.");

                //labelListConnectionDeparture.at(i)->setText();
                //labelListConnectionDeparture.at(i)->show();
            }
            else
            {
                qDebug()<<"empty DisplayContent";
            }
        }
        else
        {
            selectedGroup.eraseContent();
        }

    }

}

