#ifndef _PILE_H
#define _PILE_H

typedef struct pile {
    int value;
    struct pile* next;
} *pile;

pile init_pile();
int pile_vide_ou_non(pile p);
void ajouter_valeur(int v, pile* p);
void retirer_valeur_sans_retour(pile* p);
int sommet_pile(pile p);
int sommet_egal_ajout(int v, pile p);
void affichage_pile(pile p);

#endif