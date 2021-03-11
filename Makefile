Jeu: Jeu.c pile.o plateau.o
	gcc -Wall pile.o plateau.o -o Jeu Jeu.c

pile.o: pile.h pile.c
	gcc -Wall -c pile.c

plateau.o: plateau.h plateau.c pile.c pile.h
	gcc -Wall -c plateau.c