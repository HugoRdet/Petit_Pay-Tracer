#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "types.h"
#include "vecteurs.h"
#include "hittable.h"


int hit_sphere(ray *r,double tmin,double tmax,sphere *sph,hit_record *rec);
void creer_sphere(hittable **L,double rayon,double *centre,materieau *mat);
void libere_sphere(sphere *sph);






#endif