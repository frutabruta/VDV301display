#include "displaylabellcd.h"

#include "pasmovedvojicelcd.h"



DisplayLabelLcd::DisplayLabelLcd()
{
    timerLabelPageSwitch.setInterval(intervalSwitchPages);
}

void DisplayLabelLcd::initializeFonts()
{
    //LCD fonts
    fontLabelFareZoneLarge.setPointSize(36);
    fontLabelFareZoneLarge.setFamily("Roboto");
    fontLabelFareZoneLarge.setBold(true);

    fontLabelFareZoneSmall.setPointSize(20);
    fontLabelFareZoneSmall.setFamily("Roboto");
    fontLabelFareZoneSmall.setBold(true);
}

void DisplayLabelLcd::displayLabelStopPoint(StopPointDestination selectedStopPointDestination, bool isFollowingTrip, QLabel* labelStopName, QLabel* labelFarezoneBottom, QLabel* labelFarezoneTop)
{
    PasmoveDvojiceLcd pasmoveDvojiceLcd;


    if((mVdv301version=="2.3")||(mVdv301version=="2.3CZ1.0"))
    {
        //   QString nahradIconPiktogramem(QString vstup);
        //   nazevZastavky->setText(labelVykreslovani.zabalHtmlDoZnacek(labelVykreslovani.nahradIconPiktogramem( aktualniZastavka.stopPoint.NameLcd, nazevZastavky->font().pixelSize(),labelVykreslovani.slozkaPiktogramu )));
        pasmoveDvojiceLcd.roztridPasma2_3(selectedStopPointDestination.stopPoint.fareZoneList);
        labelStopName->setText(inlineFormatParser.parseTextLcd(selectedStopPointDestination.stopPoint.NameLcd, labelStopName->font().pixelSize(),slozkaPiktogramu) );
    }
    else
    {
        pasmoveDvojiceLcd.roztridPasma(selectedStopPointDestination.stopPoint.fareZoneList);
        labelStopName->setText(zabalHtmlDoZnacek(doplnPiktogramyBezZacatkuKonce(selectedStopPointDestination.stopPoint.NameLcd,selectedStopPointDestination.stopPoint.iconList,labelStopName->font().pixelSize() )));
    }


    if(pasmoveDvojiceLcd.pasmaSystemu1.isEmpty())
    {
        labelFarezoneBottom->setText("");

    }
    else
    {
        QString pasmaString1=fareZoneListToQString( pasmoveDvojiceLcd.pasmaSystemu1);
        QString zkratkaSystemuDvojtecka="";
        if (!pasmoveDvojiceLcd.pasmaSystemu2.isEmpty())
        {

            if(!pasmoveDvojiceLcd.pasmaSystemu1.first().system.isEmpty())
            {
                zkratkaSystemuDvojtecka=pasmoveDvojiceLcd.pasmaSystemu1.first().system+":";
            }

        }
        labelFarezoneBottom->setText(zkratkaSystemuDvojtecka+pasmaString1);
        labelFarezoneBottom->setFont(fontLabelFareZoneLarge);
    }

    if(pasmoveDvojiceLcd.pasmaSystemu2.isEmpty())
    {
        labelFarezoneTop->hide();
        labelFarezoneTop->setFont(fontLabelFareZoneLarge);
    }
    else
    {
        QString pasmaString2=fareZoneListToQString( pasmoveDvojiceLcd.pasmaSystemu2);
        labelFarezoneTop->show();

        labelFarezoneTop->setFont(fontLabelFareZoneSmall );
        labelFarezoneBottom->setFont(fontLabelFareZoneSmall );

        if(!pasmoveDvojiceLcd.pasmaSystemu2.first().system.isEmpty())
        {
            labelFarezoneTop->setText(pasmoveDvojiceLcd.pasmaSystemu2.first().system+":"+pasmaString2);
        }
        else
        {
            labelFarezoneTop->setText(pasmaString2);
        }

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


void DisplayLabelLcd::displayLabelDestination(QString nazev)
{
    qDebug() <<  Q_FUNC_INFO;


    labelSetTextSafe(labelDestination,nazev);
    /* if(cisSubscriber.verze()=="2.3")
    {
       labelVykreslovani.naplnNazevCileLabel(labelVykreslovani.inlineFormatParser.vyparsujText(nazev, ui->Lcil->font().pixelSize(),labelVykreslovani.slozkaPiktogramu), ui->Lcil);

    }
    else
    {

    }
*/
}



void DisplayLabelLcd::displayLabelConnectionList(QVector<Connection> connectionList)
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
        Connection aktualniPrestup=connectionList.at(i);
        labelListConnectionDestination.at(i)->setText(aktualniPrestup.destinationName);
        labelListConnectionDestination.at(i)->show();



        if(mVdv301version=="2.3")
        {
            displayLabelDrawLineNumber2_4(aktualniPrestup.subMode,aktualniPrestup.line, labelListConnectionLine.at(i), sizeIconConnectionDynamic,true);

        }
        else
        {
            displayLabelDrawLineNumber(aktualniPrestup.subMode,aktualniPrestup.line, labelListConnectionLine.at(i),sizeIconConnectionDynamic,true);
        }


        labelListConnectionPlatform.at(i)->setText(aktualniPrestup.platform );
        labelListConnectionPlatform.at(i)->show();

        labelListConnectionDeparture.at(i)->setText("<b>"+ QString::number( aktualniPrestup.getMinutesToDeparture(QDateTime::currentDateTime() ))+"</b> min.");
        labelListConnectionDeparture.at(i)->show();
    }
}


