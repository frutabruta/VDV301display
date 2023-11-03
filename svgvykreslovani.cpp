#include "svgvykreslovani.h"
#include <QWidget>
#include <QDebug>
#include <QDomDocument>
#include <QFile>
#include "VDV301DataStructures/stoppoint.h"
#include "VDV301DataStructures/vehiclestate.h"

SvgVykreslovani::SvgVykreslovani(QString cesta)
{
    interniCestaSlozkaSvg=cesta;
}


QDomDocument SvgVykreslovani::souborDoQDomDocument(QString cesta)
{
    qDebug()<<Q_FUNC_INFO;

    QDomDocument xmlDocument;
    QFile f(cesta);
    if(!f.open(QIODevice::ReadOnly))
    {
        qDebug("Error While Reading the File");
        //return 0;
    }

    xmlDocument.setContent(&f);
    f.close();
    qDebug("File was closed Successfully");
    return xmlDocument;
}

int SvgVykreslovani::qDomDocumentDoSouboru(QString cestaVystupnihoSouboru,QDomDocument vstupniDom)
{
    qDebug()<<Q_FUNC_INFO;



    QFile file(cestaVystupnihoSouboru);
    qDebug()<<"zapisuju svg do "<<cestaVystupnihoSouboru;
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug("Error While Reading the File");
        return 0;
    }
    QByteArray msg=vstupniDom.toByteArray();
    file.write(msg, qstrlen(msg));        // write to stderr
    file.close();
    return 1;
}

bool SvgVykreslovani::svgReplaceName(QString souborVstup, QString souborVystup,QString cil, QString zst0, QString zst1, QString zst2)
{
    qDebug()<<Q_FUNC_INFO;
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
    qDebug()<<Q_FUNC_INFO<<" "<<hledaneId<<" "<<novaHodnota;

    QDomNodeList texty = xmlDocument.elementsByTagName("text");

    for (int i=0;i<texty.length();i++)
    {
        QString idAktElementu=texty.at(i).toElement().attribute("id");

        //firstChildElement().nodeValue()
        //  qDebug()<<"nalezeny element "<<idAktElementu<<"nodeValue "<<obsah;
        if (idAktElementu==hledaneId)
        {
            qDebug()<<"menim obsah";
            texty.at(i).firstChild().firstChild().setNodeValue(novaHodnota);
            return 1;
        }
    }
    return 0;
}

QVector<StopPointDestination> SvgVykreslovani::vytvorNasledujiciZastavky(QVector<StopPointDestination> vsechnyZastavky, int index, int limit)
{
    qDebug()<<Q_FUNC_INFO;
    QVector<StopPointDestination> vyslednySeznam;


    for (int i=index; i<vsechnyZastavky.size();i++)
    {
        vyslednySeznam.append(vsechnyZastavky.at(i));
    }


    return vyslednySeznam;
}




QDomDocument SvgVykreslovani::vymazZastavky(QDomDocument xmlDocument)
{
    qDebug()<<Q_FUNC_INFO;

    for (int i=0;i<5;i++)
    {
        //this->individualniNahrazeni(xmlDocument,"pasmo"+QString::number(i)," ");
        this->individualniNahrazeni(xmlDocument,"next_stop_"+QString::number(i)," ");
        this->individualniNahrazeni(xmlDocument,"pasmo"+QString::number(i)," ");
    }

    //cil
    this->individualniNahrazeni(xmlDocument,"terminal_station"," ");
    //nacsty
    this->individualniNahrazeni(xmlDocument,"viaStops"," ");
    //linka
    this->individualniNahrazeni(xmlDocument,"line_number"," ");

    return xmlDocument;
}

QDomDocument SvgVykreslovani::vykresliZastavky(QDomDocument xmlDocument, QVector<StopPointDestination> nasledujiciZastavky)
{
    qDebug()<<Q_FUNC_INFO;

    for (int i=0;i<5;i++)
    {
        if (i<nasledujiciZastavky.count())
        {
            StopPointDestination aktZastavka=nasledujiciZastavky.at(i);
            this->individualniNahrazeni(xmlDocument,"pasmo"+QString::number(i),pasmaDoStringu(aktZastavka.stopPoint.fareZoneList ) );
            qDebug()<<"zobrazuji pasmo "<<pasmaDoStringu(aktZastavka.stopPoint.fareZoneList);
            this->individualniNahrazeni(xmlDocument,"next_stop_"+QString::number(i),aktZastavka.stopPoint.NameLcd);
        }
        else
        {
            qDebug()<<"index zastavky "<<QString::number(i)<<"je mimo rozsah "<<QString::number(nasledujiciZastavky.count());
        }


    }

    //this->individualniNahrazeni(xmlDocument,"terminal_station",nasledujiciZastavky.at(0).DestinationName);

    return xmlDocument;
}



