#include "utilitaires.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define v_abs(x) (x>0?x:-x)

void scene_alea(hittable **world){
	for (int i=-11;i<11;i++){
			for (int j=-11;j<11;j++){
				
				double choose_mat=alea_();
				
				double a=i+ 0.9 * alea_();
				double b=0.2;
				double c=j+0.9 * alea_() ;
				
				double res=sqrt((a-0.4)*(a-0.4)+(b-0.2)*(b-0.2)+c*c);
				
				if (res> 0.9) {
					
					sphere *tmp_sphere=(sphere *) malloc(sizeof(sphere));
					materieau *tmp_mat=(materieau *) malloc(sizeof(materieau));
					double *centre=(double *)malloc(sizeof(double)*3);
					double *tmp_albedo=(double *)malloc(sizeof(double)*3);
					tmp_mat->albedo=tmp_albedo;
					tmp_sphere->centre=centre;
					centre[0]=a;
					centre[1]=b;
					centre[2]=c;
					if (choose_mat<0.2){
						tmp_albedo[0]=1.0;
						tmp_albedo[1]=1.0;
						tmp_albedo[2]=1.0;
						tmp_mat->type_mat=diffuse_light;
						tmp_mat->scatter=scatter_lambertian;
					}else{
						if (choose_mat<0.8){
					
						
							tmp_albedo[0]=alea_();
							tmp_albedo[1]=alea_();
							tmp_albedo[2]=alea_();
							
							tmp_mat->type_mat=lambertian;
							tmp_mat->scatter=scatter_lambertian;
						}else {
							if (choose_mat<0.95){
								tmp_albedo[0]=alea(0.5,1);
								tmp_albedo[1]=alea(0.5,1);
								tmp_albedo[2]=alea(0.5,1);
							
								tmp_mat->type_mat=metal;			
								tmp_mat->fuzz=alea(0,0.5);		
								tmp_mat->scatter=scatter_metal;		
							}else{
								tmp_albedo[0]=0.0;
								tmp_albedo[1]=0.0;
								tmp_albedo[2]=0.0;
								tmp_mat->type_mat=dielectic;
								tmp_mat->scatter=scatter_dielectic;
								tmp_mat->fuzz=1.5;	
							}
						}
					}
					
					
					tmp_sphere->rayon=0.2;
					tmp_sphere->mat_ptr=tmp_mat;
					add(world,tmp_sphere,SPHERE);
					}
				}
			}

}


double clamp(double x,double min,double max){
	if (x<min) return min;
	if (x>max) return max;
	
	return x;
}

void write_color(FILE *fichier,double *res_color){
	
	
		
			
		double r=res_color[0];
		double g=res_color[1];
		double b=res_color[2];
		
		double scale= 1.0 / SAMPLES;
		r=sqrt(r* scale);
		g=sqrt(g* scale);
		b=sqrt(b* scale);
		
		fprintf(fichier,"%d\t%d\t%d\t",(int) (clamp(r,0.00,0.999)*256),(int)(clamp(g,0.00,0.999)*256),(int)(clamp(b,0.00,0.999)*256));
		
	
}


