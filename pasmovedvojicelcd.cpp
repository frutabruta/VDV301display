#include "pasmovedvojicelcd.h"

PasmoveDvojiceLcd::PasmoveDvojiceLcd()
{



}




int PasmoveDvojiceLcd::roztridPasma(QVector<Pasmo> vstup)
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

    foreach(Pasmo pasmo,vstup)
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
