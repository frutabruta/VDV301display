#ifndef INLINEFORMATPARSER_H
#define INLINEFORMATPARSER_H

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>
#include <QtXml>


class Icon {
public:
    QString type="";
    QString alternative="";
};

class Color{
public:
    QString fg="";
    QString bg="";
    QString content="";
};



class InlineFormatParser : public QObject
{
    Q_OBJECT
public:
    InlineFormatParser();

    static QString parseTextLcd(QString vstup, int vyskaObrazku, QString slozka);
    static QString parseTextLed(QString vstup);
private:
    static QDomNode iconToQDomNode(Icon vstup, int vyskaObrazku, QString slozka);
    static QDomNode colorToQDomNode(Color input);
};

#endif // INLINEFORMATPARSER_H
