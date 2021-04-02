#include "sphere.h"






void get_sphere_uv(double *p,double *u,double *v){
		double phi= atan2(p[2],p[0]);
		double theta = asin(p[1]);
		*u=1-(phi+pi) /(2*pi);
		*v=(theta + pi/2 ) / pi ;
}


//permet de savoir si un rayon rencontre une sphere
int hit_sphere(ray *r,double tmin,double tmax,sphere *sph,hit_record *rec){
	//calcul pour savoir si le rayon touche la sphere
	double ocx=(r->point)[0]-(sph->centre)[0];
	double ocy=(r->point)[1]-(sph->centre)[1];
	double ocz=(r->point)[2]-(sph->centre)[2];
	//calcul des coefs a b c du polynome
	double a=length_squared(r->direction);
	
	double half_b=ocx*(r->direction)[0]+ocy*(r->direction)[1]+ocz*(r->direction)[2];
	double c=(ocx*ocx+ocy*ocy+ocz*ocz)-(sph->rayon)*(sph->rayon);
	double discriminant= half_b*half_b-a*c;
	
	//si il y a deux racines:
	if (discriminant > 0){
		
		double root=sqrt(discriminant);
		double tmp=(-half_b - root)/a;
	
		if ((tmp< tmax)&&(tmp>tmin)){
			
			rec->t=tmp;
			at(r,tmp,(rec->p));
			double rayon=sph->rayon;
			(rec->normale)[0]=((rec->p)[0]-(sph->centre)[0])/rayon;
			(rec->normale)[1]=((rec->p)[1]-(sph->centre)[1])/rayon;
			(rec->normale)[2]=((rec->p)[2]-(sph->centre)[2])/rayon;
			double tmp_tab[3]={0.0,0.0,0.0};
			
			tmp_tab[0]=((rec->p)[0]-(sph->centre)[0])/(sph->rayon);
			tmp_tab[1]=((rec->p)[1]-(sph->centre)[1])/(sph->rayon);
			tmp_tab[2]=((rec->p)[2]-(sph->centre)[2])/(sph->rayon);
			
			get_sphere_uv(tmp_tab,&(rec->u),&(rec->v));
			(rec->mat_ptr)=(sph->mat_ptr);
			set_face_normal(r,rec->normale,rec);
			return 1;
		}
		
		tmp=(-half_b + root)/a;
		if ((tmp< tmax)&&(tmp>tmin)){
			rec->t=tmp;
			at(r,tmp,(rec->p));
			double rayon=sph->rayon;
			(rec->normale)[0]=((rec->p)[0]-(sph->centre)[0])/rayon;
			(rec->normale)[1]=((rec->p)[1]-(sph->centre)[1])/rayon;
			(rec->normale)[2]=((rec->p)[2]-(sph->centre)[2])/rayon;
			double tmp_tab[3]={0.0,0.0,0.0};
			
			tmp_tab[0]=((rec->p)[0]-(sph->centre)[0])/(sph->rayon);
			tmp_tab[1]=((rec->p)[1]-(sph->centre)[1])/(sph->rayon);
			tmp_tab[2]=((rec->p)[2]-(sph->centre)[2])/(sph->rayon);
			
			get_sphere_uv(tmp_tab,&(rec->u),&(rec->v));
			(rec->mat_ptr)=(sph->mat_ptr);
			set_face_normal(r,rec->normale,rec);
			
			return 1;
		}
		
	}
	return 0;
}



void libere_sphere(sphere *sph){
	free(sph->centre);
	free(sph->mat_ptr->albedo);
	free(sph->mat_ptr);
}















void creer_sphere(hittable **L,double rayon,double *centre,materieau *mat){
	
	//creation de la sphere
	sphere *tmp_s=(sphere *) malloc(sizeof(sphere));
	tmp_s->rayon=rayon;
	tmp_s->centre=centre;
	tmp_s->mat_ptr=mat;
	
	add(L,tmp_s,SPHERE);
}

void creer_triangle(hittable **L,double *a,double *b,double *c,materieau *mat){
	triangle* tmp_t=(triangle *) malloc(sizeof(triangle));
	tmp_t->a=a;
	tmp_t->b=b;
	tmp_t->c=c;
	
	tmp_t->mat_ptr=mat;
	
	add(L,tmp_t,TRIANGLE);
}

