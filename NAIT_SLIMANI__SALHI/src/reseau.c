#include <stdlib.h>
#include <stdio.h>
#include "../head/reseau.h"


Reseau * creerReseau(int NumRes,int NbPt)
{
  Reseau * res=(Reseau *)malloc(sizeof(Reseau));

  res->NumRes=NumRes;
  res->NbPt=NbPt;

  res->T_Pt=(Point**)malloc(NbPt*sizeof(Point*));

  return res;
}

void ajouterPoint(Reseau* reseau,Point* point,int numP)
{
  if(point!=NULL && reseau!=NULL)
    {
      reseau->T_Pt[numP]=point;
    }
}

//////////////////////////////////////////// detruire Reseau

void delSegInRes(Reseau* reseau,Segment* seg)
{
  Cell_segment * cour;

  if(reseau==NULL)
    return ;

  cour=seg->Lintersec;

  while(cour!=NULL)
    {
      delSegInListInter(&(cour->seg->Lintersec),seg);
      cour=cour->suiv;
    }

  detruireListCell(seg->Lintersec);
  seg->Lintersec=NULL;

  delSegInPoint(reseau->T_Pt[seg->p1],seg);
  delSegInPoint(reseau->T_Pt[seg->p2],seg);

    detruireSegment(seg);
}


void delPoint(Reseau* reseau,Point* point)
{
  Cell_segment *cour,*tmp;

  cour=point->Lincid;
  while(cour!=NULL)
    {
      tmp=cour->suiv;
      delSegInRes(reseau,cour->seg);
      cour=tmp;
    }

  reseau->NbPt--;
  free(point);
}

void detruireReseau(Reseau * reseau)
{
  int i;
  int len=reseau->NbPt;

  for(i=0;i<len;i++)
    {
      delPoint(reseau,reseau->T_Pt[i]);
      reseau->T_Pt[i]=NULL;
    }

  free(reseau->T_Pt);
  free(reseau);
}

///////////////////////////////////////////////////////////////////


int nbSegInRes(Reseau* reseau)
{
  return reseau->NbPt-1;
}

void afficherReseau(Reseau* reseau)
{
  int i;

  printf("%d %d %d\n",reseau->NumRes,reseau->NbPt,nbSegInRes(reseau));

    for(i=0;i<reseau->NbPt;i++)
    {
      printf("%2d ",i);
      afficherPoint(reseau->T_Pt[i]);
    }

    for(i=0;i<reseau->NbPt;i++)
    {
      afficherRelationPoint(reseau->T_Pt[i],i);
    }
}

void HTMLReseau(FILE*file,Segment* seg,char *color)
{
  Cell_segment* cour=seg->Lintersec;

  while (cour!=NULL)
    {
      HTMLligne(file,color,seg->p1,seg->p2,cour->seg->NumRes,cour->seg->p1,cour->seg->p2);
      cour=cour->suiv;
    }
}


void SVGReseau(SVGwriter * svg ,Reseau *res,FILE* file)
{
  int i,bool=0;
  Cell_segment *cour ;
  
  for(i=0;i<res->NbPt;i++)
    {
      
      SVGpoint(svg,res->T_Pt[i]->y,res->T_Pt[i]->x,i);
      cour=res->T_Pt[i]->Lincid;

      while(cour!=NULL)
	{
	  if(!bool && cour->seg->Lintersec!=NULL)
	    {
	      HTMLtitre(file,cour->seg->NumRes,svg->lineColor);
	      HTMLcreerTab(file,svg->lineColor);
	      bool=1;
	    }

	  if(cour->seg->p1==i)
	    {
	      SVGline(svg,res->T_Pt[i]->y,res->T_Pt[i]->x,res->T_Pt[cour->seg->p2]->y,res->T_Pt[cour->seg->p2]->x);
	      HTMLReseau(file,cour->seg,svg->lineColor);
	    }
	  
	  cour=cour->suiv;
	  
	}
    }

  if(bool)
    {
      HTMLfinTab(file);
    }
}

