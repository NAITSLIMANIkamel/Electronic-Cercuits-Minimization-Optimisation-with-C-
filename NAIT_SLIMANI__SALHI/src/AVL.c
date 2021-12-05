#include "../head/AVL.h"

int max(int a,int b)
{
  if(a>b)
    return a;
  return b;
}

AVL* creerNode(Segment* seg,Netlist* net)
{
  AVL* node=(AVL*)malloc(sizeof(AVL));

  node->seg=seg;
  node->y=net->T_Res[seg->NumRes]->T_Pt[seg->p1]->y;
  node->h=1;
  node->g=NULL;
  node->d=NULL;

  return node;
}

void detruireNode(AVL* node)
{
  free(node);
}

void detruireAVL(AVL* avl)
{
  if(avl==NULL)
    return;
  
  if(avl->g!=NULL)
    detruireNode(avl->g);
  
  if(avl->d!=NULL)
    detruireNode(avl->d);
  
  detruireNode(avl);  
}

void afficherNode(AVL* node)
{

  printf("%5.0f (%d)",node->y,node->h);
  
  if(node->g!=NULL)
    printf("%5.0f",node->g->y);
  else
    printf("  nil");
  
  if(node->d!=NULL)
    printf("%5.0f",node->d->y);
  else
    printf("  nil");
  
  printf("\n");
}

void afficherAVL(AVL* arbre)
{
  if(arbre==NULL)
    return;

  afficherNode(arbre);
  
  afficherAVL(arbre->g);
  
  afficherAVL(arbre->d);
}

void afficherHauteurAVL(AVL* arbre)
{
  if(arbre==NULL)
    return;
  
  afficherHauteurAVL(arbre->g);
  
  printf("%3d",arbre->h);
  
  afficherHauteurAVL(arbre->d);
}

int getHauteur(AVL* arbre)
{
  if(arbre==NULL)
    return 0;
  return arbre->h;
}

void majHauteur(AVL*arbre)
{
  if(arbre==NULL)
    return ;
  arbre->h=1+max(getHauteur(arbre->g),getHauteur(arbre->d));
}

void rotationG(AVL** arbre)
{
  AVL* tmp;
  
  if(*arbre==NULL || (*arbre)->d==NULL)
    return;

  tmp=(*arbre)->d;
  (*arbre)->d=tmp->g;
  tmp->g=*arbre;
  *arbre=tmp;
  majHauteur((*arbre)->g);
  majHauteur(*arbre);
}

void rotationD(AVL** arbre)
{
  AVL* tmp;
  
  if(arbre==NULL || (*arbre)->g==NULL)
    return;

  tmp=(*arbre)->g;
  (*arbre)->g=tmp->d;
  tmp->d=*arbre;
  *arbre=tmp;
  majHauteur((*arbre)->d);
  majHauteur(*arbre);
}

void doubleRotationG(AVL** arbre)
{
  if(*arbre==NULL)
    return ;
  rotationD(&((*arbre)->d));
  rotationG(arbre);
}

void doubleRotationD(AVL** arbre)
{
  if(*arbre==NULL)
    return ;
  rotationG(&((*arbre)->g));
  rotationD(arbre);
}


void equilibreAVL(AVL** arbre)
{
  if(*arbre==NULL)
    return;
  if( abs(getHauteur((*arbre)->g)-getHauteur((*arbre)->d))>=2 )
    {
      if( getHauteur((*arbre)->g)>getHauteur((*arbre)->d) )
	doubleRotationD(arbre);
      else
	doubleRotationG(arbre);
    }
    
}


int addAVL(AVL** arbre,AVL* node)
{
  if(*arbre==NULL)
    {
      *arbre=node;
      return node->h ;
    }

  
  if((*arbre)->y>=node->y)
     (*arbre)->h=1+max(getHauteur((*arbre)->d),addAVL(&((*arbre)->g),node));
  else
     (*arbre)->h=1+max(getHauteur((*arbre)->g),addAVL(&((*arbre)->d),node));

  equilibreAVL(arbre);
 
  return (*arbre)->h;
}

AVL* getSupY(AVL* arbre,double y)
{
  if(arbre==NULL)
    return NULL;

  if(arbre->y>=y)
    return arbre;
  return getSupY(arbre->d,y);
}

AVL* getInfY(AVL* arbre,double y)
{
    if(arbre==NULL)
    return NULL;

  if(arbre->y<=y)
    return arbre;
  return getInfY(arbre->g,y);
}

Segment* getSegment(AVL*node)
{
  if(node==NULL)
    return NULL;
  return node->seg;
}

double getYSegment(AVL*node)
{
  if(node==NULL)
    return NaN;
  
  return node->y;
}

AVL* SuccDroit(AVL* node)
{
  if(node==NULL)
    return NULL;
  return node->d;
}


AVL* popMax(AVL** arbre)
{

  if(*arbre==NULL)
    return NULL;

  AVL* max;

  if((*arbre)->d==NULL)
    {
      max=*arbre;
      *arbre=(*arbre)->g;
      majHauteur(*arbre);
      equilibreAVL(arbre);
      max->g=NULL;
      return max;
    }

  max=popMax(&((*arbre)->d));

  majHauteur(*arbre);
  equilibreAVL(arbre);
  return max;
}

void rmNodeSeg(AVL** arbre,Segment* seg)
{
  if(*arbre==NULL)
    return;
  
  AVL*tmp=NULL;
  
  if(cmpSegment(seg,(*arbre)->seg))
    {
      tmp=(*arbre);
      (*arbre)=popMax(&((*arbre)->g));
      if(*arbre==NULL)
	{
	  *arbre=tmp->d;
	}
      else
	{
	  (*arbre)->g=tmp->g;
	  (*arbre)->d=tmp->d;
	}
      detruireNode(tmp);
    }
  else
    {
      rmNodeSeg(&((*arbre)->g),seg);
      rmNodeSeg(&((*arbre)->d),seg);
    }
  majHauteur(*arbre);
  equilibreAVL(arbre);
}

void rmNode(AVL** arbre,Segment* seg,double y)
{
  if(*arbre==NULL)
    return ;
  


  if((*arbre)->y==y)
    {
      rmNodeSeg(arbre,seg);
    }
  else
    {
      if((*arbre)->y>y)
	rmNode(&((*arbre)->g),seg,y);
      else
	rmNode(&((*arbre)->d),seg,y);
    }
  majHauteur(*arbre);
  equilibreAVL(arbre);
}
