#include<stdio.h>
#include"base.h"

int main(int argc, char **argv)
{
	int varA, varB, varC;
	varA = atoi(argv[1]);
	varB = atoi(argv[2]);
	varC = multiplicar(varA, varB);
	printf("EL resultado de multiplicar %d con %d es: %d", varA,varB,varC);
	return 0;
}
