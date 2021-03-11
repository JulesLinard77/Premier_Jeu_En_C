#include <stdlib.h>
#include <stdio.h>
#include "pile.h"

/* @requires Rien
@assigns On alloue la place en mémoire nécessaire à un maillon
@ensures On renvoie une pile composée d'un seul maillon contenant la valeur 0 */
pile init_pile() {
    pile p=malloc(sizeof(struct pile));
    p->value=0;
    p->next=NULL;
    return p;
}

/* @requires Une pile valide 
@assigns Rien
@ensures Renvoie 1 si la pile p est vide, 0 sinon */
int pile_vide_ou_non(pile p) {
    return (p==NULL);
}

/* @requires Une pile* valide p et un entier v que l'on veut ajouter au sommet de cette pile
@assigns Un nouveau maillon que l'on rajoutera au sommet de la pile
@ensures On renvoie la pile p ayant pour nouveau sommet le maillon contenant la valeur v */
void ajouter_valeur(int v, pile* p) {
    pile tmp=malloc(sizeof(struct pile));
    tmp->value=v;
    tmp->next=*p;
    *p=tmp;
}

/* @requires Une pile* valide 
@assigns On modifie cette pile p en retirant l'élément à son sommet, c'est à dire en libérant son dernier maillon
@ensures On renvoie la pile p sans son sommet */
void retirer_valeur_sans_retour(pile* p) {
    pile tmp;
    tmp=*p;
    *p=(*p)->next;
    tmp->next=NULL;
    free(tmp);
}

/* @requires Une pile valide 
@assigns Rien
@ensures On retourne la valeur de l'élément au sommet de la pile */
int sommet_pile(pile p) {
    int res;
    res=p->value;
    return res;
}

/* @requires Un entier et une pile valide 
@assigns Rien
@ensures On retourne 1 si v est égal au sommet de la pile p, 0 sinon */
int sommet_egal_ajout(int v,pile p) {
    return(v==(p->value));
}

/* @requires Une pile valide 
@assigns Rien
@ensures On affiche les éléments de la pile en commençant par le sommet et en finissant par sa base */
void affichage_pile(pile p) {
    while (p != NULL) {
        /* Terminaison de la boucle While
        L'instruction p=p->next permet de parcourir les différents maillons composant la pile
        La pile comportant un nombre fini d'éléments, on finira par arriver au dernier maillon
        Et le dernier pointera vers le maillon NULL */
        printf(" %2d\n",p->value);
        p = p->next;
    }
    printf("---\n");
}

