#include "displaylabel.h"


#include <QMessageBox>

Q_LOGGING_CATEGORY(DisplayLabelLog, "DisplayLabel")

DisplayLabel::DisplayLabel()
{

}


void DisplayLabel::resizeLabelListPointCoeficient(QVector<QLabel *> labely, int pointSize, float scaleCoeficient)
{
    foreach (QLabel *label, labely)
    {
        resizeLabelPointCoeficient(label,pointSize,scaleCoeficient);
    }
}

void DisplayLabel::resizeLabelPointCoeficient(QLabel *label, int pointSize, float scaleCoeficient)
{
    if(label!=nullptr)
    {
        QFont fontLabelu = label->font();
        fontLabelu.setPointSize(qFloor(scaleCoeficient * pointSize * 0.6));
        label->setFont(fontLabelu);
    }
    else
    {
        qCDebug(DisplayLabelLog)<<"empty label pointer";
        return;
    }

}

bool DisplayLabel::labelSetTextSafe(QLabel *label, QString text)
{
    if(label==nullptr)
    {
        qCDebug(DisplayLabelLog)<<"DisplayLabel::labelSetTextSafe failed";
        return false;
    }

    else
    {
        label->setText(text);
    }
    return true;
}

bool DisplayLabel::labelSetStylesheetSafe(QLabel *label, QString stylesheet)
{
    if(label==nullptr)
    {
        qCDebug(DisplayLabelLog)<<Q_FUNC_INFO<<" failed";
        return false;
    }

    else
    {
        label->setStyleSheet(stylesheet);
    }
    return true;
}

bool DisplayLabel::labelSetVisibleSafe(QLabel *label, bool visibility)
{
    if(label==nullptr)
    {
        qCDebug(DisplayLabelLog)<<Q_FUNC_INFO<<" failed";
        return false;
    }

    else
    {
        label->setVisible(visibility);
    }
    return true;
}

