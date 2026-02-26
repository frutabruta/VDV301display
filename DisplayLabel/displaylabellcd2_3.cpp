#include "displaylabellcd2_3.h"

Q_LOGGING_CATEGORY(DisplayLabelLcd2_3Log, "DisplayLabelLcd2_3")


DisplayLabelStopGroup::DisplayLabelStopGroup(QPointer<QLabel> new_labelStopName, QPointer<QLabel> new_labelFarezoneBottom, QPointer<QLabel> new_labelFarezoneTop, QPointer<QLabel> new_labelPlatform, QPointer<QLabel> new_labelMinutes)
{
    labelStopName=new_labelStopName;
    labelFarezoneBottom=new_labelFarezoneBottom;
    labelFarezoneTop=new_labelFarezoneTop;
    labelPlatform=new_labelPlatform;
    labelMinutes=new_labelMinutes;
}

void DisplayLabelStopGroup::eraseContent()
{
    labelSetTextSafe(labelStopName,"");
    labelSetTextSafe(labelFarezoneBottom,"");
    labelSetTextSafe(labelFarezoneTop,"");
    labelSetTextSafe(labelMinutes,"");
}

bool DisplayLabelStopGroup::labelSetTextSafe(QLabel *label, QString text)
{
    if(label==nullptr)
    {
        qCDebug(DisplayLabelLcd2_3Log)<<Q_FUNC_INFO<<" failed";
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
    labelSetVisibleSafe(labelConnectionPlatform,false);
}

bool DisplayLabelConnectionGroup::labelSetTextSafe(QLabel *label, QString text)
{
    if(label==nullptr)
    {
        qCDebug(DisplayLabelLcd2_3Log)<<Q_FUNC_INFO<<" failed";
        return false;
    }

    else
    {
        label->setText(text);
    }
    return true;
}


bool DisplayLabelConnectionGroup::labelSetVisibleSafe(QLabel *label, bool visibility)
{
    if(label==NULL)
    {
        qCDebug(DisplayLabelLcd2_3Log)<<Q_FUNC_INFO<<" failed";
        return false;
    }

    else
    {
        label->setVisible(visibility);
    }
    return true;
}


DisplayLabelLcd2_3::DisplayLabelLcd2_3() {}


QString DisplayLabelLcd2_3::arrivalTimeDifferenceToText(QDateTime earlierTime, QDateTime laterTime, QString postFix)
{
    QString output="";

    int minutes=earlierTime.secsTo(laterTime)/60;

    if(minutes<1)
    {
        //output="";
        output=QString::number(minutes)+postFix;
    }
    else
    {
       output=QString::number(minutes)+postFix;
    }

    return output;
}




void DisplayLabelLcd2_3::displayLabelDestination(Vdv301Destination vdv301Destination)
{
    qCDebug(DisplayLabelLcd2_3Log) <<  Q_FUNC_INFO;

    int iconSize=60;
    if(labelDestination!=nullptr)
    {
        iconSize=labelDestination->font().pixelSize();
    }

    QString text=nahradIconPiktogramem(vdv301InternationalTextJoinAll(vdv301Destination.destinationNameList,"\n").text, iconSize, slozkaPiktogramu);
    labelSetTextSafe(labelDestination,text);
    /* if(cisSubscriber.verze()=="2.3")
    {
       labelVykreslovani.naplnNazevCileLabel(labelVykreslovani.inlineFormatParser.vyparsujText(nazev, ui->Lcil->font().pixelSize(),labelVykreslovani.slozkaPiktogramu), ui->Lcil);

    }
    else
    {

    }
*/
}


void DisplayLabelLcd2_3::displayLabelLineName(Vdv301Line vdv301Line)
{
    qCDebug(DisplayLabelLcd2_3Log) <<  Q_FUNC_INFO;


    if(vdv301Line.lineNameList.isEmpty())
    {
        displayLabelLineName("");
    }
    else
    {
        displayLabelLineName(vdv301Line.lineNameList.first().text);
    }
}


void DisplayLabelLcd2_3::displayLabelLineNameFollowing(Vdv301Line vdv301Line)
{
    qCDebug(DisplayLabelLcd2_3Log) <<  Q_FUNC_INFO;


    if(vdv301Line.lineNameList.isEmpty())
    {
        displayLabelLineNameFollowing("");
    }
    else
    {
        displayLabelLineNameFollowing(vdv301Line.lineNameList.first().text);
    }
}





void DisplayLabelLcd2_3::displayLabelDestinationFollowing(Vdv301Destination vdv301Destination)
{
    qCDebug(DisplayLabelLcd2_3Log) <<  Q_FUNC_INFO;

    if(frameFollowingTrip!=nullptr)
    {
       frameFollowingTrip->show();
    }


    int iconSize=60;
    if(labelDestination!=nullptr)
    {
        iconSize=labelDestination->font().pixelSize();
    }

    QString text=nahradIconPiktogramem(vdv301InternationalTextJoinAll(vdv301Destination.destinationNameList,"\n").text, iconSize, slozkaPiktogramu);
    labelSetTextSafe(labelDestinationFollowing,text);





    /*
    ui->label_followingLine->setText(followingTripLine);
    ui->label_followingDestination->setText(followingTripDestination);
    ui->frame_navaznySpoj->show();
    */



    /* if(cisSubscriber.verze()=="2.3")
    {
       labelVykreslovani.naplnNazevCileLabel(labelVykreslovani.inlineFormatParser.vyparsujText(nazev, ui->Lcil->font().pixelSize(),labelVykreslovani.slozkaPiktogramu), ui->Lcil);

    }
    else
    {

    }
*/
}

void DisplayLabelLcd2_3::displayLabelConnectionList(QVector<Vdv301Connection> connectionList)
{
    qCDebug(DisplayLabelLcd2_3Log) <<  Q_FUNC_INFO;

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
                qCDebug(DisplayLabelLcd2_3Log)<<"empty DisplayContent";
            }
        }
        else
        {
            selectedGroup.eraseContent();
        }

    }
}