void calcul_scene(int hauteur_image,int largeur_image,FILE *fichier_dst,noeud *arbre,camera *cam){
	
	
	//rayon
	ray *tmp=(ray *) malloc(sizeof(ray));
	tmp->direction=(double *) malloc(sizeof(double)*3);
	tmp->point=(double *) malloc(sizeof(double)*3);
		
	double *color=(double *)malloc(sizeof(double)*3);
	double *res_color=(double *)malloc(sizeof(double)*3);
		
	//hit record
	hit_record *rec=(hit_record *) malloc(sizeof(hit_record));
	rec->p=(double *) malloc(sizeof(double)*3);
	rec->normale=(double *) malloc(sizeof(double)*3);
		
	hit_record *tmp_rec=NULL;
	tmp_rec=(hit_record *) malloc(sizeof(hit_record));
	tmp_rec->t=INFINITY;
	tmp_rec->p=(double *) malloc(sizeof(double)*3);
	tmp_rec->normale=(double *) malloc(sizeof(double)*3);
	
	double *color_background=(double *) malloc(sizeof(double)*3);
	//bleu
	color_background[0]=0.70;	color_background[1]=0.80;	color_background[2]=1.00;
	
	//color_background[0]=0.00;	color_background[1]=0.00;	color_background[2]=0.00;
	//color_background[0]=0.90;	color_background[1]=0.90;	color_background[2]=0.90;
	//color_background[0]=255.0/255.00;	color_background[1]=159.00/255.00;	color_background[2]=159.00/255.00;
	
	//calcule de tous les vecteurs
	int cpt=0;
	for (int i=hauteur_image-1;i>=0;i--){
			
			for (int j=0;j<largeur_image;j++){
			
			res_color[0]=0;
			res_color[1]=0;
			res_color[2]=0;
			
			for (int s=0; s<SAMPLES;s++){ 
					
				color[0]=0.0;
				color[1]=0.0;
				color[2]=0.0;
					
				//calcul des coords du pixel de l'image dans le plan
				//ici on normalise le vecteur , utile?
				double u=((double)i+alea_())/(hauteur_image-1);
				double v=((double)j+alea_())/(largeur_image-1);
		
				get_ray(u,v,tmp,cam);
					
				rec->t=INFINITY;
					
				//calcul de la couleur
				ray_color(color_background,tmp,arbre,color,rec,tmp_rec);
				
				res_color[0]+=color[0];
				res_color[1]+=color[1];
				res_color[2]+=color[2];
				
				
				}
				//ecriture de la couleur dans le fichier .ppm
				write_color(fichier_dst,res_color);
				//printf(" coord calc %d %d\n",i,j);
				cpt++;
				
			}
			printf("%.2f\n",(cpt/(hauteur_image*largeur_image*1.0))*100);
			
			
		}

		
		
		free(color);
		free(res_color);
		
		
		
		
		free(rec->p);
		free(rec->normale);
		free(rec);
		
		free(tmp_rec->p);
		free(tmp_rec->normale);
		free(tmp_rec);
		
		free(tmp->direction);
		free(tmp->point);
		free(tmp);
		
}


void cree_rectangle_face(double *a,double x,double y,double z,hittable **liste,materieau *mat_ptr){
	triangle *tmp_triangle_a=(triangle *) malloc(sizeof(triangle));
	triangle *tmp_triangle_b=(triangle *) malloc(sizeof(triangle));
	
	tmp_triangle_a->mat_ptr=mat_ptr;
	tmp_triangle_b->mat_ptr=mat_ptr;
	
	tmp_triangle_a->a=(double *) malloc(sizeof(double)*3);
	tmp_triangle_a->b=(double *) malloc(sizeof(double)*3);
	tmp_triangle_a->c=(double *) malloc(sizeof(double)*3);
	
	tmp_triangle_b->a=(double *) malloc(sizeof(double)*3);
	tmp_triangle_b->b=(double *) malloc(sizeof(double)*3);
	tmp_triangle_b->c=(double *) malloc(sizeof(double)*3);
	
	(tmp_triangle_a->a)[0]=a[0];
	(tmp_triangle_a->a)[1]=a[1];
	(tmp_triangle_a->a)[2]=a[2]+z;
	
	(tmp_triangle_a->b)[0]=a[0]+x;
	(tmp_triangle_a->b)[1]=a[1];
	(tmp_triangle_a->b)[2]=a[2]+z;
	
	(tmp_triangle_a->c)[0]=a[0];
	(tmp_triangle_a->c)[1]=a[1]+y;
	(tmp_triangle_a->c)[2]=a[2]+z;
	
	(tmp_triangle_b->a)[0]=a[0]+x;
	(tmp_triangle_b->a)[1]=a[1]+y;
	(tmp_triangle_b->a)[2]=a[2]+z;
	
	(tmp_triangle_b->b)[0]=a[0]+x;
	(tmp_triangle_b->b)[1]=a[1];
	(tmp_triangle_b->b)[2]=a[2]+z;
		
	(tmp_triangle_b->c)[0]=a[0];
	(tmp_triangle_b->c)[1]=a[1]+y;
	(tmp_triangle_b->c)[2]=a[2]+z;

	add(liste,tmp_triangle_a,TRIANGLE);
	add(liste,tmp_triangle_b,TRIANGLE);
}

