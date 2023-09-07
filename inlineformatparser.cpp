#include "inlineformatparser.h"

InlineFormatParser::InlineFormatParser()
{

}



QString InlineFormatParser::vyparsujText(QString vstup, int vyskaObrazku, QString slozka)
{
    qDebug()<<Q_FUNC_INFO;


    QDomDocument vystup;

    QDomElement html=vystup.createElement("html");
    QDomElement body=vystup.createElement("body");

    vstup="<wrapper>"+vstup+"</wrapper>";
    QXmlStreamReader xmlReader(vstup);


    QString openElement="";

    QString prostyText;


    Color barva;
    Icon ikona;


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
            }
            else if(openElement=="icon")
            {
                body.appendChild(iconToQDomNode(ikona,vyskaObrazku,slozka));

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
    qDebug()<<"vystup formatovani: "<<vystupString;

    return vystupString;
}


QDomNode InlineFormatParser::iconToQDomNode(Icon vstup, int vyskaObrazku, QString slozka)
{
    qDebug() << Q_FUNC_INFO;

    QDomDocument dokumentVystup;
    QDomNode vystup;
    QString iconType = vstup.type;
    QString alternativniText = vstup.alternative;
    QString cesta = slozka + "/" + iconType + ".svg";

    qDebug() << iconType;


    qDebug() << "cesta k souboru:" << cesta;

    if (QFile::exists(cesta))
    {

        QDomElement img = dokumentVystup.createElement("img");
        img.setAttribute("src", cesta);
        img.setAttribute("height", QString::number(vyskaObrazku));
        vystup=img;
        qDebug() << "resource existuje";
    }
    else
    {
        vystup = dokumentVystup.createTextNode(alternativniText);
        qDebug() << "resource neexistuje";
    }

    // <icon type="c_RequestStop" >ŕ</icon>

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
    styl += "background-color:" + bg + "; ";
    styl += "color:" + fg + ";";
    span.setAttribute("style", styl);
    span.appendChild(vystup.createTextNode(obsahNodu));


    return span;
}

