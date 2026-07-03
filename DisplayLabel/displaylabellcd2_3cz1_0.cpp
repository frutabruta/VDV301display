#include "displaylabellcd2_3cz1_0.h"

Q_LOGGING_CATEGORY(DisplayLabelLcd2_3CZ1_0Log, "DisplayLabelLcd2_3CZ1_0")


DisplayLabelLcd2_3CZ1_0::DisplayLabelLcd2_3CZ1_0() {}

void DisplayLabelLcd2_3CZ1_0::displayLabelViaPoints(QVector<Vdv301ViaPoint2_3CZ1_0> viaPoints)
{
    qCDebug(DisplayLabelLcd2_3CZ1_0Log) <<  Q_FUNC_INFO;
    if(labelViaPointsScrolling==nullptr)
    {
        qCDebug(DisplayLabelLcd2_3CZ1_0Log)<<"NULL label";
        return;
    }

    /*
    if(currentDestinationPointList.isEmpty())
    {
        ui->label_nacestne->setText("");
        return;
    }
    */

    QString newViapointString=joinViaPointsToText(viaPoints, labelViaPointsScrolling->font().pixelSize());

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



void DisplayLabelLcd2_3CZ1_0::displayLabelStopList(Vdv301Trip2_3CZ1_0 firstTrip, Vdv301Trip2_3CZ1_0 secondTrip, int currentStopIndex,  QVector<DisplayLabelStopGroup> labelListStopGroup)
{
    qCDebug(DisplayLabelLcd2_3CZ1_0Log) <<  Q_FUNC_INFO;

    Vdv301Trip2_3CZ1_0 firstTripCopy=firstTrip;
    Vdv301Trip2_3CZ1_0 secondTripCopy=secondTrip;

    if(firstTripCopy.stopPointList.isEmpty())
    {
        return ;
    }

    firstTripCopy.stopPointList.remove(0,currentStopIndex-1);

    qCDebug(DisplayLabelLcd2_3CZ1_0Log)<<"number of labels: "<<labelListStopGroup.count();


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
                qCDebug(DisplayLabelLcd2_3CZ1_0Log)<<"pro label uz nezbyly zastavky";
                selectedGroup.eraseContent();
            }
        }

        displayLabelStopPoint(aktualniZastavka,navaznySpoj,selectedGroup.labelStopName,selectedGroup.labelFarezoneTop,selectedGroup.labelFarezoneBottom);
        labelSetTextSafe(selectedGroup.labelPlatform,aktualniZastavka.platform);

    }


}


void DisplayLabelLcd2_3CZ1_0::displayLabelStopFareZone(Vdv301AllData2_3CZ1_0 allData)
{
    qCDebug(DisplayLabelLcd2_3CZ1_0Log) <<  Q_FUNC_INFO;

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
    displayLabelStopList(firstTrip,followingTrip,allData.currentStopIndex,labelListStopGroup);

}