void cree_rectangle_sol(double *a,double x,double y,double z,hittable **liste,materieau *mat_ptr){
	triangle *tmp_triangle_a=(triangle *) malloc(sizeof(triangle));
	triangle *tmp_triangle_b=(triangle *) malloc(sizeof(triangle));
	
	tmp_triangle_a->mat_ptr=mat_ptr;
	tmp_triangle_b->mat_ptr=mat_ptr;
	
	tmp_triangle_a->a=(double *) malloc(sizeof(double)*3);
	tmp_triangle_a->b=(double *) malloc(sizeof(double)*3);
	tmp_triangle_a->c=(double *) malloc(sizeof(double)*3);
		
	tmp_triangle_b->a=(double *) malloc(sizeof(double)*3);
	tmp_triangle_b->b=(double *) malloc(sizeof(double)*3);
	tmp_triangle_b->c=(double *) malloc(sizeof(double)*3);
	
	(tmp_triangle_a->a)[0]=a[0];
	(tmp_triangle_a->a)[1]=a[1]+y;
	(tmp_triangle_a->a)[2]=a[2];
	
	(tmp_triangle_a->b)[0]=a[0]+x;
	(tmp_triangle_a->b)[1]=a[1]+y;
	(tmp_triangle_a->b)[2]=a[2];
	
	(tmp_triangle_a->c)[0]=a[0];
	(tmp_triangle_a->c)[1]=a[1]+y;
	(tmp_triangle_a->c)[2]=a[2]+z;
	
		
	(tmp_triangle_b->a)[0]=a[0]+x;
	(tmp_triangle_b->a)[1]=a[1]+y;
	(tmp_triangle_b->a)[2]=a[2];
	
	(tmp_triangle_b->b)[0]=a[0];
	(tmp_triangle_b->b)[1]=a[1]+y;
	(tmp_triangle_b->b)[2]=a[2]+z;
		
	(tmp_triangle_b->c)[0]=a[0]+x;
	(tmp_triangle_b->c)[1]=a[1]+y;
	(tmp_triangle_b->c)[2]=a[2]+z;
	
	add(liste,tmp_triangle_a,TRIANGLE);
	add(liste,tmp_triangle_b,TRIANGLE);

}

void cree_rectangle_cote(double *a,double x,double y,double z,hittable **liste,materieau *mat_ptr){
	triangle *tmp_triangle_a=(triangle *) malloc(sizeof(triangle));
	triangle *tmp_triangle_b=(triangle *) malloc(sizeof(triangle));
	
	tmp_triangle_a->mat_ptr=mat_ptr;	
	tmp_triangle_b->mat_ptr=mat_ptr;
	
	tmp_triangle_a->a=(double *) malloc(sizeof(double)*3);
	tmp_triangle_a->b=(double *) malloc(sizeof(double)*3);
	tmp_triangle_a->c=(double *) malloc(sizeof(double)*3);
		
	tmp_triangle_b->a=(double *) malloc(sizeof(double)*3);
	tmp_triangle_b->b=(double *) malloc(sizeof(double)*3);
	tmp_triangle_b->c=(double *) malloc(sizeof(double)*3);
	
	(tmp_triangle_a->a)[0]=a[0]+x;
	(tmp_triangle_a->a)[1]=a[1];
	(tmp_triangle_a->a)[2]=a[2];
	
	(tmp_triangle_a->b)[0]=a[0]+x;
	(tmp_triangle_a->b)[1]=a[1]+y;
	(tmp_triangle_a->b)[2]=a[2];
	
	(tmp_triangle_a->c)[0]=a[0]+x;
	(tmp_triangle_a->c)[1]=a[1];
	(tmp_triangle_a->c)[2]=a[2]+z;
		
	(tmp_triangle_b->a)[0]=a[0]+x;
	(tmp_triangle_b->a)[1]=a[1];
	(tmp_triangle_b->a)[2]=a[2]+z;
	
	(tmp_triangle_b->b)[0]=a[0]+x;
	(tmp_triangle_b->b)[1]=a[1]+y;
	(tmp_triangle_b->b)[2]=a[2];
		
	(tmp_triangle_b->c)[0]=a[0]+x;
	(tmp_triangle_b->c)[1]=a[1]+y;
	(tmp_triangle_b->c)[2]=a[2]+z;
	
	add(liste,tmp_triangle_a,TRIANGLE);
	add(liste,tmp_triangle_b,TRIANGLE);
}

