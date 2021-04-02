#include "rayons.h"

#define abs(x) (x<0?-x:x)
#define min(x,y) (x<y? x : y)
#define max(x,y) (x<y? y : x)


//renvoie si le rayon rencontre un onbjet ou non
int hittable_list(ray *r,hit_record *rec,hittable *L,hit_record *tmp_rec,hittable **dst){
	double tmin=0.01;
	double tmax=INFINITY;
	
	
	//res -> l objet touche quelque chose
	int res=0;
	double pt_plus_proche=tmax;
	int res_hit=0;
	
	sphere *tmp_sphere=NULL;
	triangle *tmp_triangle=NULL;
	
	if (*dst!=NULL){
		if ((*dst)->geo==SPHERE){
			tmp_sphere=(sphere *) ((*dst)->obj);
			hit_sphere(r,tmin,pt_plus_proche,tmp_sphere,tmp_rec);
			pt_plus_proche=tmp_rec->t;
		}else{
			tmp_triangle=(triangle *) ((*dst)->obj);
			res_hit=hit_triangle(r,pt_plus_proche,tmp_triangle,tmp_rec);
			pt_plus_proche=tmp_rec->t;
		}
	}
	
	//on parcourt la liste pour savoir si le rayon touche 
	while ((L)!=NULL) {
		
		res_hit=0;
		if (L->geo==SPHERE){
			tmp_sphere=(sphere *) (L->obj);
			res_hit=hit_sphere(r,tmin,pt_plus_proche,tmp_sphere,tmp_rec);
			
		}else{
			tmp_triangle=(triangle *) (L->obj);
			res_hit=hit_triangle(r,pt_plus_proche,tmp_triangle,tmp_rec);
		}
		
	
		
		if (res_hit){
			
			//if (tmp_rec->t<=rec->t){
			
			*dst=L;
			res=1;
			pt_plus_proche=tmp_rec->t;
			(rec->normale)[0]= (tmp_rec->normale)[0];
			(rec->normale)[1]= (tmp_rec->normale)[1];
			(rec->normale)[2]= (tmp_rec->normale)[2];
			
			(rec->p)[0]=(tmp_rec->p)[0];
			(rec->p)[1]=(tmp_rec->p)[1];
			(rec->p)[2]=(tmp_rec->p)[2];
			
			
			rec->t=tmp_rec->t;
			rec->front_face=tmp_rec->front_face;
			//}
		}
		L=(L)->suiv;
	}
	
	
	return res;
}




//https://medium.com/@bromanz/another-view-on-the-classic-ray-aabb-intersection-algorithm-for-bvh-traversal-41125138b525
int intersect_abb(noeud *n,ray* r,double *tmin,double *tmax){
	
	for (int a=0; a < 3 ; a++ ){
		double invD = 1.0f / (r->direction)[a];
		double t0 = ( (n->cig)[a]-(r->point)[a] )* invD;
		double t1 = ( (n->csd)[a]-(r->point)[a] )* invD;
		
		if (invD < 0.00f){
			double temp= t1;
			t1=t0;
			t0=temp;
		}
		
		*tmin= t0 > (*tmin) ? t0 : *tmin ;
		*tmax= t1 < (*tmax) ? t1 : *tmax ;
		
		if (*tmax <= *tmin){
			return 0;
			
		}
		
	}
	return 1;
}



int trouve_noeud(noeud *n,ray *rayon,hit_record *rec,hit_record *tmp_rec,hittable **dst){
	//cas feuille
	double tmin=0.01;	
	double tmax=INFINITY;
	
	if (intersect_abb(n,rayon, &tmin, &tmax)==0){
		return 0;
	}
	
	if (n->fils_gauche==NULL){
		hittable *tmp_liste=n->liste;
		return hittable_list(rayon,rec,(tmp_liste),tmp_rec,dst);
	}
	
	int a=trouve_noeud(n->fils_droit,rayon,rec,tmp_rec,dst);
	int b=trouve_noeud(n->fils_gauche,rayon,rec,tmp_rec,dst);
	
	return max(a,b);
		
}


