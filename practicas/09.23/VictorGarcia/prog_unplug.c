#include<stdio.h>

int main()
{
	FILE *apArch;
	int estado = 2;

	apArch = fopen("/home/victor/edo_unplug_ADATA.txt", "w");
	fprintf(apArch,"%d\n",estado);
	fprintf(apArch, "Disco duro desconectado");
	fclose(apArch);

	return 0;
}
