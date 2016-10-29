#include <stdio.h>
#define BUFFER 100		

static char buf[BUFFER];	
static int pbuf = 0;		
int getch(void)
{
  if (pbuf > 0)			
    return buf[--pbuf]; 	
   else				
    return getchar();		
}

void ungetch(int c)
{
  if (pbuf >= BUFFER)
    printf("ungetch: demasiados caracteres, se agotó el buffer\n");
  else
    buf[pbuf++] = c;
}