void ray_color(double *c_background,ray *r,noeud *arbre,double *color,hit_record *rec,hit_record *tmp_rec){

	
	//variables temporaires pour les fonctions de coloration
	ray *scattered=(ray *) malloc(sizeof(ray));
	
	scattered->point=(double *) malloc(sizeof(double)*3);
	(scattered->point)[0]=0.0 ; (scattered->point)[1]=0.0 ; (scattered->point)[2]=0.0;
	
	scattered->direction=(double *) malloc(sizeof(double)*3);
	(scattered->direction)[0]=0.0 ; (scattered->direction)[1]=0.0 ; (scattered->direction)[2]=0.0;
	
	double *attenuation=(double *) malloc(sizeof(double)*3);
	attenuation[0]=1.0 ; attenuation[1]=1.0 ; attenuation[2]=1.0 ;
	
	double a=1.00;
	double b=1.00;
	double c=1.00;
	
	int res=0;
	//Samples
	sphere *tmp_sphere=NULL;
	triangle *tmp_triangle=NULL;
	
	for (int i=0;i<FILS;i++){
		hittable *dst=NULL;
		attenuation[0]=1.0;
		attenuation[1]=1.0;
		attenuation[2]=1.0;
		
		//if (hittable_list(r,tmin,tmax,rec,&tmp,tmp_rec)==1){
		
		if (trouve_noeud(arbre,r,rec,tmp_rec,&dst)==1){
			
			if ((dst)->geo==SPHERE){
				tmp_sphere=(sphere *) (dst->obj);
				res=(tmp_sphere->mat_ptr->scatter)(r,rec,attenuation,scattered,tmp_sphere->mat_ptr);
				
				if (res==0){
					
						free(scattered->point);
						free(scattered->direction);
						free(scattered);
						free(attenuation);
						
						if (tmp_sphere->mat_ptr->type_mat==diffuse_light){
							color[0]=a*attenuation[0];
							color[1]=b*attenuation[1];
							color[2]=c*attenuation[2];
						}else{
							color[0]=0;
							color[1]=0;
							color[2]=0;
						}
						
						return ;
				}

			}else{
				tmp_triangle=(triangle *)(dst->obj);
				res=(tmp_triangle->mat_ptr->scatter)(r,rec,attenuation,scattered,tmp_triangle->mat_ptr);
				
				if (res==0){
					
						free(scattered->point);
						free(scattered->direction);
						free(scattered);
						free(attenuation);
						
						if (tmp_triangle->mat_ptr->type_mat==diffuse_light){
							color[0]=a*attenuation[0];
							color[1]=b*attenuation[1];
							color[2]=c*attenuation[2];
						}else{
							color[0]=0;
							color[1]=0;
							color[2]=0;
						}
						
						return ;
				}
			}
			
			
				
			(r->point)[0]=(scattered->point)[0];
			(r->point)[1]=(scattered->point)[1];
			(r->point)[2]=(scattered->point)[2];
			
			(r->direction)[0]=(scattered->direction)[0];
			(r->direction)[1]=(scattered->direction)[1];
			(r->direction)[2]=(scattered->direction)[2];
			
			
			
			a*= attenuation[0];
			b*= attenuation[1];
			c*= attenuation[2];
			

		}else{	
		
		/*	
		unit_vector(r->direction);
		
		
		double t= 0.5 * (((r->direction)[1])+1.0);
		
		color[0]+= ( 0.5*(1.0-t+t*0.5) ) * attenuation[0];
		color[1]+= ( 0.5*(1.0-t+t*0.7) ) * attenuation[1];
		color[2]+= ( 0.5*(1.0)		   ) * attenuation[2];
		*/
		color[0]=a*c_background[0];
		color[1]=b*c_background[1];
		color[2]=c*c_background[2];
		
		free(scattered->point);
		free(scattered->direction);
		free(scattered);
		free(attenuation);
		
		return ;
		}
	}
	
	color[0]=0;
	color[1]=0;
	color[2]=0;
	
	free(scattered->point);
	free(scattered->direction);
	free(scattered);
	free(attenuation);

	
	return;
	
}



