#ifndef XMLPARSER_H
#define XMLPARSER_H
//#define MAX_ZAST2 10

#include <QMainWindow>
#include <QObject>
#include <QtXml>
#include <QLoggingCategory>



class XmlParser
{
public:
    XmlParser();

    QDomDocument receivedDataDomDocument;
    void Test(); //unused
    
    void loadXmlFile(QString input);
    
    QVector<QString> propertyDomToStringList(QDomNode domNode, QString elementName);

    QDateTime parseTimestamp(QDomDocument vstupniDokument);

    bool dataChanged=false;

    //rozdelano


    QDateTime parseTimestamp(QString input);
    bool qDomElementValueToBool(QDomElement input);
private:
    QString previousXmlData="";
};




#endif // XMLPARSER_H
