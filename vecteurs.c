#include "vecteurs.h"
#include "math.h"


#define pi 3.1415926535897932385

double length_squared(double *v){
	return v[0] * v[0]+v[1] * v[1]+v[2] * v[2];
}

void unit_vector(double *v){
	double distance=sqrt(length_squared(v));
	v[0]/=distance;
	v[1]/=distance;
	v[2]/=distance;
}

double dot(double *u,double *v){
	return u[0]*v[0]+u[1]*v[1]+u[2]*v[2];
}



void at(ray *r,double t,double *dest){
	dest[0]=(r->point)[0]+t*((r->direction)[0]);
	dest[1]=(r->point)[1]+t*((r->direction)[1]);
	dest[2]=(r->point)[2]+t*((r->direction)[2]);
}

void cross(double *u,double *v,double *dest){
	dest[0]=u[1]*v[2]-u[2]*v[1];
	dest[1]=u[2]*v[0]-u[0]*v[2];
	dest[2]=u[0]*v[1]-u[1]*v[0];
}

void produit(double *u,double a){
	u[0]*=a;
	u[1]*=a;
	u[2]*=a;
}

void copy(double *u,double *dest){
	dest[0]=u[0];
	dest[1]=u[1];
	dest[2]=u[2];
}

double alea_(void){
	return (rand()/(RAND_MAX*1.0));
}

double degrees_to_radians(double degrees){

	return degrees * pi / 180;
}


double alea(double a,double b){
	return a+(b-a)*(rand()/(RAND_MAX*1.0));
}

void alea_vec(double *vect){
	vect[0]=alea_();
	vect[1]=alea_();
	vect[2]=alea_();
}

void alea_vect_c(double *vect,double a, double b){
	vect[0]=alea(a,b);
	vect[1]=alea(a,b);
	vect[2]=alea(a,b);
}

double min3(double a,double b,double c){
	double x=(a>b)?b:a;
	double y=(a>c)?c:a;
	return (x>y)?y:x;
}
double max3(double a,double b,double c){
	double x=(a<b)?b:a;
	double y=(a<c)?c:a;
	return (x<y)?y:x;
}

void random_in_unit_sphere(double *x,double *y,double *z){
	while (1) {
		double tmpx=alea(-1, 1);
		double tmpy=alea(-1, 1);
		double tmpz=alea(-1, 1);
		if ((tmpx*tmpx+tmpy*tmpy+tmpz*tmpz)<1){
			*x=tmpx;
			*y=tmpy;
			*z=tmpz;
			return ;
		}
	}
}

void random_in_unit_disk(double *dest){
	while(1){
		dest[0]=alea(-1.0,1.0);
		dest[1]=alea(-1.0,1.0);
		dest[2]=0;
		
		if (length_squared(dest)>=1) continue;
		return;
	}
}

void random_in_hemisphere(double *x,double *y,double *z,double *v){
	random_in_unit_sphere(x,y,z);
	if (((*x)*v[0]+(*y)*v[1]+(*z)*v[2])>0.0) return ;
	*x=-(*x);
	*y=-(*y);
	*z=-(*z);
	
	return;
}

void random_unit_vector(double *a,double *b,double *c){
	double a_tmp=alea(0,2*pi);
	double z=alea(-1,1);
	double r=sqrt(1-(z*z));
	(*a)=r*cos(a_tmp);
	(*b)=r*sin(a_tmp);
	(*c)=z;
}

//cette fonction permet d assigner un 
//vecteur normal a un rayon
void set_face_normal(ray* r,double *outward_normal,hit_record *rec){
	//permet de savoir si le rayon pointe vers l'interieur ou l exterieur de l objet
	(rec->front_face)=dot(r->direction,outward_normal) < 0;
	
	//correction pour qu'il pointe vers l'exterieur
	if (rec->front_face==0){
		outward_normal[0]=-(outward_normal[0]);
		outward_normal[1]=-(outward_normal[1]);
		outward_normal[2]=-(outward_normal[2]);
	}
	rec->normale=outward_normal;
}

void afficher_triangle(triangle *tri){
	printf("%lf %lf %lf\n",(tri->a)[0],(tri->a)[1],(tri->a)[2]);
	printf("%lf %lf %lf\n",(tri->b)[0],(tri->b)[1],(tri->b)[2]);
	printf("%lf %lf %lf\n",(tri->c)[0],(tri->c)[1],(tri->c)[2]);
	printf("----\n");

}

void afficher(hittable *tmp){
	while (tmp!=NULL) {
		//printf("%lf %lf %lf\n",(tmp->obj->centre)[0],(tmp->obj->centre)[1],(tmp->obj->centre)[2]);
		if (tmp->geo==TRIANGLE){
			triangle *tmp_triangle=(triangle *)(tmp->obj);
			afficher_triangle(tmp_triangle);
		}else{
			sphere *tmp_sphere=(sphere *)(tmp->obj);
			printf("%lf %lf %lf\n",(tmp_sphere->centre)[0],(tmp_sphere->centre)[1],(tmp_sphere->centre)[2]);
		}
		tmp=tmp->suiv;
	}
	printf("\n");
}