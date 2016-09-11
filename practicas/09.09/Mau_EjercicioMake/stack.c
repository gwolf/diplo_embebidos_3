/* calculadora de pila inversa: stack.c */

#include <stdio.h>
#include "calc.h"
#define MAXVAL 100	/* maxima cantidad de valores en la pila */

static int pp = 0;		/* posici¢n en la pila */
static double val[MAXVAL];

/* push: coloca f en la pila */
void push(double f)
{
  if (pp < MAXVAL)
    val[pp++] = f;
  else  {
    printf("ERROR: pila llena, no se puede agregar %g\n", f);
    exit (1);
  }
}

/* pop: extrae de la pila, devuelve el valor de tope */
double pop(void)
{
  if(pp > 0)
    return val[--pp];
  else {
    printf("ERROR: pila vac¡a, no se puede extraer\n");
    return 0.0;
  }
}

