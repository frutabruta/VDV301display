#include "displaylabellcd2_3cz1_0.h"

DisplayLabelLcd2_3CZ1_0::DisplayLabelLcd2_3CZ1_0() {}



void DisplayLabelLcd2_3CZ1_0::displayLabelStopList(Vdv301Trip2_3CZ1_0 firstTrip, Vdv301Trip2_3CZ1_0 secondTrip, int currentStopIndex)
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
        QLabel* labelFarezoneBottom=nullptr;
        QLabel* labelFarezoneTop=nullptr;

        if(!labelListStopPointName.isEmpty())
        {
            labelStopName=labelListStopPointName.at(i);
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
    }
}



void DisplayLabelLcd2_3CZ1_0::displayLabelStopFareZone(Vdv301AllData2_3CZ1_0 allData)
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
    displayLabelStopList(firstTrip,followingTrip,allData.currentStopIndex);

}



void DisplayLabelLcd2_3CZ1_0::displayLabelStopPoint(Vdv301StopPoint2_3CZ1_0 selectedStopPointDestination, bool isFollowingTrip, QLabel* labelStopName, QLabel* labelFarezoneBottom, QLabel* labelFarezoneTop)
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

}


void DisplayLabelLcd2_3CZ1_0::displayLabelShowAnnoucement(QVector<Vdv301InternationalText> additionalTextMessageList,QVector<Vdv301InternationalText> additionalTextMessage1List,QVector<Vdv301InternationalText> additionalTextMessage2List, QVector<Vdv301InternationalText> additionalTextMessage3List,QVector<Vdv301InternationalText> additionalTextMessage4List)
{
    qDebug() <<  Q_FUNC_INFO;

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


        if((stackedWidget_onService!=NULL)&&(pageRoute!=NULL))
        {
            stackedWidget_onService->setCurrentWidget(pageRoute);
        }
        if((stackedWidget_middle!=NULL)&&(pageAdditionalTextMessage!=NULL))
        {
            stackedWidget_middle->setCurrentWidget(pageAdditionalTextMessage);
        }

        if(pageAdditionalTextMessage!=NULL)
        {
            pageCycleList.push_back(pageAdditionalTextMessage);
        }
        else
        {
            qDebug("pageAnnouncement pointer is NULL");
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


        if((stackedWidget_onService!=NULL)&&(pageRoute!=NULL))
        {
            stackedWidget_onService->setCurrentWidget(pageRoute);
        }
        if((stackedWidget_middle!=NULL)&&(pageFareZoneChange!=NULL))
        {
            stackedWidget_middle->setCurrentWidget(pageFareZoneChange);
        }

        if(pageAdditionalTextMessage!=NULL)
        {
            pageCycleList.push_back(pageFareZoneChange);
        }
        else
        {
            qDebug("pageAnnouncement pointer is NULL");
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


        if((stackedWidget_onService!=NULL)&&(pageLineChange!=NULL))
        {
            stackedWidget_onService->setCurrentWidget(pageLineChange);
        }

        if(pageAdditionalTextMessage!=NULL)
        {
            pageCycleList.push_back(pageLineChange);
        }
        else
        {
            qDebug("pageAnnouncement pointer is NULL");
        }

        //    pageCycleList.push_back(page ui->page_oznameni);
    }
    else
    {
        qDebug()<<"unknown additionalTextMessage4 value";
    }


}


bool DisplayLabelLcd2_3CZ1_0::labelSetTextBgInline(QLabel *label, QString text, bool ignoreBackground )
{


    if(label==NULL)
    {
        qDebug()<<"DisplayLabel::labelSetTextSafe failed";
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


