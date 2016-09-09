/* calculadora polaca inversa: getop.c */

#include <stdio.h>
#include <ctype.h>
#include "calc.h"

int getch(void);
void ungetch(int);

/* getop: obtiene el siguiente operador u operando numérico */

int getop(char s[])
{
  int i, c;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;			/* proposición vacía */

  s[1] = '\0';
  if (!isdigit(c) && c != '.')
    return c;		/* no es un número */
  i = 0;
  if (isdigit(c))	/* reúne la parte entera */
    while(isdigit(s[++i] = c = getch()))
      ;			/* proposición vacía */
  if (c == '.')		/* reúne la parte fraccionaria */
    while (isdigit(s[++i] = c = getch()))
      ;			/* proposición vacía */
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMERO;
}

