#ifndef _NETLIST_H
#define _NETLIST_H

#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include "entree_sortie.h"
#include "reseau.h"
#include "segment.h"

////////////////////////////// Structure

typedef struct netlist{
  
  int Nbres ;
  Reseau* *T_Res; 

}Netlist;

//////////////////////////////////// Fonctions
void swapInt(int* p1,int* p2);
void triCouple(Reseau* reseau,int* p1,int* p2);
Netlist* init_netlist(char * fich);
void detruireNetlist(Netlist* net);
int nb_segment(Netlist* net);
int nb_Point(Netlist* net);
void affichage(Netlist* net);
int intersection(Netlist *N,Segment* s1,Segment* s2);
void afficherTabSeg(Segment** tabSeg,int taille);
void addSegment(Segment** tab,Point* point,int numP,int* pos);
Segment** GetSegmentInstance(Netlist * net);
void afficherListIntercTabSeg(Segment** tabSeg,int taille);
void intersect_naif(Netlist * net);
void save_intersections(Netlist *net, char * fich);
void sauvegarde_NetlistSVG(Netlist * net,char * fich,int choix);

#endif
