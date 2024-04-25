#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QCommandLineParser>


//#include <QWebEngineView>




//https://www.francescmm.com/logging-with-qt/
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
   Q_UNUSED(context);

   QString dt = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
   QString txt = QString("[%1] ").arg(dt);

  // txt += QString("{Critical} \t %1").arg(msg);
   if(type==QtDebugMsg){txt += QString("{Debug} \t\t %1").arg(msg);};
   if(type==QtWarningMsg){  txt += QString("{Warning} \t %1").arg(msg);};
   if(type==QtCriticalMsg){txt += QString("{Critical} \t %1").arg(msg);};
   if(type==QtFatalMsg)
   {
       txt += QString("{Fatal} \t\t %1").arg(msg);
       abort();
   };


   QFile outFile("E:/LogFile.log");
   outFile.open(QIODevice::WriteOnly | QIODevice::Append);

  // outFile.open(QIODevice::WriteOnly);

   QTextStream textStream(&outFile);
   textStream << txt << Qt::endl;

   outFile.close();
}


int main(int argc, char *argv[])
{
    if(QFile::exists("E:/LogFile.log"))
    {
    qInstallMessageHandler(customMessageHandler);
    }


    QApplication a(argc, argv);

    QCommandLineParser qCommandLineParser;
    qCommandLineParser.addOption(QCommandLineOption("config", "Input file path", "file"));
    qCommandLineParser.process(a.arguments());


    QString cesta="";
    //QApplication::applicationDirPath()+"/settings.ini";

    if(!qCommandLineParser.value("config").isEmpty())
    {
       cesta=qCommandLineParser.value("config");
    }
    else
    {
        cesta=QCoreApplication::applicationDirPath()+"/settings.ini";
    }

    MainWindow w(cesta,nullptr);
    w.show();
    return a.exec();
}
