#ifndef __VECTEURS_H__
#define __VECTEURS_H__

#include <stdio.h>
#include <stdlib.h>
#include "types.h"



double length_squared(double *v);
void unit_vector(double *v);
double dot(double *u,double *v);
void at(ray *r,double t,double *dest);
void cross(double *u,double *v,double *dest);
void produit(double *u,double a);
void copy(double *u,double *dest);
double alea_(void);
double degrees_to_radians(double degrees);
double alea(double a,double b);
void alea_vec(double *vect);
void alea_vect_c(double *vect,double a, double b);
double min3(double a,double b,double c);
double max3(double a,double b,double c);
void random_in_unit_sphere(double *x,double *y,double *z);
void random_in_unit_disk(double *dest);
void random_in_hemisphere(double *x,double *y,double *z,double *v);
void random_unit_vector(double *a,double *b,double *c);
void set_face_normal(ray* r,double *outward_normal,hit_record *rec);
void afficher(hittable *tmp);

#endif 