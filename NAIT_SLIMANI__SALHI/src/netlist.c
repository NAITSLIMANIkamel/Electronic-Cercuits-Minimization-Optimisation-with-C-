#include <unistd.h>
#include <string.h>
#include "../head/netlist.h"
double __MAX=0;
void swapInt(int* p1,int* p2)
{
  int tmp=*p1;
  *p1=*p2;
  *p2=tmp;
}

void triCouple(Reseau* reseau,int* p1,int* p2)
{
  if(cmpPoint(reseau->T_Pt[*p1],reseau->T_Pt[*p2]))
    swapInt(p1,p2);
}

Netlist * init_netlist(char * fich)
{
  Netlist *netl=(Netlist * ) malloc (sizeof(Netlist));
  int numres,nbsegments, nbpoints, i,j,numpoint,p1,p2;
  FILE *f=fopen(fich,"r");
  Cell_segment* cell;
  Segment* seg;
  double x,y;
  

  netl->Nbres=GetEntier(f);
  netl->T_Res = (Reseau **)malloc (netl->Nbres* sizeof(Reseau *));

  for (i=0;i<netl->Nbres;i++)
    {

      numres=GetEntier(f);
      nbpoints=GetEntier(f);
      nbsegments=GetEntier(f);

      netl->T_Res[numres]=creerReseau(numres, nbpoints);

      for(j=0;j<nbpoints;j++)
	{

	  numpoint=GetEntier(f);
	  x=GetReel(f);
	  y=GetReel(f);

	  if(x>__MAX)
	    __MAX=x;
	  if(y>__MAX)
	    __MAX=y;

	  netl->T_Res[numres]->T_Pt[numpoint]=creerPoint(x,y,numres);
	}

      for(j=0;j<nbsegments;j++)
	{

	  p1=GetEntier(f);
	  p2=GetEntier(f);
	  triCouple(netl->T_Res[numres],&p1,&p2);

	  seg=creerSegment(numres,p1,p2);
	  
	  setHorizontalVertical(netl->T_Res[numres]->T_Pt[p1],netl->T_Res[numres]->T_Pt[p2],seg);

	  
	  cell=creerCell(seg);
	  insererTeteListCell(&(netl->T_Res[numres]->T_Pt[p1]->Lincid),cell);

	  cell=creerCell(seg);
	  insererTeteListCell(&(netl->T_Res[numres]->T_Pt[p2]->Lincid),cell);

	}
    }

  
  fclose(f);
  return netl;
  
 }
void detruireNetlist(Netlist * net)
{
  int i;

  for(i=0;i<net->Nbres;i++)
    {
      detruireReseau(net->T_Res[i]);
      net->T_Res[i]=NULL;
    }

  free(net->T_Res);
  free(net);
}

int intersection(Netlist *net,Segment* s1,Segment* s2)
{
  double 
    s1x1=net->T_Res[s1->NumRes]->T_Pt[s1->p1]->x, 
    s1x2=net->T_Res[s1->NumRes]->T_Pt[s1->p2]->x,
    s2x1=net->T_Res[s2->NumRes]->T_Pt[s2->p1]->x, 
    s2x2=net->T_Res[s2->NumRes]->T_Pt[s2->p2]->x,
    s1y1=net->T_Res[s1->NumRes]->T_Pt[s1->p1]->y, 
    s1y2=net->T_Res[s1->NumRes]->T_Pt[s1->p2]->y,
    s2y1=net->T_Res[s2->NumRes]->T_Pt[s2->p1]->y, 
    s2y2=net->T_Res[s2->NumRes]->T_Pt[s2->p2]->y;



  if(s1->HouV==s2->HouV || s1->NumRes==s2->NumRes)
    return 0;

  if(s1->HouV==0)
    return s2x1>=s1x1 && s2x1<=s1x2 && s1y1>=s2y1 && s1y1<=s2y2;

  return s1x1>=s2x1 && s1x1<=s2x2 && s2y1>=s1y1 && s2y1<=s1y2;
}

int nb_segment(Netlist* net)
{
  int i,nb=0;
  
  for(i=0;i<net->Nbres;i++)
    {
      nb+=nbSegInRes(net->T_Res[i]);
    }  
  return nb;
}

int nb_Point(Netlist* net)
{
  int i,nb=0;
  
  for(i=0;i<net->Nbres;i++)
    {
      nb+=net->T_Res[i]->NbPt;
    }  
  return nb;
}

void affichage(Netlist* net)
{
  int i;

  printf("%d\n",net->Nbres);

  for (i=0;i<net->Nbres;i++)
    {
      afficherReseau(net->T_Res[i]);
    }
}

void afficherTabSeg(Segment** tabSeg,int taille)
{
  int i;

  for(i=0;i<taille;i++)
    {
      afficherSegment(tabSeg[i]);
      printf("\n");
    }

}

void addSegment(Segment** tab,Point* point,int numP,int* pos)
{
  Cell_segment* cour=point->Lincid;
  
  while(cour!=NULL)
    {
      if(cour->seg->p1==numP)
	{
	  tab[*pos]=cour->seg;
	  (*pos)--;
	}
      cour=cour->suiv;
    }

}


