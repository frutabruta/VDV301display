#include "displaylabelled.h"


Q_LOGGING_CATEGORY(DisplayLabelLedLog, "DisplayLabelLed")

DisplayLabelLed::DisplayLabelLed() {}


void DisplayLabelLed::initializeFonts()
{
    qCDebug(DisplayLabelLedLog) <<  Q_FUNC_INFO;
    fontLed1.setFamily("21-PID 1");
    fontLed1.setPointSize(65);

    fontLed3.setFamily("21-PID 3");
    fontLed3.setPointSize(65);

    fontLed3v.setFamily("pid 3v");
    fontLed3v.setPointSize(65);

    fontLed5.setFamily("21-PID 5");
    fontLed5.setPointSize(65);

    fontLed8.setFamily("21-PID 8");
    fontLed8.setPointSize(65);

    fontLed10.setFamily("21-PID 10");
    fontLed10.setPointSize(65);
}


void DisplayLabelLed::ledUpdateDisplayedInformationFromDisplayContentList2_3(QVector<Vdv301DisplayContent> displayContentListAll )
{
    //new approach to display viapoint from DisplayContent
    qCDebug(DisplayLabelLedLog) <<  Q_FUNC_INFO;


    QVector<Vdv301DisplayContent> displayContentListFront;
    QVector<Vdv301DisplayContent> displayContentListSide;
    QVector<Vdv301DisplayContent> displayContentListRear;
    QVector<Vdv301DisplayContent> displayContentListInterior;
    QVector<Vdv301DisplayContent> displayContentListLcd; //might be replaced with Inner

    foreach(Vdv301DisplayContent selectedDisplayContent, displayContentListAll)
    {
        switch(selectedDisplayContent.displayContentType)
        {
        case DisplayContentFront:
            displayContentListFront.append(selectedDisplayContent);
            break;
        case DisplayContentSide:
            displayContentListSide.append(selectedDisplayContent);
            break;
        case DisplayContentRear:
            displayContentListRear.append(selectedDisplayContent);
            break;
        case DisplayContentLcd:
            displayContentListLcd.append(selectedDisplayContent);
            break;
        case DisplayContentInterior:
            displayContentListInterior.append(selectedDisplayContent);
            break;
        case DisplayContentUndefined:
            qCDebug(DisplayLabelLedLog)<<"undefined displayContent";
            break;
        default:
            break;


        }

    }

    frontDisplay.displayContentList=displayContentListFront;
    sideDisplay.displayContentList=displayContentListSide;
    rearDisplay.displayContentList=displayContentListRear;


    ledUpdateDisplaySizes();

    frontDisplay.ticker=0;
    sideDisplay.ticker=0;
    rearDisplay.ticker=0;


    slotTickLedPanels2_3();
    timerLedSideCycleViaPoints.start();

}


void DisplayLabelLed::slotTickLedPanels2_3()
{

    ledDisplaySetDisplayContent(frontDisplay);
    ledDisplaySetDisplayContent(sideDisplay);
    ledDisplaySetDisplayContent(rearDisplay);


}



void DisplayLabelLed::slotLedIterateAllDisplays()
{
    // qCDebug(DisplayLabelLedLog)<<"MainWindow::iterujVsechnyPanely()";
    ledIterateSide(textyBocniPanelkIteraci,currentPageIndexLed);
    ledIterateInner(textyVnitrniPanelkIteraci,currentPageIndexLed);
}

void DisplayLabelLed::ledIterateSide(QVector<QString> texty, int &iteracniIndex)
{
    // qCDebug(DisplayLabelLedLog)<<"MainWindow::iterujBocniPanel";

    if(iteracniIndex<texty.length())
    {
        sideDisplay.destination2Label->setText(texty.at(iteracniIndex));
        ledAlignTextOverflow(sideDisplay.destination2Label);

        //  iteracniIndex++;

    }
    else
    {
        //   iteracniIndex=0;
    }
}

void DisplayLabelLed::ledIterateInner(QVector<QString> texty, int &iteracniIndex)
{
    // qCDebug(DisplayLabelLedLog)<<"MainWindow::iterujBocniPanel";

    if(iteracniIndex<texty.length())
    {
        innerDisplay.destination2Label->setText(texty.at(iteracniIndex));

        iteracniIndex++;

    }
    else
    {
        iteracniIndex=0;
    }
}



