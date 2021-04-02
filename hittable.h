#ifndef __HITTABLE_H__
#define __HITTABLE_H__

#include "types.h"
#include "vecteurs.h"
#include "triangle.h"
#include "sphere.h"

int len(hittable *liste);
void detruire_conteneur(hittable **liste);
void add(hittable **L,void *sph,enum geometrie type);
void add_liste(hittable **L,hittable **dest);
void libere_liste(hittable **L);
#endif