#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../head/SVGwriter.h"


void SVGinit(SVGwriter *svg, char *nom, int sizeX, int sizeY) {
  char filename[100];

  strcpy(filename,nom);
  strcat(filename,".svg");
  
  svg->file=fopen(filename, "w");

  if (svg->file==NULL) {
    printf("Unable to create %s\n",nom);
    exit(1);
  }
  
  strcpy(svg->lineColor, Red);
  strcpy(svg->pointColor, Black);

  svg->sizeX=sizeX;
  svg->sizeY=sizeY;

  svg->gencol[0]='0';svg->gencol[1]='1';svg->gencol[2]='2';svg->gencol[3]='3';
  svg->gencol[4]='4';svg->gencol[5]='5';svg->gencol[6]='6';svg->gencol[7]='7';
  svg->gencol[8]='8';svg->gencol[9]='9';svg->gencol[10]='A';svg->gencol[11]='B';
  svg->gencol[12]='C';svg->gencol[13]='D';svg->gencol[14]='E';svg->gencol[15]='F';


  fprintf(svg->file,"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.2\"");
  fprintf(svg->file, " width=\"100%%\" height=\"100%%\"");
  fprintf(svg->file, " viewBox=\"%lf %lf %lf %lf\"", -2.0, -2.0, sizeX+7.0, sizeY+7.0);
  fprintf(svg->file, " preserveAspectRatio=\"yes\">\n");
  fprintf(svg->file, "<g >\n\n");

  svg->lineColor[0]='#';
}


void SVGlineColor(SVGwriter *svg, char *col) {
  strcpy(svg->lineColor,col);
}

void SVGlineRandColor(SVGwriter *svg){
  int i;
  for (i=1;i<=6;i++) svg->lineColor[i]=svg->gencol[rand()%16];

}

void SVGpointColor(SVGwriter *svg, char *col) {
  strcpy(svg->pointColor,col);
}

void SVGtext(SVGwriter *svg, double x, double y,int num)
{
  fprintf(svg->file,"<text x=\"%lf\" y=\"%lf\" font-size=\"2\" font-family=\"Accanthis ADF Std\" style=\" fill: %s ;\">%d</text>\n",x+1,y-1,svg->lineColor,num);
}

void SVGrectangle(SVGwriter *svg, double x, double y)
{
  fprintf(svg->file,"<rect x=\"%lf\" y=\"%lf\" width=\"0.5\" height=\"0.5\" stroke=\"#FDF901\" stroke-width=\"1\" fill=\"#FDF901\" />\n",x-0.5,y-0.5);

}

void SVGpoint(SVGwriter *svg, double x, double y,int i) {
  fprintf(svg->file,"<circle cx=\"%lf\" cy=\"%lf\" r=\"0.1\" stroke=\"%s\" stroke-width=\"1\" fill=\"%s\" />\n",x,y,svg->pointColor,svg->pointColor);
  if(i!=-1)
    SVGtext(svg,x,y,i);
}


void SVGcircle(SVGwriter* svg, double x, double y,int i)
{
  fprintf(svg->file,"<circle cx=\"%lf\" cy=\"%lf\" r=\"7\" stroke=\"black\" stroke-width=\"1\" fill=\"#FFFFFFFF\" />\n",x,y);

  SVGtext(svg,x-3,y+2,i);
}

void SVGlineCop(SVGwriter *svg,double xa,double ya,double xb,double yb)
{
  fprintf(svg->file, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" ", xa, ya, xb, yb);
  fprintf(svg->file, " stroke-dasharray=\"1,1\" style=\"stroke:%s;stroke-width:0.5\"/>\n", svg->lineColor); 

}
void SVGline(SVGwriter *svg,double xa,double ya,double xb,double yb) {
  fprintf(svg->file, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" ", xa, ya, xb, yb);
  fprintf(svg->file, " style=\"stroke:%s;stroke-width:0.5\"/>\n", svg->lineColor);    
}


void SVGfinalize(SVGwriter *svg) {

  fprintf(svg->file, "\n\n</g></svg>\n");
  fclose(svg->file);
  svg->file=NULL;
}

///////////////////////////////////////////////// page HTML intersection

FILE* HTMLinit(char* nom)
{
  char name[100];
  FILE* file;
  
  strcpy(name,nom);
  strcat(name,"Inter.html");

  file=fopen(name,"w");

  if (file==NULL)
    {
      printf("Unable to create %s\n",nom);
      exit(1);
    }

  fprintf(file,"<!DOCTYPE html>\n<html>\n<head><meta charset=\"utf-8\" /> <link rel=\"stylesheet\" href=\"../styleMenu.css\" /> </head>");
  fprintf(file,"<body>\n");

  fprintf(file,"<nav>\n<ul>\n<li><a class=\"accueil1\" href=\"../partieA.html\">Partie A</a></li>\n");
  fprintf(file,"<li><a href=\"../circuit.html\">Circuit</a></li>\n");
  fprintf(file,"<li><a href=\"#\">Intersection</a></li>\n");
  fprintf(file,"<li><a href=\"../complexite.html\">Complexite</a></li>\n");
  fprintf(file,"<li><a class=\"accueil2\" href=\"../partieB.html\">Partie B</a></li>\n");
  fprintf(file,"</ul>\n</nav>\n<div style=\"margin-left:25%c;padding:1px 16px;height:1000px;\">\n",'%');

  
  return file;
}

void HTMLcreerTab(FILE* file,char* color)
{
  fprintf(file,"<table>\n<thead>\n<tr><th style=\"color: %s\">Segment</th> <th>Reseau</th> <th>Segment</th></tr>\n</thead>\n<tbody>\n",color);
}

void HTMLfinTab(FILE* file)
{
  fprintf(file,"</tbody>\n</table>\n");
}

void HTMLtitre(FILE* file,int numRes,char* color)
{
  fprintf(file,"<h1 style=\"color: %s\">Reseau %d :</h1>\n",color,numRes);
}

void HTMLligne(FILE* file,char*color,int a,int b,int c,int d,int e)
{
  fprintf(file,"<tr><th style=\"color: %s\">( %d , %d )</th><th>%d</th><th>( %d , %d )</th></tr>\n",color,a,b,c,d,e);
}

void HTMLfinalize(FILE* file)
{
  fprintf(file, "\n\n</div>\n</body>\n</html>\n");
  fclose(file);
}

void HTMLdelText(FILE* file)
{
  char c;
  
  c=getc(file);

  while(c!=EOF && c!='\n')
    {
      fseek(file,-1,SEEK_CUR);
      fprintf(file," ");
      c=getc(file);
    }
  fseek(file,-1,SEEK_CUR);
  fprintf(file," ");
}
