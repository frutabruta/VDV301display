#include "labelvykreslovani.h"
#include <QtMath>


LabelVykreslovani::LabelVykreslovani()
{

}


void LabelVykreslovani::naplnZmenaLabel(QString vstup, QLabel* stitek)
{
    qDebug()<<"LabelVykreslovani::naplnZmenaLabel";
    stitek->setText(vstup);
}



QString LabelVykreslovani::vyrobTextZmenyPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma)
{
    qDebug()<<"LabelVykreslovani::vyrobTextZmenyPasma";
    QString vysledek="";
    vysledek+="prosím pozor! Změna tarifního pásma: "+SvgVykreslovani::pasmaDoStringu(zPasem)+"->"+SvgVykreslovani::pasmaDoStringu(naPasma);


    return vysledek;
}


void LabelVykreslovani::poleLabelNastavVelikost(QVector<QLabel*> labely, int bodovaVelikost, float pomerBodu)
{
    foreach(QLabel* label, labely)
    {
        QFont fontLabelu =label->font();
        qDebug()<<"pomer stran vyska pomer:"<<pomerBodu;
        fontLabelu.setPixelSize(qFloor(pomerBodu*bodovaVelikost));
        label->setFont(fontLabelu);
    }
}

void LabelVykreslovani::labelNastavVelikost(QLabel* label, int bodovaVelikost, float pomerBodu)
{
    QFont fontLabelu =label->font();
   // qDebug()<<"pomer stran vyska pomer:"<<pomerBodu;
    fontLabelu.setPixelSize(qFloor(pomerBodu*bodovaVelikost));
    label->setFont(fontLabelu);
}

void LabelVykreslovani::zmensiCisloLinkyLabel( QLabel* label)
{
    qDebug()<<"LabelVykreslovani::naplnCisloLinkyLabel";

    QFont puvodniFont=label->font();
    puvodniFont.setPixelSize(label->height());
    label->setFont(puvodniFont);

    int vyskaLabelu=label->height();
    int sirkaLabelu=label->width();

    int vyskaFontu= label->fontMetrics().boundingRect(label->text()).height();
    int sirkaFontu= label->fontMetrics().boundingRect(label->text()).width();

    qDebug()<<"V labelu "<<vyskaLabelu<<" V Fontu "<< vyskaFontu <<" S labelu "<<sirkaLabelu<<" S fontu "<< sirkaFontu;


    int counter=0;
    while(((sirkaFontu>sirkaLabelu) || (vyskaFontu>vyskaLabelu))&&(counter<4 ) )
    {
        puvodniFont.setPixelSize(qRound( puvodniFont.pixelSize()*0.90));

        vyskaFontu= label->fontMetrics().boundingRect(label->text()).height();
        sirkaFontu= label->fontMetrics().boundingRect(label->text()).width();
        label->setFont(puvodniFont);
        counter++;
    }


    /*
    int velikostFontuDefault=80;
    label->setFont(QFont("Roboto",velikostFontuDefault ));
   label->update();
    int pomer= int(sirkaFontu/sirkaLabelu);
    label->setFont(QFont("Roboto",velikostFontuDefault*pomer ));
   label->update();
*/
    /*
    QFont font("times", 24);
    QFontMetrics fm(font);
    int pixelsWide = fm.horizontalAdvance("What's the width of this text?");
    int pixelsHigh = fm.height();
    */
}

void LabelVykreslovani::naplnNazevCileLabel(QString vstup, QLabel* label)
{
    qDebug()<<"LabelVykreslovani::naplnNazevCileLabel";
    label->setText(vstup);
}


void LabelVykreslovani::naplnAnouncementLabel(QString vstup, QLabel* label)
{
    qDebug()<<"LabelVykreslovani::naplnAnouncementLabel";
    label->setText(vstup);
    //ui->label_announcement->setText(vstup);
}



