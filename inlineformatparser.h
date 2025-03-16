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


class Font{
public:
    QString type="";
    QString size="";
    QString content="";
};




class InlineFormatParser : public QObject
{
    Q_OBJECT
public:
    InlineFormatParser();

    static QString parseTextLcd(QString vstup, int vyskaObrazku, QString slozka);
    static QString parseTextLed(QString vstup);

    static QString parseTextLcdOuter(QString vstup, int vyskaObrazku, QString slozka, QString &bgColor);
    static QString parseTextLcdRecursive(QXmlStreamReader &xmlReader, QString parent, int vyskaObrazku, QString slozka, QString &bgColor);

    static QString iconToQDomNodeStart(Icon vstup, int vyskaObrazku, QString slozka);
private:
    static QDomNode iconToQDomNode(Icon vstup, int vyskaObrazku, QString slozka);
    static QDomNode colorToQDomNode(Color input);
    static QDomNode fontToQDomNode(Font input);
    static QDomNode boldToQDomNode(QString input);
    static QString fontToQDomNodeStart(Font input);
    static QString colorToQDomNodeStart(QString fg, QString bg);
    static QString getDirectParent(QString input);
};

#endif // INLINEFORMATPARSER_H
