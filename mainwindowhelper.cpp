#include "mainwindowhelper.h"

Q_LOGGING_CATEGORY(MainWindowHelperLog, "MainWindow")

MainWindowHelper::MainWindowHelper() {}


void MainWindowHelper::connectionListToTable(QVector<Vdv301Connection> connectionList,QTableWidget* tableWidget)
{

    eraseTable(tableWidget);


    foreach(Vdv301Connection connection, connectionList)
    {
        connectionToTable(connection,tableWidget);
    }
}




void MainWindowHelper::connectionListToTable(QVector<ConnectionGolemioV4> connectionList,QTableWidget* tableWidget)
{

    eraseTable(tableWidget);


    foreach(ConnectionGolemioV4 connection, connectionList)
    {
        connectionToTable(connection,tableWidget);
    }
}




void MainWindowHelper::connectionToTable(Vdv301Connection connection, QTableWidget* tableWidget)
{
    qCDebug(MainWindowHelperLog) <<  Q_FUNC_INFO;
    qint32 row;
    QTableWidgetItem *cell;

    if(connection.vdv301displayContentList.isEmpty())
    {
        return;
    }
    else
    {
        Vdv301DisplayContent firstDisplayContent=connection.vdv301displayContentList.first();
        row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        QString lineName=InlineFormatParser::parseTextLed(DisplayLabel::vdv301InternationalTextJoinAll(firstDisplayContent.lineInformation.lineNameList,"\n").text);
        cell = new QTableWidgetItem(lineName);

        tableWidget->setItem(row, 0, cell);

        QString destinationName=InlineFormatParser::parseTextLed(DisplayLabel::vdv301InternationalTextJoinAll(firstDisplayContent.destination.destinationNameList,"\n").text);
        cell = new QTableWidgetItem(destinationName);
        tableWidget->setItem(row, 1, cell);

        cell = new QTableWidgetItem(connection.platform);
        tableWidget->setItem(row, 2, cell);

        cell = new QTableWidgetItem(connection.scheduledDepartureTime.toString("hh:mm") );
        tableWidget->setItem(row, 3, cell);

        cell = new QTableWidgetItem(connection.expectedDepartureTime.toString("hh:mm") );
        tableWidget->setItem(row, 4, cell);

        tableWidget->resizeColumnsToContents();
    }
}

void MainWindowHelper::connectionToTable(ConnectionGolemioV4 connection, QTableWidget* tableWidget)
{
    qCDebug(MainWindowHelperLog) <<  Q_FUNC_INFO;
    qint32 row;
    QTableWidgetItem *cell;

    row = tableWidget->rowCount();
    tableWidget->insertRow(row);

    QString lineName=connection.routeShortName;
    cell = new QTableWidgetItem(lineName);

    tableWidget->setItem(row, 0, cell);

    QString destinationName=connection.tripHeadsign;
    cell = new QTableWidgetItem(destinationName);
    tableWidget->setItem(row, 1, cell);

    cell = new QTableWidgetItem(connection.stopPlatformCode);
    tableWidget->setItem(row, 2, cell);

    cell = new QTableWidgetItem("");
    tableWidget->setItem(row, 3, cell);

    cell = new QTableWidgetItem(connection.departureTimestampMinutes.join(","));
    tableWidget->setItem(row, 4, cell);

    cell = new QTableWidgetItem(QString::number(connection.tripIsGuaranteed));
    tableWidget->setItem(row, 5, cell);

    cell = new QTableWidgetItem(connection.icons.join(","));
    tableWidget->setItem(row, 6, cell);

    tableWidget->resizeColumnsToContents();
}



void MainWindowHelper::eraseTable(QTableWidget *tableWidget)
{
    //used to erase tablewidgets without program crash due to signals
    //  https://stackoverflow.com/a/31564541
    qCDebug(MainWindowHelperLog) <<  Q_FUNC_INFO;

    tableWidget->clearSelection();

    // Disconnect all signals from table widget ! important !
    tableWidget->disconnect();

    // Remove all items
    tableWidget->clearContents();

    // Set row count to 0 (remove rows)
    tableWidget->setRowCount(0);

}
