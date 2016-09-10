#include "alu.h"

int operacion( int a, int b, char operacion )
{
   switch ( operacion )
   {
      case 0:
         return suma( a, b );
      case 1:
         return resta( a, b );
      case 2:
         return and( a, b );
      case 3:
         return or( a, b );
      default:
         return -1;
   }
}

int suma( int a, int b )
{
   return a + b;
}

int resta( int a, int b )
{
   return a - b;
}

int and( int a, int b )
{
   return a & b;
}

int or( int a, int b )
{
   return a | b;
}
