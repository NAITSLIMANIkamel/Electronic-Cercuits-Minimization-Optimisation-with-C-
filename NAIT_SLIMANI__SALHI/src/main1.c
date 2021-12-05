#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../head/echeancierAVL.h"
#include "../head/menu.h"

#define M 60


int main (int argc , char * * argv )
{
  Netlist * net;
  char ch;


  if ( argc !=2) {
    printf ("\033[31m Erreur format : %s <NomFichier.net> \033[0m\n",argv [0]) ;
    return 1;
  }

  do{
    net=init_netlist(argv[1]);
    menu(); /* affiche le menu */
    ch=getchar()-48;

    system("clear");

    switch (ch){
    case 1:
      intersect_naif(net);
      break ;

    case 2:
      intersections_balayage(net);
      break ;

    case 3: 
      intersectionsBalayageAVL(net);
      break;
  
    case 4:

      system("ls HTML/IntersectionHTML/ 2>t");
      printf("les fichiers sont supprime\n");
      system("rm HTML/IntersectionHTML/* 2>t");
      system("rm t");
      break;  

    case 0:break;
    default :
      printf("\033[31mVoute choix n'existe pas :-(\033[0m\n");
      break;
    }
    if(ch>0 && ch <4)
      {
	sauvegarde_NetlistSVG(net,argv[1],ch);
	system("xdg-open HTML/partieA.html");
	printf("Un page web va s'ouvrire .......\n");
	detruireNetlist(net);
      }
    if(ch!=0)
      retourAuMenu();
  } while(ch!=0) ;

  detruireNetlist(net);
  printf ("Au revoir :-) \n");

  return EXIT_SUCCESS;
}
