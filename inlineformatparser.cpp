#include "inlineformatparser.h"
#include <QDateTime>

Q_LOGGING_CATEGORY(InLineFormatParserLog, "InLineFormatParser")

InlineFormatParser::InlineFormatParser()
{

}



QString InlineFormatParser::parseTextLcd(QString vstup, int vyskaObrazku, QString slozka)
{
    qCDebug(InLineFormatParserLog)<<Q_FUNC_INFO;


    QDomDocument vystup;

    QDomElement html=vystup.createElement("html");
    QDomElement body=vystup.createElement("body");

    vstup="<wrapper>"+vstup+"</wrapper>";
    QXmlStreamReader xmlReader(vstup);


    QString openElement="";

    QString rawContent="";


    Color barva;
    Icon ikona;
    Font font;



    while (!xmlReader.atEnd())
    {
        xmlReader.readNext();

        if (xmlReader.isStartElement())
        {
            rawContent="";

            QString elementName = xmlReader.name().toString();

            QXmlStreamAttributes attributes = xmlReader.attributes();
            while (!attributes.isEmpty())
            {

                QString attributeName = attributes.front().name().toString();
                QString attributeValue = attributes.front().value().toString();
                // Process attribute

                if(attributeName=="bg")
                {
                    barva.bg=attributeValue;
                }
                else if(attributeName=="fg")
                {
                    barva.fg=attributeValue;
                }
                else if(attributeName=="size")
                {
                    font.size=attributeValue;
                }
                else if(attributeName=="type")
                {
                    ikona.type=attributeValue;
                }            


                attributes.pop_front();
            }


            if(elementName=="color")
            {

            }
            else if(elementName=="icon")
            {

            }

            openElement=elementName;
        }
        else if (xmlReader.isCharacters())
        {
            // Handle text content
            QString textContent = xmlReader.text().toString();

            if((openElement=="")||(openElement=="wrapper"))
            {
                body.appendChild(vystup.createTextNode(textContent ));
            }
            else if(openElement=="color")
            {
                barva.content=textContent;
            }
            else if(openElement=="font")
            {
                font.content=textContent;
            }
            else if(openElement=="icon")
            {
                ikona.alternative=textContent;
            }
            else if(openElement=="b")
            {
                rawContent=textContent;
            }



            // Process text content
        }
        else if (xmlReader.isEndElement())
        {
            // Handle element end tag
            QString elementName = xmlReader.name().toString();


            if(openElement=="")
            {

            }
            else if(openElement=="color")
            {
                body.appendChild(colorToQDomNode(barva));
            }
            else if(openElement=="font")
            {
                body.appendChild(fontToQDomNode(font));
            }
            else if(openElement=="icon")
            {
                body.appendChild(iconToQDomNode(ikona,vyskaObrazku,slozka));

                ikona.alternative="";
                ikona.type="";
            }
            else if(openElement=="font")
            {
                body.appendChild(fontToQDomNode(font));
            }
            else if(openElement=="b")
            {
                body.appendChild(boldToQDomNode(rawContent));
            }





            openElement="";

        }
    }

    if (xmlReader.hasError()) {
        // Handle XML parsing error
    }


    html.appendChild(body);
    vystup.appendChild(html);

    QString vystupString=vystup.toString();
    qCDebug(InLineFormatParserLog)<<"vystup formatovani: "<<vystupString;

    return vystupString;
}



