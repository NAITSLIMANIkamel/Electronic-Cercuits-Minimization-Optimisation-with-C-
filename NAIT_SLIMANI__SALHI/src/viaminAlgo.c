#include <unistd.h>
#include "../head/viaminAlgo.h"

ListCycle* creerListCycle()
{
  ListCycle* res=(ListCycle*)malloc(sizeof(ListCycle));

  res->len=0;
  res->debut=NULL;
  res->fin=NULL;

  return res;
}

void addListCycle(ListCycle* cycle,Somme* som)
{
  insererTeteList(&(cycle->debut),som);

  if(cycle->len==0)
    cycle->fin=cycle->debut;

  cycle->len++;
}

void delElemListCycle(ListCycle* cycle)
{
  if(cycle==NULL)
    return;

  detruireListAdj(popListAdj(&(cycle->debut)));

  if(cycle->debut==NULL)
    {
      cycle->len=0;
      cycle->fin=cycle->debut;
    }
  else
    cycle->len--;
}

void delListCycle(ListCycle* cycle)
{
  if(cycle==NULL)
    return;

  detruireListAdj(cycle->debut);
  free(cycle);
}

ListCycle* ChaineCycle(Graphe* graphe,int u,int v,int *M)
{
  ListCycle* cycle=NULL;
  ListAdj* cour;

  M[u]=3-M[v];

  cour=graphe->tabS[u]->list;
  while(cour!=NULL)
    {
      if(M[cour->som->num]!=0 && cour->som->num!=v)
	{
	  if(M[cour->som->num]==-1)
	    {
	      cycle=ChaineCycle(graphe,cour->som->num,u,M);

	      if(cycle!=NULL)
		{
		  if(cycle->debut->som!=cycle->fin->som)
		    addListCycle(cycle,graphe->tabS[u]);
		  M[u]=-1;
		  return cycle;
		}
	    }
	  else
	    {
	      if(M[cour->som->num]==M[u])
		{
		  cycle=creerListCycle();
		  addListCycle(cycle,graphe->tabS[cour->som->num]);
		  addListCycle(cycle,graphe->tabS[u]);
		  M[u]=-1;
		  return cycle;
		}
	    }
	}
      cour=cour->suiv;
    }

  M[u]=3;
  return NULL;
}

ListCycle* detecte_cycle_impair(Graphe* graphe,int u,int v,int *M)
{
  ListCycle* res=ChaineCycle(graphe,u,v,M);

  if(res==NULL)
    return NULL;

  delElemListCycle(res);

  return res;
}


void initTabMarc(int* M,int len)
{
  for(len--;len>=0;len--)
    {
	M[len]=-1;
    }
}

int premPoint(ListCycle* cycle)
{
  ListAdj* cour=cycle->debut;

  while(cour->som->t!=0)
    {
      cour=cour->suiv;
    }

  return cour->som->num;
}

int* Ajout_vias_cycle_impair(Graphe* graphe)
{
  int*S=(int*)malloc(graphe->nbS*sizeof(int));
  int*M=(int*)malloc(graphe->nbS*sizeof(int));
  int i=0,via;
  ListCycle* cycle=NULL;

  initTabMarc(M,graphe->nbS);
  initTabMarc(S,graphe->nbS);

  i=nextSomme(M,graphe->nbS);

  while(i!=-1)
    {
      M[i]=2;
      cycle=detecte_cycle_impair(graphe,i,i,M);
      if(cycle!=NULL)
	{
	  via=premPoint(cycle);
	  delListCycle(cycle);
	  M[via]=0;S[via]=0;
	}
      i=nextSomme(M,graphe->nbS);
    }

  free(M);

  return S;
}

void afficherTab(int* tab,int len)
{
  int i=0;

  for(i=0;i<len;i++)
    {
      printf("%d\t",tab[i]);
    }
  printf("\n");
}