QDomDocument SvgVykreslovani::vykresliNacestneZastavky(QDomDocument xmlDocument, QVector<StopPoint> nacestneZastavky)
{
    qDebug()<<Q_FUNC_INFO;
    if (nacestneZastavky.count()==0)
    {
        return xmlDocument;
    }

    QString nacestyString="";
    nacestyString+=nacestneZastavky.at(0).NameLcd;
    for (int i=1;i<nacestneZastavky.count();i++)
    {
        nacestyString+=" – "+nacestneZastavky.at(i).NameLcd;
    }
    qDebug()<<"vypis radku nacestnych zastavek"<<nacestyString;
    this->individualniNahrazeni(xmlDocument,"viaStops",nacestyString);

    //this->individualniNahrazeni(xmlDocument,"terminal_station",nasledujiciZastavky.at(0).DestinationName);

    return xmlDocument;
}

QString SvgVykreslovani::vykresliNacestneZastavkyText( QVector<StopPoint> nacestneZastavky)
{
    qDebug()<<Q_FUNC_INFO;
    if (nacestneZastavky.count()==0)
    {
        return "";
    }

    QString nacestyString="";



    nacestyString+=  nacestneZastavky.at(0).NameLcd;
    for (int i=1;i<nacestneZastavky.count();i++)
    {
        nacestyString+=" – "+nacestneZastavky.at(i).NameLcd;
    }
    qDebug()<<"vypis radku nacestnych zastavek"<<nacestyString;
    return nacestyString;
}

void SvgVykreslovani::vymazObrazovku()
{
    qDebug()<<Q_FUNC_INFO;



    QString celaCesta=interniCestaSlozkaSvg+"/hlavni.svg";

    QDomDocument xmlko = this->souborDoQDomDocument(celaCesta);
    if (xmlko.isNull())
    {
        qDebug()<<"soubor SVG se nenacetl";
    }
    xmlko=vymazZastavky(xmlko);
    qDomDocumentDoSouboru(interniCestaSlozkaSvg+"/vystup.svg",xmlko);
}






QDomDocument SvgVykreslovani::vykresliCil(QDomDocument xmlDocument, QVector<StopPointDestination> globalniZastavky, VehicleState stav)
{
    qDebug()<<Q_FUNC_INFO;

    if (stav.currentStopIndex0<globalniZastavky.count())
    {
        this->individualniNahrazeni(xmlDocument,"terminal_station",globalniZastavky.at(stav.currentStopIndex0).destination.NameLcd);
    }
    else
    {
        qDebug()<<"index cile je mimo rozsah";
    }
    return xmlDocument;
}

QDomDocument SvgVykreslovani::vykresliLinku(QDomDocument xmlDocument, QVector<StopPointDestination> globalniZastavky, VehicleState stav)
{
    qDebug()<<Q_FUNC_INFO;

    if (stav.currentStopIndex0<globalniZastavky.count())
    {
        this->individualniNahrazeni(xmlDocument,"line_number",globalniZastavky.at(stav.currentStopIndex0).line.lineName);
    }
    else
    {
        qDebug()<<"index linky je mimo rozsah";
    }
    return xmlDocument;
}

QString SvgVykreslovani::pasmaDoStringu(QVector<FareZone> seznamPasem)
{
    qDebug()<<Q_FUNC_INFO;
    QString vysledek;
    if (seznamPasem.size()>0)
    {
        vysledek=seznamPasem.at(0).name;
        for (int i=1;i<seznamPasem.size();i++)
        {
            vysledek+=","+seznamPasem.at(i).name;
        }
    }
    qDebug()<<"vysledek pasmaDoStringu"<<vysledek;
    return vysledek;
}

int SvgVykreslovani::aktualizujVse(QVector<StopPointDestination> zastavky, VehicleState stav)
{
    QString celaCesta=interniCestaSlozkaSvg+"/hlavni.svg";
    qDebug()<<"cesta k hlavnimu SVG: "<<celaCesta;
    QDomDocument xmlko = this->souborDoQDomDocument(celaCesta);
    if (xmlko.isNull())
    {
        qDebug()<<"soubor SVG se nenacetl";
    }
    QVector<StopPointDestination> nasledujiciZastavky=this->vytvorNasledujiciZastavky(zastavky,stav.currentStopIndex0,4);
    xmlko=vymazZastavky(xmlko);
    xmlko=vykresliZastavky(xmlko,nasledujiciZastavky);
    xmlko=vykresliCil(xmlko,zastavky,stav);
    xmlko=vykresliLinku(xmlko,zastavky,stav);
    xmlko=vykresliNacestneZastavky(xmlko,zastavky.at(stav.currentStopIndex0).viaPoints);
    //xmlko=vykresliNacestneZastavky(xmlko,vytvorNacestneZastavky(zastavky,stav.indexAktZastavky));

    qDomDocumentDoSouboru(interniCestaSlozkaSvg+"/vystup.svg",xmlko);
    return 1;
}

void SvgVykreslovani::zobrazZmenuPasma(QVector<FareZone> zPasem, QVector<FareZone> naPasma)
{
    qDebug()<<Q_FUNC_INFO;
}


void SvgVykreslovani::obarviPozadiPristi(QString barvaPisma,QString barvaPozadi)
{
    qDebug()<<Q_FUNC_INFO;

}


void SvgVykreslovani::zobrazAnnoucement(QString title,QString type,QString textCz, QString textEn)
{
    qDebug()<<Q_FUNC_INFO;


}
