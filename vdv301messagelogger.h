#ifndef VDV301MESSAGELOGGER_H
#define VDV301MESSAGELOGGER_H

#include "XmlRopidImportStream/sqlitebase.h"

class Vdv301MessageLogger
{
public:
    Vdv301MessageLogger();
    QSqlQuery prepareInsertQuery(QVector<QString> &hlavicka, SqLiteBase &sqLiteZaklad);

    int initialize();
    void stop();
    void addRecord(QDateTime timestamp, QString content, int stopPointCount, int currentStopIndex, QString locationState, int connectionsCount);
    void truncateDb();
protected:
    SqLiteBase sqLiteZaklad;
    QVector<QString> hlavicka;

    QSqlQuery insertQuery;

    QString escape(QString vstup);
    QVector<QString> toQVectorQString(QHash<QString, QString> content, QVector<QString> &hlavicka);
    QString tableName="messages";
};

#endif // VDV301MESSAGELOGGER_H
