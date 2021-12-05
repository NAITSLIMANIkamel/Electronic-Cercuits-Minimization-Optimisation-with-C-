#ifndef __POINT_H__
#define __POINT_H__
#include "cell_segment.h"
#include "segment.h"
////////////////////// Structure

 typedef struct point {
 double x,y; /* Coordonnees du point */

 int num_res ; /* Numero du reseau contenant ce point = Index du tableau T_res*/

 Cell_segment * Lincid ; /* Liste des segments incidents a ce point */

 } Point ;


/////////////////////// Fonctions

int cmpPoint(Point* p1,Point* p2);
int HorizontalVertical(Point* p1,Point* p2);
void setHorizontalVertical(Point* p1,Point* p2,Segment* seg);
Point* creerPoint(double x,double y,int num_res);
void delSegInPoint(Point * point,Segment* seg);
void detruireSegInListInter(Segment* seg);
void detruireInterSegInListIncid(Cell_segment* listIncid);
void detruirePoint(Point* point);
void afficherPoint(Point * point);
void afficherListIncid(Point * point);
void ajouterListIncid(Point* point,Cell_segment* Lincid);
void afficherRelationPoint(Point * point,int numP);


#endif
