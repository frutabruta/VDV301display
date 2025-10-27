#include "displaylabellcd.h"

Q_LOGGING_CATEGORY(DisplayLabelLcdLog, "DisplayLabelLcd")

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

void DisplayLabelLcd::displayLabelDestination(QString nazev)
{
    qCDebug(DisplayLabelLcdLog) <<  Q_FUNC_INFO;


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

void DisplayLabelLcd::displayLabelDestinationFollowing(QString nazev)
{
    qCDebug(DisplayLabelLcdLog) <<  Q_FUNC_INFO;


    labelSetTextSafe(labelDestinationFollowing,nazev);
    /* if(cisSubscriber.verze()=="2.3")
    {
       labelVykreslovani.naplnNazevCileLabel(labelVykreslovani.inlineFormatParser.vyparsujText(nazev, ui->Lcil->font().pixelSize(),labelVykreslovani.slozkaPiktogramu), ui->Lcil);

    }
    else
    {

    }
*/
}





void DisplayLabelLcd::displayLabelDrawLineNumber2_4(QString lineName, QLabel* label, int velikostPiktogramu,bool prestup)
{
    qCDebug(DisplayLabelLcdLog)<<Q_FUNC_INFO;


    QString linkaStyleSheetStandard="font-weight: bold; background-color:#ffffff; color:#000000; padding: 0px; margin: 0px; ";

    if(prestup)
    {
        linkaStyleSheetStandard+="border-radius:6px;padding: 0px; ";
    }


    QString linkaStyleSheetPiktogram="border-radius:6px; padding: 0px; margin: 0px; font-weight: bold;";


    if(label!=nullptr)
    {
        labelSetStylesheetSafe(label,linkaStyleSheetStandard);

        QString vyslednyText= inlineFormatParser.parseTextLcd(lineName, label->font().pixelSize(),slozkaPiktogramu);
        labelSetTextSafe(label,vyslednyText);

        qCDebug(DisplayLabelLcdLog).noquote()<<"obsah pole linky: "<<vyslednyText;

        label->show();
    }

}

void DisplayLabelLcd::displayLabelEraseInformation()
{
    qCDebug(DisplayLabelLcdLog) <<  Q_FUNC_INFO;
    labelSetTextSafe(labelDestination,"");
    labelSetTextSafe(labelDestination,"");

    //   ui->label_nacestne->setText("");



    if(frameFollowingTrip!=nullptr)
    {
        frameFollowingTrip->hide();
    }



  //  vymazPoleLabelu(labelListStopPointName);
  //  vymazPoleLabelu(labelListFareZoneUpper);
  //  vymazPoleLabelu(labelListFareZoneLower);
    //obrazovka prestupu
  //  vymazPoleLabelu(labelListConnectionDestination);
  //  vymazPoleLabelu(labelListConnectionLine);
  //  vymazPoleLabelu(labelListConnectionPlatform);
  //  vymazPoleLabelu(labelListConnectionDeparture);

    timerLabelPageSwitch.stop();
    pageCycleList.clear();
    // pageCycleList.push_back(ui->page_hlavni_2);
}









void DisplayLabelLcd::displayLabelLineName(QString lineName)
{
    qCDebug(DisplayLabelLcdLog) <<  Q_FUNC_INFO;
    displayLabelDrawLineNumber2_4(lineName,labelLine, qFloor(ratioPixelPoint*200),false);
}

void DisplayLabelLcd::displayLabelLineNameFollowing(QString lineName)
{
    qCDebug(DisplayLabelLcdLog) <<  Q_FUNC_INFO;
    displayLabelDrawLineNumber2_4(lineName,labelLineFollowing, qFloor(ratioPixelPoint*200),false);


}



void DisplayLabelLcd::lcdResizeLabels(int frameHeight)
{
    qCDebug(DisplayLabelLcdLog) <<  Q_FUNC_INFO;
    //this->show();
    ratioPixelPoint=frameHeight/1050.0;

    sizeIconConnectionDynamic=qFloor(sizeIconConnection*ratioPixelPoint);


    labelNastavVelikost(labelDestination,sizeFontDestination,ratioPixelPoint ); //100
    labelNastavVelikost(labelViaPointsScrolling,sizeFontViaPoints,ratioPixelPoint); //72

    //poleLabelNastavVelikost(labelListStopPointName,sizeFontFollowing,ratioPixelPoint); //100

  //  poleLabelNastavVelikost(labelListConnectionLine,sizeFontTransferLine,ratioPixelPoint); //48
  //  poleLabelNastavSirku(labelListConnectionLine,ratioPixelPoint*sizeConnectionFrameWidth); //95
  //  poleLabelNastavVysku(labelListConnectionLine,ratioPixelPoint*sizeConnectionFrameHeight); //65

   // poleLabelNastavVelikost(labelListConnectionDestination,sizeFontTransferDestination,ratioPixelPoint); //36
   // poleLabelNastavVelikost(labelListConnectionPlatform,sizeFontTransferDestination,ratioPixelPoint); //36
   // poleLabelNastavVelikost(labelListConnectionDeparture,sizeFontTransferDestination,ratioPixelPoint); //36

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
