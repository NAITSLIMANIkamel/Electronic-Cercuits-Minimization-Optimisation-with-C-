#include <stdlib.h>
#include <stdio.h>
#include "../head/segment.h"

Segment * creerSegment(int NumRes,int p1,int p2)
{
  Segment* res=(Segment *)malloc(sizeof(Segment));

  res->NumRes=NumRes;
  res->p1=p1;
  res->p2=p2;
  res->Lintersec=NULL;

  return res;
}

void detruireSegment(Segment* seg)
{
  if(seg!=NULL)
    free(seg);
}

void delSegInListIncid(Cell_segment** listIncid,Segment * seg)
{
  Cell_segment* cell=popCell(listIncid,seg);

  if(cell!=NULL)
    detruireCell(cell);
}

void delSegInListInter(Cell_segment** listInter,Segment * seg)
{
  Cell_segment* cell=popCell(listInter,seg);

  if(cell!=NULL)
    detruireCell(cell);
}

void afficherSegment(Segment * seg)
{
  printf("%20d %d\n",seg->p1,seg->p2);
}

void afficherListInter(Segment * seg)
{
  afficherListCell(seg->Lintersec);
}

int cmpSegment(Segment * seg1,Segment * seg2)
{

  if(seg1!=NULL && seg2!=NULL)
    return seg1==seg2 || (seg2->NumRes==seg1->NumRes && seg2->p1==seg1->p1 && seg2->p2==seg1->p2);
  return 0;
}

void ajouterListInter(Segment* seg,Cell_segment* listSeg)
{
  seg->Lintersec=listSeg;
}
