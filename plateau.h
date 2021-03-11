#ifndef _PLATEAU_H
#define _PLATEAU_H

typedef struct plateau {
    int taille;
    pile** p;
} plateau;

typedef struct tableau {
    int taille;
    int** c; 
} case_activee;

plateau* init_plateau(int taille);
void print_plateau(plateau* p);
int plateau_plein_ou_non(plateau* p);
case_activee init_case_activee(int taille);
plateau* activation_plateau(plateau* p,int joueur,int ligne,int colonne,case_activee* tab);

#endif