void DisplayLabelLcd2_3CZ1_0::displayLabelStopPoint(Vdv301StopPoint2_3CZ1_0 selectedStopPointDestination, bool isFollowingTrip, QLabel* labelStopName, QLabel* labelFarezoneBottom, QLabel* labelFarezoneTop, bool invert)
{
    QVector<Vdv301InternationalText> fareZoneList= selectedStopPointDestination.fareZoneList;


    Vdv301InternationalText joinedStopName=vdv301InternationalTextJoinAll(selectedStopPointDestination.stopNameList,"\n");
    if(labelStopName!=nullptr)
    {
        labelSetTextSafe(labelStopName,inlineFormatParser.parseTextLcd(joinedStopName.text, labelStopName->font().pixelSize(),slozkaPiktogramu) )    ;
    }

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
        labelSetTextSafe(labelFarezoneBottom,"");
        break;
    case 1:
    {

        if(labelFarezoneBottom!=nullptr)
        {
            labelFarezoneBottom->setText(fareZoneList.at(0).text);
            labelFarezoneBottom->setFont(fontLabelFareZoneLarge);
        }

        if(labelFarezoneTop!=nullptr)
        {
            labelFarezoneTop->hide();
            labelFarezoneTop->setFont(fontLabelFareZoneLarge);
        }

        break;
    }

    case 2:
    {

        if(labelFarezoneBottom!=nullptr)
        {
            labelSetTextSafe(labelFarezoneBottom,fareZoneList.at(0).text);
            labelFarezoneBottom->setFont(fontLabelFareZoneSmall );

        }

        if(labelFarezoneTop!=nullptr)
        {
            labelFarezoneTop->show();
            labelFarezoneTop->setFont(fontLabelFareZoneSmall );
            labelSetTextSafe(labelFarezoneTop,fareZoneList.at(1).text);
        }


        break;

    }


    case 3:
        //prepared for case of 3 systems
        break;
    default:
        break;
    }


    if(isFollowingTrip==false)
    {
        labelSetStylesheetSafe(labelStopName,"color:"+barvyLinek.barva_bila_255_255_255+";");
        labelSetStylesheetSafe(labelFarezoneTop,"color:"+barvyLinek.barva_bila_255_255_255+";");
        labelSetStylesheetSafe(labelFarezoneBottom,"color:"+barvyLinek.barva_bila_255_255_255+";");
    }
    else
    {
        labelSetStylesheetSafe(labelStopName,"color:"+barvyLinek.barva_PozadiC_100_100_100+";");
        labelSetStylesheetSafe(labelFarezoneTop,"color:"+barvyLinek.barva_PozadiC_100_100_100+";");
        labelSetStylesheetSafe(labelFarezoneBottom,"color:"+barvyLinek.barva_PozadiC_100_100_100+";");
    }

    if(invert)
    {
        labelSetStylesheetSafe(labelStopName,"color:"+barvyLinek.barva_PozadiA_25_25_25+";");
        labelSetStylesheetSafe(labelFarezoneTop,"color:"+barvyLinek.barva_PozadiA_25_25_25+";");
        labelSetStylesheetSafe(labelFarezoneBottom,"color:"+barvyLinek.barva_PozadiA_25_25_25+";");
    }

}


