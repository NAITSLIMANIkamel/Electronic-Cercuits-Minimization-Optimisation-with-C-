#include <stdlib.h>
#include <stdio.h>

int main(int argc,char** argv)
{
  if(argc<2)
    return 1;

  int max=atoi(argv[1]);
  int i,j=max-1;
  char nom[200];
  FILE* file;

  sprintf(nom,"bmw%d.net",max);
  nom[199]='\0';

  file=fopen(nom,"w");

  fprintf(file,"%d\n",max);
  fprintf(file,"0 2 1\n");
  fprintf(file,"  0 0 0\n");
  fprintf(file,"  1 0 %d\n",max);
  fprintf(file,"  0 1\n");

  for(i=1;i<max;i++)
    {
      fprintf(file,"%d 2 1\n",i);
      fprintf(file,"  0 0 %d\n",j);
      fprintf(file,"  1 %d %d\n",i,j);
      fprintf(file,"  0 1\n");
      j--;
    }

  fclose(file);

  return EXIT_SUCCESS;
}
