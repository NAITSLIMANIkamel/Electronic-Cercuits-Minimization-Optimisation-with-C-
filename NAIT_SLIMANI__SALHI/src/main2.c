#include <stdlib.h>
#include <stdio.h>
#include "../head/graphe.h"
#include "../head/echeancierAVL.h"
#include "../head/viamin.h"

int main()
{
  Netlist * net;
  Graphe * graphe;

  net=init_netlist("ibm01_2.net");
  intersectionsBalayageAVL(net);
  save_intersections(net,"ibm01_2.int");
  graphe=creerGraphe(net,"ibm01_2.int");

  afficherGraphe(graphe);
  printf("---------------------ok----------------------------\n");

  SVGsolutionViaMinAlgo2(graphe,"ibm01");
  //SVGsolutionViaMinAlgo1(graphe,"ibm01");

  printf("---------------------ok----------------------------\n");


  detruireGraphe(graphe);
  detruireNetlist(net);

  return EXIT_SUCCESS;
}
