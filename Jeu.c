#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "pile.h"
#include "plateau.h"

int main() {
    int j,n,joueur_actuel=1,g,compteur,l,c,indice,gagnant_final,indice_final;
    char buf[256],buf1[256];
    printf("Combien de joueurs jouent au jeu ?\n"); // On récupère ici le nombre de joueurs
    fgets(buf,256,stdin);
    sscanf(buf,"%d",&j);
    if (j<2) { // On impose ici de jouer au minimum à deux
        printf("Le jeu se joue au moins à deux !\n");
        exit(0);
    }
    printf("Quelle est la taille du plateau ?\n"); // On récupère ici la taille du plateau
    fgets(buf1,256,stdin);
    sscanf(buf1,"%d",&n);
    if (n<3) { // On impose un plateau minimum de taille 3x3
        printf("La taille minimale du plateau est 3x3\n");
        exit(1);
    }
    printf("\n");
    plateau* plateau_de_jeu=init_plateau(n);
    while (plateau_plein_ou_non(plateau_de_jeu)) {
        /* Terminaison de la boucle While
        Cette boucle se termine lorsque toutes les cases du plateau sont occupées
        Ainsi, elle va se terminer au bout d'un certain nombre de coup */
        case_activee tab_case_activee=init_case_activee(n);
        int ligne,colonne;
        char buf2[256],buf3[256],decision[256];
        if (joueur_actuel>j) { // On récupère ici le joueur qui doit jouer ce tour et on le rénitialise en cas de problème
            joueur_actuel=1;
        }
        printf("Tour du joueur %d\n",joueur_actuel);
        print_plateau(plateau_de_jeu);
        printf("Quelle case choisissez-vous ?\n"); //On récupère ici la case où souhaite jouer le joueur
        fgets(buf2,256,stdin);
        sscanf(buf2,"%i%i",&ligne,&colonne);
        if (ligne>n || ligne<1) { // Si le numéro de ligne n'est pas valide, on renvoie le joueur au début de son tour
            printf("Le numéro de ligne n'est pas valide\n");
        }
        else if (colonne>n || colonne<1) { // Si le numéro de colonne n'est pas valide, on renvoie le joueur au début de son tour
            printf("Le numéro de colonne n'est pas valide\n");
        }
        else {
            printf("\n");
            affichage_pile(plateau_de_jeu->p[ligne-1][colonne-1]); // On affiche la pile se situant sur la case choisie par le joueur
            printf("Voulez vous mettre le jeton ici ?\n");
            fgets(buf3,256,stdin);
            sscanf(buf3,"%s",decision);
            printf("\n");
            if (!strcmp(decision,"o") || !strcmp(decision,"oui")) { // Si le joueur tape "o" ou "oui", son choix est confirmé
                plateau_de_jeu=activation_plateau(plateau_de_jeu,joueur_actuel,ligne-1,colonne-1,&tab_case_activee);
                joueur_actuel+=1; // Au tour du joueur suivant
            }
        }
    }
    int gagnant[j];
    for (g=1;g<=j;g++) { // On va créer un tableau contenant le nombre de jetons au sommet des piles pour chacun des joueurs
        compteur=0;
        for (l=0;l<n;l++) {
            for (c=0;c<n;c++) {
                if ((sommet_pile(plateau_de_jeu->p[l][c]))==g) {
                    compteur+=1;
                }
            }
        }
        gagnant[g-1]=compteur;
    }
    gagnant_final=gagnant[0];
    indice_final=0;
    for (indice=1;indice<j;indice++) { // On récupère le numéro du joueur gagnant ainsi que son score
        if (gagnant[indice]>gagnant_final) {
            gagnant_final=gagnant[indice];
            indice_final=indice;
        }
    }
    print_plateau(plateau_de_jeu);
    printf("Le gagnant est le joueur %d avec un score de %d !\n",indice_final+1,gagnant_final);
    free(plateau_de_jeu); // On libère le plateau une fois le gagnant annoncé et le plateau final affiché
    return 0;
}