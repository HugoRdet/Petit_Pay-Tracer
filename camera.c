#include "camera.h"

#include "sphere.h"
#include "vecteurs.h"
#include "utilitaires.h"

void camera_init(camera **c,double angle,double aspect_ratio,double *lookfrom,double *lookat,double *vup,double aperture,double focus_dist){
	camera *new=(camera *) malloc(sizeof(camera));
	
	
	new->focal_length=1.00;
	double theta= degrees_to_radians(angle);
	double h=tan(theta/2);
	
	// ratio de l image
	new->aspect_ratio=aspect_ratio;
		
	//largeur image en pixels
	new->largeur_plan	=2.00 * h ;
	//longueur image en pixels
	new->longueur_plan	=(new->largeur_plan)*(new->aspect_ratio);
	
	//vecteurs utilitaires
	
	double *u=(double *) malloc(sizeof(double)*3);
	double *v=(double *) malloc(sizeof(double)*3);
	double *w=(double *) malloc(sizeof(double)*3);
	
	w[0]=lookfrom[0] - lookat[0];
	w[1]=lookfrom[1] - lookat[1];
	w[2]=lookfrom[2] - lookat[2];
	unit_vector(w);
	cross(vup,w,u);
	unit_vector(u);
	cross(w,u,v);
	
	new->u=u;
	new->v=v;
	new->w=w;

		
	new->origine=(double *) malloc(sizeof(double)*3);
	new->vertical=(double *) malloc(sizeof(double)*3);
	new->horizontal=(double *) malloc(sizeof(double)*3);
	new->llc=(double *) malloc(sizeof(double)*3);
	
	copy(u,new->horizontal);
	copy(v,new->vertical);
	
	(new->origine)[0]=lookfrom[0]; (new->origine)[1]=lookfrom[1]; (new->origine)[2]=lookfrom[2];
	
	
	produit(new->horizontal,new->longueur_plan);
	produit(new->horizontal,focus_dist);
	
	produit(new->vertical,new->largeur_plan);
	produit(new->vertical,focus_dist);
	
	
	(new->llc)[0]=(new->origine)[0]-((new->horizontal)[0]/2.)-((new->vertical)[0]/2.)-w[0]*focus_dist;
	(new->llc)[1]=(new->origine)[1]-((new->horizontal)[1]/2.)-((new->vertical)[1]/2.)-w[1]*focus_dist;
	(new->llc)[2]=(new->origine)[2]-((new->horizontal)[2]/2.)-((new->vertical)[2]/2.)-w[2]*focus_dist;
	
	new->lens_radius=aperture/2.0;
	(*c)=new;
}

void clear_camera(camera **cam){
	free((*cam)->u);
	free((*cam)->v);
	free((*cam)->w);
	
	free((*cam)->origine);
	free((*cam)->horizontal);
	free((*cam)->vertical);
	free((*cam)->llc);
	
	free(*cam);
}