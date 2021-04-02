#ifndef __RAYONS_H__
#define __RAYONS_H__

#include "types.h"
#include "vecteurs.h"
#include "sphere.h"
#include "triangle.h"
#include "hittable.h"
#include "camera.h"
#include "utilitaires.h"

int hittable_list(ray *r,hit_record *rec,hittable *L,hit_record *tmp_rec,hittable **dst);
void ray_color(double *c_background,ray *r,noeud *arbre,double *color,hit_record *rec,hit_record *tmp_rec);
void ray_color_normal(double *c_background,ray *r,noeud *arbre,double *color,hit_record *rec,hit_record *tmp_rec);
void get_ray(double t,double s, ray *r , camera *c);

#endif