void DisplayLabelLed::ledAlignTextOverflow(QLabel* label)
{
    qCDebug(DisplayLabelLedLog) <<  Q_FUNC_INFO;
    QFontMetrics metrics(label->font());

    if(metrics.horizontalAdvance(label->text())> label->width())
    {
        label->setAlignment(Qt::AlignLeading|Qt::AlignBottom);
    }
    else
    {
        label->setAlignment(Qt::AlignHCenter|Qt::AlignBottom);
    }
}


void DisplayLabelLed::ledSetTextFront(QString line,QString destinationTop,QString destinationBottom)
{
    qCDebug(DisplayLabelLedLog) <<  Q_FUNC_INFO;


    if (destinationBottom!="")
    {
        frontDisplay.destinationLabel->setVisible(false);
        frontDisplay.destination1Label->setVisible(true);
        frontDisplay.destination2Label->setVisible(true);

    }
    else
    {
        frontDisplay.destinationLabel->setVisible(true);
        frontDisplay.destination1Label->setVisible(false);
        frontDisplay.destination2Label->setVisible(false);

    }

    frontDisplay.destinationLabel->setText(destinationTop);
    frontDisplay.destination1Label->setText(destinationTop);
    frontDisplay.destination2Label->setText(destinationBottom);


    ledSetLine(frontDisplay.lineLabel,line);
}




void DisplayLabelLed::ledSetTextSide(QString line,QString destinationTop,QString destinationBottom)
{
    qCDebug(DisplayLabelLedLog) <<  Q_FUNC_INFO;



    if (destinationBottom!="")
    {
        sideDisplay.destinationLabel->setVisible(false);
        sideDisplay.destination1Label->setVisible(true);
        sideDisplay.destination2Label->setVisible(true);

    }
    else
    {
        sideDisplay.destinationLabel->setVisible(true);
        sideDisplay.destination1Label->setVisible(false);
        sideDisplay.destination2Label->setVisible(false);

    }

    sideDisplay.lineLabel->setText(line); //??? excessive?


    sideDisplay.destinationLabel->setText(destinationTop);
    ledAlignTextOverflow(sideDisplay.destinationLabel);

    sideDisplay.destination1Label->setText(destinationTop);
    ledAlignTextOverflow(sideDisplay.destination1Label);

    sideDisplay.destination2Label->setText(destinationBottom);
    ledAlignTextOverflow(sideDisplay.destination2Label);

    ledSetLine(sideDisplay.lineLabel,line);

}


void DisplayLabelLed::ledSetLine(QLabel* label, QString text)
{
    qCDebug(DisplayLabelLedLog)<<Q_FUNC_INFO;
    label->setText(text);
    if (text.length()>3)
    {

        label->setFont(fontLed10);
    }
    else
    {
        label->setFont(fontLed8);
    }
    ledAlignTextOverflow(label);
}

void DisplayLabelLed::ledSetTextRear(QString line)
{
    qCDebug(DisplayLabelLedLog) <<  Q_FUNC_INFO;

    ledSetLine(rearDisplay.lineLabel,line);

}

void DisplayLabelLed::ledSetTextInner(QString line,QString destinationTop,QString destinationBottom)
{
    qCDebug(DisplayLabelLedLog) <<  Q_FUNC_INFO;
    innerDisplay.lineLabel->setText(line);
    innerDisplay.destination1Label->setText(destinationTop);
    innerDisplay.destination2Label->setText(destinationBottom);
}


void DisplayLabelLed::ledInitializeFormat()
{
    qCDebug(DisplayLabelLedLog) <<  Q_FUNC_INFO;
    /*
    ledNaplnFront("123","čelní horní","čelní dolní");
    ledNaplnSide("456","Boční cíl","Boční nácestné");
    ledNaplnRear("789");
    ledNaplnInner("123","vnitřní cíl", "vnitřní nácesty");
*/



    frontDisplay.destinationLabel->setFont(fontLed5);
    frontDisplay.destination1Label->setFont(fontLed3);
    frontDisplay.destination2Label->setFont(fontLed3);

    sideDisplay.destinationLabel->setFont(fontLed5);
    sideDisplay.destination1Label->setFont(fontLed1);
    sideDisplay.destination2Label->setFont(fontLed1);

    innerDisplay.lineLabel->setFont(fontLed3);
    innerDisplay.destination1Label->setFont(fontLed1);
    innerDisplay.destination2Label->setFont(fontLed1);

    /* font 3v is not size optimised at the moment
    ui->labelInnerBottomRow->setFont(fontLed3v);
    ui->labelInnerTopRow->setFont(fontLed3v);
    */

    if(frontDisplay.lineLabel->text().length()>3)
    {
        frontDisplay.lineLabel->setFont(fontLed10);
        sideDisplay.lineLabel->setFont(fontLed10);
        rearDisplay.lineLabel->setFont(fontLed10);
    }
    else
    {
        frontDisplay.lineLabel->setFont(fontLed8);
        sideDisplay.lineLabel->setFont(fontLed8);
        rearDisplay.lineLabel->setFont(fontLed8);
    }

}

