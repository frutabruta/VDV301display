#include "displaylabellcd2_3cz1_0_jis.h"

Q_LOGGING_CATEGORY(DisplayLabelLcd2_3CZ1_0_JisLog, "DisplayLabelLcd2_3CZ1_0_Jis")

DisplayLabelLcd2_3CZ1_0_Jis::DisplayLabelLcd2_3CZ1_0_Jis() {

}



void DisplayLabelLcd2_3CZ1_0_Jis::displayLabelLineName(Vdv301Line vdv301Line)
{
    qCDebug(DisplayLabelLcd2_3CZ1_0_JisLog) <<  Q_FUNC_INFO;


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
    qCDebug(DisplayLabelLcd2_3CZ1_0_JisLog) <<  Q_FUNC_INFO;
    displayLabelDrawLineNumber2_4(lineName,labelLine, qFloor(ratioPixelPoint*200),false);
    displayLabelDrawLineNumber2_4(lineName,labelLineConnection, qFloor(ratioPixelPoint*200),false);
}




void DisplayLabelLcd2_3CZ1_0_Jis::displayLabelStopListNew(Vdv301Trip2_3CZ1_0 firstTrip, Vdv301Trip2_3CZ1_0 secondTrip, int currentStopIndex,  QVector<DisplayLabelStopGroup> labelListStopGroup, bool invertFirstStop)
{
    qCDebug(DisplayLabelLcd2_3CZ1_0_JisLog) <<  Q_FUNC_INFO;

    Vdv301Trip2_3CZ1_0 firstTripCopy=firstTrip;
    Vdv301Trip2_3CZ1_0 secondTripCopy=secondTrip;

    if(firstTripCopy.stopPointList.isEmpty())
    {
        return ;
    }

    firstTripCopy.stopPointList.remove(0,currentStopIndex-1);

    qCDebug(DisplayLabelLcd2_3CZ1_0_JisLog)<<"number of labels: "<<labelListStopGroup.count();


    bool isFirst=true;
    bool invert=false;

    for(DisplayLabelStopGroup &selectedGroup : labelListStopGroup)
    {

        Vdv301StopPoint2_3CZ1_0 aktualniZastavka;
        bool navaznySpoj=false;
        if(invertFirstStop)
        {
            if(isFirst)
            {
                isFirst=false;

                if((firstTrip.locationState==Vdv301Enumerations::LocationStateAtStop)||(firstTrip.locationState==Vdv301Enumerations::LocationStateBeforeStop))
                {
                    invert=true;
                }
                else
                {
                    invert=false;
                }
            }
            else
            {
                invert=false;
            }
        }
        else
        {
            invert=false;
        }

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
                qCDebug(DisplayLabelLcd2_3CZ1_0_JisLog)<<"pro label uz nezbyly zastavky";
                selectedGroup.eraseContent();
            }
        }

        displayLabelStopPoint(aktualniZastavka,navaznySpoj,selectedGroup.labelStopName,selectedGroup.labelFarezoneTop,selectedGroup.labelFarezoneBottom,invert);
        labelSetTextSafe(selectedGroup.labelPlatform,aktualniZastavka.platform);

    }


}


void DisplayLabelLcd2_3CZ1_0_Jis::displayLabelStopFareZone(Vdv301AllData2_3CZ1_0 allData)
{
    qCDebug(DisplayLabelLcd2_3CZ1_0_JisLog) <<  Q_FUNC_INFO;

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

    displayLabelStopListNew(firstTrip,followingTrip,allData.currentStopIndex, labelListStopGroup,true);
    displayLabelStopListNew(firstTrip,followingTrip,allData.currentStopIndex, labelListStopConnectionGroup,false);
}



void DisplayLabelLcd2_3CZ1_0_Jis::displayLabelConnectionList(QVector<Vdv301Connection> connectionList)
{
    qCDebug(DisplayLabelLcd2_3CZ1_0_JisLog) <<  Q_FUNC_INFO;

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
                qCDebug(DisplayLabelLcd2_3CZ1_0_JisLog)<<"empty DisplayContent";
            }
        }
        else
        {
            selectedGroup.eraseContent();
        }

    }

}


void DisplayLabelLcd2_3CZ1_0_Jis::displayLabelConnectionListBasic(QVector<ConnectionBasic> connectionList)
{
    qCDebug(DisplayLabelLcd2_3CZ1_0_JisLog) <<  Q_FUNC_INFO;

    QVector<ConnectionBasic> connectionListCopy=connectionList;

    for(DisplayLabelConnectionGroup &selectedGroup : labelListConnectionGroup)
    {
        if(!connectionListCopy.isEmpty())
        {
            ConnectionBasic selectedConnection=connectionListCopy.takeFirst();

            if(selectedGroup.labelConnectionDestination!=nullptr)
            {
                labelSetTextSafe(selectedGroup.labelConnectionDestination,inlineFormatParser.parseTextLcd(selectedConnection.destinationName, selectedGroup.labelConnectionDestination->font().pixelSize(),slozkaPiktogramu) )    ;
            }

          //  labelSetTextSafe(selectedGroup.labelConnectionDestination,selectedConnection.destinationName);

            displayLabelDrawLineNumber2_4(selectedConnection.lineName , selectedGroup.labelConnectionLine, sizeIconConnectionDynamic,true);

            if(selectedConnection.platform=="")
            {
                labelSetVisibleSafe(selectedGroup.labelConnectionPlatform,false);
            }
            else
            {
                labelSetTextSafe(selectedGroup.labelConnectionPlatform,selectedConnection.platform);
                labelSetVisibleSafe(selectedGroup.labelConnectionPlatform,true);
               // selectedGroup.labelConnectionPlatform.setBa
            }

            QString departureTime="";
            departureTime=selectedConnection.departureTime;
            labelSetTextSafe(selectedGroup.labelConnectionDeparture,"<b>"+ departureTime+"</b> min.");

        }
        else
        {
            selectedGroup.eraseContent();
        }
    }
}


void DisplayLabelLcd2_3CZ1_0_Jis::displayLabelDrawLineNumber2_4(QString lineName, QLabel* label, int velikostPiktogramu,bool prestup)
{
    qCDebug(DisplayLabelLcd2_3CZ1_0_JisLog)<<Q_FUNC_INFO;


    QString linkaStyleSheetStandard="font-weight: bold; background-color:rgb(200,200,200); color:rgb(29,29,27); padding: 0px; margin: 0px; ";

    if(prestup)
    {
        linkaStyleSheetStandard="font-weight: bold; color:#ffffff; padding: 0px; margin: 0px;  ";
    }



    QString linkaStyleSheetPiktogram="border-radius:6px; padding: 0px; margin: 0px; font-weight: bold;";


    if(label!=nullptr)
    {
        labelSetStylesheetSafe(label,linkaStyleSheetStandard);

        QString vyslednyText= inlineFormatParser.parseTextLcdJis(lineName, label->font().pixelSize(),slozkaPiktogramu);
        labelSetTextSafe(label,vyslednyText);

        qCDebug(DisplayLabelLcd2_3CZ1_0_JisLog).noquote()<<"obsah pole linky: "<<vyslednyText;

        label->show();
    }

}


