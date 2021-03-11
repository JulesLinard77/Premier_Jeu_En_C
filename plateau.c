#include <stdlib.h>
#include <stdio.h>
#include "pile.h"
#include "plateau.h"

/* @requires taille est supérieur ou égal à 1
@assigns On alloue la place en mémoire pour un plateau en allouant en mémoire une pile par case
@ensures On retourne un plateau initialisé de la taille souhaitée */
plateau* init_plateau(int taille) {
    int i,j,k;
    plateau *plat=malloc(sizeof(struct plateau));
    plat->taille=taille;
    plat->p=malloc(taille*sizeof(struct pile*));
    for (i=0;i<taille;i++) {
        plat->p[i]=malloc(taille*sizeof(struct pile*));
    }
    for (j=0;j<taille;j++) {
        for (k=0;k<taille;k++) {
            (plat->p)[j][k]=init_pile();
        }
    }
    return plat;
};

/* @requires plat est un plateau* valide
@assigns Rien
@ensures On affiche le plateau plat en affichant sur chaque case le sommet de la pile associée*/
void print_plateau(plateau* plat) {
    int i,l,c,k;
    printf("   ");
    printf("|");
    for (i=1;i<(plat->taille)+1;i++) {
        printf("%3d",i);
    }
    printf("\n");
    printf("---");
    printf("+");
    for (k=1;k<(plat->taille)+1;k++) {
        printf("---");
    }
    printf("\n");
    for (l=1;l<(plat->taille)+1;l++) {
        printf("%3d",l);
        printf("|");
        for (c=0;c<(plat->taille);c++) {
            printf("%3d",sommet_pile((plat->p)[l-1][c]));
        }
        printf("\n");
    }
}

/* @requires plat est un plateau* valide
@assigns Rien
@ensures On retourne 1 si le plateau est vide (cases du plateau = 0), 0 sinon */
int plateau_plein_ou_non(plateau* plat) {
    int c,l,res;
    for (l=0;l<(plat->taille);l++) {
        for (c=0;c<(plat->taille);c++) {
            if (sommet_pile(plat->p[l][c])==0) {
                res=1;
                return res;
            }
        }
    }
    res=0;
    return res;
}

/* @requires Un entier supérieur à 0 
@assigns On alloue en mémoire la place pour un tableau 2D d'entiers
@ensures On retourne un tableau 2D d'entiers initialisé avec tous ses éléments égaux à 0 */
case_activee init_case_activee(int taille) {
    case_activee tab;
    int i,j,k;
    tab.taille=taille;
    (tab.c)=(int**)calloc(taille, sizeof(int*));
    for (i=0;i<tab.taille;i++) {
        (tab.c)[i]= (int*)calloc(taille,sizeof(int));
    }
    for (j=0;j<tab.taille;j++) {
        for (k=0;k<tab.taille;k++) {
            (tab.c)[j][k]=0;
        }
    }
    return tab;
}

/* @requires Un plateau* valide, joueur supérieur ou égal à 2, 0<ligne<plat->taille, 0<colonne<plat->taille, et un tableau 2D d'entiers
@assigns Les valeurs des cases du plateau, ainsi que les valeurs dans le tableau 2D d'entiers indiquant si une case est activée ou non
@ensures On renvoie le plateau de jeu avec les modifications effectuées suite à l'activation ou non de (plusieurs) cases */
plateau* activation_plateau(plateau* plat,int joueur,int ligne,int colonne,case_activee* tab) {
    /*programme récursif
    Ce programme se termine grâce à tab.
    En effet, une case ne pouvant être activée qu'une seule fois par tour,
    Le programme va s'appeler au maximum autant de fois qu'il faut pour activer toutes les cases du plateau
    Or, ce nombre de cases est fini, donc le programme va se terminer. */
    if (joueur==sommet_pile( (plat->p)[ligne][colonne]) && (tab->c)[ligne][colonne]!=1) { 
        retirer_valeur_sans_retour( &((plat->p)[ligne][colonne]) ); 
        ((*tab).c)[ligne][colonne]=1;
        if (ligne==0 && colonne==0) {
            plat=activation_plateau(plat,joueur,ligne+1,colonne,tab);
            plat=activation_plateau(plat,joueur,ligne,colonne+1,tab);
        }
        else if (ligne==0 && colonne==((*plat).taille-1)) {
            plat=activation_plateau(plat,joueur,ligne+1,colonne,tab);
            plat=activation_plateau(plat,joueur,ligne,colonne-1,tab);
        }
        else if (ligne==((*plat).taille-1) && colonne==((*plat).taille-1)) {
            plat=activation_plateau(plat,joueur,ligne-1,colonne,tab);
            plat=activation_plateau(plat,joueur,ligne,colonne-1,tab);
        }
        else if (ligne==((*plat).taille-1) && colonne==0) {
            plat=activation_plateau(plat,joueur,ligne,colonne+1,tab);
            plat=activation_plateau(plat,joueur,ligne-1,colonne,tab);
        }
        else if (ligne==0) {
            plat=activation_plateau(plat,joueur,ligne,colonne-1,tab);
            plat=activation_plateau(plat,joueur,ligne,colonne+1,tab);
            plat=activation_plateau(plat,joueur,ligne+1,colonne,tab);
        }
        else if (colonne==0) {
            plat=activation_plateau(plat,joueur,ligne-1,colonne,tab);
            plat=activation_plateau(plat,joueur,ligne+1,colonne,tab);
            plat=activation_plateau(plat,joueur,ligne,colonne+1,tab);
        }
        else if (ligne==((*plat).taille-1)) {
            plat=activation_plateau(plat,joueur,ligne-1,colonne,tab);
            plat=activation_plateau(plat,joueur,ligne,colonne-1,tab);
            plat=activation_plateau(plat,joueur,ligne,colonne+1,tab);
        }
        else if (colonne==((*plat).taille-1)) { 
            plat=activation_plateau(plat,joueur,ligne-1,colonne,tab);
            plat=activation_plateau(plat,joueur,ligne+1,colonne,tab);
            plat=activation_plateau(plat,joueur,ligne,colonne-1,tab);
        }
        else {
            plat=activation_plateau(plat,joueur,ligne,colonne-1,tab);
            plat=activation_plateau(plat,joueur,ligne,colonne+1,tab);
            plat=activation_plateau(plat,joueur,ligne-1,colonne,tab);
            plat=activation_plateau(plat,joueur,ligne+1,colonne,tab);
        }
    }
    if ((tab->c)[ligne][colonne]==0) {
        ajouter_valeur(joueur,&(plat->p)[ligne][colonne]);
    }
    return plat;
}