QString InlineFormatParser::parseTextLcdJis(QString vstup, int vyskaObrazku, QString slozka)
{
    qCDebug(InLineFormatParserLog)<<Q_FUNC_INFO;


    QDomDocument vystup;

    QDomElement html=vystup.createElement("html");
    QDomElement body=vystup.createElement("body");

    vstup="<wrapper>"+vstup+"</wrapper>";
    QXmlStreamReader xmlReader(vstup);


    QString openElement="";

    QString rawContent="";


    Color barva;
    Icon ikona;
    Font font;



    while (!xmlReader.atEnd())
    {
        xmlReader.readNext();

        if (xmlReader.isStartElement())
        {
            rawContent="";

            QString elementName = xmlReader.name().toString();

            QXmlStreamAttributes attributes = xmlReader.attributes();
            while (!attributes.isEmpty())
            {

                QString attributeName = attributes.front().name().toString();
                QString attributeValue = attributes.front().value().toString();
                // Process attribute

                if(attributeName=="bg")
                {
                    barva.bg=attributeValue;
                }
                else if(attributeName=="fg")
                {
                    barva.fg=attributeValue;
                }
                else if(attributeName=="size")
                {
                    font.size=attributeValue;
                }
                else if(attributeName=="type")
                {
                    ikona.type=attributeValue;
                }


                attributes.pop_front();
            }


            if(elementName=="color")
            {

            }
            else if(elementName=="icon")
            {

            }

            openElement=elementName;
        }
        else if (xmlReader.isCharacters())
        {
            // Handle text content
            QString textContent = xmlReader.text().toString();

            if((openElement=="")||(openElement=="wrapper"))
            {
                body.appendChild(vystup.createTextNode(textContent ));
            }
            else if(openElement=="color")
            {
                barva.content=textContent;
            }
            else if(openElement=="font")
            {
                font.content=textContent;
            }
            else if(openElement=="icon")
            {
                ikona.alternative=textContent;
            }
            else if(openElement=="b")
            {
                rawContent=textContent;
            }



            // Process text content
        }
        else if (xmlReader.isEndElement())
        {
            // Handle element end tag
            QString elementName = xmlReader.name().toString();


            if(openElement=="")
            {

            }
            else if(openElement=="color")
            {
             //  body.appendChild(colorToQDomNode(barva));
                body.appendChild(vystup.createTextNode(barva.content));
            }
            else if(openElement=="font")
            {
                body.appendChild(fontToQDomNode(font));
            }
            else if(openElement=="icon")
            {
                body.appendChild(iconToQDomNode(ikona,vyskaObrazku,slozka));

                ikona.alternative="";
                ikona.type="";
            }
            else if(openElement=="font")
            {
                body.appendChild(fontToQDomNode(font));
            }
            else if(openElement=="b")
            {
                body.appendChild(boldToQDomNode(rawContent));
            }





            openElement="";

        }
    }

    if (xmlReader.hasError()) {
        // Handle XML parsing error
    }


    html.appendChild(body);
    vystup.appendChild(html);

    QString vystupString=vystup.toString();
    qCDebug(InLineFormatParserLog)<<"vystup formatovani: "<<vystupString;

    return vystupString;
}


QString InlineFormatParser::parseTextLcdOuter(QString vstup, int vyskaObrazku, QString slozka, QString &bgColor)
{
    qCDebug(InLineFormatParserLog)<<Q_FUNC_INFO;


    QDomDocument vystup;

    QDomElement html=vystup.createElement("html");
    QDomElement body=vystup.createElement("body");

    vstup="<wrapper>"+vstup+"</wrapper>";
    QXmlStreamReader xmlReader(vstup);
  //  Color color;


    QString output= "<html><body>"+parseTextLcdRecursive(xmlReader,"",vyskaObrazku,slozka,bgColor)+"</body></html>";

    return output;
}


QString InlineFormatParser::parseTextLcdRecursive(QXmlStreamReader &xmlReader, QString parent, int vyskaObrazku, QString slozka, QString &bgColor)
{
    qCDebug(InLineFormatParserLog) << Q_FUNC_INFO;
    QString timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);
    qCDebug(InLineFormatParserLog) << timestamp;

    QDomDocument vystup;
    QString rawContent = "";

    Icon ikona;
    Font font;
    Color barva;

    QString popredi = "xx";
    QString result = "";

    QStack<QString> elementStack;

    try
    {
        while (!xmlReader.atEnd())
        {
            xmlReader.readNext();
            QXmlStreamReader::TokenType typTokenu = xmlReader.tokenType();
            QString currentElement = xmlReader.name().toString();

            switch (xmlReader.tokenType())
            {
            case QXmlStreamReader::StartElement:
            {
                rawContent = "";
                elementStack.push(currentElement);
                QXmlStreamAttributes attributes = xmlReader.attributes();
                QString elementStart ="";



                // + currentElement;

                while (!attributes.isEmpty())
                {
                    QString attributeName = attributes.front().name().toString();
                    QString attributeValue = attributes.front().value().toString();

                    if (attributeName == "bg")
                    {

                        barva.bg = attributeValue;
                        if(parent==".wrapper")
                        {
                            bgColor=barva.bg;
                        }
                    }
                    else if (attributeName == "fg")
                    {
                        barva.fg = attributeValue;
                        popredi = attributeValue;
                        qCDebug(InLineFormatParserLog) << "Setting barva.fg to" << barva.fg;
                    }
                    else if (attributeName == "size")
                    {
                        font.size = attributeValue;
                    }
                    else if (attributeName == "type")
                    {
                        ikona.type = attributeValue;
                    }

                    //  elementStart += " " + attributeName + "=\"" + attributeValue + "\"";
                    attributes.pop_front();
                }

                if(currentElement=="color")
                {
                    elementStart=colorToQDomNodeStart(barva.fg,barva.bg);
                }
                else if(currentElement=="font")
                {
                    elementStart=fontToQDomNodeStart(font);
                }
                else if(currentElement=="b")
                {
                    elementStart="<b>";
                }
                else if(currentElement=="br")
                {
                    elementStart="<br>";
                }
                else if(currentElement=="icon")
                {
                    elementStart=iconToQDomNodeStart(ikona,vyskaObrazku,slozka);
                }
                else if(currentElement=="wrapper")
                {
                    qCDebug(InLineFormatParserLog)<<"wrapper";

                }
                else
                {
                    qCDebug(InLineFormatParserLog)<<"unknown element";
                    //  elementStart += ">";
                }
                /*
                if(currentElement=="")
                {
                    qCDebug(InLineFormatParserLog)<<"empty start element";
                     result += "xxx";
                }
                else
                {

                }
*/
                result += elementStart;
                result += parseTextLcdRecursive(xmlReader, parent + "." + currentElement, vyskaObrazku, slozka, bgColor);
                break;
            }

            case QXmlStreamReader::Characters:
            {
                QString textContent = xmlReader.text().toString();
                if(getDirectParent(parent)!="icon")
                {
                    result += textContent; //need to be fixed to support replacement characters
                }

                break;
            }

            case QXmlStreamReader::EndElement:
            {
                /*

                if (elementStack.isEmpty())
                {
                    qCDebug(InLineFormatParserLog) << "Error: Element stack is empty!";
                    return result;
                }*/

                // QString closingElement = elementStack.pop();

                QString closingElement = currentElement;


                if (closingElement == "color")
                {
                    return result+"</span>";
                }
                else if (closingElement == "font")
                {
                    return result+"</span>";
                }
                else if (closingElement == "b")
                {
                    return result+"</b>";

                }
                else if (closingElement == "icon")
                {
                    vystup.appendChild(iconToQDomNode(ikona, vyskaObrazku, slozka));
                    ikona.alternative = "";
                    ikona.type = "";
                }
                else if (closingElement == "wrapper")
                {
                    return result;

                }


                result += "</" + closingElement + ">";
                break;
            }

            default:
                break;
            }
        }

        if (xmlReader.hasError())
        {
            qCDebug(InLineFormatParserLog) << "XML Parsing Error:" << xmlReader.errorString();
        }
    }
    catch (const std::exception &e)
    {
        qCDebug(InLineFormatParserLog) << "Exception caught:" << e.what();
    }

    return result;
}

