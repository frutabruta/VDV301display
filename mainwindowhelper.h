#ifndef MAINWINDOWHELPER_H
#define MAINWINDOWHELPER_H

#include <QObject>
#include <QTableWidget>
#include <QLoggingCategory>
#include "VDV301subscriber/VDV301DataStructures/vdv301connection.h"
#include "GolemioClient/connectiongolemiov4.h"
#include "inlineformatparser.h"
#include "DisplayLabel/displaylabel.h"

class MainWindowHelper
{
public:
    MainWindowHelper();
    void connectionListToTable(QVector<Vdv301Connection> connectionList, QTableWidget *tableWidget);
    void eraseTable(QTableWidget *tableWidget);
    void connectionListToTable(QVector<ConnectionGolemioV4> connectionList, QTableWidget *tableWidget);
    void connectionToTable(Vdv301Connection connection, QTableWidget *tableWidget);
    void connectionToTable(ConnectionGolemioV4 connection, QTableWidget *tableWidget);
};

#endif // MAINWINDOWHELPER_H
