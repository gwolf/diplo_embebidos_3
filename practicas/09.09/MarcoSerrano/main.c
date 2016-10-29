
#include <stdio.h>
#include <stdlib.h>	
#include "calc.h"

#define MAXOP 100      
#define NUMERO '0'	

int getop(char[]);
void push(double);
double pop(void);

/* programa principal */
main()
{
  int tipo;
  double op2;
  char s[MAXOP];

  printf("\nCALCULADORA\n");
  printf("Ingrese expresiones en notación inversa.\n");
  printf("Para finalizar, digite Ctrl-D.\n");

  while((tipo = getop(s)) != EOF) {
    switch (tipo) {
    case NUMERO:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();          
      push(pop() - op2);     
      break;
    case '/':
      op2 = pop();          
      if (op2 != 0.0)
	push(pop() / op2);    
      else
	printf("ERROR: divisor nulo\n");
      break;
    case '\n':
      printf("Resultado:\t%.8g\n", pop());
      break;
    default:
      printf("ERROR: comando desconocido %s\n", s);
      break;
    }
  }
  return 0;
}

