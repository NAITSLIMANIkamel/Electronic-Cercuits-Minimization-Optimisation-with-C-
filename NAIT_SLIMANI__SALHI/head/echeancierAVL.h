#ifndef	__ECHEANCIER_AVL_H__
#define __ECHEANCIER_AVL_H__
#include <stdlib.h>
#include <stdio.h>
#include "AVL.h"
#include "echeancier.h"

///////////////////////////////// Fonctions
void InsererAVL(AVL** arbre,Netlist* net,Segment *seg);
void SupprimerAVL(AVL**arbre,Segment* seg,double y);
AVL* Prem_segment_apresAVL(double y1,double y2,AVL* arbre);
int AuDessusAVL(AVL* h,Segment* seg,double y2,double y1);
void ajouterInterAVL(Netlist* net,AVL* arbre,Segment* seg);
void intersectionsBalayageAVL(Netlist* net);
float complexiteBalayageAVL(Netlist* N);

#endif
