#include <at89x51.h>
#include "display.h"

void delay()
{
    unsigned int t;
    for (t = 0; t < 600; t++);
}

void imprimeDisplay(char dezenaMin, char unidadeMin, char dezenaSeg, char unidadeSeg)
{

    switch (3)
    {
    case 3:
        P2 = numDisp[dezenaMin];
        DISP3 = 1;
        delay();
        DISP3 = 0;

    case 2:
        P2 = numDisp[unidadeMin];
        DISP2 = 1;
        delay();
        DISP2 = 0;

    case 1:
        P2 = numDisp[dezenaSeg];
        DISP1 = 1;
        delay();
        DISP1 = 0;

    case 0:
        P2 = numDisp[unidadeSeg];
        DISP0 = 1;
        delay();
        DISP0 = 0;
    }
}
