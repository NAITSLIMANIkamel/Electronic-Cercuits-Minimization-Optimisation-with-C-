#include <stdlib.h>
#include <stdio.h>
#include "../head/cell_segment.h"
#include "../head/segment.h"

///////////////////////////////////////////////// Fonctions Cell

Cell_segment * creerCell(struct segment *seg)
{
  Cell_segment * res=(Cell_segment *)malloc(sizeof(Cell_segment));

  res->seg=seg;
  res->suiv=NULL;

  return res;
}

void detruireCell(Cell_segment* cell)
{
  free(cell);
}

void afficherCell(Cell_segment* cell)
{
      afficherSegment(cell->seg);
}



///////////////////////////////////////////////// Fonctions ListCell

int lenListCell(Cell_segment*listCell)
{
  int len;

  while(listCell!=NULL)
    {
      len++;
      listCell=listCell->suiv;
    }

  return len;
}

int supprimerEleListCell(Cell_segment** listCell,Cell_segment * cell)
{
  Cell_segment* cour=*listCell,*tmp;

  if(cell==NULL || listCell==NULL)
    return 0;

  if(*listCell==cell)
    {
      *listCell=cour->suiv;
      detruireCell(cour);
      return 1;
    }
  else{

  while(cour!=NULL)
    {
      if(cell==cour->suiv)
	{
	  tmp=cour->suiv;
	  cour->suiv=tmp->suiv;
	  detruireCell(tmp);
	  return 1;
	}
      cour=cour->suiv;
    }
  }
  return 0;
}

Cell_segment* popCell(Cell_segment** listCell,Segment * seg)
{
  Cell_segment* cour=*listCell,*tmp;

  if(*listCell==NULL)
    return NULL;

  if(cmpSegment(cour->seg,seg))
    {
      *listCell=cour->suiv;
      cour->suiv=NULL;
      return cour;
    }
  else
    {

      while(cour!=NULL)
	{
	  if(cmpSegment(cour->suiv->seg,seg))
	    {
	      tmp=cour->suiv;
	      cour->suiv=tmp->suiv;
	      tmp->suiv=NULL;
	      return tmp;
	    }
	  cour=cour->suiv;
	}
    }
  return NULL;

}

void detruireListCell(Cell_segment* listCell)
{
  Cell_segment *cell=listCell;

  while(cell!=NULL)
    {
      cell=listCell->suiv;
      detruireCell(listCell);
      listCell=cell;
    }
}


void afficherListCell(Cell_segment* listCell)
{
  while(listCell!=NULL)
    {
      afficherCell(listCell);
      listCell=listCell->suiv;
    }
}

void insererTeteListCell(Cell_segment** listCell, Cell_segment * cell)
{
  cell->suiv=*listCell;
  *listCell=cell;
}

Cell_segment* insererTeteListCell2(Cell_segment* listCell, Cell_segment * cell)
{
  cell->suiv=listCell;
  return cell;
}

Cell_segment * indexList(Cell_segment* listCell,int i)
{
  while(i>0 && listCell != NULL)
    {
      listCell=listCell->suiv;
      i--;
    }
  return listCell;
}
