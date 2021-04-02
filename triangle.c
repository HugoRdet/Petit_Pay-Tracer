#include "triangle.h"


int hit_triangle(ray *rayon,double tmax,triangle *t,hit_record *rec){
	
	double edge1[3];
	double edge2[3];
	double h[3];
	double s[3];
	double q[3];
	
	double a,f,u,v;
	
	edge1[0]=(t->b)[0]-(t->a)[0];
	edge1[1]=(t->b)[1]-(t->a)[1];
	edge1[2]=(t->b)[2]-(t->a)[2];
	
	edge2[0]=(t->c)[0]-(t->a)[0];
	edge2[1]=(t->c)[1]-(t->a)[1];
	edge2[2]=(t->c)[2]-(t->a)[2];
	

	cross(edge2,rayon->direction,h);
	a=dot(edge1, h);
	
	if ((a > - EPSILON)&&(a<EPSILON)){
		return 0;
	}
	
	f= ((double) 1.0)/a;
	s[0]=(rayon->point)[0]-(t->a)[0];
	s[1]=(rayon->point)[1]-(t->a)[1];
	s[2]=(rayon->point)[2]-(t->a)[2];
	
	u=f  * dot(s,h);
	
	if ((u<0.0)||(u>1.0)){
		
		return 0;
	}
	
	cross(edge1,s,q);
	v=f*dot(rayon->direction,q);
	if ((v<0.0)||(u+v>1.0)){
		return 0;
	}
	
	double t_len=f* dot(edge2,q);
	
	if ((t_len > EPSILON )&&(t_len<tmax)){
		
		at(rayon,t_len,rec->p);
		cross(edge1,edge2,rec->normale);
		double len=length_squared(rec->normale);
		
		(rec->normale)[0]=(rec->normale)[0]/sqrt(len);
		(rec->normale)[1]=(rec->normale)[1]/sqrt(len);
		(rec->normale)[2]=(rec->normale)[2]/sqrt(len);
		set_face_normal(rayon,rec->normale,rec);
		rec->front_face=1;
		rec->t=t_len;
		rec->mat_ptr=t->mat_ptr;
		
		return 1;
	}
	
	return 0;
	
	
}

void libere_triangle(triangle *tri){
	free(tri->mat_ptr->albedo);
	free(tri->mat_ptr);
	free(tri->a);
	free(tri->b);
	free(tri->c);
}