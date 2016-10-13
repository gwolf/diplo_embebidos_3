#include <stdio.h>
#include "func_cal_fact.h"

int main (int argc, char **argv) {
	int a;
	a = atoi(argv[1]);

	printf("El Factorial de %d es: %d \n",a,fact(a));

	return 0;
}