void DisplayLabelLcd2_3::displayLabelStopFareZone(Vdv301AllData allData)
{
    qCDebug(DisplayLabelLcd2_3Log) <<  Q_FUNC_INFO;

    Vdv301Trip firstTrip;
    Vdv301Trip followingTrip;

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
    displayLabelStopList(firstTrip,followingTrip,allData.currentStopIndex,labelListStopGroup);

}
/*
void DisplayLabelLcd2_3::displayLabelStopList(Vdv301Trip firstTrip, Vdv301Trip secondTrip, int currentStopIndex)
{
    qCDebug(DisplayLabelLcd2_3Log) <<  Q_FUNC_INFO;
    //stavSystemu.indexAktZastavky;
    int pocetPoli=labelListStopPointName.count();
    if(firstTrip.stopPointList.isEmpty())
    {
        return ;
    }

    //   zastavky=vektorZastavkaCilZahoditZacatek(zastavky,index);

    firstTrip.stopPointList.remove(0,currentStopIndex-1);



    for(int i=0;i<pocetPoli;i++)
    {
        Vdv301StopPoint aktualniZastavka;
        bool navaznySpoj=false;
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
                qCDebug(DisplayLabelLcd2_3Log)<<"pro label "<<i<<" uz nezbyly zastavky";

                return;
            }
        }

        displayLabelStopPoint(aktualniZastavka,navaznySpoj,labelListStopPointName.at(i),labelListFareZoneUpper.at(i),labelListFareZoneLower.at(i));

    }



}*/

void DisplayLabelLcd2_3::displayLabelStopList(Vdv301Trip firstTrip, Vdv301Trip secondTrip, int currentStopIndex,  QVector<DisplayLabelStopGroup> labelListStopGroup)
{
    qCDebug(DisplayLabelLcd2_3Log) <<  Q_FUNC_INFO;

    Vdv301Trip firstTripCopy=firstTrip;
    Vdv301Trip secondTripCopy=secondTrip;

    if(firstTripCopy.stopPointList.isEmpty())
    {
        return ;
    }

    firstTripCopy.stopPointList.remove(0,currentStopIndex-1);

    qCDebug(DisplayLabelLcd2_3Log)<<"number of labels: "<<labelListStopGroup.count();


    for(DisplayLabelStopGroup &selectedGroup : labelListStopGroup)
    {

        Vdv301StopPoint aktualniZastavka;
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
                qCDebug(DisplayLabelLcd2_3Log)<<"pro label uz nezbyly zastavky";
                selectedGroup.eraseContent();
            }
        }

        displayLabelStopPoint(aktualniZastavka,navaznySpoj,selectedGroup.labelStopName,selectedGroup.labelFarezoneTop,selectedGroup.labelFarezoneBottom);
        labelSetTextSafe(selectedGroup.labelPlatform,aktualniZastavka.platform);
    }
}





