#include "xmlparser.h"
#include "VDV301subscriber/VDV301DataStructures/stoppoint.h"
#include "VDV301subscriber/VDV301DataStructures/vehiclestate.h"
#include "VDV301subscriber/VDV301DataStructures/farezone.h"

#include <QDebug>
#include <QMainWindow>




XmlParser::XmlParser()
{
    qDebug()<<Q_FUNC_INFO;
}

void XmlParser::loadXmlFile(QString input)
{
    qDebug()<<Q_FUNC_INFO;

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
    qDebug()<<Q_FUNC_INFO;

    QDateTime timestamp =  QDateTime::fromString(vstupniDokument.firstChildElement("CustomerInformationService.GetAllDataResponse").firstChildElement("AllData").firstChildElement("TimeStamp").firstChildElement("Value").firstChild().nodeValue() ,Qt::ISODate);

    return timestamp;

}


QDateTime XmlParser::parseTimestamp(QString input)
{
    qDebug()<<Q_FUNC_INFO;

    QDateTime timestamp =  QDateTime::fromString(input ,Qt::ISODate);

    return timestamp;

}





QVector<QString> XmlParser::propertyDomToStringList(QDomNode domNode,QString elementName)
{
    QVector<QString> output;

    QDomNodeList propertyNodes=domNode.toElement().elementsByTagName(elementName+"Property");
    // qDebug()<<"naplnVektor Zastavka ma tolik priznaku:"<<priznaky.count();

    for (int j=0;j<propertyNodes.count();j++)
    {
        QString propertyValue=propertyNodes.at(j).firstChild().nodeValue();
        //     qDebug()<<"priznak "<<hodnotaPriznaku;
        output.push_back(propertyValue);
    }
    return output;
}



void XmlParser::Test()
{
    qDebug()<<Q_FUNC_INFO;
    qInfo()<<"xmlParserTestPoint2";
}








