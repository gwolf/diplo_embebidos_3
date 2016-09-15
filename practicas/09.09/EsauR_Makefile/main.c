#include "stdio.h"
#include "funciones.h"

int
main (int argc, char **argv)
{
	int x, y;

	printf ("x: "); scanf ("%d", &x);
	printf ("y: "); scanf ("%d", &y);
	
	swap (&x, &y);

	printf ("x: %d, y: %d\n", x, y);

	exit (1);
}
