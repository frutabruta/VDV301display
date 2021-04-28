#include "svgvykreslovani.h"
#include <QWidget>
#include <QDebug>
#include <QDomDocument>
#include <QFile>

SvgVykreslovani::SvgVykreslovani()
{

}




bool SvgVykreslovani::svgReplaceName(QString souborVstup, QString souborVystup,QString cil, QString zst0, QString zst1, QString zst2)
{
    qDebug()<<"MainWindow::svgReplaceName";
    QDomDocument xmlDocument;
    QFile f(souborVstup);
    if(!f.open(QIODevice::ReadOnly))
    {
        qDebug("Error While Reading the File");
        return 0;
    }

    xmlDocument.setContent(&f);
    f.close();
    qDebug("File was closed Successfully");



    this->individualniNahrazeni(xmlDocument,"terminal_station",cil);
    this->individualniNahrazeni(xmlDocument,"next_stop_0",zst0);
    this->individualniNahrazeni(xmlDocument,"next_stop_1",zst1);
    this->individualniNahrazeni(xmlDocument,"next_stop_2",zst2);



    QFile file(souborVystup);
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug("Error While Reading the File");
        return 0;
    }
        QByteArray msg=xmlDocument.toByteArray();
        file.write(msg, qstrlen(msg));        // write to stderr
        file.close();

    return 1;
}


bool SvgVykreslovani::individualniNahrazeni(QDomDocument &xmlDocument, QString hledaneId, QString novaHodnota)
{
    QDomElement root=xmlDocument.firstChildElement();
    QString idElementu="terminal_station";
    QDomNodeList texty = xmlDocument.elementsByTagName("text");

    for (int i=0;i<texty.length();i++)
    {
        QString idAktElementu=texty.at(i).toElement().attribute("id");
        QString obsah=   texty.at(i).firstChild().firstChild().nodeValue() ;
        //firstChildElement().nodeValue()
        qDebug()<<"nalezeny element "<<idAktElementu<<"nodeValue "<<obsah;
        if (idAktElementu==hledaneId)
        {
            qDebug()<<"menim obsah";
            texty.at(i).firstChild().firstChild().setNodeValue(novaHodnota);
        }
    }
    return 1;
}