void DisplayLabelLcd::displayLabelDrawLineNumber( QString subMode, Line line, QLabel* label, int iconSize,bool isConnection)
{
    qDebug()<<Q_FUNC_INFO;
    if(label==NULL)
    {
        qDebug()<<Q_FUNC_INFO<<" NULL label";
        return;
    }
    QString linkaStyleSheetStandard="font-weight: bold;";

    if(isConnection)
    {
        linkaStyleSheetStandard+="border-radius:6px;padding: 5px; ";
    }


    QString linkaStyleSheetPiktogram="border-radius:6px; padding: 0px; margin: 0px; font-weight: bold;";



    QString nahrazeno=nahradMetro(line.lineName,subMode,iconSize);

    //defaultni seda barva na bile pozadi, neznama kombinace

    StylLinkyOld stylLinky;



    stylLinky.pozadi="background-color:"+barvyLinek.barva_bila_255_255_255+";";


    stylLinky.text="color:"+barvyLinek.barva_PozadiD_150_150_150+";";




    if(nahrazeno==line.lineName)
    {
        stylLinky=barvyLinek.linkaDoStylu(subMode,line);

        label->setStyleSheet(linkaStyleSheetStandard+stylLinky.text+stylLinky.pozadi);
        label->setText(line.lineName);
    }
    else
    {
        label->setStyleSheet(linkaStyleSheetPiktogram);
        label->setText(nahrazeno);
        //   qDebug()<<"nahrazeny retezec metra:"<<nahrazeno;
    }



    label->show();
}

void DisplayLabelLcd::displayLabelDrawLineNumber2_4( QString subMode, Line line, QLabel* label, int velikostPiktogramu,bool prestup)
{
    qDebug()<<Q_FUNC_INFO;


    QString linkaStyleSheetStandard="font-weight: bold; background-color:#ffffff; padding: 0px; margin: 0px; ";

    if(prestup)
    {
        linkaStyleSheetStandard+="border-radius:6px;padding: 0px; ";
    }


    QString linkaStyleSheetPiktogram="border-radius:6px; padding: 0px; margin: 0px; font-weight: bold;";


    label->setStyleSheet(linkaStyleSheetStandard);

    QString vyslednyText= inlineFormatParser.parseTextLcd(line.lineName, label->font().pixelSize(),slozkaPiktogramu);
    label->setText( vyslednyText);


    qDebug().noquote()<<"obsah pole linky: "<<vyslednyText;
    label->show();
}

void DisplayLabelLcd::displayLabelEraseInformation()
{
    qDebug() <<  Q_FUNC_INFO;
    labelSetTextSafe(labelDestination,"");
    labelSetTextSafe(labelDestination,"");

    //   ui->label_nacestne->setText("");



    if(frameFollowingTrip!=NULL)
    {
        frameFollowingTrip->hide();
    }



    vymazPoleLabelu(labelListStopPointName);
    vymazPoleLabelu(labelListFareZoneUpper);
    vymazPoleLabelu(labelListFareZoneLower);
    //obrazovka prestupu
    vymazPoleLabelu(labelListConnectionDestination);
    vymazPoleLabelu(labelListConnectionLine);
    vymazPoleLabelu(labelListConnectionPlatform);
    vymazPoleLabelu(labelListConnectionDeparture);

    timerLabelPageSwitch.stop();
    pageCycleList.clear();
    // pageCycleList.push_back(ui->page_hlavni_2);
}






