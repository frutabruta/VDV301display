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



ConnectionBasic TypeConvertor::connectionGolemioV4toConnectionBasic(ConnectionGolemioV4 connectionGolemio)
{
    ConnectionBasic output;

    // output.lineName=lineToIconJisUnderGround("C",1);
    output.lineName=lineToIconJisUnderground(connectionGolemio.routeShortName,connectionGolemio.routeType);
    if(connectionGolemio.routeType==1)
    {
        output.platform="";
    }
    else
    {
        output.platform=connectionGolemio.stopPlatformCode;
    }
    output.destinationName=connectionGolemio.tripHeadsign;
    output.destinationName+=TypeConvertor::golemioIconListToInlineFormattingString(connectionGolemio.icons);
    output.departureTime=connectionGolemio.departureTimestampMinutes.join(" min.    ");



    return output;
}


QString TypeConvertor::lineToIconJisUnderground(QString routeShortName,int routeType)
{
    QString output="";

    if(routeType==1)
    {
        output="<icon type=\"c_Underground"+routeShortName+"\">["+routeShortName+"]</icon>";
    }
    else
    {
        output=routeShortName;
    }


    return output;
}


int TypeConvertor::vehicleSubmodeToGolemioType(QString subMode)
{
    QMap<QString,int> types;

    types.insert("TramSubmode",0);
    types.insert("MetroSubmode",1);
    types.insert("RailSubmode",2);
    types.insert("BusSubmode",3);
    types.insert("WaterSubmode",4);
    types.insert("FunicularSubmode",7);
    types.insert("TrolleybusSubmode",11);

    return types.value(subMode);

}
