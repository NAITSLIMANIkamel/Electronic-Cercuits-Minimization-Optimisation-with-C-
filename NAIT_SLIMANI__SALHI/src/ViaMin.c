#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../head/menu.h"


int main (int argc , char * * argv )
{
  char choix1[2],choix2[2];
  int pid=-1;

  choix1[1]='\0';
  choix2[1]='\0';

  if ( argc !=2) {
    printf ("\033[31m Erreur format : %s <NomFichier.net> \033[0m\n",argv [0]) ;
    return 1;
  }

  do
    {

      menu1(); /* affiche le menu */
      read(0,&choix1[0],2);
      system("clear");

      if(choix1[0]=='0')
	{
	  printf ("Au revoir :-) \n");
	  return EXIT_SUCCESS;
	}

      if(choix1[0]=='4')
	{
	  system("rm HTML/IntersectionHTML/* *.int 2>t");
	  system("rm t");
	}

      if(choix1[0]-48<0 && choix1[0]-48>4)
	printf("\033[31mVoute choix n'existe pas :-(\033[0m\n");
      else
	if(choix1[0]!='4')
	  {
	    menu2();
	    read(0,&choix2[0],2);
	    system("clear");

	    if(choix2[0]-48<0 && choix2[0]-48>3)
	      printf("\033[31mVoute choix n'existe pas :-(\033[0m\n");

	    if(choix2[0]!='0')
	      {
		if(fork()==0)
		  {
		    execlp("./main","./main",argv[1],choix1,choix2,NULL);
		    exit(1);
		  }

		pid=fork();
		if(pid==0)
		  {
		    execlp("./wait","./wait",NULL);
		    exit(1);
		  }
		wait(NULL);
		kill(pid,9);
		printf("\033[32m╣ \033[0m\n");
		system("clear");
		printf("Un page web va s'ouvrire .......\n");
	      
		pid=fork();
		if(pid==0)
		  {
		    execlp("/usr/bin/firefox","firefox","ViaMin.html",NULL);
		    exit(1);
		  }
		wait(NULL);
		wait(NULL);
	      }
	  
	  }
    }while(1);


  return EXIT_SUCCESS;
}
