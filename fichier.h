#ifndef __FICHIER_H__
#define __FICHIER_H__

#include "types.h"
#include "materiaux.h"
#include "hittable.h"
#include "arbre.h"


void attribue_id(hittable *liste);
void charge_fichier_spheres(char *nom_f,hittable **L);
void ecris_fichier_sphere(char *nom_f,hittable *L);
void charge_fichier_ply(char *nom,hittable **liste);
void charge_fichier_obj(char *nom,hittable **liste,materieau *mat);

void ecrire_arbre(char *nom,hittable *liste);
int charge_fichier_arbre(char *nom_f,hittable ***tab_s,noeud ***tab_n,int *ts,int *tn);
#endif

