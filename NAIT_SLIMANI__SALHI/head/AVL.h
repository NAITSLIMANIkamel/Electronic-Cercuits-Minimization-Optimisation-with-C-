#ifndef __AVL_H__
#define __AVL_H__

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "netlist.h"
#define NaN 1.0e+308*10
////////////////////////////////////////// Structure

typedef struct AVL_s
{
  Segment* seg;
  double y;
  int h;

  struct AVL_s *g,*d;
  
}AVL;



//////////////////////////////////////// Fonction

AVL* creerNode(Segment* seg,Netlist* net);
void detruireNode(AVL* node);
void detruireAVL(AVL* avl);
void afficherNode(AVL* node);
void afficherAVL(AVL* arbre);
void afficherHauteurAVL(AVL* arbre);
int getHauteur(AVL* arbre);
void rotationG(AVL** arbre);
void rotationD(AVL** arbre);
void doubleRotationG(AVL** arbre);
void doubleRotationD(AVL** arbre);
void equilibreAVL(AVL** arbre);
int addAVL(AVL** arbre,AVL* node);
AVL* getSupY(AVL* arbre,double y);
AVL* getInfY(AVL* arbre,double y);
Segment* getSegment(AVL*node);
double getYSegment(AVL*node);
AVL* SuccDroit(AVL* node);
AVL* popMax(AVL** arbre);
void rmNode(AVL** arbre,Segment* seg,double y);

#endif
