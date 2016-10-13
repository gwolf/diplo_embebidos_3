#include <stdio.h>
int valores()
{
  int  n1, n2, n3;
  printf("Escribe tres números: \n");
  scanf("%d %d %d",&n1,&n2,&n3);

  if (n1>=n2 && n1>=n3)
    printf("%d es el número más grande.",n1);

  if (n2>=n1 && n2>=n3)
    printf("%d es el número más grande.",n2);

  if (n3>=n1 && n3>=n2)
    printf("%d es el ńumero más grande",n3);

  return 0;
}
