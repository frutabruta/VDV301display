#include "displaylabel.h"


#include <QMessageBox>


DisplayLabel::DisplayLabel()
{
    //    nahradIkonyFormat("", velikostPiktogramu,slozkaPiktogramu);

}

void DisplayLabel::naplnZmenaLabel(QString vstup, QLabel *stitek)
{
    qDebug()<<Q_FUNC_INFO;
    stitek->setText(vstup);
}


void DisplayLabel::ledDisplaySetDisplayContent(LedLabelDisplay &selectedDisplay)
{
    qDebug()<<Q_FUNC_INFO<<" "<<" displayContentCount:"<<selectedDisplay.displayContentList.count();



    if(selectedDisplay.displayContentList.isEmpty())
    {
        return; //display clear
    }
    else
    {
        if(selectedDisplay.ticker<selectedDisplay.displayContentList.length())
        {
            Vdv301DisplayContent selectedDisplayContent=selectedDisplay.displayContentList.at(selectedDisplay.ticker);
            QString lineText="";
            QString destinationTopRow="";
            QString destinationBottomRow="";

            if(selectedDisplayContent.lineInformation.lineNameList.isEmpty())
            {
                lineText="";
            }
            else
            {
                lineText=selectedDisplayContent.lineInformation.lineNameList.first().text;
            }

            switch (selectedDisplayContent.destination.destinationNameList.count()) {
            case 0:

                break;
            case 1:
                destinationTopRow=selectedDisplayContent.destination.destinationNameList.first().text;
                break;
            case 2:
                destinationTopRow=selectedDisplayContent.destination.destinationNameList.at(0).text;
                destinationBottomRow=selectedDisplayContent.destination.destinationNameList.at(1).text;
                break;

            default:
                break;
            }


            ledWriteToDisplay(selectedDisplay,lineText,destinationTopRow,destinationBottomRow);
            selectedDisplay.ticker++;
        }
        else
        {
            selectedDisplay.ticker=0;
            qDebug()<<"displayContent out of range";
        }
    }

}


void DisplayLabel::ledWriteToDisplay(LedLabelDisplay display,QString linka,QString horniRadek,QString dolniRadek)
{
    qDebug() <<  Q_FUNC_INFO;

    linka=InlineFormatParser::parseTextLed(linka);
    horniRadek=InlineFormatParser::parseTextLed(horniRadek);
    dolniRadek=InlineFormatParser::parseTextLed(dolniRadek);

    if (dolniRadek!="")
    {
        if(display.destinationLabel!=NULL)
        {
            display.destinationLabel->setVisible(false);
        }
        if(display.destination2Label!=NULL)
        {
            display.destination2Label->setVisible(true);
        }
        if(display.destination1Label!=NULL)
        {
            display.destination1Label->setVisible(true);
        }

    }
    else
    {
        if(display.destinationLabel!=NULL)
        {
            display.destinationLabel->setVisible(true);
        }
        if(display.destination2Label!=NULL)
        {
            display.destination2Label->setVisible(false);
        }
        if(display.destination1Label!=NULL)
        {
            display.destination1Label->setVisible(false);
        }

    }

    if(display.lineLabel!=NULL)
    {
        display.lineLabel->setText(linka);
    }
    if(display.destinationLabel!=NULL)
    {
        display.destinationLabel->setText(horniRadek);
    }
    if(display.destination1Label!=NULL)
    {
        display.destination1Label->setText(horniRadek);
    }
    if(display.destination2Label!=NULL)
    {
        display.destination2Label->setText(dolniRadek);
    }

}


QString DisplayLabel::vyrobTextZmenyPasma(QVector<FareZone> zPasem, QVector<FareZone> naPasma)
{
    qDebug()<<Q_FUNC_INFO;
    QString vysledek = "";
    vysledek += "prosím pozor! Změna tarifního pásma: " + SvgVykreslovani::pasmaDoStringu(zPasem) + "->" + SvgVykreslovani::pasmaDoStringu(naPasma);

    return vysledek;
}

