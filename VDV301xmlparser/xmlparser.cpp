#include "xmlparser.h"
#include <QDebug>
#include <QMainWindow>

Q_LOGGING_CATEGORY(XmlParserLog, "XmlParser")


XmlParser::XmlParser()
{
    qCDebug(XmlParserLog)<<Q_FUNC_INFO;
}

void XmlParser::loadXmlFile(QString input)
{
    qCDebug(XmlParserLog)<<Q_FUNC_INFO;

    if(input!=previousXmlData)
    {
        dataChanged=true;
    }
    else
    {
        dataChanged=false;
    }

    receivedDataDomDocument.setContent(input);
}


QDateTime XmlParser::parseTimestamp(QDomDocument vstupniDokument)
{
    qCDebug(XmlParserLog)<<Q_FUNC_INFO;

    QDateTime timestamp =  QDateTime::fromString(vstupniDokument.firstChildElement("CustomerInformationService.GetAllDataResponse").firstChildElement("AllData").firstChildElement("TimeStamp").firstChildElement("Value").firstChild().nodeValue() ,Qt::ISODate);

    return timestamp;

}


QDateTime XmlParser::parseTimestamp(QString input)
{
    qCDebug(XmlParserLog)<<Q_FUNC_INFO;

    QDateTime timestamp =  QDateTime::fromString(input ,Qt::ISODate);

    return timestamp;

}





QVector<QString> XmlParser::propertyDomToStringList(QDomNode domNode,QString elementName)
{
    QVector<QString> output;

    QDomNodeList propertyNodes=domNode.toElement().elementsByTagName(elementName+"Property");
    // qCDebug(XmlParserLog)<<"naplnVektor Zastavka ma tolik priznaku:"<<priznaky.count();

    for (int j=0;j<propertyNodes.count();j++)
    {
        QString propertyValue=propertyNodes.at(j).firstChild().nodeValue();
        //     qCDebug(XmlParserLog)<<"priznak "<<hodnotaPriznaku;
        output.push_back(propertyValue);
    }
    return output;
}



void XmlParser::Test()
{
    qCDebug(XmlParserLog)<<Q_FUNC_INFO;
    qInfo()<<"xmlParserTestPoint2";
}








