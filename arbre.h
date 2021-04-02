#ifndef __ARBRE_H__
#define __ARBRE_H__

#include "types.h"
#include "tri.h"
#include "utilitaires.h"



int len(hittable *liste);

hittable *merge_sort(hittable **droite,int clef);
int construction_noeud(int prof,noeud **n,hittable **liste,int clef,int* id,liste_noeud **l);
void afficher_noeud(noeud *n);
void afficher(hittable *tmp);

void detruire_conteneur(hittable **liste);
void ajouter_liste(liste_noeud **l,noeud *n);

#endif