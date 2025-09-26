#include "displaylabellcd2_3.h"

DisplayLabelLcd2_3::DisplayLabelLcd2_3() {}



void DisplayLabelLcd2_3::displayLabelDestination(Vdv301Destination vdv301Destination)
{
    qDebug() <<  Q_FUNC_INFO;

    int iconSize=60;
    if(labelDestination!=NULL)
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


void DisplayLabelLcd2_3::displayLabelLineNameFollowing(Vdv301Line vdv301Line)
{
    qDebug() <<  Q_FUNC_INFO;


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
    qDebug() <<  Q_FUNC_INFO;

    if(frameFollowingTrip!=nullptr)
    {
       frameFollowingTrip->show();
    }


    int iconSize=60;
    if(labelDestination!=NULL)
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
    qDebug() <<  Q_FUNC_INFO;

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





    for (int i=0;i<minimum(connectionList.count(), labelListConnectionDestination.count()) ; i++)
    {
        Vdv301Connection selectedConnection=connectionList.at(i);


        if(!selectedConnection.vdv301displayContentList.isEmpty() )
        {
            Vdv301DisplayContent firstDisplayContent=selectedConnection.vdv301displayContentList.first();

            labelListConnectionDestination.at(i)->setText(vdv301InternationalTextJoinAll(firstDisplayContent.destination.destinationNameList,"\n").text);
            labelListConnectionDestination.at(i)->show();

            displayLabelDrawLineNumber2_4(vdv301InternationalTextJoinAll(firstDisplayContent.lineInformation.lineNameList,"\n").text, labelListConnectionLine.at(i), sizeIconConnectionDynamic,true);

            labelListConnectionPlatform.at(i)->setText(selectedConnection.platform );
            labelListConnectionPlatform.at(i)->show();

            QString departureTime="";
            if( selectedConnection.getMinutesToDeparture(QDateTime::currentDateTime())<1)
            {
                departureTime="&lt;1";
            }
            else
            {
                departureTime=QString::number( selectedConnection.getMinutesToDeparture(QDateTime::currentDateTime()));
            }
            labelListConnectionDeparture.at(i)->setText("<b>"+ departureTime+"</b> min.");
            labelListConnectionDeparture.at(i)->show();
        }
        else
        {
            qDebug()<<"empty DisplayContent";
        }


    }
}




void DisplayLabelLcd2_3::displayLabelStopFareZone(Vdv301AllData allData)
{
    qDebug() <<  Q_FUNC_INFO;

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
    displayLabelStopList(firstTrip,followingTrip,allData.currentStopIndex);

}

void DisplayLabelLcd2_3::displayLabelStopList(Vdv301Trip firstTrip, Vdv301Trip secondTrip, int currentStopIndex)
{
    qDebug() <<  Q_FUNC_INFO;
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
                qDebug()<<"pro label "<<i<<" uz nezbyly zastavky";

                return;
            }
        }

        displayLabelStopPoint(aktualniZastavka,navaznySpoj,labelListStopPointName.at(i),labelListFareZoneUpper.at(i),labelListFareZoneLower.at(i));

    }



}



void DisplayLabelLcd2_3::displayLabelViaPoints(QVector<Vdv301ViaPoint> viaPoints)
{
    qDebug() <<  Q_FUNC_INFO;
    if(labelViaPointsScrolling==NULL)
    {
        qDebug()<<"NULL label";
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
