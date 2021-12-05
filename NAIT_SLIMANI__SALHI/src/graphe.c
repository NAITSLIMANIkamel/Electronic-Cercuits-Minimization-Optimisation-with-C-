#include "../head/graphe.h"

Somme* creerSomme(int num,int t,void * data)
{
  Somme* res=(Somme*)malloc(sizeof(Somme));

  res->num=num;
  res->t=t;
  res->data=data;
  res->list=NULL;
  res->point=NULL;

  return res;
}

ListAdj* creerAdj(Somme* som)
{
  ListAdj* res=(ListAdj*)malloc(sizeof(ListAdj));

  res->som=som;
  res->suiv=NULL;

  return res;
}

void detruireListAdj(ListAdj* list)
{
  ListAdj* cour=list;

  while(cour!=NULL)
    {
      list=list->suiv;
      free(cour);
      cour=list;
    }
}

void detruireSomme(Somme* som)
{
  if(som!=NULL)
    {
      detruireListAdj(som->list);
      free(som);
    }
}

void insererTeteList(ListAdj** list,Somme* adj)
{
  ListAdj* cell=creerAdj(adj);
  
  cell->suiv=*list;
  *list=cell;
}

void insererListAdj(Somme* som,Somme* adj)
{
  insererTeteList(&(som->list),adj);
}

void delElemList(ListAdj** list,int num)
{
  ListAdj* cour=*list,*tmp;

  if(cour==NULL)
    return;

  if(cour->som->num==num)
    {
      *list=cour->suiv;
      free(cour);
    }
  else
    {
      while(cour->suiv!=NULL)
	{
	  if(cour->suiv->som->num==num)
	    {
	      tmp=cour->suiv;
	      cour->suiv=tmp->suiv;
	      free(tmp);
	    }
	  cour=cour->suiv;
	}
    }
}

void delElemListAdj(Somme *som,int num)
{
  delElemList(&(som->list),num);
}

ListAdj* popListAdj(ListAdj** list)
{
  ListAdj* tmp=*list;

  if(tmp==NULL)
    return NULL;

  *list=tmp->suiv;
  tmp->suiv=NULL;

  return tmp;
}

int hachagePoint(int * aux,int NumRes,int numP)
{
  return aux[NumRes]+numP;
}

Somme* getSommePoint(Graphe* graphe,int * aux,int NumRes,int numP)
{
  int h=hachagePoint(aux,NumRes,numP);
  return graphe->tabS[h];
}

Somme* getSommeSeg(Graphe* graphe,int *aux,int NumRes,int p1,int p2)
{
  Somme* tmp=getSommePoint(graphe,aux,NumRes,p1);
  ListAdj* cour=tmp->list;
  
  while(cour!=NULL)    
    {
      if((SEG cour->som->data)->p1==p1 && (SEG cour->som->data)->p2==p2)
	break;
      cour=cour->suiv;
    }

  return cour->som;
}

void AjouterAreteInter(Graphe* graphe,int *aux,char* fileInt)
{
  FILE* file=fopen(fileInt,"r");
  int p1,p2,NumRes;
  Somme* som1,*som2;

  NumRes=GetEntier(file);
  p1=GetEntier(file);
  p2=GetEntier(file);

  while(NumRes!=EOF)
    {
      som1=getSommeSeg(graphe,aux,NumRes,p1,p2);
      NumRes=GetEntier(file);
      p1=GetEntier(file);
      p2=GetEntier(file);
      som2=getSommeSeg(graphe,aux,NumRes,p1,p2);
      insererListAdj(som1,som2);
      insererListAdj(som2,som1);
      NumRes=GetEntier(file);
      p1=GetEntier(file);
      p2=GetEntier(file);
    }

  fclose(file);
}

Graphe* creerGraphe(Netlist* net,char* fileInt)
{
  int i,j,len=0;
  int *aux=(int *)malloc(net->Nbres*sizeof(int));
  Graphe* graphe=(Graphe*)malloc(sizeof(Graphe));
  Segment** segs=GetSegmentInstance(net);
  Somme* tmp3,*tmp1,*tmp2;

  graphe->np=nb_Point(net);
  graphe->nbS=graphe->np+nb_segment(net);
  graphe->tabS=(Somme**)malloc(graphe->nbS*sizeof(Somme*));


  //Points
  for(i=0;i<net->Nbres;i++)
    {
      aux[i]=len;

      for(j=0;j<net->T_Res[i]->NbPt;j++,len++)
	{
	  graphe->tabS[len]=creerSomme(len,0,net->T_Res[i]->T_Pt[j]);
	}
    }

  //Segment
  j=nb_segment(net);
  for(i=0;i<j;i++)
    {
      tmp1=creerSomme(len,1,segs[i]);
      tmp2=getSommePoint(graphe,aux,segs[i]->NumRes,segs[i]->p1);
      tmp3=getSommePoint(graphe,aux,segs[i]->NumRes,segs[i]->p2);

      graphe->tabS[len]=tmp1;
      len++;

      insererListAdj(tmp1,tmp2);
      insererListAdj(tmp1,tmp3);
      insererListAdj(tmp2,tmp1);
      insererListAdj(tmp3,tmp1);
      tmp1->point=tmp1->list;
    }

  AjouterAreteInter(graphe,aux,fileInt);

  free(aux);
  free(segs);
  return graphe;
}

