#include "pasmovedvojicelcd.h"

PasmoveDvojiceLcd::PasmoveDvojiceLcd()
{



}




int PasmoveDvojiceLcd::roztridPasma(QVector<FareZone> vstup)
{
    pasmaSystemu1.clear();
    pasmaSystemu2.clear();


    if(vstup.isEmpty())
    {
        return 0;
    }

    prvniPasmo=vstup.first();

    QString prvniPasmoTyp=prvniPasmo.system;
    QString druhePasmoTyp="";

    foreach(FareZone pasmo,vstup)
    {
        if (pasmo.system==prvniPasmoTyp)
        {
            pasmaSystemu1.append(pasmo);
        }

        else
        {
            if(druhePasmoTyp=="")
            {
                druhePasmoTyp=pasmo.system;
                pasmaSystemu2.append(pasmo);
            }
            else
            {
                if(pasmo.system==druhePasmoTyp)
                {
                    pasmaSystemu2.append(pasmo);
                }
            }




        }
    }



    return 1;
}


int PasmoveDvojiceLcd::roztridPasma2_3(QVector<FareZone> vstup)
{
    pasmaSystemu1.clear();
    pasmaSystemu2.clear();


    if(vstup.isEmpty())
    {
        return 0;
    }


    pasmaSystemu1.append(vstup.first());
    if(vstup.count()>1)
    {
        pasmaSystemu2.append(vstup.at(1));
    }


    return 1;
}
