#include "displaylabellcd2_3cz1_0.h"

DisplayLabelLcd2_3CZ1_0::DisplayLabelLcd2_3CZ1_0() {}



void DisplayLabelLcd2_3CZ1_0::displayLabelStopList(Vdv301Trip2_3CZ1_0 firstTrip, Vdv301Trip2_3CZ1_0 secondTrip, int currentStopIndex)
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
        Vdv301StopPoint2_3CZ1_0 aktualniZastavka;
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
    // PasmoveDvojiceLcd pasmoveDvojiceLcd;

    QVector<Vdv301InternationalText> fareZoneList= selectedStopPointDestination.fareZoneList;




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
        labelFarezoneBottom->setText(fareZoneList.at(0).text);
        labelFarezoneBottom->setFont(fontLabelFareZoneLarge);

        labelFarezoneTop->hide();
        labelFarezoneTop->setFont(fontLabelFareZoneLarge);
        break;
    case 2:
        labelFarezoneBottom->setText(fareZoneList.at(0).text);
        labelFarezoneBottom->setFont(fontLabelFareZoneSmall );

        labelFarezoneTop->show();
        labelFarezoneTop->setFont(fontLabelFareZoneSmall );
        labelFarezoneTop->setText(fareZoneList.at(1).text);

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


void DisplayLabelLcd2_3CZ1_0::displayLabelShowAnnoucement(QVector<Vdv301InternationalText> additionalTextMessageList,QVector<Vdv301InternationalText> additionalTextMessage1List,QVector<Vdv301InternationalText> additionalTextMessage2List, QVector<Vdv301InternationalText> additionalTextMessage3List,QVector<Vdv301InternationalText> additionalTextMessage4List)
{
    qDebug() <<  Q_FUNC_INFO;

    labelSetTextSafe(labelAnnouncementLeft,"");
    labelSetTextSafe(labelAnnouncementRight,"");


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


bool DisplayLabelLcd2_3CZ1_0::labelSetTextBgInline(QLabel *label, QString text)
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

        if(barvaPozadi!="")
        {
            label->setStyleSheet(barvaPozadiCss);
        }
        else
        {
            label->setStyleSheet("");
        }

        label->setText(result);
    }
    return true;
}