void DisplayLabelLcd2_3CZ1_0::displayLabelShowAnnoucement(QVector<Vdv301InternationalText> additionalTextMessageList,QVector<Vdv301InternationalText> additionalTextMessage1List,QVector<Vdv301InternationalText> additionalTextMessage2List, QVector<Vdv301InternationalText> additionalTextMessage3List,QVector<Vdv301InternationalText> additionalTextMessage4List)
{
    qCDebug(DisplayLabelLcd2_3CZ1_0Log) <<  Q_FUNC_INFO;

    labelSetTextSafe(labelAnnouncementLeft,"");
    labelSetTextSafe(labelAnnouncementRight,"");


    labelSetTextSafe(labelFareZoneAnnouncementLeft,"");
    labelSetTextSafe(labelFareZoneAnnouncementRight,"");
    labelSetTextSafe(labelFareZoneChangeFrom,"");
    labelSetTextSafe(labelFareZoneChangeTo,"");

    labelSetTextSafe(labelLineChangeAnnouncementLeft,"");
    labelSetTextSafe(labelLineChangeAnnouncementRight,"");
    labelSetTextSafe(labelLineChangeAnnouncementFrom,"");
    labelSetTextSafe(labelLineChangeAnnouncementTo,"");


    if(additionalTextMessage4List.isEmpty())
    {
        if(!additionalTextMessage1List.isEmpty() )
        {
            //labelAnnouncementLeft->setText(  additionalTextMessage1List.first().text);
            //  labelSetTextSafe( labelAnnouncementLeft,inlineFormatParser.parseTextLcdOuter(additionalTextMessage1List.first().text,  labelAnnouncementLeft->font().pixelSize(),slozkaPiktogramu) );
            labelSetTextBgInline(labelAnnouncementLeft,additionalTextMessage1List.first().text);
        }
        else
        {
            labelSetTextSafe(labelAnnouncementLeft,"");
        }

        if(!additionalTextMessageList.isEmpty() )
        {
            //labelSetTextSafe( labelAnnouncementRight,inlineFormatParser.parseTextLcdOuter(additionalTextMessageList.first().text,  labelAnnouncementRight->font().pixelSize(),slozkaPiktogramu) );
            labelSetTextBgInline(labelAnnouncementRight,additionalTextMessageList.first().text);
        }
        else
        {
            labelSetTextSafe( labelAnnouncementRight,"");
        }

        // ui->label_oznTextEn->setText("");


        if((stackedWidget_onService!=nullptr)&&(pageRoute!=nullptr))
        {
            stackedWidget_onService->setCurrentWidget(pageRoute);
        }
        if((stackedWidget_middle!=nullptr)&&(pageAdditionalTextMessage!=nullptr))
        {
            stackedWidget_middle->setCurrentWidget(pageAdditionalTextMessage);
        }

        if(pageAdditionalTextMessage!=nullptr)
        {
            pageCycleList.push_back(pageAdditionalTextMessage);
        }
        else
        {
            qDebug("pageAnnouncement pointer is nullptr");
        }

        //    pageCycleList.push_back(page ui->page_oznameni);

    }
    else if(additionalTextMessage4List.first().text=="FareZoneChange")
    {
        if(!additionalTextMessage1List.isEmpty() )
        {
            //labelAnnouncementLeft->setText(  additionalTextMessage1List.first().text);
            //  labelSetTextSafe( labelAnnouncementLeft,inlineFormatParser.parseTextLcdOuter(additionalTextMessage1List.first().text,  labelAnnouncementLeft->font().pixelSize(),slozkaPiktogramu) );
            labelSetTextBgInline(labelFareZoneAnnouncementLeft,additionalTextMessage1List.first().text);
        }
        else
        {
            labelSetTextSafe(labelFareZoneAnnouncementLeft,"");
        }

        if(!additionalTextMessageList.isEmpty() )
        {
            //labelSetTextSafe( labelAnnouncementRight,inlineFormatParser.parseTextLcdOuter(additionalTextMessageList.first().text,  labelAnnouncementRight->font().pixelSize(),slozkaPiktogramu) );
            labelSetTextBgInline(labelFareZoneAnnouncementRight,additionalTextMessageList.first().text);
        }
        else
        {
            labelSetTextSafe(labelFareZoneAnnouncementRight,"");
        }

        if(!additionalTextMessage2List.isEmpty() )
        {
            //labelSetTextSafe( labelAnnouncementRight,inlineFormatParser.parseTextLcdOuter(additionalTextMessageList.first().text,  labelAnnouncementRight->font().pixelSize(),slozkaPiktogramu) );
            labelSetTextBgInline(labelFareZoneChangeFrom,additionalTextMessage2List.first().text,true);
        }
        else
        {
            labelSetTextSafe(labelFareZoneChangeFrom,"");
        }

        if(!additionalTextMessage3List.isEmpty() )
        {
            //labelSetTextSafe( labelAnnouncementRight,inlineFormatParser.parseTextLcdOuter(additionalTextMessageList.first().text,  labelAnnouncementRight->font().pixelSize(),slozkaPiktogramu) );
            labelSetTextBgInline(labelFareZoneChangeTo,additionalTextMessage3List.first().text,true);
        }
        else
        {
            labelSetTextSafe(labelFareZoneChangeTo,"");
        }

        // ui->label_oznTextEn->setText("");


        if((stackedWidget_onService!=nullptr)&&(pageRoute!=nullptr))
        {
            stackedWidget_onService->setCurrentWidget(pageRoute);
        }
        if((stackedWidget_middle!=nullptr)&&(pageFareZoneChange!=nullptr))
        {
            stackedWidget_middle->setCurrentWidget(pageFareZoneChange);
        }

        if(pageAdditionalTextMessage!=nullptr)
        {
            pageCycleList.push_back(pageFareZoneChange);
        }
        else
        {
            qDebug("pageAnnouncement pointer is nullptr");
        }

        //    pageCycleList.push_back(page ui->page_oznameni);
    }
    else if(additionalTextMessage4List.first().text=="LineChange")
    {
        if(!additionalTextMessageList.isEmpty() )
        {
            //labelSetTextSafe( labelAnnouncementRight,inlineFormatParser.parseTextLcdOuter(additionalTextMessageList.first().text,  labelAnnouncementRight->font().pixelSize(),slozkaPiktogramu) );
            labelSetTextBgInline(labelLineChangeAnnouncementRight,additionalTextMessageList.first().text,true);
        }
        else
        {
            labelSetTextSafe(labelLineChangeAnnouncementRight,"");
        }

        if(!additionalTextMessage1List.isEmpty() )
        {
            //labelAnnouncementLeft->setText(  additionalTextMessage1List.first().text);
            //  labelSetTextSafe( labelAnnouncementLeft,inlineFormatParser.parseTextLcdOuter(additionalTextMessage1List.first().text,  labelAnnouncementLeft->font().pixelSize(),slozkaPiktogramu) );
            labelSetTextBgInline(labelLineChangeAnnouncementLeft,additionalTextMessage1List.first().text,true);
        }
        else
        {
            labelSetTextSafe(labelLineChangeAnnouncementLeft,"");
        }


        if(!additionalTextMessage2List.isEmpty() )
        {
            //labelSetTextSafe( labelAnnouncementRight,inlineFormatParser.parseTextLcdOuter(additionalTextMessageList.first().text,  labelAnnouncementRight->font().pixelSize(),slozkaPiktogramu) );
            labelSetTextBgInline(labelLineChangeAnnouncementFrom,additionalTextMessage2List.first().text,true);
        }
        else
        {
            labelSetTextSafe(labelLineChangeAnnouncementFrom,"");
        }


        if(!additionalTextMessage2List.isEmpty() )
        {
            //labelSetTextSafe( labelAnnouncementRight,inlineFormatParser.parseTextLcdOuter(additionalTextMessageList.first().text,  labelAnnouncementRight->font().pixelSize(),slozkaPiktogramu) );
            labelSetTextBgInline(labelLineChangeAnnouncementTo,additionalTextMessage3List.first().text,true);
        }
        else
        {
            labelSetTextSafe(labelLineChangeAnnouncementTo,"");
        }


        // ui->label_oznTextEn->setText("");


        if((stackedWidget_onService!=nullptr)&&(pageLineChange!=nullptr))
        {
            stackedWidget_onService->setCurrentWidget(pageLineChange);
        }

        if(pageAdditionalTextMessage!=nullptr)
        {
            pageCycleList.push_back(pageLineChange);
        }
        else
        {
            qDebug("pageAnnouncement pointer is nullptr");
        }

        //    pageCycleList.push_back(page ui->page_oznameni);
    }
    else
    {
        qCDebug(DisplayLabelLcd2_3CZ1_0Log)<<"unknown additionalTextMessage4 value";
    }


}