QString InlineFormatParser::getDirectParent(QString input)
{
    QStringList list=input.split(".");
    if(list.isEmpty())
    {
        return "";
    }
    else
    {
        return list.last();
    }
}

QString InlineFormatParser::parseTextLed(QString vstup)
{
    qCDebug(InLineFormatParserLog)<<Q_FUNC_INFO;


    QDomDocument vystup;

    QDomElement html=vystup.createElement("html");
    QDomElement body=vystup.createElement("body");

    vstup="<wrapper>"+vstup+"</wrapper>";
    QXmlStreamReader xmlReader(vstup);


    QString openElement="";

    QString prostyText="";


    Color barva;
    Icon ikona;

    QString vystupText2="";


    while (!xmlReader.atEnd()) {
        xmlReader.readNext();

        if (xmlReader.isStartElement()) {
            prostyText="";
            // Handle element start tag
            QString elementName = xmlReader.name().toString();
            // Process attributes if needed
            QXmlStreamAttributes attributes = xmlReader.attributes();
            while (!attributes.isEmpty()) {
                QString attributeName = attributes.front().name().toString();
                QString attributeValue = attributes.front().value().toString();
                // Process attribute

                if(attributeName=="bg")
                {
                    barva.bg=attributeValue;
                }
                else if(attributeName=="fg")
                {
                    barva.fg=attributeValue;
                }
                else if(attributeName=="type")
                {
                    ikona.type=attributeValue;
                }


                attributes.pop_front();
            }


            if(elementName=="color")
            {

            }
            else if(elementName=="icon")
            {

            }

            openElement=elementName;
        }
        else if (xmlReader.isCharacters())
        {
            // Handle text content
            QString textContent = xmlReader.text().toString();

            if((openElement=="")||(openElement=="wrapper"))
            {
                body.appendChild(vystup.createTextNode(textContent ));
                vystupText2+=textContent;
            }
            else if(openElement=="color")
            {
                barva.content=textContent;
            }
            else if(openElement=="icon")
            {
                ikona.alternative=textContent;
            }



            // Process text content
        }
        else if (xmlReader.isEndElement())
        {
            // Handle element end tag
            QString elementName = xmlReader.name().toString();


            if(openElement=="")
            {

            }
            else if(openElement=="color")
            {
                body.appendChild(colorToQDomNode(barva));
                vystupText2+=barva.content;
            }
            else if(openElement=="icon")
            {
                body.appendChild(iconToQDomNode(ikona,1,"xx"));
                vystupText2+=ikona.alternative;

                ikona.alternative="";
                ikona.type="";
            }




            openElement="";

        }
    }

    if (xmlReader.hasError()) {
        // Handle XML parsing error
    }


    html.appendChild(body);
    vystup.appendChild(html);

    QString vystupString=vystup.toString();
    qCDebug(InLineFormatParserLog)<<"vystup formatovani: "<<vystupString;
    return vystupText2;
    //return vystupString;
}


