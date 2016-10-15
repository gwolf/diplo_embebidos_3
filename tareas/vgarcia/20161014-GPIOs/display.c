/*
 * display.c:
 *
 *    Este programa manda un contador hexadecimal decodificado
 *    a un display de siete segmentos de catodo comun
 *    Se utiliza una señal de control de entrada para manejar
 *    conteo ascendente y desendente. 
 *    CTRL = 1, conteo ascendente
 *    CTRL = 0, conteo descendente
 ***********************************************************************
 */

#include <stdio.h>
#include <wiringPi.h>
#include "display.h"

unsigned char contador [] =
	{
		DIG_0, DIG_1, DIG_2, DIG_3, DIG_4, DIG_5, DIG_6, DIG_7,
		DIG_8, DIG_9, DIG_A, DIG_B, DIG_C, DIG_D, DIG_E, DIG_F
	};

int main ( void )
{
  register int c, d;

  printf ("PRACTICA: MANEJO DE DISPLAY\n") ;

  wiringPiSetup () ;
//CONFIGURACION DE SEGMENTOS DEL DISPLAY COMO SALIDAS
  pinMode (SEG_G, OUTPUT) ;
  pinMode (SEG_F, OUTPUT) ;
  pinMode (SEG_E, OUTPUT) ;
  pinMode (SEG_D, OUTPUT) ;
  pinMode (SEG_C, OUTPUT) ;
  pinMode (SEG_B, OUTPUT) ;
  pinMode (SEG_A, OUTPUT) ;
//CONFIGURACION DE LA ENTRADA DE CONTROL
  pinMode (CTRL, INPUT) ;
  pullUpDnControl(CTRL,PUD_UP);

  d = 0;
  for( c = 0; c < 80; c++ ) //Definimos los ciclos
  {
	if( digitalRead(CTRL) == HIGH )
		d++;
  	else
		d--;

	d = d & 0x0F;
	escribeDatoDisp( contador[d] );
	delay(500);
  }
  escribeDatoDisp( DIG_Z ); //Apagamos el display

  return 0 ;
}

/*
 * escribeDatoDisp:
 *
 *    Esta funcion manda un dato de 7 bits al display
 *    de siete segmentos de anodo comun
 ***********************************************************************
 */
void escribeDatoDisp( unsigned char dato )
{
	int seg;
	unsigned char bitValor, mascara = 0x01;

	for( seg = 0; seg < 7; seg++ )
	{
		bitValor = dato & mascara;
     		digitalWrite (seg, bitValor);
		dato = dato >> 1;
    		delay (5) ;
	}
}