void DisplayLabel::poleLabelNastavVelikost(QVector<QLabel *> labely, int bodovaVelikost, float pomerBodu)
{
    foreach (QLabel *label, labely)
    {
        QFont fontLabelu = label->font();

        int pixelSize = qFloor(pomerBodu * bodovaVelikost * 0.6);
        //qDebug()<<"label:"<<label->objectName()<<" pomer stran vyska pomer: "<<pomerBodu<<" pixelSize:"<<pixelSize;
        fontLabelu.setPointSize(pixelSize);
        //fontLabelu.setPixelSize(pixelSize);
        label->setFont(fontLabelu);
        //  label->font().setPointSize(pixelSize);
        //qDebug()<<"obsah: "<<label->style ;
    }
}

void DisplayLabel::labelNastavVelikost(QLabel *label, int bodovaVelikost, float pomerBodu)
{
    if(label!=NULL)
    {
        QFont fontLabelu = label->font();
        // qDebug()<<"pomer stran vyska pomer:"<<pomerBodu;
        fontLabelu.setPointSize(qFloor(pomerBodu * bodovaVelikost * 0.6));
        label->setFont(fontLabelu);
    }
    else
    {
        qDebug()<<"empty label pointer";
        return;
    }

}

void DisplayLabel::zmensiCisloLinkyLabel(QLabel *label)
{
    qDebug()<<Q_FUNC_INFO;
    if(label==NULL)
    {
        qDebug()<<"empty label pointer";
        return;
    }

    QFont puvodniFont = label->font();
    puvodniFont.setPixelSize(label->height());
    label->setFont(puvodniFont);

    int vyskaLabelu = label->height();
    int sirkaLabelu = label->width();

    int vyskaFontu = label->fontMetrics().boundingRect(label->text()).height();
    int sirkaFontu = label->fontMetrics().boundingRect(label->text()).width();

    qDebug() << "V labelu " << vyskaLabelu << " V Fontu " << vyskaFontu << " S labelu " << sirkaLabelu << " S fontu " << sirkaFontu;

    int counter = 0;
    while (((sirkaFontu > sirkaLabelu) || (vyskaFontu > vyskaLabelu)) && (counter < 4))
    {
        puvodniFont.setPixelSize(qRound(puvodniFont.pixelSize() * 0.90));

        vyskaFontu = label->fontMetrics().boundingRect(label->text()).height();
        sirkaFontu = label->fontMetrics().boundingRect(label->text()).width();
        label->setFont(puvodniFont);
        counter++;
    }

    /*
    int velikostFontuDefault=80;
    label->setFont(QFont("Roboto",velikostFontuDefault ));
   label->update();
    int pomer= int(sirkaFontu/sirkaLabelu);
    label->setFont(QFont("Roboto",velikostFontuDefault*pomer ));
   label->update();
*/
    /*
    QFont font("times", 24);
    QFontMetrics fm(font);
    int pixelsWide = fm.horizontalAdvance("What's the width of this text?");
    int pixelsHigh = fm.height();
    */
}

void DisplayLabel::naplnNazevCileLabel(QString vstup, QLabel *label)
{
    qDebug()<<Q_FUNC_INFO;

    if(label!=NULL)
    {
        label->setText(vstup);
    }
    else
    {
        qDebug()<<"label is not set";
    }

}

void DisplayLabel::naplnAnouncementLabel(QString vstup, QLabel *label)
{
    qDebug()<<Q_FUNC_INFO;
    label->setText(vstup);
    //ui->label_announcement->setText(vstup);
}

void DisplayLabel::obarviPozadiPristi(QString barvaPisma, QString barvaPozadi, QFrame *qframe)
{
    qDebug()<<Q_FUNC_INFO;
    //
    qframe->setStyleSheet("background-color :" + barvaPozadi + " ; color : " + barvaPisma + "; ");
    //  ui->frame_spodniRadek->setStyleSheet("background-color :"+barvaPozadi+" ; color : "+barvaPisma+"; ");
}

void DisplayLabel::poleLabelNastavSirku(QVector<QLabel *> seznamLabelu, int sirka)
{
    foreach (QLabel *label, seznamLabelu)
    {
        label->setMaximumWidth(sirka);
    }
}

void DisplayLabel::poleLabelNastavVysku(QVector<QLabel *> seznamLabelu, int vyska)
{
    foreach (QLabel *label, seznamLabelu)
    {
        label->setMaximumHeight(vyska);
    }
}

QString DisplayLabel::nahradMetro(QString linka, QString submode, int vyska)
{
    QString vysledek = linka;

    if (submode == "metro")
    {
        vysledek = "<html><head/><body><p><img src=\":/images/Underground" + linka + "\" height=\"" + QString::number(vyska) + "\" /></p></body></html>";
    }

    //<html><head/><body><p><img src=":/images/UndergroundA" height="50" /></p></body></html>
    qDebug() << "nahradMetro:" << vysledek;
    return vysledek;
}

