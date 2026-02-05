#ifndef TYPECONVERTOR_H
#define TYPECONVERTOR_H

#include <QStringList>
#include <QMap>

#include "GolemioClient/connectiongolemiov4.h"
#include "DisplayLabel/displaylabellcd2_3cz1_0_jis.h"


class TypeConvertor
{
public:
    TypeConvertor();
    static QString golemioIconToInlineFormattingIcon(QString input);
    static QString golemioIconListToInlineFormattingString(QStringList iconList);
    static ConnectionBasic connectionGolemioV4toConnectionBasic(ConnectionGolemioV4 connectionGolemio);
    static QString lineToIconJisUnderground(QString routeShortName, int routeType);
};

#endif // TYPECONVERTOR_H