Segment** GetSegmentInstance(Netlist * net)
{
  int len=nb_segment(net),i,j;
  Segment ** res=(Segment **)malloc(len*sizeof(Segment*));

  len--;

  for(i=0;i<net->Nbres;i++)
    {
      for(j=0;j<net->T_Res[i]->NbPt && len>=0;j++)
	{
	  addSegment(res,net->T_Res[i]->T_Pt[j],j,&len);
	}
    }
  return res;
}

void afficherListIntercTabSeg(Segment** tabSeg,int taille)
{
  int i;

  for(i=0;i<taille;i++)
    {
      printf("reseau : %d\n",tabSeg[i]->NumRes);
      afficherSegment(tabSeg[i]);
      printf("\n");
      afficherListInter(tabSeg[i]);
      printf("fin\n");
    }

}

void intersect_naif(Netlist * net)
{
  int len=nb_segment(net);
  int i,j;
  Segment** segs=GetSegmentInstance(net);
  
  for(i=0;i<len-1;i++)
    {
      for(j=i+1;j<len;j++)
	{
	  if(intersection(net,segs[i],segs[j]))
	    {
	      insererTeteListCell(&(segs[i]->Lintersec),creerCell(segs[j]));
	      insererTeteListCell(&(segs[j]->Lintersec),creerCell(segs[i]));
	    }
	}
    }

  free(segs);
}

float complexiteNaif(Netlist*N)
{
  int n=nb_segment(N);
  clock_t t1,t2;
  float temps;

  t1=clock();		 
  intersect_naif(N);
  t2=clock();	
  temps=(float)(t2-t1)/CLOCKS_PER_SEC; 
  printf("%7d %f\n",n,temps);

  return temps;
}

void save_intersections(Netlist *N , char * fich)
{
  int  i,n=nb_segment(N);
  Segment ** tseg;
  Cell_segment *cour;
  FILE * f=fopen(fich,"w");

  tseg=GetSegmentInstance(N);
  
  for(i=0;i<n; i++)
    {
      cour=tseg[i]->Lintersec;
      while (cour!=NULL)
	{
	  if (cour->seg->NumRes > tseg[i]->NumRes)
	    fprintf(f,"%d %d %d %d %d %d \n",
		    tseg[i]->NumRes,tseg[i]->p1,tseg[i]->p2,
		    cour->seg->NumRes,cour->seg->p1,cour->seg->p2);
	  cour=cour->suiv;
	}
    }
    
  free(tseg);
  
  fclose(f);
}

void majMenu(char *fich)
{
  FILE* file=fopen("HTML/partieA.html","r+");

  fseek(file,289,SEEK_SET);
  HTMLdelText(file);
  fseek(file,289,SEEK_SET);
  fprintf(file,"IntersectionHTML/%sInter.html\n",fich);
  fclose(file);
}

void majCircuit(char *fich)
{
  FILE* file=fopen("HTML/circuit.html","r+");

  fseek(file,321,SEEK_SET);
  HTMLdelText(file);
  fseek(file,321,SEEK_SET);
  fprintf(file,"IntersectionHTML/%sInter.html\n",fich);

  fseek(file,623,SEEK_SET);
  HTMLdelText(file);
  fseek(file,623,SEEK_SET);
  fprintf(file,"<center><img width=\"1200\" height=\"1200\" onclick=\"aux(this,event)\" style=\"float:middle\" src=\"IntersectionHTML/%s.svg\" alt=\"\" /></center>\n",fich);
  fclose(file);
}

void majComplexite(char *fich,int choix)
{
  FILE* file=fopen("HTML/complexite.html","r+");

  fseek(file,286,SEEK_SET);
  HTMLdelText(file);
  fseek(file,286,SEEK_SET);
  fprintf(file,"IntersectionHTML/%sInter.html\n",fich);

  fseek(file,589,SEEK_SET);
  HTMLdelText(file);
  fseek(file,589,SEEK_SET);
  fprintf(file,"<center><img  style=\"float:middle\" src=\"complexite%d.png\" alt=\"\" /></center>\n",choix);
  fclose(file);
}

  void sauvegarde_NetlistSVG(Netlist * net,char * fich,int choix)
{
  SVGwriter svg;
  int i;
  FILE* file;
  char filename[100]="HTML/IntersectionHTML/";

  strcat(filename,fich);
  write(1,"\n\033[32m Mise a jour de la page HTML Menu ... \n╠",49);
  majMenu(fich);
  write(1,"╣\n",4);

  write(1,"\033[32m Mise a jour de la page HTML Circuit ... \n╠",50);
  majCircuit(fich);
  write(1,"╣\n",4);

  write(1,"\033[32m Mise a jour de la page HTML Complexite ... \n╠",54);
  majComplexite(fich,choix);
  write(1,"╣\n",4);  


  write(1,"\033[32m Creer le fichier SVG Circuit et page HTML Intersection ... \n╠",69);
  file=HTMLinit(filename);  
  SVGinit(&svg,filename,__MAX,__MAX);
  SVGpointColor(&svg,"White");
  
  for (i=0;i<net->Nbres;i++)
    {
      SVGlineRandColor(&svg);
      SVGReseau(&svg,net->T_Res[i],file);
    }
  HTMLfinalize(file);
  SVGfinalize(&svg);
  write(1,"╣\n",4);
 }

