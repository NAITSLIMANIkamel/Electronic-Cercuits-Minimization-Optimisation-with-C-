#ifndef __GRAPHE_H__
#define __GRAPHE_H__
#include "echeancierAVL.h"
#include <string.h>

#define POINT (Point *)
#define SEG (Segment *)

/*--------------------SDL ListAdj-------------------------*/
struct somme;
typedef struct listadj{
  struct somme * som;
  struct listadj * suiv;
}ListAdj;
/*-------------------------------------------------------*/

/*--------------------SDL Sommes-------------------------*/
typedef struct somme{
  int num; // num somme dans le graphe 
  int t; // 0 si Point, 1 si Segment
  void* data; // Segment ou Point
  ListAdj* list;
  ListAdj* point;
}Somme;
/*-------------------------------------------------------*/

/*--------------------SDL Graphe-------------------------*/
typedef struct {
  int nbS;
  int np;
  Somme ** tabS;
}Graphe;
/*-------------------------------------------------------*/

extern double __MAX;

/*--------------------Fonctions---------------------------*/
Somme* creerSomme(int num,int t,void * data);
ListAdj* creerAdj(Somme* som);
void detruireListAdj(ListAdj* list);
void detruireSomme(Somme* som);
void insererTeteList(ListAdj** list,Somme* adj);
void insererListAdj(Somme* som,Somme* adj);
ListAdj* popListAdj(ListAdj** list);
int hachagePoint(int * aux,int NumRes,int numP);
Somme* getSommePoint(Graphe* graphe,int * aux,int NumRes,int numP);
Somme* getSommeSeg(Graphe* graphe,int *aux,int NumRes,int p1,int p2);
void AjouterAreteInter(Graphe* graphe,int *aux,char* fileInt);
Graphe* creerGraphe(Netlist* net,char* fileInt);
void afficherSomme(Somme* somme);
void afficherListAdj(ListAdj* list);
void afficherGraphe(Graphe* graphe);
int nextSomme(int * M,int len);
void GraphePS(Graphe *graphe,char* nomfile);
void GrapheDot(Graphe *graphe,char* nom);
int * ViaMinAlgo1(Graphe* graphe);
void SVGsolutionViaMinAlgo1(Graphe* graphe,int*B,char* nom);
void SVGsolutionViaMin(Graphe* graphe,int*B,char* nom);
int nbVia(int*B,int len);
void parcourGraphe(Graphe* graphe);
void detruireGraphe(Graphe* graphe);
/*-------------------------------------------------------*/

#endif
