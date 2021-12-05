#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../head/viaminAlgo.h"
#include "../head/echeancierAVL.h"
#include "../head/menu.h"

#define M 60


int main (int argc , char * * argv )
{
  Netlist * net;
  Graphe* graphe;
  char ch;
  char file[100];
  int *B;

  if ( argc !=4) {
    printf ("\033[31m Erreur format : %s <NomFichier.net> <Choix1> <Choix2>\033[0m\n",argv [0]) ;
    return 1;
  }

  net=init_netlist(argv[1]);

  //////////////////////// Partie A
  ch=atoi(argv[2]);
  switch (ch){
  case 1:
    intersect_naif(net);
    break ;

  case 2:
    intersections_balayage(net);
    break ;

  case 3: 
    intersectionsBalayageAVL(net);
    break;
  default: return 1;  
  }
  sauvegarde_NetlistSVG(net,argv[1],ch);
  strcpy(file,argv[1]);
  strcat(file,".int");
  file[99]='\0';
  write(1,"\033[32m Creer le fichier Int ... \n╠",36);
  save_intersections(net,file);
  write(1,"╣\n",4);

  printf("-----------------------------------------------------\n");

  //////////////////////// Partie B
  ch=atoi(argv[3]);
  graphe=creerGraphe(net,file);
  switch (ch){
  case 1:
    B=ViaMinAlgo1(graphe);
    break ;

  case 2:
    B=bicolore(graphe);
    break ;

  default:return 1;  
  }
  HTMLmajPartieB(graphe,file,B,ch);

  printf("\033[0m\n");


  detruireGraphe(graphe);
  free(B);
  detruireNetlist(net);
  return EXIT_SUCCESS;
}