void afficherSomme(Somme* somme)
{
  printf("%d\n",somme->num);
}

void afficherSomme2(Somme* somme)
{
  if(somme->t==1)
    afficherSegment(somme->data);
  else
    afficherPoint(somme->data);
}

void afficherListAdj(ListAdj* list)
{
  while(list!=NULL)
    {
      afficherSomme(list->som);
      list=list->suiv;
    }
}

void afficherGraphe(Graphe* graphe)
{
  int i;

  for(i=0;i<graphe->nbS;i++)
    {
      printf("***\n");
      afficherSomme(graphe->tabS[i]);
      printf("***\n");
      afficherListAdj(graphe->tabS[i]->list);
      printf("-------------------------------------------------\n");
      printf("\n");
    }
}

int nextSomme(int * M,int len)
{
  len--;

  for(;len>=0;len--)
    {
      if(M[len]==-1)
	return len;
    }
  return -1;
}

void copierList(ListAdj** list1,ListAdj* list2)
{
  while(list2!=NULL)
    {
      insererTeteList(list1,list2->som);
      list2=list2->suiv;
    }
}



void getCordonneesSommet(Somme *s,double* x,double*y)
{
  if(s->t==0)
    {
      *x=(POINT s->data)->x;
      *y=(POINT s->data)->y;
    }
  else
    {
      *y=(POINT s->point->som->data)->y;
      *y+=(POINT s->point->suiv->som->data)->y;
      *y/=2;

      *x=(POINT s->point->som->data)->x;
      *x+=(POINT s->point->suiv->som->data)->x;
      *x/=2;
    }
}


void AretesPS(Graphe* graphe,FILE* file,int *M,int u,int v)
{
  ListAdj* cour;
  double x1,y1,x2,y2;

  M[u]=1;

  if(graphe->tabS[u]->t==1)
    fprintf(file,"1 0 0 setrgbcolor\n");
  else
    fprintf(file,"0 1 0 setrgbcolor\n");

  getCordonneesSommet(graphe->tabS[u],&x1,&y1);

  fprintf(file,"%f %f 2.5 0 360 arc\nfill\nstroke\n",x1,y1);

  cour=graphe->tabS[u]->list;

  while(cour!=NULL)
    {
      if(cour->som->num!=v)
	{
	  if(M[cour->som->num]!=2 || M[cour->som->num]==0)
	    {
	      getCordonneesSommet(graphe->tabS[cour->som->num],&x2,&y2);
	      fprintf(file,"0 0 0 setrgbcolor\n");
	      fprintf(file,"%f %f  moveto\n%f %f lineto\nstroke\n",x1,y1,x2,y2);
	    
	      if(M[cour->som->num]==0)
		AretesPS(graphe,file,M,cour->som->num,u);
	    }
	}

      cour=cour->suiv;
    }

  M[u]=2;

}

void GraphePS(Graphe *graphe,char* nomfile)
{
  int *M=(int *)malloc(graphe->nbS*sizeof(int));
  char nom[100]="\0";
  FILE* file;
  int i;

  strcpy(nom,nomfile);
  strcat(nom,"GraphePS.ps");

  file=fopen(nom,"w");

  for(i=0;i<graphe->nbS;i++)
    M[i]=-1;

  i=nextSomme(M,graphe->nbS);

  while(i!=-1)
    {
      AretesPS(graphe,file,M,i,-1);
      i=nextSomme(M,graphe->nbS);
    }

  free(M);
  fclose(file);
}


void AretesDot(Graphe* graphe,FILE* file,int *M,int u,int v)
{
  ListAdj* cour;

  M[u]=1;

  if(graphe->tabS[u]->t==1)
    fprintf(file,"\t%d [shape=box,color=blue];\n",u);

  cour=graphe->tabS[u]->list;

  while(cour!=NULL)
    {
      if(cour->som->num!=v)
	{
	  if(M[cour->som->num]!=2)
	    fprintf(file,"\t%d -- %d;\n",u,cour->som->num);
	  if(M[cour->som->num]==0)
	    {
	      AretesDot(graphe,file,M,cour->som->num,u);
	    }
	}

      cour=cour->suiv;
    }

  M[u]=2;

}

