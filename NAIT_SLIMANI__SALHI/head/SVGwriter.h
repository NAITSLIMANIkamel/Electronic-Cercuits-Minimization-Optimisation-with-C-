#ifndef _SVGWRITER_H_
#define _SVGWRITER_H_

/* Dans cette librairie, les couleurs sont utilisees sous leur forme
   hexadecimale comme le montre les exemples suivants) */
#define White "#FFFFFF"
#define Black "#000000"
#define Cyan "#00FFFF"
#define Fuchsia "#FF00FF"
#define Lime "#00FF00"
#define Orange "#FFA800"
#define Red "#FF0000"
#define RoyalBlue "#486CE8"



typedef struct SVGwriter_struct {
  
  char lineColor[10];  /* Default color value */
  char pointColor[10]; /* Default color value */
  int sizeX, sizeY;    /* Picture size */
   
  FILE *file; /* File stream */

  /* Technical value for random color generation */
  char gencol[16];

} SVGwriter;


  
/* Initialise le struct SVGwriter passe en parametre
      nomfic: nom du fichier html \'a creer
      sizeX, sizeY: taille en pixel de l'image \'a creer */
void SVGinit(SVGwriter *svg,char *nomfic, int sizeX, int sizeY);

/* Fixe la couleur des lignes pour la suite */
void SVGlineColor(SVGwriter *svg, char *col);

/* Fixe une couleur aleatoire pour les lignes pour la suite */
void SVGlineRandColor(SVGwriter *svg);

/* Fixe la couleur des points pour la suite */
void SVGpointColor(SVGwriter *svg, char *col);

/* Ecrit un rectangle dans le fichier */ 
void SVGrectangle(SVGwriter *svg, double x, double y);

/* Ecrit un point dans le fichier */ 
void SVGpoint(SVGwriter *svg, double x, double y,int i);

/* Ecrit un circle dans le fichier */ 
void SVGcircle(SVGwriter* svg, double x, double y,int i);

/*Ecrit un segment dans le fichier */
void SVGline(SVGwriter *svg, double xa, double ya, double xb, double yb);

/*Ecrit un segment coupée dans le fichier */
void SVGlineCop(SVGwriter *svg,double xa,double ya,double xb,double yb);

/* Ferme le fichier */
void SVGfinalize(SVGwriter *svg);

///////////////////////////////////// fonction pour HTML
FILE* HTMLinit(char* nom);
void HTMLcreerTab(FILE* file,char* color);
void HTMLfinTab(FILE* file);
void HTMLtitre(FILE* file,int numRes,char* color);
void HTMLligne(FILE* file,char* color,int a,int b,int c,int d,int e);
void HTMLfinalize(FILE* file);
void HTMLdelText(FILE* file);

#endif
