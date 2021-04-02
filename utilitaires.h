#ifndef __UTILITAIRES_H__
#define __UTILITAIRES_H__


#define SAMPLES 50
#define pi 3.1415926535897932385
#define ASPECT_RATIO 16.0/9.0
#define profondeur 8
#define FILS 8
#define longueur_noeud 4
#define EPSILON 0.00000001



#include "types.h"
#include "vecteurs.h"
#include "sphere.h"
#include "camera.h"
#include "hittable.h"
#include "rayons.h"
#include "triangle.h"
#include "materiaux.h"

#include <math.h>

void scene_alea(hittable **world);
double clamp(double x,double min,double max);
void write_color(FILE *fichier,double *res_color);
void calcul_scene(int hauteur_image,int largeur_image,FILE *fichier_dst,noeud *arbre,camera *cam);
void creer_pave(double *a,double x,double y,double z,hittable **liste,materieau *mat_ptr);
void cree_rectangle_sol(double *a,double x,double y,double z,hittable **liste,materieau *mat_ptr);
void sol_cube(hittable **liste,materieau *mat_ptr);
void cornell_box(hittable **liste);

void rotation_x(double angle,hittable *liste);
void rotation_y(double angle,hittable *liste);
void rotation_z(double angle,hittable *liste);

void translation(double x,double y,double z,hittable *liste);

#endif
