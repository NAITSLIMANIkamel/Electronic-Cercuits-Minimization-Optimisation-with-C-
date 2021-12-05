#ifndef __SEGMENT_H__
#define __SEGMENT_H__
#include "cell_segment.h"

///////////////// Structure

typedef struct segment {

  int NumRes ;

  int p1 , p2;

  int HouV ; 

  struct cell_segment * Lintersec ;

} Segment ;

////////////////// Fonctions

Segment * creerSegment(int NumRes,int p1,int p2);
void detruireSegment(Segment* seg);
void delSegInListIncid(Cell_segment** listIncid,Segment* seg);
void delSegInListInter(Cell_segment** listInter,Segment* seg);
void  afficherSegment(Segment * seg);
void afficherListInter(Segment * seg);
int cmpSegment(Segment * seg1,Segment * seg2);
void ajouterListInter(Segment* seg,Cell_segment* listSeg);

#endif
