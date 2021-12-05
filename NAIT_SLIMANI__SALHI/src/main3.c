#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../head/viaminAlgo.h"
#include "../head/echeancierAVL.h"
#include "../head/menu.h"

#define M 60

int main()
{
  majSolution("test",10,2);
  majGraphe("test");

  return EXIT_SUCCESS;
}


int main3(int argc , char * * argv )
{
  Netlist * net;
  Graphe* graphe;
  char file[100];
  int *B;

  if ( argc !=2) {
    printf ("\033[31m Erreur format : %s <NomFichier.net> \033[0m\n",argv [0]) ;
    return 1;
  }

  net=init_netlist(argv[1]);

  //////////////////////// Partie A
  intersectionsBalayageAVL(net);
  strcpy(file,argv[1]);
  strcat(file,".int");
  file[99]='\0';
  save_intersections(net,file);

  //////////////////////// Partie B
  graphe=creerGraphe(net,file);
  printf("ok\n");
  //B=ViaMinAlgo1(graphe);
  B=bicolore(graphe);

  printf("ok\n");

  printf("%d\n",nbVia(B,graphe->nbS));

  GraphePS(graphe,"y.ps");

  detruireGraphe(graphe);
  free(B);
  detruireNetlist(net);
  return EXIT_SUCCESS;
}
