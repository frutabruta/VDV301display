#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QCommandLineParser>


//#include <QWebEngineView>


#ifdef Q_OS_ANDROID
#include <QJniObject>
#include <QCoreApplication>

void keepScreenOn(bool enable)
{
    QJniObject activity = QJniObject::callStaticObjectMethod(
        "org/qtproject/qt/android/QtNative",
        "activity",
        "()Landroid/app/Activity;");

    if (!activity.isValid())
        return;

    QJniObject window = activity.callObjectMethod("getWindow", "()Landroid/view/Window;");
    if (!window.isValid())
        return;

    const int FLAG_KEEP_SCREEN_ON = 128; // WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON

    if (enable)
        window.callMethod<void>("addFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
    else
        window.callMethod<void>("clearFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
}
#endif

QString getWritableDirectory()
{
#ifdef Q_OS_ANDROID
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
#else
    QString dir = QCoreApplication::applicationDirPath();
#endif
    QDir().mkpath(dir);
    return dir;
}

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
   bool result = outFile.open(QIODevice::WriteOnly | QIODevice::Append);
   if(result)
   {
       // outFile.open(QIODevice::WriteOnly);

       QTextStream textStream(&outFile);
       textStream << txt << Qt::endl;

       outFile.close();
   }

}

void copyResourceRecursive(QString resourcePath, QString targetPath)
{
    QDir targetDir(targetPath);
    if (!targetDir.exists())
    {
        targetDir.mkpath(".");
    }

    QDir resourceDir(resourcePath);
    QFileInfoList entries = resourceDir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    QFileInfoList::const_iterator it;
    for (it = entries.constBegin(); it != entries.constEnd(); ++it)
    {
        QFileInfo entry = *it;
        QString destPath = targetPath + "/" + entry.fileName();

        if (entry.isDir())
        {
            copyResourceRecursive(entry.filePath(), destPath);
        }
        else
        {
            if (!QFile::exists(destPath))
            {
                QFile::copy(entry.filePath(), destPath);
                QFile::setPermissions(destPath, QFile::ReadOwner | QFile::WriteOwner);
            }
        }
    }
}

void initializeResources()
{
    copyResourceRecursive(":/", getWritableDirectory());
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

    QString writableDirectory=getWritableDirectory();
    initializeResources();


    QString cesta="";
    //QApplication::applicationDirPath()+"/settings.ini";

    if(!qCommandLineParser.value("config").isEmpty())
    {
       cesta=qCommandLineParser.value("config");
    }
    else
    {
        //cesta=QCoreApplication::applicationDirPath()+"/settings.ini";
        cesta=writableDirectory+"/settings.ini";
    }

    MainWindow w(cesta,nullptr);
    w.show();
    return a.exec();
}
