#include<stdio.h>

int main()
{
	FILE *apArch;
	int estado = 1;

	apArch = fopen("/home/victor/edo_plug_ADATA.txt", "w");
	fprintf(apArch,"%d \n",estado);
	fprintf(apArch, "Disco Duro conectado");
	fclose(apArch);

	return 0;
}