QVector<Vdv301DisplayContent2_3CZ1_0> DisplayLabelLcd2_3CZ1_0::filterVdv301DisplayContentByClass(QVector<Vdv301DisplayContent2_3CZ1_0> displayContentList, DisplayContentClass displayContentType)
{
    QVector<Vdv301DisplayContent2_3CZ1_0> output;
    foreach (Vdv301DisplayContent2_3CZ1_0 displayContent, displayContentList)
    {

        if(displayContent.displayContentType==displayContentType)
        {
            output<<displayContent;
        }

    }

    return output;
}

bool DisplayLabelLcd2_3CZ1_0::labelSetTextBgInline(QLabel *label, QString text, bool ignoreBackground )
{


    if(label==nullptr)
    {
        qCDebug(DisplayLabelLcd2_3CZ1_0Log)<<"DisplayLabel::labelSetTextSafe failed";
        return false;
    }

    else
    {
        QXmlStreamReader xmlReader("<wrapper>"+text+"</wrapper>");


        QString barvaPozadi="";
        QString result=inlineFormatParser.parseTextLcdOuter(text,100,slozkaPiktogramu,barvaPozadi);


        QString barvaPozadiCss="background-color:"+barvaPozadi+";";

        if(!ignoreBackground)
        {
            if(barvaPozadi!="")
            {
                label->setStyleSheet(barvaPozadiCss);
            }
            else
            {
                label->setStyleSheet("");
            }
        }


        label->setText(result);
    }
    return true;
}


QString DisplayLabelLcd2_3CZ1_0::joinViaPointsToText(QVector<Vdv301ViaPoint2_3CZ1_0> viaPoints, int iconSize)
{
    qCDebug(DisplayLabelLcd2_3CZ1_0Log)<<Q_FUNC_INFO;
    if (viaPoints.count() == 0)
    {
        return "";
    }

    QString viapointsString = "";

    //  nacestyString+=  doplnPiktogramyBezZacatkuKonce(nacestneZastavky.at(0).NameLcd,nacestneZastavky.at(0).seznamPiktogramu,velikostPiktogramu);
    QString separator=" ";


    QStringList viaPointStringList;
    foreach(Vdv301ViaPoint viaPoint, viaPoints)
    {
        Vdv301InternationalText viaPointNameJoin=vdv301InternationalTextJoinAll(viaPoint.placeNameList," x ") ;
        // viaPointStringList<<viaPointNameJoin.text;
        viaPointStringList<<nahradIconPiktogramem(viaPointNameJoin.text, iconSize, slozkaPiktogramu);
    }
    viapointsString = viaPointStringList.join(" - ");

    QString result = zabalHtmlDoZnacek(viapointsString);
    qCDebug(DisplayLabelLcd2_3CZ1_0Log) << "vypis radku nacestnych zastavek text html" << result;

    return result;
}
