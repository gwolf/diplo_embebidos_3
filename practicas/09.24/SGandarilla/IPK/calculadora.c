

#include <stdio.h>
#include "func_calc.h"

int main (int argc, char **argv) {
	int a, b;
	a = atoi(argv[1]);
	b = atoi(argv[2]);

	printf("La suma de A y B es %d\n", suma(a, b));
	printf("La resta de A y B es %d\n", resta(a, b));
	printf("La multiplicación de A y B es %d\n", mult(a, b));
	printf("La división de A y B es %d\n", div(a, b));

	return 0;
}
