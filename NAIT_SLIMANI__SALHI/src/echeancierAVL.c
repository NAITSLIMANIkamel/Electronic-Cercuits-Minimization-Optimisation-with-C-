#include "../head/echeancierAVL.h"

void InsererAVL(AVL** arbre,Netlist* net,Segment *seg)
{
  addAVL(arbre,creerNode(seg,net));
}

void SupprimerAVL(AVL**arbre,Segment* seg,double y)
{
  rmNode(arbre,seg,y);
}

AVL* Prem_segment_apresAVL(double y1,double y2,AVL* arbre)
{
  
  return  getInfY(getSupY(arbre,y1),y2);
}



int AuDessusAVL(AVL* h,Segment* seg,double y2,double y1)
{

  if(h==NULL)
    return 0;
  
  if(getYSegment(h)>y2)
    {
      AuDessusAVL(h->g,seg,y2,y1);
      return 0;
    }
  if(getYSegment(h)<y1)
    {
      AuDessusAVL(h->d,seg,y2,y1);
      return 0;
    }
  
  if(h->seg->NumRes!=seg->NumRes)
    {
      insererTeteListCell(&(seg->Lintersec),creerCell(h->seg));
      insererTeteListCell(&(h->seg->Lintersec),creerCell(seg));
    }
  
  AuDessusAVL(h->d,seg,y2,y1);
  AuDessusAVL(h->g,seg,y2,y1);

  return 0;
}

void ajouterInterAVL(Netlist* net,AVL* arbre,Segment* seg)
{
  double 
    y1=net->T_Res[seg->NumRes]->T_Pt[seg->p1]->y,
    y2=net->T_Res[seg->NumRes]->T_Pt[seg->p2]->y;

  AVL* h=Prem_segment_apresAVL(y1,y2,arbre);
  
  if(h!=NULL )
    {
      if(h->seg->NumRes!=seg->NumRes && getYSegment(h)>=y1 )
	{
	  insererTeteListCell(&(seg->Lintersec),creerCell(h->seg));
	  insererTeteListCell(&(h->seg->Lintersec),creerCell(seg));
	}
      AuDessusAVL(h->g,seg,y2,y1);
      AuDessusAVL(h->d,seg,y2,y1);
    }

}

void intersectionsBalayageAVL(Netlist* net)
{
  Echeancier* ech=creer_echeancier(net);
  AVL* arbre=NULL;
  int i;
  double y;

  tri_echeancier(ech);

  for(i=0;i<ech->len;i++)
    {
      switch( ech->E[i]->VouGouD)
	{
	case 1: 
	  InsererAVL(&arbre,net,ech->E[i]->PtrSeg);
	  break;
	case 2:
	  y=net->T_Res[ech->E[i]->PtrSeg->NumRes]->T_Pt[ech->E[i]->PtrSeg->p1]->y;
	  SupprimerAVL(&arbre,ech->E[i]->PtrSeg,y);
	  break;
	case 0: 
	  ajouterInterAVL(net,arbre,ech->E[i]->PtrSeg);
	  break;
	}
    }
  
  detruireEcheancier(ech);
}

float complexiteBalayageAVL(Netlist* N)
{
  int n=nb_segment(N);
  clock_t t1,t2;
  float temps;

  t1=clock();		 
  intersectionsBalayageAVL(N);
  t2=clock();	
  temps=(float)(t2-t1)/CLOCKS_PER_SEC; 
  printf("%7d %f\n",n,temps);

  return temps;
}

