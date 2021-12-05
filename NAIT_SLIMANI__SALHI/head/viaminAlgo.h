#ifndef __VIAMIN_H__
#define __VIAMIN_H__
#include "graphe.h"
#include <stdlib.h>
#include <stdio.h>

/////////////////////////// Structur

typedef struct{
  ListAdj* debut,*fin;
  int len;
}ListCycle;


////////////////////////// Fonctions

ListCycle* creerListCycle();
void addListCycle(ListCycle* cycle,Somme* som);
void delElemListCycle(ListCycle* cycle);
void delListCycle(ListCycle* cycle);
void initTabMarc(int* M,int len);
ListCycle* ChaineCycle(Graphe* graphe,int u,int v,int *M);
ListCycle* detecte_cycle_impair(Graphe* graphe,int u,int v,int *M);
int* Ajout_vias_cycle_impair(Graphe* graphe);
void afficherTab(int* tab,int len);
int* bicolore(Graphe* graphe);
void SVGsolutionViaMinAlgo2(Graphe* graphe,int*M,char* nom);
void majSolution(char *fich,int nbVia,int choix);
void majGraphe(char *fich);
void HTMLmajPartieB(Graphe* graphe,char* nom,int* B,int choix);

#endif
