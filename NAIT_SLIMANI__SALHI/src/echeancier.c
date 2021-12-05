#include "../head/echeancier.h"

void afficherExt(Extremite* ext)
{
  printf("%.0f",ext->x);
  printf("%10d",ext->PtrSeg->NumRes);
  printf("%10d\n",ext->VouGouD);
}

void afficherEch(Echeancier* ech)
{
  int i;
  printf("-----------------------------------------------------\n");
  for(i=0;i<ech->len;i++)
    { 
      afficherExt(ech->E[i]);
      printf("\n");
    }
}


int nbExtremite(Segment** segments,int len)
{
  int i,nb=0;

  for(i=0;i<len;i++)
    {
      if(segments[i]->HouV==0)
	nb+=2;
      else
	nb++;
    }

  return nb;
}

void addSegH(Extremite** tabExt,Netlist*net,Segment*seg)
{
  Extremite* ext=(Extremite*)malloc(sizeof(Extremite));

  ext->PtrSeg=seg;
  ext->x=net->T_Res[seg->NumRes]->T_Pt[seg->p1]->x;
  ext->VouGouD=1;
  ext->NumPt=seg->p1;

  *tabExt=ext;

  ext=(Extremite*)malloc(sizeof(Extremite));

  ext->PtrSeg=seg;
  ext->x=net->T_Res[seg->NumRes]->T_Pt[seg->p2]->x;
  ext->VouGouD=2;
  ext->NumPt=seg->p2;

  tabExt++;
  *tabExt=ext;

}

void addSegV(Extremite** tabExt,Netlist*net,Segment*seg)
{
  Extremite* ext=(Extremite*)malloc(sizeof(Extremite));

  ext->PtrSeg=seg;
  ext->x=net->T_Res[seg->NumRes]->T_Pt[seg->p1]->x;
  ext->VouGouD=0;
  ext->NumPt=-1;

  *tabExt=ext;

}

Echeancier *creer_echeancier(Netlist* net)
{
  int i=0,j=0,nbSeg=nb_segment(net);
  Segment** segments=GetSegmentInstance(net);
  Echeancier* res=(Echeancier*)malloc(sizeof(Echeancier));

  res->len=nbExtremite(segments,nbSeg);
  res->E=(Extremite**)malloc(res->len*sizeof(Extremite*));
  
  for(j=0;j<nbSeg;j++)
    {
      if(segments[j]->HouV==0)
	{ 
	  addSegH(&(res->E[i]),net,segments[j]);
	  i+=2;
	}
      else
	{
	  addSegV(&(res->E[i]),net,segments[j]);
	  i++;
	}
    }

  free(segments);

  return res;
}

void detruireEcheancier(Echeancier* ech)
{
  int i;
  
  for(i=0;i<ech->len;i++)
    {
      free(ech->E[i]);
    }
  free(ech->E);
  free(ech);
}

int cmpExtremite(Extremite * ext1,Extremite * ext2)
{
  if(ext1->x==ext2->x)
    {
      if(ext1->VouGouD>ext2->VouGouD)
	return  ext1->VouGouD==2;
      return ext2->VouGouD!=2;
    }
  
  return ext1->x>ext2->x;
}

void swapEecheancier(Extremite ** ext1,Extremite ** ext2)
{
  Extremite * tmp=*ext1;
  *ext1=*ext2;
  *ext2=tmp;
}

int partition(Extremite** E,int d,int f)
{
  int pivo=d;

  d++;
  while(d<=f)
    {
      if(cmpExtremite(E[pivo],E[d]))
	{
	  swapEecheancier(&E[pivo],&E[d]);
	  pivo++;
	  d++;
	}
      else
	{
	  swapEecheancier(&E[f],&E[d]);
	  f--;
	}
    }
  return pivo;
}

void tri_echeancier_rec(Extremite** E,int d,int f)
{
  int pivo;

  if(d>f)
    return ;
  
  pivo=partition(E,d,f);

  tri_echeancier_rec(E,d,pivo-1);
  tri_echeancier_rec(E,pivo+1,f);
  
}

void tri_echeancier(Echeancier* ech)
{
  tri_echeancier_rec(ech->E,0,ech->len-1);
}

void Inserer(Segment *seg,Cell_segment** T,Netlist* net)
{
  Cell_segment * cel=creerCell(seg);
  int y=net->T_Res[seg->NumRes]->T_Pt[seg->p1]->y;
  Cell_segment * cour;
  
  if(*T==NULL)
    {
      *T=cel;
    }
  else{
    if (net->T_Res[(*T)->seg->NumRes]->T_Pt[(*T)->seg->p1]->y>=y)
      {
	cel->suiv=*T;
	*T=cel;
      }
    else
      {
	cour=*T;
	
	while(cour->suiv!=NULL && net->T_Res[cour->suiv->seg->NumRes]->T_Pt[cour->suiv->seg->p1]->y<=y)
	  {
	    cour=cour->suiv;
	  }
	
	cel->suiv=cour->suiv;
	cour->suiv=cel;

      }
  }
}

void Supprimer(Segment *s,Cell_segment** T)
{
  detruireCell(popCell(T,s));
}

Segment* Prem_segment_apres(double y,Cell_segment* T,Netlist* net)
{
  while(T!=NULL)
    {
      if(net->T_Res[T->seg->NumRes]->T_Pt[T->seg->p1]->y>=y)
	return T->seg;
      T=T->suiv;
    }
  return NULL;
}


Segment * AuDessus(Segment *s,Cell_segment* T)
{
  while(T!=NULL) 
    {
      if(cmpSegment(s,T->seg))
	{
	  if(T->suiv==NULL)
	    return NULL;
	  return T->suiv->seg;
	}
      
      T=T->suiv;
    }

  return NULL;
}

void ajouterInter(Netlist* net,Cell_segment* T,Segment* seg)
{
  double 
    y1=net->T_Res[seg->NumRes]->T_Pt[seg->p1]->y,
    y2=net->T_Res[seg->NumRes]->T_Pt[seg->p2]->y;

  Segment* h=Prem_segment_apres(y1,T,net);

  while(h!=NULL && net->T_Res[h->NumRes]->T_Pt[h->p1]->y<=y2)
    {
      if(h->NumRes!=seg->NumRes)
	{
	  insererTeteListCell(&(seg->Lintersec),creerCell(h));
	  insererTeteListCell(&(h->Lintersec),creerCell(seg));
	}
      h=AuDessus(h,T);
    }
  
}

void intersections_balayage(Netlist* net)
{
  Echeancier* ech=creer_echeancier(net);
  Cell_segment* T=NULL;
  int i;
  
  tri_echeancier(ech);
  
  
  for(i=0;i<ech->len;i++)
    {

      switch( ech->E[i]->VouGouD)
	{
	case 1: Inserer(ech->E[i]->PtrSeg,&T,net);
	  break;
	case 2: Supprimer(ech->E[i]->PtrSeg,&T);
	  break;
	case 0: ajouterInter(net,T,ech->E[i]->PtrSeg);
	  break;
	}
    }
  
  detruireEcheancier(ech);
}

float complexiteBalayage(Netlist* N)
{
  int n=nb_segment(N);
  clock_t t1,t2;
  float temps;

  t1=clock();		 
  intersections_balayage(N);
  t2=clock();	
  temps=(float)(t2-t1)/CLOCKS_PER_SEC; 
  printf("%7d %f\n",n,temps);

  return temps;
}