void bicoloreAux(Graphe* graphe,int u,int v,int* S)
{
  ListAdj* cour;

  S[u]=3-S[v];

  cour=graphe->tabS[u]->list;

  while(cour!=NULL)
    {
      if(S[cour->som->num]==-1)
	{
	  bicoloreAux(graphe,cour->som->num,u,S);
	}
      cour=cour->suiv;
    }
}


int* bicolore(Graphe* graphe)
{
  int* S;
  int i;

  S=Ajout_vias_cycle_impair(graphe);

  i=nextSomme(S,graphe->nbS);

  while(i!=-1)
    {
      S[i]=1;
      bicoloreAux(graphe,i,i,S);
      i=nextSomme(S,graphe->nbS);
    }

  return S;
}

void SVGsolutionViaMinAlgo2(Graphe* graphe,int *M,char* nom)
{
  char solution[100]="\0";

  strcat(solution,nom);
  strcat(solution,"Algo2");
  solution[99]='\0';

  SVGsolutionViaMin(graphe,M,solution);

}


void majSolution(char *fich,int nbVia,int choix)
{
  FILE* file=fopen("HTML/solution.html","r+");

  fseek(file,526,SEEK_SET);
  HTMLdelText(file);
  fseek(file,526,SEEK_SET);
  fprintf(file,"<center><img width=\"1200\" height=\"1200\" onclick=\"aux(this,event)\" style=\"float:middle\" src=\"IntersectionHTML/%sAlgo%dSolution.svg\" alt=\"\" /></center>",fich,choix);

  fprintf(file,"<div style=\"font-size: 50px;line-height: 1.3;color: #FDF901;\"><p>Nombre de VIA : %d</p></div>\n",nbVia);

  fclose(file);
}

void majGraphe(char *fich)
{
  FILE* file=fopen("HTML/graphe.html","r+");

  fseek(file,528,SEEK_SET);
  HTMLdelText(file);
  fseek(file,528,SEEK_SET);
  fprintf(file,"<center><img width=\"1200\" height=\"1200\" onclick=\"aux(this,event)\" style=\"float:middle\" src=\"IntersectionHTML/%sGraphe.svg\" alt=\"\" /></center>\n",fich);
  fclose(file);
}

void majComplexite2(int choix)
{
  FILE* file=fopen("HTML/complexite2.html","r+");

  fseek(file,523,SEEK_SET);
  HTMLdelText(file);
  fseek(file,523,SEEK_SET);
  fprintf(file,"<center><img width=\"1200\" height=\"1200\" onclick=\"aux(this,event)\" style=\"float:middle\" src=\"complexite2%d.png\" alt=\"\" /></center>\n",choix);
  fclose(file);
}

void HTMLmajPartieB(Graphe* graphe,char* nom,int *B,int choix)
{
  char cmd[300];

  sprintf(cmd,"dot -Tsvg %sGraphe -o HTML/IntersectionHTML/%sGraphe.svg;rm %sGraphe",nom,nom,nom);
  cmd[199]='\0';
  
  write(1,"\033[32m Creer le fichier Dot ... \n╠",36);
  GrapheDot(graphe,nom);
  write(1,"╣\n",4);

  write(1,"\033[32m Convertire Dot en SVG ... \n╠",36);
  system(cmd);
  write(1,"╣\n",4);
  
  write(1,"\033[32m Creer le fichier SVG Solution ... \n╠",44);
  if(choix==1)
    SVGsolutionViaMinAlgo1(graphe,B,nom);
  else
    SVGsolutionViaMinAlgo2(graphe,B,nom);
  write(1,"╣\n",4);

  write(1,"\033[32m Mise a jour de la page HTML Graphe ... \n╠",49);
  majGraphe(nom);
  write(1,"╣\n",4);

  write(1,"\033[32m Mise a jour de la page HTML Solution ... \n╠",51);
  majSolution(nom,nbVia(B,graphe->nbS),choix);
  write(1,"╣\n",4);
  write(1,"\033[32m Mise a jour de la page HTML Complexite ... \n╠",54);
  majComplexite2(choix);
  write(1,"╣\n",4);
}