void GrapheDot(Graphe *graphe,char* nomfile)
{
  int *M=(int *)malloc(graphe->nbS*sizeof(int));
  char nom[100]="\0";
  FILE* file;
  int i;

  strcpy(nom,nomfile);
  strcat(nom,"Graphe");

  file=fopen(nom,"w");

  for(i=0;i<graphe->nbS;i++)
    M[i]=-1;

  fprintf(file,"graph{\n\tnode [color=green];\n");
  fprintf(file,"\tPoint ;\n");
  fprintf(file,"\tSegment[shape=box,color=blue];\n");
  i=nextSomme(M,graphe->nbS);

  while(i!=-1)
    {
      AretesDot(graphe,file,M,i,-1);
      i=nextSomme(M,graphe->nbS);
    }
  fprintf(file,"\n}");

  free(M);
  fclose(file);
}


void parcourGraphe(Graphe* graphe)
{
  int * M=(int *)malloc(graphe->nbS*sizeof(int));
  ListAdj* list=NULL,*cour=NULL;
  int i;


  for(i=0;i<graphe->nbS;i++)
    {
      M[i]=-1;
    }

  i=nextSomme(M,graphe->nbS);

  while(i!=-1)
    {
      cour=creerAdj(graphe->tabS[i]);
      do{
	if(M[cour->som->num]==0)
	  {
	    M[cour->som->num]=1;
	    copierList(&list,cour->som->list);
	    afficherSomme(cour->som);
	  }
	free(cour);
	cour=popListAdj(&list);
      }while(cour!=NULL);

      i=nextSomme(M,graphe->nbS);
    }

  free(M);
}

int testVia(Somme* som)
{
  ListAdj* cour=som->list;
  int tmp=0;

  if(cour==NULL)
    return -1;//impossible

  tmp=(SEG cour->som->data)->HouV;

  while(cour!=NULL )
    {
      if(tmp!=(SEG cour->som->data)->HouV)
	return 1;
      cour=cour->suiv;
    }

  return 0;
}

int * ViaMinAlgo1(Graphe* graphe)
{
  int *B=(int *)malloc(graphe->nbS*sizeof(int));
  int i;

  for(i=0;i<graphe->nbS;i++)
    {
      if(graphe->tabS[i]->t==1)
	{
	  B[i]=(SEG graphe->tabS[i]->data)->HouV+1;// 0+1 || 1+1 ( H->0 V->1 )
	}
      else
	{
	  if(testVia(graphe->tabS[i])==1)
	    {
	      B[i]=0;
	    }
	  else
	    {
	      B[i]=3;
	    }
	}
    }

  return B;
}

int nbVia(int * B,int len)
{
  int res=0;

  for(len--;len>=0;len--)
    {
      if(B[len]==0)
	res++;
    }

  return res;
}

void SVGpointVia(SVGwriter* svg,Point* p,int via)
{
  if(via==0)
    {
      SVGrectangle(svg,p->y,p->x);
    }
}

void SVGlineVia(SVGwriter* svg,Point *p1,Point* p2,int face)
{
  if(face==1)
    SVGline(svg,p1->y,p1->x,p2->y,p2->x);
  else
    SVGlineCop(svg,p1->y,p1->x,p2->y,p2->x);
}

void SVGsolutionViaMin(Graphe* graphe,int*B,char* nom)
{
  char face1[200]="HTML/IntersectionHTML/";
  int i=graphe->np,reseau;
  Somme* s1,*s2;
  SVGwriter svg1;

  strcat(face1,nom);
  strcat(face1,"Solution");
  face1[199]='\0';

  SVGinit(&svg1,face1,__MAX,__MAX);


  reseau=(SEG graphe->tabS[i]->data)->NumRes;
  


  for(;i<graphe->nbS;i++)
    {

      if(reseau!=(SEG graphe->tabS[i]->data)->NumRes)
	{
	  SVGlineRandColor(&svg1);
	  reseau=(SEG graphe->tabS[i]->data)->NumRes;
	}

      s1=graphe->tabS[i]->point->som;
      s2=graphe->tabS[i]->point->suiv->som;

      SVGpointVia(&svg1,s1->data,B[s1->num]);
      SVGpointVia(&svg1,s2->data,B[s2->num]);
      SVGlineVia(&svg1,s1->data,s2->data,B[graphe->tabS[i]->num]);

    }


  SVGfinalize(&svg1);
}

void SVGsolutionViaMinAlgo1(Graphe* graphe,int *B,char* nom)
{
  char solution[100]="\0";

  strcat(solution,nom);
  strcat(solution,"Algo1");
  solution[99]='\0';

  SVGsolutionViaMin(graphe,B,solution);

}

void detruireGraphe(Graphe* graphe)
{
  int i;

  for(i=0;i<graphe->nbS;i++)
    {
      detruireSomme(graphe->tabS[i]);
    }
  free(graphe->tabS);
  free(graphe);
}