QString DisplayLabel::vykresliNacestneZastavkyText(QVector<StopPoint> nacestneZastavky, int velikostPiktogramu, QString verze)
{
    qDebug()<<Q_FUNC_INFO;
    if (nacestneZastavky.count() == 0)
    {
        return "";
    }

    QString nacestyString = "";

    //  nacestyString+=  doplnPiktogramyBezZacatkuKonce(nacestneZastavky.at(0).NameLcd,nacestneZastavky.at(0).seznamPiktogramu,velikostPiktogramu);
    QString separator=" ";
    for (int i = 0; i < nacestneZastavky.count(); i++)
    {
        if(i==0)
        {
            separator="";
        }
        else
        {
            separator=" - ";
        }
        if (verze == "2.3")
        {
            nacestyString += separator + nahradIconPiktogramem(nacestneZastavky.at(i).NameLcd, velikostPiktogramu, slozkaPiktogramu);
        }
        else
        {
            nacestyString += separator + doplnPiktogramyBezZacatkuKonce(nacestneZastavky.at(i).NameLcd, nacestneZastavky.at(i).iconList, velikostPiktogramu);
        }
    }

    QString htmlZacatek = "<html><head/><body><p>";
    QString htmlKonec = "</p></body></html>";

    QString vysledek = htmlZacatek + nacestyString + htmlKonec;
    qDebug() << "vypis radku nacestnych zastavek text html" << vysledek;
    return vysledek;
}

QString DisplayLabel::doplnPiktogramyBezZacatkuKonce(QString nazevZastavky, QVector<QString> seznamPiktogramu, int vyskaObrazku)
{
    QString vystup = "";
    // int vyskaObrazku=40; //konstanta v px, ovlivnuje vysku piktogramu
    QString htmlObrazky = "";

    foreach (QString nazevPiktogramu, seznamPiktogramu)
    {
        htmlObrazky += "   <img  src=\":/images/" + nazevPiktogramu + "\"height=\"" + QString::number(vyskaObrazku) + "\"  >";
    }

    vystup = nazevZastavky + htmlObrazky;
    return vystup;
}

QString DisplayLabel::textNaPiktogramOznameni(QString announcementType, int vyskaObrazku)
{
    QString vystup = "";
    // int vyskaObrazku=40; //konstanta v px, ovlivnuje vysku piktogramu
    QString htmlObrazky = "";
    if (announcementType == "")
    {
        return "";
    }

    htmlObrazky += "<img  src=\":/images/" + announcementType + "\" height=\"" + QString::number(vyskaObrazku) + "\"  >";

    qDebug() << "nastavuju piktogram oznameni:" << htmlObrazky;

    vystup = htmlObrazky;
    return vystup;
}

QString DisplayLabel::zabalHtmlDoZnacek(QString vstup)
{
    return "<html><head/><body><p>" + vstup + "</p></body></html>";
}

int DisplayLabel::minimum(int cislo1, int cislo2)
{
    if (cislo1 < cislo2)
    {
        return cislo1;
    }
    return cislo2;
}

void DisplayLabel::vykresliNacestneForce(QVector<StopPointDestination> globalniSeznamZastavek, VehicleState stavSystemu, QLabel *label, QString verze)
{
    qDebug() << Q_FUNC_INFO;

    //label_nacestne
    if (globalniSeznamZastavek.isEmpty())
    {
        label->setText("");
        return;
    }

    /*
    QString oldInput=label->text();
    if(newInput!=oldInput )
    {

    }*/

    label->setText(" ");
    int velikostTextu = label->font().pixelSize();
    QString newInput = vykresliNacestneZastavkyText(globalniSeznamZastavek.at(stavSystemu.currentStopIndex0).viaPoints, velikostTextu, verze);

    label->setText(newInput);

}

void DisplayLabel::vymazPoleLabelu(QVector<QLabel *> vstup)
{
    foreach (QLabel *odkaz, vstup)
    {
        odkaz->setText("");
    }
}

