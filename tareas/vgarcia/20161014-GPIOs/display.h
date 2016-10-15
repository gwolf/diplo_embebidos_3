#ifndef DISPLAY_H
#define DISPLAY_H
/*
 * display.h:
 *
 *    Aqui se encuentran las definiciones de los segmentos del display
 *    y los codigos de cada digito del contador
 ***********************************************************************
 */


/*
 * DEFINICION DE SEGMENTOS (A-G) DEL DISPLAY.
 *	 ____
 *     F| A  |B
 *	|____|
 *     E| G  |C
 *	|____|
 *	  D
*/
#define	SEG_G	0
#define SEG_F	1
#define SEG_E	2
#define SEG_D	3
#define SEG_C	4
#define SEG_B	5
#define SEG_A	6

#define CTRL 	7
/*
 * ABCDEFG DIGITO CODIGO
 * 1111110   0     7EH
 * 0110000   1     30H
 * 1101101   2     6DH
 * 1111001   3     79H
 * 0110011   4     33H
 * 1011011   5     5BH
 * 1011111   6     5FH
 * 1110000   7     70H
 * 1111111   8     7FH
 * 1111011   9     7BH
 * 1110111   A     77H
 * 0011111   b     1FH
 * 1001110   C     4EH
 * 0111101   d     3DH
 * 1001111   E     4FH
 * 1000111   F     47H
*/
#define DIG_0	0x7E
#define DIG_1	0x30
#define DIG_2	0x6D
#define DIG_3	0x79
#define DIG_4	0x33
#define DIG_5	0x5B
#define DIG_6	0x5F
#define DIG_7	0x70
#define DIG_8	0x7F
#define DIG_9	0x7B
#define DIG_A	0x77
#define DIG_B	0x1F
#define DIG_C	0x4E
#define DIG_D	0x3D
#define DIG_E	0x4F
#define DIG_F	0x47
#define DIG_Z	0x00

void  escribeDatoDisp( unsigned char );

#endif
