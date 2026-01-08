#ifndef TYPECONVERTOR_H
#define TYPECONVERTOR_H

#include <QStringList>
#include <QMap>


class TypeConvertor
{
public:
    TypeConvertor();
    static QString golemioIconToInlineFormattingIcon(QString input);
    static QString golemioIconListToInlineFormattingString(QStringList iconList);
};

#endif // TYPECONVERTOR_H
