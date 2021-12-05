#ifndef __ECHEANCIER_H__
#define  __ECHEANCIER_H__
#include "netlist.h"

//////////////////////////////////// Structure

typedef struct
{
  double x; /* Ordonnee du point */

int VouGouD ; /* 0 si segment V / 1 si pt gauche d'un segment H / 2 si pt droit d'un
		 segment H */

  Segment * PtrSeg ; /* Pointeur sur le segment correspondant a l'extremite */

  int NumPt ; /* si segment H: numero du point correspondant */

} Extremite ;

typedef struct
{
  Extremite ** E;
  int len;

}Echeancier;

///////////////////////////////////// Fonctions


void afficherEch(Echeancier* ech);
Echeancier *creer_echeancier(Netlist* net);
void detruireEcheancier(Echeancier* ech);
int cmpExtremite(Extremite * ext1,Extremite * ext2);
void swapEecheancier(Extremite ** ext1,Extremite ** ext2);
int partition(Extremite** E,int d,int f);
void tri_echeancier_rec(Extremite** E,int d,int f);
void tri_echeancier(Echeancier* ech);
void Inserer(Segment *s,Cell_segment** T,Netlist * net);
void Supprimer(Segment *s,Cell_segment** T);
Segment* Prem_segment_apres(double y,Cell_segment* T,Netlist* net);
Segment * AuDessus(Segment *s,Cell_segment* T);
void intersections_balayage(Netlist* net);

#endif
