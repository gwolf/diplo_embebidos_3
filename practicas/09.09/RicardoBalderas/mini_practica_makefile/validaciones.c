#include "validaciones.h"

int esEntero( char *entrada )
{
   int i = 0;

   for ( i = 0; entrada[i] != 0; i++ )
   {
      if ( entrada[i] < '0' || entrada[i] > '9' )
      {
         return 0;
      }
   }

   return 1;
}