void DisplayLabel::resizeLineLabel(QLabel *label)
{
    qCDebug(DisplayLabelLog)<<Q_FUNC_INFO;
    if(label==nullptr)
    {
        qCDebug(DisplayLabelLog)<<"empty label pointer";
        return;
    }

    QFont previousFontSize = label->font();
    previousFontSize.setPixelSize(label->height());
    label->setFont(previousFontSize);

    int labelHeight = label->height();
    int labelWidth = label->width();

    int fontHeight = label->fontMetrics().boundingRect(label->text()).height();
    int fontWidth = label->fontMetrics().boundingRect(label->text()).width();

    qCDebug(DisplayLabelLog) << "V labelu " << labelHeight << " V Fontu " << fontHeight << " S labelu " << labelWidth << " S fontu " << fontWidth;

    int counter = 0;
    while (((fontWidth > labelWidth) || (fontHeight > labelHeight)) && (counter < 4))
    {
        previousFontSize.setPixelSize(qRound(previousFontSize.pixelSize() * 0.90));

        fontHeight = label->fontMetrics().boundingRect(label->text()).height();
        fontWidth = label->fontMetrics().boundingRect(label->text()).width();
        label->setFont(previousFontSize);
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


void DisplayLabel::setAnouncementLabel(QString input, QLabel *label)
{
    qCDebug(DisplayLabelLog)<<Q_FUNC_INFO;
    labelSetTextSafe(label,input);
}

void DisplayLabel::setNextStopBackground(QString textColor, QString backgroundColor, QFrame *qframe)
{
    qCDebug(DisplayLabelLog)<<Q_FUNC_INFO;
    //
    if(qframe!=nullptr)
    {
          qframe->setStyleSheet("background-color :" + backgroundColor + " ; color : " + textColor + "; ");
    }
}



QString DisplayLabel::viaPointListToFormattedString(QVector<Vdv301ViaPoint> viaPointList, int iconSize)
{
    qCDebug(DisplayLabelLog)<<Q_FUNC_INFO;
    if (viaPointList.count() == 0)
    {
        return "";
    }

    QString viaPointsString = "";

    QStringList viaPointStringList;
    foreach(Vdv301ViaPoint viaPoint, viaPointList)
    {
        Vdv301InternationalText viaPointNameJoin=vdv301InternationalTextJoinAll(viaPoint.placeNameList," x ") ;
       viaPointStringList<<iconToHtmlImage(viaPointNameJoin.text, iconSize, iconDirectory);
    }
    viaPointsString = viaPointStringList.join(" - ");

    QString output = wrapInHtml(viaPointsString);
    qCDebug(DisplayLabelLog) << "vypis radku nacestnych zastavek text html" << output;

    return output;
}



Vdv301InternationalText DisplayLabel::vdv301InternationalTextJoinAll(QVector<Vdv301InternationalText> internationalTextList, QString separator)
{
    Vdv301InternationalText output;
    if(internationalTextList.isEmpty())
    {
        return output;
    }

    QStringList internationalTextForLanguageList;
    foreach(Vdv301InternationalText text, internationalTextList)
    {
        internationalTextForLanguageList<<text.text;
    }
    output=Vdv301InternationalText(internationalTextForLanguageList.join(separator),internationalTextList.first().language );

    return output;
}

QVector<Vdv301InternationalText> DisplayLabel::vdv301InternationalTextJoinByLanguage(QVector<Vdv301InternationalText> internationalTextList, QString separator)
{
    QStringList languages;
    QVector<Vdv301InternationalText> output;

    foreach(Vdv301InternationalText internationalText, internationalTextList)
    {
        if(!languages.contains(internationalText.language))
        {
            languages<<internationalText.language;
        }
    }

    foreach (QString language, languages)
    {
        QStringList internationalTextForLanguageList;
        foreach(Vdv301InternationalText text, internationalTextList)
        {
            if(text.language==language)
            {
                internationalTextForLanguageList<<text.text;
            }
        }
        output<<Vdv301InternationalText(internationalTextForLanguageList.join(separator),language );
    }
    return output;
}


QString DisplayLabel::textToAnnouncementIcon(QString announcementType, int iconSize)
{
    QString output = "";
    // int vyskaObrazku=40; //konstanta v px, ovlivnuje vysku piktogramu
    QString htmlImages = "";
    if (announcementType == "")
    {
        return "";
    }

    htmlImages += "<img  src=\":/images/" + announcementType + "\" height=\"" + QString::number(iconSize) + "\"  >";

    qCDebug(DisplayLabelLog) << "setting announcement icon:" << htmlImages;

    output = htmlImages;
    return output;
}

QString DisplayLabel::wrapInHtml(QString input)
{
    return "<html><head/><body><p>" + input + "</p></body></html>";
}

int DisplayLabel::minimum(int number1, int number2)
{
    if (number1 < number2)
    {
        return number1;
    }
    return number2;
}


void DisplayLabel::eraseLabelList(QVector<QLabel *> input)
{
    foreach (QLabel *selectedLabel, input)
    {
        labelSetTextSafe(selectedLabel, "");
    }
}

QString DisplayLabel::iconToHtmlImage(QString input, int iconSize, QString iconDirectory)
{
    // bude nahrazeno v inlineformatparser, jen kvuli nacestnym zastavkam
    qCDebug(DisplayLabelLog) << Q_FUNC_INFO;
    QString output = "";

    QDomDocument domDocument;
    domDocument.setContent("<wrapper>" + input + "</wrapper>");

    QDomNodeList domIconList = domDocument.firstChildElement().elementsByTagName("icon");
    qCDebug(DisplayLabelLog) << domDocument.toByteArray();

    qCDebug(DisplayLabelLog) << "icon count: " << domIconList.count();

    //check if necessary!
    QString iconName = domDocument.firstChildElement().firstChild().nodeValue();
    output = iconName;

    for (int i = 0; i < domIconList.length(); i++)
    {
        QDomNode domIcon = domIconList.at(i);
        QString typeName = domIcon.attributes().namedItem("type").firstChild().nodeValue();
        QString alternativniText = domIcon.firstChild().nodeValue();
        qCDebug(DisplayLabelLog) << typeName;

        QString filePath = iconDirectory + "/" + typeName + ".svg";
        qCDebug(DisplayLabelLog) << "filePath:" << filePath;

        if (QFile::exists(filePath))
        {
            //resources  vystup+="<img  src=\":/images/"+nazev+"\"height=\""+QString::number(vyskaObrazku)+"\"  >";

            output += "<img  src=\"" + filePath + "\" height=\"" + QString::number(iconSize) + "\"  >";
            qCDebug(DisplayLabelLog) << "resource existuje";
        }
        else
        {
            output += alternativniText;
            qCDebug(DisplayLabelLog) << "resource neexistuje";
        }
    }

    // <icon type="c_RequestStop" >ŕ</icon>

    return output;
}

QString DisplayLabel::replaceIconOuterDisplays(QString input)
{
    // bude nahrazeno v inlineformatparser, jen kvuli nacestnym zastavkam
    qCDebug(DisplayLabelLog) << Q_FUNC_INFO;
    QString output = "";

    QDomDocument domDocument;
    domDocument.setContent("<wrapper>" + input + "</wrapper>");

    QDomNodeList domIconList = domDocument.firstChildElement().elementsByTagName("icon");
    qCDebug(DisplayLabelLog) << domDocument.toByteArray();
    qCDebug(DisplayLabelLog) << "icon count: " << domIconList.count();

    QString jenNazev = domDocument.firstChildElement().firstChild().nodeValue();
    output = jenNazev;

    for (int i = 0; i < domIconList.length(); i++)
    {
        QDomNode ikona = domIconList.at(i);
        QString nazev = ikona.attributes().namedItem("type").firstChild().nodeValue();
        QString alternativniText = ikona.firstChild().nodeValue();
        qCDebug(DisplayLabelLog) << nazev;
        output += alternativniText;

    }

    // <icon type="c_RequestStop" >ŕ</icon>

    return output;
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
        qCDebug(DisplayLabelLog)<<" errorMessage";
        msgBox.exec();
        return 0;
    }
}



QString DisplayLabel::fareZoneToQString(QVector<FareZone> fareZoneList)
{
    qCDebug(DisplayLabelLog)<<Q_FUNC_INFO;
    QString output;
    if (fareZoneList.size()>0)
    {
        output=fareZoneList.at(0).name;
        for (int i=1;i<fareZoneList.size();i++)
        {
            output+=","+fareZoneList.at(i).name;
        }
    }
    return output;
}

void DisplayLabel::setVdv301version(const QString &newVdv301version)
{
    mVdv301version = newVdv301version;
}

QString DisplayLabel::vdv301version() const
{
    return mVdv301version;
}
