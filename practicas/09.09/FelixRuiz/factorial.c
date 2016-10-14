#include <stdio.h>
#include "include/valida.h"
int main(void)
{
  int n, i, y;
  unsigned long long factorial = 1;

  printf("Escribe un número entero: \n");
  scanf("%d",&n);

  /* Checa si es un entero negativo*/
  y = esnegativo(n);
  if (y==0)
    printf("Error, no existen factoriales de enteros negativos.\n");
  
  else
    {
      for(i=1; i<=n; ++i)
	{
          factorial *=i;
	}
      printf("Factorial de %d = %llu",n,factorial);
    }
  return 0;
}
