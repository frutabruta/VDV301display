#include "vdv301messagelogger.h"


Q_LOGGING_CATEGORY(Vdv301MessageLoggerLog, "Vdv301MessageLogger")


Vdv301MessageLogger::Vdv301MessageLogger()
{

}



int Vdv301MessageLogger::initialize()
{

    qCDebug(Vdv301MessageLoggerLog)<<Q_FUNC_INFO;

    // zdroj: https://stackoverflow.com/questions/5444959/read-a-text-file-line-by-line-in-qt

    // QDomElement vystup;
    int counter=0;

    hlavicka<<"timestamp";
    hlavicka<<"vehicleState";
    hlavicka<<"currentStopIndex";
    hlavicka<<"stopPointCount";
    hlavicka<<"connectionsCount";
    hlavicka<<"content";



    //sqLiteZaklad.dbFilePath="data.sqlite";

    if(!sqLiteZaklad.initialize())
    {
        qCDebug(Vdv301MessageLoggerLog)<<"initialization failed";
        return 0;
    }
    else
    {
        qCDebug(Vdv301MessageLoggerLog)<<"initialization OK";

        if(!sqLiteZaklad.tableCreate(tableName,hlavicka))
        {
            qCDebug(Vdv301MessageLoggerLog)<<"Failed to create table";
            insertQuery = prepareInsertQuery(hlavicka,sqLiteZaklad);
            return false;
        }
        insertQuery = prepareInsertQuery(hlavicka,sqLiteZaklad);

        return counter;
    }
}


void Vdv301MessageLogger::stop()
{
    sqLiteZaklad.dbClose();
}


void Vdv301MessageLogger::addRecord(QDateTime timestamp, QString content, int stopPointCount,int currentStopIndex, QString locationState, int connectionsCount )
{
    qCDebug(Vdv301MessageLoggerLog)<<Q_FUNC_INFO;

    QHash<QString, QString>  obsah;

    obsah.insert("timestamp",timestamp.toString(Qt::ISODateWithMs));
    obsah.insert("vehicleState",locationState);
    obsah.insert("currentStopIndex",QString::number(currentStopIndex));
    obsah.insert("stopPointCount",QString::number(stopPointCount));
    obsah.insert("connectionsCount",QString::number(connectionsCount));
    obsah.insert("content",content);


    sqLiteZaklad.insertDataRow(insertQuery,toQVectorQString(obsah,hlavicka));

}
QSqlQuery Vdv301MessageLogger::prepareInsertQuery(QVector<QString> &hlavicka, SqLiteBase &sqLiteZaklad)
{
    qCDebug(Vdv301MessageLoggerLog)<<Q_FUNC_INFO;



    /////////////////


    //qCDebug(Vdv301MessageLoggerLog) << Q_FUNC_INFO;
    /*
    if (hlavicka.size() != data.size())
    {
        qCDebug(Vdv301MessageLoggerLog) << "insertDataRow failed: header/data size mismatch";
        qCDebug(Vdv301MessageLoggerLog) << "hlavicka size:" << hlavicka.size();
        qCDebug(Vdv301MessageLoggerLog) << "data size:" << data.size();
        return false;
    }*/

    /*
    if (!sqLiteZaklad.dbFile.isOpen())
    {
        qCDebug(Vdv301MessageLoggerLog) << "insertDataRow failed: database is not open";
        qCDebug(Vdv301MessageLoggerLog) << sqLiteZaklad.dbFile.lastError().text();
        return;
    }
*/

    QString safeTableName = sqLiteZaklad.sanitizeSqlIdentifier(tableName);

    QVector<QString> safeColumns;
    QVector<QString> placeholders;

    for (int i = 0; i < hlavicka.size(); i++)
    {
        safeColumns.append(sqLiteZaklad.sanitizeSqlIdentifier(hlavicka.at(i)));
        placeholders.append("?");
    }

    QString queryText = QString("INSERT INTO %1 (%2) VALUES (%3);")
                            .arg(
                                safeTableName,
                                safeColumns.join(","),
                                placeholders.join(",")
                                );

    //qCDebug(Vdv301MessageLoggerLog) << queryText;

    QSqlQuery query(sqLiteZaklad.dbFile);

    if (!query.prepare(queryText))
    {
        qCDebug(Vdv301MessageLoggerLog) << "Prepare failed:";
        qCDebug(Vdv301MessageLoggerLog) << query.lastError().text();
        qCDebug(Vdv301MessageLoggerLog) << queryText;
    }

    return query;
}


QVector<QString> Vdv301MessageLogger::toQVectorQString(QHash<QString, QString> content, QVector<QString> &hlavicka)
{
    //  qCDebug(Vdv301MessageLoggerLog)<<"ZaznamMpvLogu::vypisCsv()";
    QVector<QString> vystup;
    QString separator=";";


    /*
    foreach( QString polozka,hlavicka)
    {
        vystup+=escape(this->Obsah.value(polozka));
        vystup+=separator;
    }*/


    foreach(QString polozkaHlavicky, hlavicka)
    {
        vystup.push_back(escape(content.value(polozkaHlavicky)));
        // qCDebug(Vdv301MessageLoggerLog)<<"polozka "<<polozka;


    }
    //vystup+=escape(this->Obsah.value(hlavicka.last()));


    // vystup+="\n";

    return vystup;
}



QString Vdv301MessageLogger::escape(QString vstup)
{
    QString vystup;
    vystup= "\""+vstup+"\"";
    return vystup;
}


void Vdv301MessageLogger::truncateDb()
{
    sqLiteZaklad.truncateTable(tableName);
}
