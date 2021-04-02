#include "materiaux.h"


double scatter_pdf(ray *r_in,hit_record *rec,double* albedo,ray *scattered, double *pdf){
	return 0;
}


int color_value_check(double u,double v,double *p){
	double sines=sin(10*p[0])*sin(10*p[1])*sin(10*p[2]);
	if (sines<0){
		return 1;
	}
	return 0;
}

int scatter_lambertian(ray *in,hit_record *rec,double *attenuation,ray *scattered,materieau *mat){
	double a=0;
	double b=0;
	double c=0;
	random_unit_vector(&a,&b,&c);

	(scattered->direction)[0]=(rec->normale)[0]+a;
	(scattered->direction)[1]=(rec->normale)[1]+b;
	(scattered->direction)[2]=(rec->normale)[2]+c;
	
	(scattered->point)[0]=(rec->p)[0];
	(scattered->point)[1]=(rec->p)[1];
	(scattered->point)[2]=(rec->p)[2];
	if (mat->type_mat==diffuse_light){
		attenuation[0]*=(mat->albedo)[0];
		attenuation[1]*=(mat->albedo)[1];
		attenuation[2]*=(mat->albedo)[2];
		return 0;
	}
	if (mat->type_mat==lambertian){
		attenuation[0]*=(mat->albedo)[0];
		attenuation[1]*=(mat->albedo)[1];
		attenuation[2]*=(mat->albedo)[2];
	}else{
		if (color_value_check(rec->u,rec->v,rec->p)){
			attenuation[0]*=(mat->text->odd)[0];
			attenuation[1]*=(mat->text->odd)[1];
			attenuation[2]*=(mat->text->odd)[2];
		}else{
			attenuation[0]*=(mat->text->even)[0];
			attenuation[1]*=(mat->text->even)[1];
			attenuation[2]*=(mat->text->even)[2];
		}
	}
		
	return 1;
}



void reflect(double *v,double *n,double *dest){
	
	double dot_=dot(v,n);
	dest[0]=v[0]-(2*dot_)*n[0];
	dest[1]=v[1]-(2*dot_)*n[1];
	dest[2]=v[2]-(2*dot_)*n[2];
}



void refract(double *v,double *n,double *dest,double etai){
	double cos_tetha=(-v[0]*n[0])-(v[1]*n[1])-(v[2]*n[2]);
	
	dest[0]=etai * ( v[0] + cos_tetha * ( n[0] ) );
	dest[1]=etai * ( v[1] + cos_tetha * ( n[1] ) );
	dest[2]=etai * ( v[2] + cos_tetha * ( n[2] ) );
	
	double len=length_squared(dest);
	
	dest[0]+=( - sqrt(fabs(1.0-len)) * n [0] ) ;
	dest[1]+=( - sqrt(fabs(1.0-len)) * n [1] ) ;
	dest[2]+=( - sqrt(fabs(1.0-len)) * n [2] ) ;
	
}

int scatter_metal(ray *in,hit_record *rec,double *attenuation,ray *scattered,materieau *mat){
	
	
	unit_vector(in->direction);
	
	reflect(in->direction,rec->normale,scattered->direction);
	
	double a;
	double b;
	double c;
	
	random_in_unit_sphere(&a,&b,&c);
	
	(scattered->direction)[0]+=(mat->fuzz)*a;
	(scattered->direction)[1]+=(mat->fuzz)*b;
	(scattered->direction)[2]+=(mat->fuzz)*c;
	
	(scattered->point)[0]=(rec->p)[0];
	(scattered->point)[1]=(rec->p)[1];
	(scattered->point)[2]=(rec->p)[2];
	
	attenuation[0]*=(mat->albedo)[0];
	attenuation[1]*=(mat->albedo)[1];
	attenuation[2]*=(mat->albedo)[2];
	
	return (dot(rec->normale,scattered->direction)>0);
	
}

double schlick(double cosine, double ref_idx){
	double r0=(1 - ref_idx)/ (1 + ref_idx);
	r0=r0*r0;
	return r0 + (1 - r0) * pow( 1 - cosine,5);
}

int scatter_dielectic(ray *in,hit_record *rec,double *attenuation,ray *scattered,materieau *mat){
	
	double eve= (rec->front_face)?  (1.0/ ( mat->fuzz ) ) : mat->fuzz ;
	unit_vector(in->direction);
	
	double dot_unit=-(in->direction)[0]*(rec->normale)[0]-(in->direction)[1]*(rec->normale)[1]-(in->direction)[2]*(rec->normale)[2];
	
	double cos_tetha = fmin(dot_unit,1.0);
	double sin_tetha = sqrt( 1.0 - cos_tetha * cos_tetha);
	
	(scattered->point)[0]=(rec->p)[0];
	(scattered->point)[1]=(rec->p)[1];
	(scattered->point)[2]=(rec->p)[2];
	
	if (eve * sin_tetha > 1.0 ){
		reflect(in->direction,rec->normale,scattered->direction);
		return 1;	
	}
	
	
	double reflect_prob=schlick(cos_tetha,eve);
	
	if (alea_()<reflect_prob){
		reflect(in->direction,rec->normale,scattered->direction);
		return 1;	
	}
	
	refract(in->direction,rec->normale,scattered->direction,eve);
	return 1;
}

