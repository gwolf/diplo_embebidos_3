#include<math.h>
#include"defs.h"

extern int pulsoCardiaco[N], bufferCircular[N];
extern int indiceProcesar;

/*
 *	Descripcion: Esta funcion realiza el ventaneo de la señal con una 
 *	ventana hamming
 *	Matematicamente: v[n] = a0 - a1 cos(2*PI*n/(N-1)) 
 *	Donde: a0 = 0.53836, a1 = 0.46164
 *	Parametros: s, arreglo donde se genera la señal discreta del seno
 *****************************************************************************************
 */
void ventaneo( void )
{
	register int n, v;
	float vn, a0 = 0.53836, a1 = 0.46164; 

	for( n = 0; n < N; n++ )
	{
		vn = a0 - a1 * cosf(2*M_PI*n/(N-1));
		v = vn * 32768;								//Se aplica formato Q15
		v = v * bufferCircular[indiceProcesar++]; 	//Q15 = Q15 * Q0
		v = v >> 15;								//Se regresa a formato Q0
		pulsoCardiaco[n] = v;
		indiceProcesar = indiceProcesar & 0x0FFF;	//Se recorre el buffer Circular 
	}
}

/*
 *	Descripción: Esta funcion genera una señal discreta del seno
 *	con una frecuencia fundamental de fo hz y una frecuencia de 
 *	muestreo de fs hz.
 *	Matematicamente: sen[n] = sen(w*t)|t=nTs 	= sen(w*n*Ts) 
 *							= sen(2*PI*fo*n*Ts) = sen(2*PI*fo*n/fs) 
 *	Parametros: s, arreglo donde se genera la señal discreta del seno
 *****************************************************************************************
 */
void calcSeno( int s[] )
{
	float fs = 512, fo = 1.1;
	register int n;

	for( n = 0; n < N; n++ )
	{
		s[n] = sinf(2*M_PI*n*fo/fs)*128;	//Se coloca a 8 bits de resolución
	}
}


