#ifndef DISPLAY_H
#define DISPLAY_H


#define DISP0 P1_0
#define DISP1 P1_1
#define DISP2 P1_2
#define DISP3 P1_3


__code unsigned char numDisp[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void delay();
void imprimeDisplay(char dezenaMin, char unidadeMin, char dezenaSeg, char unidadeSeg);

#endif