void LabelVykreslovani::obarviPozadiPristi(QString barvaPisma,QString barvaPozadi,QFrame* qframe)
{
    qDebug()<<"LabelVykreslovani::obarviPozadiPristi";
    //
    qframe->setStyleSheet("background-color :"+barvaPozadi+" ; color : "+barvaPisma+"; ");
    //  ui->frame_spodniRadek->setStyleSheet("background-color :"+barvaPozadi+" ; color : "+barvaPisma+"; ");
}

void LabelVykreslovani::poleLabelNastavSirku(QVector<QLabel*> seznamLabelu, int sirka)
{
    foreach(QLabel* label, seznamLabelu)
    {
        label->setMaximumWidth(sirka);
    }
}

void LabelVykreslovani::poleLabelNastavVysku(QVector<QLabel*> seznamLabelu, int vyska)
{
    foreach(QLabel* label, seznamLabelu)
    {
        label->setMaximumHeight(vyska);
    }
}

QString LabelVykreslovani::nahradMetro(QString linka, QString submode, int vyska)
{
    QString vysledek=linka;

    if(submode=="metro")
    {
        vysledek="<html><head/><body><p><img src=\":/images/Underground"+linka+"\" height=\""+QString::number(vyska)+"\" /></p></body></html>";
    }


    //<html><head/><body><p><img src=":/images/UndergroundA" height="50" /></p></body></html>
    qDebug()<<"nahradMetro:"<<vysledek;
    return vysledek;

}


QString LabelVykreslovani::vykresliNacestneZastavkyText( QVector<Zastavka> nacestneZastavky)
{
    qDebug()<<"MainWindow::vykresliNacestneZastavkyText";
    if (nacestneZastavky.count()==0)
    {
        return "";
    }

    QString nacestyString="";



    nacestyString+=  doplnPiktogramyBezZacatkuKonce(nacestneZastavky.at(0).NameLcd,nacestneZastavky.at(0).seznamPiktogramu);
    for (int i=1;i<nacestneZastavky.count();i++)
    {
        nacestyString+=" – "+doplnPiktogramyBezZacatkuKonce( nacestneZastavky.at(i).NameLcd, nacestneZastavky.at(i).seznamPiktogramu);
    }


    QString htmlZacatek="<html><head/><body><p>";
    QString htmlKonec="</p></body></html>";

    QString vysledek=htmlZacatek+nacestyString+htmlKonec;
    qDebug()<<"vypis radku nacestnych zastavek text html"<<vysledek;
    return vysledek;
}


QString LabelVykreslovani::doplnPiktogramyBezZacatkuKonce(QString nazevZastavky,QVector<QString> seznamPiktogramu)
{
    QString vystup="";
    int vyskaObrazku=40; //konstanta v px, ovlivnuje vysku piktogramu
    QString htmlObrazky="";

    foreach(QString nazevPiktogramu,seznamPiktogramu)
    {
        htmlObrazky+="<img  src=\":/images/"+nazevPiktogramu+"\" height=\""+QString::number(vyskaObrazku)+"\"  >";
    }

    vystup=nazevZastavky+htmlObrazky;
    return vystup;

}


QString LabelVykreslovani::zabalHtmlDoZnacek(QString vstup)
{
    return "<html><head/><body><p>"+vstup+"</p></body></html>";
}


int LabelVykreslovani::minimum(int cislo1, int cislo2)
{
    if(cislo1<cislo2)
    {
        return cislo1;
    }
    return cislo2;
}



void LabelVykreslovani::vykresliNacestneForce(QVector<ZastavkaCil> globalniSeznamZastavek,CestaUdaje stavSystemu, QLabel* label)
{
    qDebug()<<"LabelVykreslovani::vykresliNacestneForce()";

    //label_nacestne
    if(globalniSeznamZastavek.isEmpty())
    {
        label->setText("");
        return;
    }

    label->setText(" ");
    QString novyVstup=vykresliNacestneZastavkyText(globalniSeznamZastavek.at(stavSystemu.indexAktZastavky).nacestneZastavky);
    label->setText( novyVstup);
}
