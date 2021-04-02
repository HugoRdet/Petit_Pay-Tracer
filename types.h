#ifndef _TYPES_H_
#define _TYPES_H_

#include <pthread.h>

typedef struct ray_{
	double *point;
	double *direction;
}ray;

enum type{lambertian,metal,dielectic,checker_texture,diffuse_light};
enum geometrie{TRIANGLE,SPHERE,RECTANGLE};




typedef struct hit_record_{
	//point ou le vecteur touche l'objet
	double* p;
	//vecteur normal au point
	double* normale;
	struct materieau_ *mat_ptr;

	double t;
	double u;
	double v;
	//dit si la normale pointe vers l'interieur ou lexterieur de l objet
	int front_face;
}hit_record;


typedef struct texture_{
	double *odd;
	double *even;
}texture;

typedef struct materieau_{
	enum type type_mat;
	double *albedo;
	texture *text;
	double fuzz;
	int ( * scatter) (ray *,hit_record *,double *,ray *,struct materieau_ *);
}materieau;


typedef struct triangle_{
	double *a;
	double *b;
	double *c;
	int id;
	struct materieau_ *mat_ptr;
}triangle;

typedef struct rectangle_{
	double *a;
	double *b;
	int id;
	struct materieau_ *mat_ptr;
}rectangle;

typedef struct sphere_{
	double *centre;
	double rayon;
	materieau *mat_ptr;
	int id;
}sphere;

typedef struct hittable_{
	void *obj;
	enum geometrie geo;
	struct hittable_ *suiv;
}hittable;

enum type_noeud{feuille,branche};

typedef struct noeud_{
	
	struct noeud_ *fils_droit;
	struct noeud_ *fils_gauche;
	
	hittable *liste;
	
	double *cig;
	double *csd;
	
	int clef;
	int id;
		
}noeud;


typedef struct liste_n{
	noeud *n;
	struct liste_n *suiv;
}liste_noeud;

typedef struct camera_{
	
	
	double aspect_ratio;
	double largeur_plan;
	double longueur_plan;
	double focal_length;
	
	
	double lens_radius;
	
	double *u;
	double *v;
	double *w;
	
	double *origine;
	double *horizontal;
	double *vertical;
	double *llc;
}camera;



typedef struct point_fichier_{
	double x;
	double y;
	double z;
	
	int id;
	struct point_fichier_ *suiv;
}point_fichier;







#endif