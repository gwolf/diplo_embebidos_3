/*
*	Descripción: Este programa realiza la detección de frecuencia fundamental de una
*	señal senoidal usando la función de autocorrelación.
*	El programa calcula esta función en forma secuencial.
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 4096					//Bloque de datos
#define L 4096					//Valores de autocorrelación
#define FS 512.0				//Frecuencia de muestreo

void calcAutoCorr1	( int [], int [] );
void calcAutoCorr2	( int [], int [] );
void calcAutoCorr3	( int [], int [] );
void calcSeno		( int [], int [] );
void guardaDatosArch( int [], int [] );
void ventaneo		( int [] );
void detFrec		( int [] );

int main()
{
	int seno[N], rxx[N];

	calcSeno		( seno, rxx );
	ventaneo		( seno );
	calcAutoCorr2	( seno, rxx );
	detFrec			( rxx );
	guardaDatosArch	( seno, rxx );

	return 0;
}
/*
*	Descripción: Esta función encuentra la frecuencia fundamental de 
*	la señal senoidal usando la función de autocorrelación.
*	La frecuencia fundamental se encuentra en el primer máximo
*	después del origen
*	Parametros: s, arreglo donde se genera la función de autocorrelación
*/
void detFrec( int rxx[] )
{
	register int l;
	int fun_creciente = 0;

	for( l = 2; l < N; l++ )
	{
		if( (rxx[l] > rxx[l-1]) )
		{
			fun_creciente = 1;
		}else if( (rxx[l] < rxx [l-1]) && fun_creciente )
		{
			printf("Muestra: %d, Frecuencia: %f, Pulsos por minuto: %f\n ", l, FS / l, FS / l * 60 );
			return;
		}
	}
}
/*
*	Descripcion: Esta funcion realiza el ventaneo de la señal con una 
*	ventana hamming
*	Matematicamente: v[n] = a0 - a1 cos(2*PI*n/(N-1)) 
*	Donde: a0 = 0.53836, a1 = 0.46164
*	Parametros: s, arreglo donde se genera la señal discreta del seno
*/
void ventaneo( int s[] )
{
	register int n;
	float vn, a0 = 0.53836, a1 = 0.46164; 
	int v[N];

	for( n = 0; n < N; n++ )
	{
		vn = a0 - a1 * cosf(2*M_PI*n/(N-1));
		v[n] = vn * 32768;		//Se aplica formato Q15
	}

	for( n = 0; n < N; n++ )
	{
		s[n] = s[n] * v[n];		//Q15 = Q0 * Q15
		s[n] = s[n] >> 15;		//Se regresa a formato Q0
	}
}

/*
*	Descripcion: Esta funcion genera una señal discreta del seno
*	con una frecuencia fundamental de fo hz y una frecuencia de 
*	muestreo de fs hz.
*	Matematicamente: sen[n] = sen(w*t)|t=nTs 	= sen(w*n*Ts) 
*							= sen(2*PI*fo*n*Ts) = sen(2*PI*fo*n/fs) 
*	Parametros: s, arreglo donde se genera la señal discreta del seno
*	            r, arreglo de autocorrelación
*/
void calcSeno( int s[], int r[] )
{
	float fs = 512, fo = 1.3;
	register int n;

	for( n = 0; n < N; n++ )
	{
		s[n] = sinf(2*M_PI*n*fo/fs)*128;	//Se coloca a 8 bits de resolución
		r[n] = 0;
	}
}
/*
*	Descripcion: Esta funcion calcula la funcion de autocorrelacion discreta
*							  N-|k|-1
*							  _____
*	Matematicamente: rxx(l) = \	   x(n)x(n-l)
*							  /____ 
*								n = i
*	Donde: 	i = l, k = 0, para l >= 0
*			i = 0, k = l, para l <  0
*	Parametros: s, arreglo donde se genera la señal discreta del seno
*				rxx, arreglo donde se encuentra el resultado de la 
*				autocorrelacion
*/
void calcAutoCorr1( int x[], int rxx[] )
{
	register int n, l;
	int i, k, ind;

	for( l = -L/2; l < L/2; l++ )
	{		
		i = ( l >= 0 )? l : 0;
		k = ( l >= 0 )? 0 : l;
		rxx[l] = 0;
		for( n = i; n < N-abs(k); n++ )
		{
			ind = ((n-l) < 0)? 0 : n-l;
			rxx[l+L/2] += x[n] * x[ind];  
		}
	}
}
/*
*	Descripcion: Esta funcion calcula la funcion de autocorrelacion discreta.
*	se usa la propiedad de simetria rxx(n) = rxx(-n) para evaluar la parte positiva
*							  N-1
*							  _____
*	Matematicamente: rxx(l) = \	   x(n)x(n-l)
*							  /____ 
*								n = l
*	Parametros: s, arreglo donde se genera la señal discreta del seno
*				rxx, arreglo donde se encuentra el resultado de la 
*				autocorrelacion
*/
void calcAutoCorr2( int x[], int rxx[] )
{
	register int n, l;

	for( l = 0; l < L; l++ )
	{		
		for( n = l; n < N; n++ )
		{
			rxx[l] += x[n] * x[n-l];  
		}
	}
}
/*
*	Descripcion: Esta funcion calcula la funcion de autocorrelacion discreta.
*	se usa determina el primer máximo después del origen.
*							  N-1
*							  _____
*	Matematicamente: rxx(l) = \	   x(n)x(n-l)
*							  /____ 
*								n = l
*	Parametros: s, arreglo donde se genera la señal discreta del seno
*				rxx, arreglo donde se encuentra el resultado de la 
*				autocorrelacion
*/
void calcAutoCorr3( int x[], int rxx[] )
{
	register int n, l;
	int fun_creciente = 0;

	for( l = 0; l < L; l++ )
	{		
		for( n = l; n < N; n++ )
		{
			rxx[l] += x[n] * x[n-l];  
		}
		if( (rxx[l] > rxx[l-1]) && l > 1 )
		{
			fun_creciente = 1;
		}else if( (rxx[l] < rxx [l-1]) && fun_creciente )
		{
			printf("Muestra: %d, Frecuencia: %f, Pulsos por minuto: %f\n ", l, FS / l, FS / l * 60 );
			return;
		}
	}
}

/*
*	Descripcion: Esta funcion guarda los datos de la señal seno 
* 	y la funcion de autocorrelacion en archivos para su posterior graficacion
*	Parametros: s, arreglo donde se genera la señal discreta del seno
*				r, arreglo donde se genera la funcion de autocorrelacion
*				nDatos, Tamaño de los arreglos
*/
void guardaDatosArch( int s[], int r[] )
{
	FILE *apFileS, *apFileR;
	register int i;

	apFileS = fopen("seno.dat","w");
	if( apFileS == NULL )
	{
		perror("Error al abrir el archivo");
		exit(1);
	}
	apFileR = fopen("rxx.dat","w");
	if( apFileR == NULL )
	{
		perror("Error al abrir el archivo");
		exit(1);
	}

	for( i = 0; i < N; i++ )
	{
		fprintf(apFileS, "%d \n", s[i]*100000);
		fprintf(apFileR, "%d \n", r[i]);
	}
	fclose(apFileS);	
	fclose(apFileR);	
}

