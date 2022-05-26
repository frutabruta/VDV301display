#include "svgvykreslovani.h"
#include <QWidget>
#include <QDebug>
#include <QDomDocument>
#include <QFile>
#include <VDV301struktury/zastavka.h>
#include "VDV301struktury/cestaudaje.h"

SvgVykreslovani::SvgVykreslovani()
{

}


QDomDocument SvgVykreslovani::souborDoQDomDocument(QString cesta)
{
    qDebug()<<"SvgVykreslovani::souborDoQDomDocument";



    qDebug()<<"SvgVykreslovani::svgReplaceName";
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
    qDebug()<<"SvgVykreslovani::qDomDocumentDoSouboru";



    QFile file(cestaVystupnihoSouboru);
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
    qDebug()<<"SvgVykreslovani::svgReplaceName";
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
    qDebug()<<"SvgVykreslovani::individualniNahrazeni "<<hledaneId<<" "<<novaHodnota;
    QDomElement root=xmlDocument.firstChildElement();
    QString idElementu="terminal_station";
    QDomNodeList texty = xmlDocument.elementsByTagName("text");

    for (int i=0;i<texty.length();i++)
    {
        QString idAktElementu=texty.at(i).toElement().attribute("id");
        QString obsah=   texty.at(i).firstChild().firstChild().nodeValue() ;
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

QVector<ZastavkaCil> SvgVykreslovani::vytvorNasledujiciZastavky(QVector<ZastavkaCil> vsechnyZastavky, int index, int limit)
{
    qDebug()<<"SvgVykreslovani::vytvorNasledujiciZastavky";
    QVector<ZastavkaCil> vyslednySeznam;


    for (int i=index; i<vsechnyZastavky.size();i++)
    {
        vyslednySeznam.append(vsechnyZastavky.at(i));
    }


    return vyslednySeznam;
}




QDomDocument SvgVykreslovani::vymazZastavky(QDomDocument xmlDocument)
{
    qDebug()<<"SvgVykreslovani::vymazZastavky";

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

QDomDocument SvgVykreslovani::vykresliZastavky(QDomDocument xmlDocument, QVector<ZastavkaCil> nasledujiciZastavky)
{
    qDebug()<<"SvgVykreslovani::vykresliZastavky";

    for (int i=0;i<5;i++)
    {
        if (i<nasledujiciZastavky.count())
        {
            ZastavkaCil aktZastavka=nasledujiciZastavky.at(i);
            this->individualniNahrazeni(xmlDocument,"pasmo"+QString::number(i),pasmaDoStringu(aktZastavka.zastavka.seznamPasem ) );
            qDebug()<<"zobrazuji pasmo "<<pasmaDoStringu(aktZastavka.zastavka.seznamPasem);
            this->individualniNahrazeni(xmlDocument,"next_stop_"+QString::number(i),aktZastavka.zastavka.NameLcd);
        }
        else
        {
            qDebug()<<"index zastavky "<<QString::number(i)<<"je mimo rozsah "<<QString::number(nasledujiciZastavky.count());
        }


    }

    //this->individualniNahrazeni(xmlDocument,"terminal_station",nasledujiciZastavky.at(0).DestinationName);

    return xmlDocument;
}



QDomDocument SvgVykreslovani::vykresliNacestneZastavky(QDomDocument xmlDocument, QVector<Zastavka> nacestneZastavky)
{
    qDebug()<<"SvgVykreslovani::vykresliNacestneZastavky";
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

QString SvgVykreslovani::vykresliNacestneZastavkyText( QVector<Zastavka> nacestneZastavky)
{
    qDebug()<<"SvgVykreslovani::vykresliNacestneZastavkyText";
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
    qDebug()<<"SvgVykreslovani::vymazObrazovku()";

}






QDomDocument SvgVykreslovani::vykresliCil(QDomDocument xmlDocument, QVector<ZastavkaCil> globalniZastavky, CestaUdaje stav)
{
    qDebug()<<"SvgVykreslovani::vykresliCil";

    if (stav.indexAktZastavky<globalniZastavky.count())
    {
        this->individualniNahrazeni(xmlDocument,"terminal_station",globalniZastavky.at(stav.indexAktZastavky).cil.NameLcd);
    }
    else
    {
        qDebug()<<"index cile je mimo rozsah";
    }
    return xmlDocument;
}

QDomDocument SvgVykreslovani::vykresliLinku(QDomDocument xmlDocument, QVector<ZastavkaCil> globalniZastavky, CestaUdaje stav)
{
    qDebug()<<"SvgVykreslovani::vykresliLinku";

    if (stav.indexAktZastavky<globalniZastavky.count())
    {
        this->individualniNahrazeni(xmlDocument,"line_number",globalniZastavky.at(stav.indexAktZastavky).linka.LineName);
    }
    else
    {
        qDebug()<<"index linky je mimo rozsah";
    }
    return xmlDocument;
}

QString SvgVykreslovani::pasmaDoStringu(QVector<Pasmo> seznamPasem)
{
    qDebug()<<"SvgVykreslovani::pasmaDoStringu";
    QString vysledek;
    if (seznamPasem.size()>0)
    {
        vysledek=seznamPasem.at(0).nazev;
        for (int i=1;i<seznamPasem.size();i++)
        {
            vysledek+=","+seznamPasem.at(i).nazev;
        }
    }
    qDebug()<<"vysledek pasmaDoStringu"<<vysledek;
    return vysledek;
}

int SvgVykreslovani::aktualizujVse(QVector<ZastavkaCil> zastavky, CestaUdaje stav)
{
    QDomDocument xmlko = this->souborDoQDomDocument("hlavni.svg");
    if (xmlko.isNull())
    {
        qDebug()<<"soubor SVG se nenacetl";
    }
    QVector<ZastavkaCil> nasledujiciZastavky=this->vytvorNasledujiciZastavky(zastavky,stav.indexAktZastavky,4);
    xmlko=vymazZastavky(xmlko);
    xmlko=vykresliZastavky(xmlko,nasledujiciZastavky);
    xmlko=vykresliCil(xmlko,zastavky,stav);
    xmlko=vykresliLinku(xmlko,zastavky,stav);
    xmlko=vykresliNacestneZastavky(xmlko,zastavky.at(stav.indexAktZastavky).nacestneZastavky);
    //xmlko=vykresliNacestneZastavky(xmlko,vytvorNacestneZastavky(zastavky,stav.indexAktZastavky));

    qDomDocumentDoSouboru("vystup.svg",xmlko);
    return 1;
}

void SvgVykreslovani::zobrazZmenuPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma)
{
    qDebug()<<"SvgVykreslovani::zobrazZmenuPasma";
}


void SvgVykreslovani::obarviPozadiPristi(QString barvaPisma,QString barvaPozadi)
{
    qDebug()<<"SvgVykreslovani::obarviPozadiPristi";

}


void SvgVykreslovani::zobrazAnnoucement(QString title,QString type,QString textCz, QString textEn)
{
    qDebug()<<"SvgVykreslovani::hlavniZobrazAnnoucement";


}