void DisplayLabelLcd2_3::displayLabelViaPoints(QVector<Vdv301ViaPoint> viaPoints)
{
    qCDebug(DisplayLabelLcd2_3Log) <<  Q_FUNC_INFO;
    if(labelViaPointsScrolling==nullptr)
    {
        qCDebug(DisplayLabelLcd2_3Log)<<"NULL label";
        return;
    }

    /*
    if(currentDestinationPointList.isEmpty())
    {
        ui->label_nacestne->setText("");
        return;
    }
    */

    QString newViapointString=vykresliNacestneZastavkyText(viaPoints, labelViaPointsScrolling->font().pixelSize());



    if(oldViapointString!=newViapointString)
    {
        labelSetTextSafe(labelViaPointsScrolling,newViapointString);
        timerScrollingText.start(intervalScrollingText);
        oldViapointString=newViapointString;
    }
    else
    {
        if(labelViaPointsScrolling->text()=="")
        {
            labelSetTextSafe(labelViaPointsScrolling,newViapointString);
        }

    }


}



void DisplayLabelLcd2_3::displayLabelStopPoint(Vdv301StopPoint selectedStopPointDestination, bool isFollowingTrip, QLabel* labelStopName, QLabel* labelFarezoneBottom, QLabel* labelFarezoneTop)
{

    QStringList fareZoneList= selectedStopPointDestination.fareZoneList;




    Vdv301InternationalText joinedStopName=vdv301InternationalTextJoinAll(selectedStopPointDestination.stopNameList,"\n");
    labelStopName->setText(inlineFormatParser.parseTextLcd(joinedStopName.text, labelStopName->font().pixelSize(),slozkaPiktogramu) );
    /*
    if((mVdv301version=="2.3")||(mVdv301version=="2.3CZ1.0"))
    {
        //   QString nahradIconPiktogramem(QString vstup);
        //   nazevZastavky->setText(labelVykreslovani.zabalHtmlDoZnacek(labelVykreslovani.nahradIconPiktogramem( aktualniZastavka.stopPoint.NameLcd, nazevZastavky->font().pixelSize(),labelVykreslovani.slozkaPiktogramu )));
       }
    else
    {
        pasmoveDvojiceLcd.roztridPasma(selectedStopPointDestination.stopPoint.fareZoneList);
        labelStopName->setText(zabalHtmlDoZnacek(doplnPiktogramyBezZacatkuKonce(selectedStopPointDestination.stopPoint.NameLcd,selectedStopPointDestination.stopPoint.iconList,labelStopName->font().pixelSize() )));
    }
    */

    switch(fareZoneList.count())
    {
    case 0:
        labelFarezoneBottom->setText("");

        break;
    case 1:
        labelFarezoneBottom->setText(fareZoneList.at(0));
        labelFarezoneBottom->setFont(fontLabelFareZoneLarge);

        labelFarezoneTop->hide();
        labelFarezoneTop->setFont(fontLabelFareZoneLarge);
        break;
    case 2:
        labelFarezoneBottom->setText(fareZoneList.at(0));
        labelFarezoneBottom->setFont(fontLabelFareZoneSmall );

        labelFarezoneTop->show();
        labelFarezoneTop->setFont(fontLabelFareZoneSmall );
        labelFarezoneTop->setText(fareZoneList.at(1));

        break;
    case 3:
        //prepared for case of 3 systems
        break;
    default:
        break;
    }


    if(isFollowingTrip==false)
    {
        labelStopName->setStyleSheet("color:"+barvyLinek.barva_bila_255_255_255+";");
        labelFarezoneTop->setStyleSheet("color:"+barvyLinek.barva_bila_255_255_255+";");
        labelFarezoneBottom->setStyleSheet("color:"+barvyLinek.barva_bila_255_255_255+";");
    }
    else
    {
        labelStopName->setStyleSheet("color:"+barvyLinek.barva_PozadiC_100_100_100+";");
        labelFarezoneTop->setStyleSheet("color:"+barvyLinek.barva_PozadiC_100_100_100+";");
        labelFarezoneBottom->setStyleSheet("color:"+barvyLinek.barva_PozadiC_100_100_100+";");
    }

}



QVector<Vdv301DisplayContent> DisplayLabelLcd2_3::filterVdv301DisplayContentByClass(QVector<Vdv301DisplayContent> displayContentList, DisplayContentClass displayContentType)
{
    QVector<Vdv301DisplayContent> output;
    foreach (Vdv301DisplayContent displayContent, displayContentList)
    {

        if(displayContent.displayContentType==displayContentType)
        {
            output<<displayContent;
        }

    }

    return output;
}
