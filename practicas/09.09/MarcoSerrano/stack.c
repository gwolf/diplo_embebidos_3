#include <stdio.h>
#include "calc.h"
#define MAXVAL 100	

static int pp = 0;		
static double val[MAXVAL];


void push(double f)
{
  if (pp < MAXVAL)
    val[pp++] = f;
  else  {
    printf("ERROR: pila llena, no se puede agregar %g\n", f);
    exit (1);
  }
}

double pop(void)
{
  if(pp > 0)
    return val[--pp];
  else {
    printf("ERROR: pila vac¡a, no se puede extraer\n");
    return 0.0;
  }
}

