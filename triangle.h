#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "types.h"
#include "hittable.h"
#include "utilitaires.h"

int hit_triangle(ray *rayon,double tmax,triangle *t,hit_record *rec);
void libere_triangle(triangle *tri);


#endif