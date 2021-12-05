#include <stdlib.h>
#include <stdio.h>
#include "../head/point.h"

int cmpPoint(Point* p1,Point* p2)
{
  if(p1->x==p2->x)
    return p1->y>p2->y;

  return p1->x>p2->x;
}

int HorizontalVertical(Point* p1,Point* p2)
{
  return p1->y-p2->y!=0;
}

void setHorizontalVertical(Point* p1,Point* p2,Segment* seg)
{
  seg->HouV=HorizontalVertical(p1,p2);
}

Point* creerPoint(double x,double y,int num_res)
{
  Point* res=(Point *)malloc(sizeof(Point));

  res->x=x;
  res->y=y;
  res->num_res=num_res;
  res->Lincid=NULL;

  return res;
}

void delSegInPoint(Point* point,Segment * seg)
{
  if(point !=NULL)
    delSegInListIncid(&(point->Lincid),seg);
}

void afficherPoint(Point * point)
{
  printf("%.0f %.0f\n",point->x,point->y);
}

void afficherListIncid(Point * point)
{
  printf("%.0f %.0f\n",point->x,point->y);
  afficherListCell(point->Lincid);
}

void ajouterListIncid(Point* point,Cell_segment* Lincid)
{
  point->Lincid=Lincid;
}
 
void afficherRelationPoint(Point * point,int numP)
{
  Cell_segment* cour=point->Lincid;

  while(cour!=NULL)
    {
      if(cour->seg->p1==numP)
	{
	  printf("%2d %d\n",numP,cour->seg->p2);
	}
      cour=cour->suiv;
    }
  
}