void DisplayLabelLcd::displayLabelLineName(StopPointDestination selectedStopPointDestinationstavka,QString subMode)
{
    qDebug() <<  Q_FUNC_INFO;
    //  labelVykreslovani.naplnCisloLinkyLabel(alias,ui->Llinka);
    qDebug()<<"vypis linky:"<<selectedStopPointDestinationstavka.destination.NameLcd<<" "<<selectedStopPointDestinationstavka.line.lineName<<" vylukova:"<<selectedStopPointDestinationstavka.line.isDiversion ;

    if(mVdv301version=="2.3")
    {
        displayLabelDrawLineNumber2_4(subMode,selectedStopPointDestinationstavka.line,labelLine, qFloor(ratioPixelPoint*200),false);

    }
    else
    {
        displayLabelDrawLineNumber(subMode,selectedStopPointDestinationstavka.line,labelLine, qFloor(ratioPixelPoint*200),false);

    }
    //  labelVykreslovani.zmensiCisloLinkyLabel(ui->Llinka);

}



void DisplayLabelLcd::displayLabelStopFareZone(QVector<StopPointDestination> thisStopPointDestinationList, QVector<StopPointDestination> nextStopPointDestinationList, VehicleState vehicleState)
{
    qDebug() <<  Q_FUNC_INFO;

    //
    displayLabelStopList(thisStopPointDestinationList,nextStopPointDestinationList,vehicleState.currentStopIndex0);

}



void DisplayLabelLcd::displayLabelStopList(QVector<StopPointDestination> thisStopPointDestinationList,QVector<StopPointDestination> nextStopPointDestinationList, int index)
{
    qDebug() <<  Q_FUNC_INFO;
    //stavSystemu.indexAktZastavky;
    int pocetPoli=labelListStopPointName.count();
    if(thisStopPointDestinationList.isEmpty())
    {
        return ;
    }

    //   zastavky=vektorZastavkaCilZahoditZacatek(zastavky,index);

    thisStopPointDestinationList.remove(0,index);



    for(int i=0;i<pocetPoli;i++)
    {
        StopPointDestination aktualniZastavka;
        bool navaznySpoj=false;
        if(!thisStopPointDestinationList.isEmpty())
        {
            aktualniZastavka=thisStopPointDestinationList.takeFirst();
        }
        else
        {
            if(!nextStopPointDestinationList.isEmpty())
            {
                navaznySpoj=true;
                aktualniZastavka=nextStopPointDestinationList.takeFirst();
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





void DisplayLabelLcd::displayLabelViaPoints(QVector<StopPointDestination> currentDestinationPointList, VehicleState vehicleState)
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

    QString newViapointString=vykresliNacestneZastavkyText(currentDestinationPointList.at(vehicleState.currentStopIndex0).viaPoints, labelViaPointsScrolling->font().pixelSize(),mVdv301version);



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





void DisplayLabelLcd::lcdResizeLabels(int frameHeight)
{
    qDebug() <<  Q_FUNC_INFO;
    //this->show();
    ratioPixelPoint=frameHeight/1050.0;

    sizeIconConnectionDynamic=qFloor(sizeIconConnection*ratioPixelPoint);


    labelNastavVelikost(labelDestination,sizeFontDestination,ratioPixelPoint ); //100
    labelNastavVelikost(labelViaPointsScrolling,sizeFontViaPoints,ratioPixelPoint); //72

    poleLabelNastavVelikost(labelListStopPointName,sizeFontFollowing,ratioPixelPoint); //100

    poleLabelNastavVelikost(labelListConnectionLine,sizeFontTransferLine,ratioPixelPoint); //48
    poleLabelNastavSirku(labelListConnectionLine,ratioPixelPoint*sizeConnectionFrameWidth); //95
    poleLabelNastavVysku(labelListConnectionLine,ratioPixelPoint*sizeConnectionFrameHeight); //65

    poleLabelNastavVelikost(labelListConnectionDestination,sizeFontTransferDestination,ratioPixelPoint); //36
    poleLabelNastavVelikost(labelListConnectionPlatform,sizeFontTransferDestination,ratioPixelPoint); //36
    poleLabelNastavVelikost(labelListConnectionDeparture,sizeFontTransferDestination,ratioPixelPoint); //36

    labelNastavVelikost(labelClock,80,ratioPixelPoint); //80
    //  labelNastavVelikost(ui->label_textPres,30,ratioPixelPoint); //30
    //  labelNastavVelikost(ui->label_textVia ,30,ratioPixelPoint); //30

    /*
    labelVykreslovani.labelNastavVelikost(,,);
    labelVykreslovani.labelNastavVelikost(,,);
    labelVykreslovani.labelNastavVelikost(,,);
    labelVykreslovani.labelNastavVelikost(,,);
    */
    zmensiCisloLinkyLabel(labelLine);

}