void ray_color_normal(double *c_background,ray *r,noeud *arbre,double *color,hit_record *rec,hit_record *tmp_rec){
	
	
	//variables temporaires pour les fonctions de coloration
	ray *scattered=(ray *) malloc(sizeof(ray));
	
	scattered->point=(double *) malloc(sizeof(double)*3);
	(scattered->point)[0]=0.0 ; (scattered->point)[1]=0.0 ; (scattered->point)[2]=0.0;
	
	scattered->direction=(double *) malloc(sizeof(double)*3);
	(scattered->direction)[0]=0.0 ; (scattered->direction)[1]=0.0 ; (scattered->direction)[2]=0.0;
	
	double *attenuation=(double *) malloc(sizeof(double)*3);
	attenuation[0]=1.0 ; attenuation[1]=1.0 ; attenuation[2]=1.0 ;
	
	
	
	int res=0;
	//Samples
	sphere *tmp_sphere=NULL;
	triangle *tmp_triangle=NULL;
	
	
	hittable *dst=NULL;
		
	if (trouve_noeud(arbre,r,rec,tmp_rec,&dst)==1){
			
		if ((dst)->geo==SPHERE){
			tmp_sphere=(sphere *) (dst->obj);
			res=(tmp_sphere->mat_ptr->scatter)(r,rec,attenuation,scattered,tmp_sphere->mat_ptr);
		
	    }else{
			tmp_triangle=(triangle *)(dst->obj);
			res=(tmp_triangle->mat_ptr->scatter)(r,rec,attenuation,scattered,tmp_triangle->mat_ptr);
	    }	
			
		double max_=max((scattered->direction)[0],(scattered->direction)[1]);
		int tmp_color=( (scattered->direction)[0] / max_) / ( (scattered->direction)[1] / max_ );
			
		color[0]=tmp_color;
		color[1]=tmp_color;
		color[2]=tmp_color;
			
		free(scattered->point);
		free(scattered->direction);
		free(scattered);
		free(attenuation);
		
		return;
			
		}else{	
			
			
			color[0]=c_background[0];
			color[1]=c_background[1];
			color[2]=c_background[2];
			
			free(scattered->point);
			free(scattered->direction);
			free(scattered);
			free(attenuation);
			
			return ;
		}
	
}






void get_ray(double t,double s, ray *r , camera *c){
	
	double rd[3]={1.,1.,0.};
	random_in_unit_disk(rd);
	
	rd[0]*=(c->lens_radius);
	rd[1]*=(c->lens_radius);
	
	double offset[3]={0.,0.,0.};
	
	offset[0]=(c->u)[0] * rd [0] + (c->v)[0] * rd[1];
	offset[1]=(c->u)[1] * rd [0] + (c->v)[1] * rd[1];
	offset[2]=(c->u)[2] * rd [0] + (c->v)[2] * rd[1];
	
	(r->point)[0]=(c->origine)[0]+offset[0];
	(r->point)[1]=(c->origine)[1]+offset[1];
	(r->point)[2]=(c->origine)[2]+offset[2];
	
	(r->direction)[0]=(c->llc)[0]+ s*(c->horizontal)[0] + t * (c->vertical)[0] - (c->origine)[0]- offset[0];
	(r->direction)[1]=(c->llc)[1]+ s*(c->horizontal)[1] + t * (c->vertical)[1] - (c->origine)[1]- offset[1];
	(r->direction)[2]=(c->llc)[2]+ s*(c->horizontal)[2] + t * (c->vertical)[2] - (c->origine)[2]- offset[2];
	
}