QString DisplayLabel::nahradIconPiktogramem(QString vstup, int vyskaObrazku, QString slozka)
{
    // bude nahrazeno v inlineformatparser, jen kvuli nacestnym zastavkam
    qDebug() << Q_FUNC_INFO;
    QString vystup = "";

    QDomDocument dokument;
    dokument.setContent("<wrapper>" + vstup + "</wrapper>");

    QDomNodeList seznamIkon = dokument.firstChildElement().elementsByTagName("icon");
    qDebug() << dokument.toByteArray();

    qDebug() << "pocet ikon: " << seznamIkon.count();

    QString jenNazev = dokument.firstChildElement().firstChild().nodeValue();
    vystup = jenNazev;

    /*
    labelVykreslovani.zabalHtmlDoZnacek(labelVykreslovani.doplnPiktogramyBezZacatkuKonce(aktualniZastavka.NameLcd,aktualniZastavka.seznamPiktogramu,seznamLabelNazevZastavky.at(i)->font().pixelSize() ))
*/
    for (int i = 0; i < seznamIkon.length(); i++)
    {
        QDomNode ikona = seznamIkon.at(i);
        QString nazev = ikona.attributes().namedItem("type").firstChild().nodeValue();
        QString alternativniText = ikona.firstChild().nodeValue();
        qDebug() << nazev;

        QString cesta = slozka + "/" + nazev + ".svg";
        qDebug() << "cesta k souboru:" << cesta;

        // if(QFile::exists(":/images/"+nazev))
        if (QFile::exists(cesta))
        {
            //resources  vystup+="<img  src=\":/images/"+nazev+"\"height=\""+QString::number(vyskaObrazku)+"\"  >";

            vystup += "<img  src=\"" + cesta + "\" height=\"" + QString::number(vyskaObrazku) + "\"  >";
            qDebug() << "resource existuje";
        }
        else
        {
            vystup += alternativniText;
            qDebug() << "resource neexistuje";
        }
    }

    // <icon type="c_RequestStop" >ŕ</icon>

    return vystup;
}

QString DisplayLabel::replaceIconOuterDisplays(QString vstup)
{
    // bude nahrazeno v inlineformatparser, jen kvuli nacestnym zastavkam
    qDebug() << Q_FUNC_INFO;
    QString vystup = "";

    QDomDocument dokument;
    dokument.setContent("<wrapper>" + vstup + "</wrapper>");

    QDomNodeList seznamIkon = dokument.firstChildElement().elementsByTagName("icon");
    qDebug() << dokument.toByteArray();

    qDebug() << "pocet ikon: " << seznamIkon.count();

    QString jenNazev = dokument.firstChildElement().firstChild().nodeValue();
    vystup = jenNazev;

    /*
    labelVykreslovani.zabalHtmlDoZnacek(labelVykreslovani.doplnPiktogramyBezZacatkuKonce(aktualniZastavka.NameLcd,aktualniZastavka.seznamPiktogramu,seznamLabelNazevZastavky.at(i)->font().pixelSize() ))
*/
    for (int i = 0; i < seznamIkon.length(); i++)
    {
        QDomNode ikona = seznamIkon.at(i);
        QString nazev = ikona.attributes().namedItem("type").firstChild().nodeValue();
        QString alternativniText = ikona.firstChild().nodeValue();
        qDebug() << nazev;
        vystup += alternativniText;

    }

    // <icon type="c_RequestStop" >ŕ</icon>

    return vystup;
}


int DisplayLabel::isInRange(int index, int limit)
{
    if((index<limit)&&(index>=0))
    {

        return 1;
    }
    else
    {
        QMessageBox msgBox;
        QString errorMessage="value"+QString::number(index)+" is out of range "+ QString::number(limit);
        msgBox.setText(errorMessage);
        qDebug()<<" errorMessage";
        msgBox.exec();


        return 0;
    }

}
QString DisplayLabel::fareZoneListToQString(QVector<FareZone> seznamPasem)
{
    qDebug()<<Q_FUNC_INFO;
    QString vysledek;
    if (seznamPasem.size()>0)
    {
        vysledek=seznamPasem.at(0).name;
        for (int i=1;i<seznamPasem.size();i++)
        {
            vysledek+=","+seznamPasem.at(i).name;
        }
    }
    qDebug()<<"vysledek pasmaDoStringu"<<vysledek;
    return vysledek;
}

void DisplayLabel::setVdv301version(const QString &newVdv301version)
{
    mVdv301version = newVdv301version;
}

QString DisplayLabel::vdv301version() const
{
    return mVdv301version;
}
