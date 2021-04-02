#ifndef __MATERIAUX_H__
#define __MATERIAUX_H__

#include "types.h"
#include "vecteurs.h"
#include <math.h>
int scatter_lambertian(ray *in,hit_record *rec,double *attenuation,ray *scattered,materieau *mat);
int scatter_metal(ray *in,hit_record *rec,double *attenuation,ray *scattered,materieau *mat);
int scatter_dielectic(ray *in,hit_record *rec,double *attenuation,ray *scattered,materieau *mat);

#endif