void creer_pave(double *a,double x,double y,double z,hittable **liste,materieau *mat_ptr){
	cree_rectangle_face(a,x,y,0,liste,mat_ptr);
	
	cree_rectangle_face(a,x,y,z,liste,mat_ptr);
	cree_rectangle_cote(a,0,y,z,liste,mat_ptr);
	cree_rectangle_cote(a,x,y,z,liste,mat_ptr);
	cree_rectangle_sol(a,x,0,z,liste,mat_ptr);
	cree_rectangle_sol(a,x,y,z,liste,mat_ptr);
	
}


void cornell_box(hittable **liste){
	//creation de la box;
	materieau *mat_r=(materieau *)malloc(sizeof(materieau));
	materieau *mat_v=(materieau *)malloc(sizeof(materieau));
	materieau *mat_b=(materieau *)malloc(sizeof(materieau));
	materieau *mat_l=(materieau *)malloc(sizeof(materieau));
			
	mat_r->type_mat=lambertian;
	mat_v->type_mat=lambertian;
	mat_b->type_mat=lambertian;
	mat_l->type_mat=diffuse_light;
	
	mat_r->albedo=(double *) malloc(sizeof(double)*3);
	mat_v->albedo=(double *) malloc(sizeof(double)*3);
	mat_b->albedo=(double *) malloc(sizeof(double)*3);
	mat_l->albedo=(double *) malloc(sizeof(double)*3);
	
	(mat_r->albedo)[0]=0.65;
	(mat_r->albedo)[1]=0.05;
	(mat_r->albedo)[2]=0.05;
	
	(mat_b->albedo)[0]=0.73;
	(mat_b->albedo)[1]=0.73;
	(mat_b->albedo)[2]=0.73;
	
	(mat_v->albedo)[0]=0.12;
	(mat_v->albedo)[1]=0.45;
	(mat_v->albedo)[2]=0.15;
	
	(mat_l->albedo)[0]=15.000;
	(mat_l->albedo)[1]=15.000;
	(mat_l->albedo)[2]=15.000;
	
	mat_r->text=NULL;
	mat_v->text=NULL;
	mat_b->text=NULL;
	mat_l->text=NULL;
	
	mat_r->fuzz=0.0;
	mat_v->fuzz=0.0;
	mat_b->fuzz=0.0;
	mat_l->fuzz=0.0;
	
	mat_r->scatter=scatter_lambertian;
	mat_v->scatter=scatter_lambertian;
	mat_b->scatter=scatter_lambertian;
	mat_l->scatter=scatter_lambertian;
	
	double a[3]={0.00,0.00,0.00};
	
	cree_rectangle_sol(a,555.00,555.00,555.00,liste,mat_b);
	cree_rectangle_sol(a,555.00,0.00,555.00,liste,mat_b);
	cree_rectangle_face(a,555.00,555.00,555.00,liste,mat_b);
	cree_rectangle_cote(a,0.00,555.00,555.00,liste,mat_r);
	cree_rectangle_cote(a,555.00,555.00,555.00,liste,mat_v);
	a[0]=213.00;
	a[2]=332.00;
	cree_rectangle_sol(a,130.0,554.0,119.0,liste,mat_l);
	
	

	

}





