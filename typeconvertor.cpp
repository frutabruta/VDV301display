#include "typeconvertor.h"


TypeConvertor::TypeConvertor() {}

QString TypeConvertor::golemioIconListToInlineFormattingString(QStringList iconList)
{
    QString output="";


    foreach(QString icon, iconList)
    {
        output+=golemioIconToInlineFormattingIcon(icon);
    }

    return output;
}


QString TypeConvertor::golemioIconToInlineFormattingIcon(QString input)
{
    QString output="";
    QMap<QString, QString> iconTranslate;
    iconTranslate.insert("a","c_UndergroundA");
    iconTranslate.insert("b","c_UndergroundB");
    iconTranslate.insert("c","c_UndergroundC");
    iconTranslate.insert("d","c_UndergroundD");

    iconTranslate.insert("space"," ");
    iconTranslate.insert("train","c_Train");
    iconTranslate.insert("s_bahn","c_SBahn");
    iconTranslate.insert("metro","c_Underground");

    if(iconTranslate[input]!=" ")
    {
        output="<icon type=\""+iconTranslate[input]+"\">"+input+"</icon>";
    }
    else
    {
        return " ";
    }


    return output;
}
