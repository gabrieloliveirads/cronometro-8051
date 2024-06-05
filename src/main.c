#include <at89x51.h>
#include "display.h"

#define BTN_START_STOP P1_4

enum fsm
{
    INICIO = 0,
    CONTAGEM
};

volatile char dezenaMim = 0, unidadeMim = 0, dezenaSeg = 0, unidadeseg = 0;

volatile int contaUmSegundo = 0;

void init()
{
    P2 = 0;
    P1_4 = 0; // configura P1_4 como entrada
}
void timerConfig()
{
    // TIMER0 no modo 16bits(0->65535) | Período 750n
    /*
    Configuração do modo do contador:
    tamanho: 16bits
    */
    TMOD = 0X01;
    //carrega 0x2faa como valor inicial para contagem de 40ms 
    TH0 = 0x2F;
    TL0 = 0XAA;
    /*
    TCOM: apemans um bit de interesse -> TR0 (inicia  a contagem). E TF0 para monitorar
    */
    EA  = 1; // Habilita interrupção do timer0
}
void isrConfig()
{
    /*
    IE: inicialmente ET0 será setado. IE = 0x02;
    */
    //    IE = 0x02;
    ET0 = 1;
}

int main()
{
    char ESTADO = 0;

    init();
    timerConfig();
    isrConfig();

    while (1)
    {
        switch (ESTADO)
        {
        case INICIO:
            if (BTN_START_STOP == 0)
            {
                ESTADO = INICIO;
            }else{
                ESTADO = CONTAGEM;
                TR0 = 1; //Liga TIMER0
            }
            break;
        
        case CONTAGEM:
            if(BTN_START_STOP != 0)
            {
                TR0 = 0; //Desliga TIMER0
                ESTADO = INICIO;
            }
            break;
        }

        imprimeDisplay(dezenaMim, unidadeMim, dezenaSeg, unidadeseg);
    }
}

void timer_isr(void) __interrupt(1)
{
    TH0 = 0x2F;
    TL0 = 0XAA;

    contaUmSegundo++;

    if (contaUmSegundo == 25)
    {
        contaUmSegundo = 0;

        unidadeseg += 1;

        if (unidadeseg > 9)
        {
            unidadeseg = 0;
            dezenaSeg += 1;

            if (dezenaSeg > 5)
            {
                dezenaSeg = 0;
                unidadeMim += 1;

                if (unidadeMim > 9)
                {
                    unidadeMim = 0;
                    dezenaMim += 1;

                    if (dezenaMim > 9)
                    {
                        unidadeseg = 0;
                        dezenaSeg = 0;
                        unidadeMim = 0;
                        dezenaMim = 0;
                    }
                }
            }
        }
    }
}