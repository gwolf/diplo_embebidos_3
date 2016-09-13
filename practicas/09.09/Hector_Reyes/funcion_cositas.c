#include <stdio.h>
#include "cositas.h"

int main (int argc, char **argv)
{
	int l,caras;
	l = atoi(argv[1]);
	caras = atoi(argv[2]);
	int g = figura(l,caras);
	printf("el area de tu poligono de %d es de %d",caras,g);
	return 0;
}