void sol_cube(hittable **liste,materieau *mat_ptr){
	int i,j;
	double a[3]={0.00,-1.50,0.00};
	for (i=-10;i<10;i++){
		for (j=-10;j<10;j++){
			double y=alea(0.0,1.5);
			creer_pave(a,1,y,1,liste,mat_ptr);
			a[0]=i;
			a[2]=j;
		}
	}
}

void rotation_y(double angle,hittable *liste){

	
	while(liste!=NULL){
		if (liste->geo==TRIANGLE){
			triangle *tmp_triangle=(triangle *) (liste->obj);
			double *coord=tmp_triangle->a;
			
			double x=coord[0];
			double z=coord[2];
			
			coord[0]=x * cos(angle)  + sin(angle) * z;
			coord[2]=x * -sin(angle) + cos(angle) * z;
			
			coord=tmp_triangle->b;
			
			x=coord[0];
			z=coord[2];
			
			coord[0]=x * cos(angle)  + sin(angle) * z;
			coord[2]=x * -sin(angle) + cos(angle) * z;
			
			coord=tmp_triangle->c;
			
			x=coord[0];
			z=coord[2];
			
			coord[0]=x * cos(angle)  + sin(angle) * z;
			coord[2]=x * -sin(angle) + cos(angle) * z;
			
		}
		liste=liste->suiv;
	}
}

void rotation_x(double angle,hittable *liste){	
	while(liste!=NULL){
		if (liste->geo==TRIANGLE){
			triangle *tmp_triangle=(triangle *) (liste->obj);
			double *coord=tmp_triangle->a;
			
			double y=coord[1];
			double z=coord[2];
			
			coord[1]=cos(angle) * y-sin(angle)*z;
			coord[2]=sin(angle) * y+cos(angle)*z;
			
			coord=tmp_triangle->b;
			
			y=coord[1];
			z=coord[2];
			
			coord[1]=cos(angle) * y-sin(angle)*z;
			coord[2]=sin(angle) * y+cos(angle)*z;
			
			coord=tmp_triangle->c;
			
			y=coord[1];
			z=coord[2];
			
			coord[1]=cos(angle) * y-sin(angle)*z;
			coord[2]=sin(angle) * y+cos(angle)*z;
		}
		liste=liste->suiv;
	}
}

void rotation_z(double angle,hittable *liste){
		while(liste!=NULL){
		if (liste->geo==TRIANGLE){
			triangle *tmp_triangle=(triangle *) (liste->obj);
			double *coord=tmp_triangle->a;
			
			double x=coord[0];
			double y=coord[1];
			
			coord[0]=x * cos(angle) - sin(angle) * y ;
			coord[1]=x * sin(angle) + cos(angle) * y ;
						
			coord=tmp_triangle->b;
			
			x=coord[0];
			y=coord[1];
			
			coord[0]=x * cos(angle) - sin(angle) * y ;
			coord[1]=x * sin(angle) + cos(angle) * y ;
			
			coord=tmp_triangle->c;
			
			x=coord[0];
			y=coord[1];
			
			coord[0]=x * cos(angle) - sin(angle) * y ;
			coord[1]=x * sin(angle) + cos(angle) * y ;
			
		}
		liste=liste->suiv;
	}
}

void translation(double x,double y,double z,hittable *liste){
		while(liste!=NULL){
		if (liste->geo==TRIANGLE){
			triangle *tmp_triangle=(triangle *) (liste->obj);
			double *coord=tmp_triangle->a;
						
			coord[0]+=x;
			coord[1]+=y;
			coord[2]+=z;
						
			coord=tmp_triangle->b;
			
			coord[0]+=x;
			coord[1]+=y;
			coord[2]+=z;
			
			coord=tmp_triangle->c;
			
			coord[0]+=x;
			coord[1]+=y;
			coord[2]+=z;
			
		}
		liste=liste->suiv;
	}
}