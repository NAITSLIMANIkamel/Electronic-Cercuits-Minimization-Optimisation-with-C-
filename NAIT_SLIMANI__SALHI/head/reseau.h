#ifndef __RESEAU_H__
#define __RESEAU_H__
#include <stdio.h>
#include "point.h"
#include "SVGwriter.h"

/////////////////////////// Structure

typedef struct reseau {
  int NumRes ; /* Numero du reseau = Indice dans le tableau T_Res */

  int NbPt ; /* Nombre de points de ce reseau */

  Point * * T_Pt ; /* Tableau de pointeurs sur chaque point de ce reseau */

} Reseau ;


//////////////////////////// Fonctions

Reseau * creerReseau(int NumRes,int NbPt);
void ajouterPoint(Reseau* reseau,Point* point,int numP);
void detruireSegInListIncid(Segment* seg,Point* point);
void detruireSegInListIncidPoint(Reseau* reseau,Cell_segment* listIncid);
void suppremerPoint(Reseau* reseau,Point* point);
void delPoint(Reseau* reseau,Point* point);
void detruireReseau(Reseau * reseau);
int nbSegInRes(Reseau* reseau);
void afficherReseau(Reseau* reseau);
void SVGReseau(SVGwriter * svg ,Reseau *res,FILE* file);

#endif
