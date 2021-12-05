#ifndef __CELL_SEGMENT_H__
#define __CELL_SEGMENT_H__

//////////////////////// Structure

struct segment ;

typedef struct cell_segment {

   struct segment * seg ;
   struct cell_segment * suiv ;

}Cell_segment ;

/////////////////////// Fonctions Cell

Cell_segment * creerCell(struct segment *seg);
void detruireCell(Cell_segment* cell);
void afficherCell(Cell_segment* c);


/////////////////////// Fonctions ListCell

int lenListCell(Cell_segment*listCell);
void detruireListCell(Cell_segment* listCell);
Cell_segment* popCell(Cell_segment** listCell,struct segment * seg);
int supprimerEleListCell(Cell_segment** listCell,Cell_segment * seg);
void insererTeteListCell(Cell_segment** listCell,Cell_segment * seg);
Cell_segment* insererTeteListCell2(Cell_segment* listCell,Cell_segment * seg);
void afficherListCell(Cell_segment* listCell);
Cell_segment * indexList(Cell_segment* listCell,int i);

#endif