QDomNode InlineFormatParser::iconToQDomNode(Icon vstup, int vyskaObrazku, QString slozka)
{
    qCDebug(InLineFormatParserLog) << Q_FUNC_INFO;

    QDomDocument dokumentVystup;
    QDomNode vystup;
    QString iconType = vstup.type;
    QString alternativniText = vstup.alternative;
    QString cesta = slozka + "/" + iconType + ".svg";

    qCDebug(InLineFormatParserLog) << iconType;


    qCDebug(InLineFormatParserLog) << "cesta k souboru:" << cesta;

    if (QFile::exists(cesta))
    {

        QDomElement img = dokumentVystup.createElement("img");
        img.setAttribute("src", cesta);
        img.setAttribute("height", QString::number(vyskaObrazku));
        vystup=img;
        qCDebug(InLineFormatParserLog) << "resource existuje";
    }
    else
    {
        vystup = dokumentVystup.createTextNode(alternativniText);
        qCDebug(InLineFormatParserLog) << "resource neexistuje";
    }

    // <icon type="c_RequestStop" >ŕ</icon>

    return vystup;
}



QString InlineFormatParser::iconToQDomNodeStart(Icon vstup, int vyskaObrazku, QString slozka)
{
    qCDebug(InLineFormatParserLog) << Q_FUNC_INFO;


    QString vystup;
    QString iconType = vstup.type;
    QString alternativniText = vstup.alternative;
    QString cesta = slozka + "/" + iconType + ".svg";

    qCDebug(InLineFormatParserLog) << iconType;


    qCDebug(InLineFormatParserLog) << "cesta k souboru:" << cesta;

    if (QFile::exists(cesta))
    {
        return "<img src=\""+cesta+"\" height="+QString::number(vyskaObrazku)+">";


    }
    else
    {
        qCDebug(InLineFormatParserLog) << "resource neexistuje";
        return alternativniText;
    }


    return vystup;
}


QDomNode  InlineFormatParser::colorToQDomNode(Color input)
{
    QDomDocument vystup;

    QString bg = input.bg;
    QString fg = input.fg;
    QString obsahNodu = input.content;

    QDomElement span = vystup.createElement("span");
    QString styl = "";
    if(bg!="")
    {
        styl += "background-color:" + bg + "; ";
    }
    if(fg!="")
    {
        styl += "color:" + fg + ";";
    }

    span.setAttribute("style", styl);
    span.appendChild(vystup.createTextNode(obsahNodu));


    return span;
}



QString  InlineFormatParser::colorToQDomNodeStart(QString fg, QString bg)
{
    QString styl = "";
    if(bg!="")
    {
        styl += "background-color:" + bg + "; ";
    }
    if(fg!="")
    {
        styl += "color:" + fg + ";";
    }

    return "<span style=\""+styl+"\">";
}

/*
QDomNode  InlineFormatParser::elementWithAttributes(QString name,QDomNode content, QDomNamedNodeMap attributes )
{
    QDomNode result;
    QDomElement element;
    element.setTagName(name);
   // element.attributes()=atributes;

    QString obsahNodu = input.content;

    QDomElement span = vystup.createElement("span");
    QString styl = "";
    styl += "font-size:" + input.size + "; ";
    //styl += "color:" + fg + ";";
    span.setAttribute("style", styl);
    span.appendChild(vystup.createTextNode(obsahNodu));


    return span;
}
*/

QDomNode  InlineFormatParser::fontToQDomNode(Font input)
{
    QDomDocument vystup;


    QString obsahNodu = input.content;

    QDomElement span = vystup.createElement("span");
    QString styl = "";
    styl += "font-size:" + input.size + "; ";
    //styl += "color:" + fg + ";";
    span.setAttribute("style", styl);
    span.appendChild(vystup.createTextNode(obsahNodu));


    return span;
}


QString  InlineFormatParser::fontToQDomNodeStart(Font input)
{
    QDomDocument vystup;

    return "<span style=\"font-size:"+input.size+"px;\">";

}


QDomNode  InlineFormatParser::boldToQDomNode(QString input)
{
    QDomDocument vystup;

    QDomElement span = vystup.createElement("span");
    QString styl = "";
    styl += "font-weight: bold;";
    //styl += "color:" + fg + ";";
    span.setAttribute("style", styl);
    span.appendChild(vystup.createTextNode(input));


    return span;
}