void DisplayLabelLed::ledClearDisplays()
{
    qCDebug(DisplayLabelLedLog) <<  Q_FUNC_INFO;
    ledSetTextFront("","","");
    ledSetTextSide("","","");
    ledSetTextRear("");
    ledSetTextInner("","", "");
    textyBocniPanelkIteraci.clear();
    textyVnitrniPanelkIteraci.clear();
}





void DisplayLabelLed::ledSetWindowSizeDot(QLabel * label, int lengthDotCount, int heightDotCount, float coeficient)
{
    //int koeficient = pomer pixel:pocetDotu
    label->setFixedHeight(float(heightDotCount)*coeficient);
    label->setFixedWidth(float(lengthDotCount)*coeficient);
}


void DisplayLabelLed::ledUpdateDisplaySizes()
{
    qCDebug(DisplayLabelLedLog)<<Q_FUNC_INFO;

    const int cilSirka=108;
    const int cilVyskaVelky=19;

    const int vyskaHorniRadek=9;
    const int vyskaDolniRadek=10;


    const int linkaSirka=30;
    const int linkaVyska=19;


    const int linkaVnitrniSirka=22;
    const int linkaVnitrniVyska=8;

    const int vyskaVnitrniHorniRadek=8;
    const int vyskaVnitrniDolniRadek=8;

    const int sirkaVnitrniHorniRadek=113;
    const int sirkaVnitrniDolniRadek=135;

    const int cilBocniSirka=82;


    int velikostFontu=fontLed8.pointSize();
    int vyskaLinky=frontDisplay.lineLabel->height();
    float pomerFontuKvysce=float(velikostFontu)/float(vyskaLinky);

    ratioPixelLed=frontDisplay.destinationLabel->width() /(float(cilSirka)); //A

    //ui->spinBox_frontSignWidth->setValue(frontDisplay.destinationLabel->width());
    emit signalFrontDisplayWidthChanged(frontDisplay.destinationLabel->width());

    float novaVyskaLinky=float(linkaVyska)*ratioPixelLed;
    float staraVyskaLinky=78.0;

    float novaVelikostFontu=65*(novaVyskaLinky/staraVyskaLinky);


    frontDisplay.destinationLabel->setFixedHeight(float(cilVyskaVelky)*ratioPixelLed);

    frontDisplay.destination1Label->setFixedHeight(float(vyskaHorniRadek)*ratioPixelLed);
    frontDisplay.destination2Label->setFixedHeight(float(vyskaDolniRadek)*ratioPixelLed);


    ledSetWindowSizeDot(frontDisplay.lineLabel,linkaSirka,linkaVyska,ratioPixelLed);

    ledSetWindowSizeDot(sideDisplay.lineLabel,linkaSirka,linkaVyska,ratioPixelLed);
    ledSetWindowSizeDot(sideDisplay.destination1Label,cilBocniSirka,vyskaHorniRadek,ratioPixelLed);
    ledSetWindowSizeDot(sideDisplay.destination2Label,cilBocniSirka,vyskaDolniRadek,ratioPixelLed);

    ledSetWindowSizeDot(rearDisplay.lineLabel,linkaSirka,linkaVyska,ratioPixelLed);

    ledSetWindowSizeDot(innerDisplay.lineLabel,linkaVnitrniSirka,linkaVnitrniVyska,ratioPixelLed);

    ledSetWindowSizeDot(innerDisplay.destination1Label,sirkaVnitrniHorniRadek,vyskaVnitrniHorniRadek,ratioPixelLed);
    ledSetWindowSizeDot(innerDisplay.destination2Label,sirkaVnitrniDolniRadek,vyskaVnitrniDolniRadek,ratioPixelLed);



    qCDebug(DisplayLabelLedLog)<<"pomer vysky: "<<pomerFontuKvysce; //pomer vysky:  0.833333

    fontLed1.setPointSize(novaVelikostFontu);
    fontLed3.setPointSize(novaVelikostFontu);
    fontLed5.setPointSize(novaVelikostFontu);
    fontLed8.setPointSize(novaVelikostFontu);
    fontLed10.setPointSize(novaVelikostFontu);

    ledInitializeFormat();
}
