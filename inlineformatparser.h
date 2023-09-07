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

    QString vyparsujText(QString vstup, int vyskaObrazku, QString slozka);
private:
    QDomNode iconToQDomNode(Icon vstup, int vyskaObrazku, QString slozka);
    QDomNode colorToQDomNode(Color input);
};

#endif // INLINEFORMATPARSER_H
