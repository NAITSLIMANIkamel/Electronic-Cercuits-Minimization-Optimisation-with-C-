ViaMin.o:main wait menu.o ViaMin.c
	gcc  -Wall -ggdb menu.o ViaMin.c -o ../ViaMin -lm;rm *~ *.o

main3: cell_segment.o  entree_sortie.o  main3.o netlist.o  point.o  reseau.o  segment.o echeancier.o SVGwriter.o echeancierAVL.o AVL.o menu.o graphe.o viaminAlgo.o
	gcc -Wall -ggdb cell_segment.o  entree_sortie.o  main3.o  netlist.o  point.o  reseau.o  segment.o echeancier.o SVGwriter.o graphe.o echeancierAVL.o AVL.o viaminAlgo.o  -o ../main3 -lm;rm *~ *.o

wait:wait.c
	gcc -Wall -ggdb wait.c -o ../wait -lm

main: cell_segment.o  entree_sortie.o  main.o netlist.o  point.o  reseau.o  segment.o echeancier.o SVGwriter.o echeancierAVL.o AVL.o menu.o graphe.o viaminAlgo.o
	gcc -Wall -ggdb cell_segment.o  entree_sortie.o  main.o  netlist.o  point.o  reseau.o  segment.o echeancier.o SVGwriter.o graphe.o echeancierAVL.o AVL.o viaminAlgo.o  -o ../main -lm

all4: cell_segment.o  entree_sortie.o  main.o  netlist.o  point.o  reseau.o  segment.o echeancier.o SVGwriter.o echeancierAVL.o AVL.o menu.o graphe.o viaminAlgo.o
	gcc -Wall -ggdb cell_segment.o  entree_sortie.o  main.o  netlist.o  point.o  reseau.o  segment.o echeancier.o SVGwriter.o graphe.o echeancierAVL.o AVL.o menu.o viaminAlgo.o -o ../main -lm;rm *~ *.o

all3: cell_segment.o  entree_sortie.o  main2.o  netlist.o  point.o  reseau.o  segment.o echeancier.o SVGwriter.o echeancierAVL.o AVL.o menu.o graphe.o viaminAlgo.o
	gcc -Wall -ggdb cell_segment.o  entree_sortie.o  main2.o  netlist.o  point.o  reseau.o  segment.o echeancier.o SVGwriter.o graphe.o echeancierAVL.o AVL.o menu.o viaminAlgo.o -o ../g -lm;rm *~ *.o


all2: cell_segment.o  entree_sortie.o  main2.o  netlist.o  point.o  reseau.o  segment.o echeancier.o SVGwriter.o echeancierAVL.o AVL.o menu.o graphe.o
	gcc -Wall -ggdb cell_segment.o  entree_sortie.o  main2.o  netlist.o  point.o  reseau.o  segment.o echeancier.o SVGwriter.o graphe.o echeancierAVL.o AVL.o menu.o -o ../g -lm;rm *~ *.o

all: cell_segment.o  entree_sortie.o  main.o  netlist.o  point.o  reseau.o  segment.o echeancier.o SVGwriter.o echeancierAVL.o AVL.o menu.o
	gcc -Wall -ggdb cell_segment.o  entree_sortie.o  main.o  netlist.o  point.o  reseau.o  segment.o echeancier.o SVGwriter.o echeancierAVL.o AVL.o menu.o -o ../main -lm;rm *~ *.o


main.o: main.c
	gcc -c -Wall -ggdb main.c -o main.o -lm

main3.o: main3.c
	gcc -c -Wall -ggdb main3.c -o main3.o -lm

cell_segment.o: cell_segment.c ../head/cell_segment.h
	gcc -c -Wall -ggdb cell_segment.c -o cell_segment.o -lm


netlist.o:netlist.c ../head/netlist.h
	gcc -c -Wall -ggdb netlist.c -o netlist.o -lm


point.o:point.c ../head/point.h
	gcc -c -Wall -ggdb point.c -o point.o -lm


reseau.o:reseau.c ../head/reseau.h
	gcc -c -Wall -ggdb reseau.c -o reseau.o -lm


segment.o:segment.c ../head/segment.h
	gcc -c -Wall -ggdb segment.c -o segment.o -lm

echeancier.o: echeancier.c ../head/echeancier.h
	gcc -c -Wall -ggdb echeancier.c -o echeancier.o -lm

SVGwriter.o: SVGwriter.c ../head/SVGwriter.h
	gcc -c -Wall -ggdb SVGwriter.c -o SVGwriter.o

echeancierAVL.o: echeancierAVL.c ../head/echeancierAVL.h
	gcc -c -Wall -ggdb echeancierAVL.c -o echeancierAVL.o -lm

AVL.o:AVL.c ../head/AVL.h
	gcc -c -Wall -ggdb AVL.c -o AVL.o -lm

graphe.o: graphe.c ../head/graphe.h
	gcc -c -Wall -ggdb graphe.c -o graphe.o -lm

viaminAlgo.o:viaminAlgo.c ../head/viaminAlgo.h
	gcc -c -Wall -ggdb viaminAlgo.c -o viaminAlgo.o -lm

main2.o: main2.c
	gcc -c -Wall -ggdb main2.c -o main2.o -lm
main1.o: main1.c
	gcc -c -Wall -ggdb main1.c -o main1.o -lm
