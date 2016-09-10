#include "stdio.h"
#include "alu.h"
#include "validaciones.h"

int main( int argc, char **argv )
{
   if ( esEntero( argv[1] ) && esEntero( argv[2] ) && esEntero( argv[3] ) )
   {
      printf( "resultado: %d\n", operacion( atoi( argv[1] ), atoi( argv[2] ), atoi( argv[3] ) ) );
   }
   else
   {
      printf( "hay argumentos incorrectos\n" );
   }

   return 0;
}
