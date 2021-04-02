#include "fichier.h"
#include <stdio.h>
#include <stdlib.h>

void attribue_id(hittable *liste){
	int id=0;
	
	sphere *tmp_sphere=NULL;
	triangle *tmp_triangle=NULL;
	
	while (liste!=NULL) {
		if (liste->geo==SPHERE){
			tmp_sphere=(sphere *) (liste->obj);
			tmp_sphere->id=id;
		}
		
		if (liste->geo==TRIANGLE){
			tmp_triangle=(triangle *) (liste->obj);
			tmp_triangle->id=id;
		}
		id++;
		liste=liste->suiv;
	}
}

void charge_fichier_spheres(char *nom_f,hittable **L){
	FILE* fichier=fopen(nom_f,"r");
	int cpt=0;
	char c=' ';
	double x=0.,y=0.,z=0.,r=0.,fuzz=0.,a1=0.,a2=0.,a3=0.,a4=0.,a5=0.,a6=0.;
	double xa=0.,ya=0.,za=0.;
	double xb=0.,yb=0.,zb=0.;
	
		while (c!=EOF) {
			
			if ((c=fgetc(fichier))=='s'){
				
				c=fgetc(fichier);
				
				materieau *new_mat=(materieau *) malloc(sizeof(materieau));
				sphere *new_sph=(sphere *) malloc(sizeof(sphere));
				new_sph->mat_ptr=new_mat;
				add(L,new_sph,SPHERE);
				
				if (c!='c'){
					fscanf(fichier,"%lf %lf %lf %lf %lf %lf %lf %lf\n",&x,&y,&z,&r,&fuzz,&a1,&a2,&a3);
					if (c=='i'){
						new_mat->type_mat=diffuse_light;
						new_mat->scatter=scatter_lambertian;
					}
					//lambertian
					if (c=='l'){
						new_mat->type_mat=lambertian;
						new_mat->scatter=scatter_lambertian;
					}
					//dialectic
					if (c=='d'){
						new_mat->type_mat=dielectic;
						new_mat->scatter=scatter_dielectic;
					}
					//metal
					
					if (c=='m'){
						new_mat->type_mat=metal;
						new_mat->scatter=scatter_metal;
					}
					new_mat->albedo=(double *) malloc(sizeof(double)*3);
					new_mat->fuzz=fuzz;
					(new_mat->albedo)[0]=a1;
					(new_mat->albedo)[1]=a2;
					(new_mat->albedo)[2]=a3;
					new_mat->text=NULL;	
				}else{
					//checkered
					if (c=='c'){
							
							fscanf(fichier,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",&x,&y,&z,&r,&fuzz,&a1,&a2,&a3,&a4,&a5,&a6);
							new_mat->type_mat=checker_texture;
							new_mat->scatter=scatter_lambertian;
							new_mat->text=(texture *)malloc(sizeof(texture));
							new_mat->text->odd=(double *) malloc(sizeof(double)*3);
							new_mat->text->even=(double *) malloc(sizeof(double)*3);
							(new_mat->text->odd)[0]=a1;
							(new_mat->text->odd)[1]=a2;
							(new_mat->text->odd)[2]=a3;
							
							(new_mat->text->even)[0]=a4;
							(new_mat->text->even)[1]=a5;
							(new_mat->text->even)[2]=a6;
					}
				}
											
				new_sph->rayon=r;
				new_sph->centre=(double *) malloc(sizeof(double)*3);
				
				(new_sph->centre)[0]=x;
				(new_sph->centre)[1]=y;
				(new_sph->centre)[2]=z;
				cpt++;
								
		}
		
		if (c=='t'){
			
			c=fgetc(fichier);
			materieau *new_mat=(materieau *) malloc(sizeof(materieau));
			triangle *new_tri=(triangle *) malloc(sizeof(triangle));
			
			new_tri->a=(double *) malloc(sizeof(double)*3);
			new_tri->b=(double *) malloc(sizeof(double)*3);
			new_tri->c=(double *) malloc(sizeof(double)*3);
			
			add(L,new_tri,TRIANGLE);
			
			
			if (c=='i'){
				new_mat->type_mat=diffuse_light;
				new_mat->scatter=scatter_lambertian;
			}
			//lambertian
			if (c=='l'){
				new_mat->type_mat=lambertian;
				new_mat->scatter=scatter_lambertian;
			}
			//dialectic
			if (c=='d'){
				new_mat->type_mat=dielectic;
				new_mat->scatter=scatter_dielectic;
			}
			//metal
			
			if (c=='m'){
				new_mat->type_mat=metal;
				new_mat->scatter=scatter_metal;
			}
			fscanf(fichier," %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",&x,&y,&z,&xa,&ya,&za,&xb,&yb,&zb,&fuzz,&a1,&a2,&a3);
			
			new_mat->albedo=(double *) malloc(sizeof(double)*3);
			(new_mat->albedo)[0]=a1;
			(new_mat->albedo)[1]=a2;
			(new_mat->albedo)[2]=a3;
			new_mat->text=NULL;	
		
		
		
			(new_tri->a)[0]=x;(new_tri->a)[1]=y;(new_tri->a)[2]=z;
			(new_tri->b)[0]=xa;(new_tri->b)[1]=ya;(new_tri->b)[2]=za;
			(new_tri->c)[0]=xb;(new_tri->c)[1]=yb;(new_tri->c)[2]=zb;
			new_mat->fuzz=fuzz;
			new_tri->mat_ptr=new_mat;
			
			cpt++;

		}
		
		
	}
	fclose(fichier);
}

void ecris_fichier_sphere(char *nom_f,hittable *L){
	FILE* fichier=fopen(nom_f,"w");
	
	hittable *tmp=L;
	
	double x,y,z,xa,ya,za,xb,yb,zb,r,fuzz,a1,a2,a3,a4,a5,a6;
	char c;
	sphere *tmp_sphere=NULL;
	triangle *tmp_triangle=NULL;
	
	while (tmp!=NULL) {
			
					
			if (tmp->geo==SPHERE){
			
				tmp_sphere=(sphere *) (tmp->obj);
				
				if ((tmp_sphere->mat_ptr->type_mat)==lambertian){
				c='l';
				}
				if  ((tmp_sphere->mat_ptr->type_mat)==metal){
					c='m';
				}
				if  ((tmp_sphere->mat_ptr->type_mat)==dielectic){
					c='d';
				}
				if  ((tmp_sphere->mat_ptr->type_mat)==checker_texture){
					c='c';
				}
				if	((tmp_sphere->mat_ptr->type_mat)==diffuse_light){
					c='i';
				}

				
				x=(tmp_sphere->centre)[0];
				y=(tmp_sphere->centre)[1];
				z=(tmp_sphere->centre)[2];
				r=(tmp_sphere->rayon);
				fuzz=(tmp_sphere->mat_ptr->fuzz);
		
				if (c!='c'){
					a1=(tmp_sphere->mat_ptr->albedo)[0];
					a2=(tmp_sphere->mat_ptr->albedo)[1];
					a3=(tmp_sphere->mat_ptr->albedo)[2];
			
					fprintf(fichier,"s%c %lf %lf %lf %lf %lf %lf %lf %lf\n",c,x,y,z,r,fuzz,a1,a2,a3);
			
				}else{
					a1=(tmp_sphere->mat_ptr->text->odd)[0];
					a2=(tmp_sphere->mat_ptr->text->odd)[1];
					a3=(tmp_sphere->mat_ptr->text->odd)[2];
			
					a4=(tmp_sphere->mat_ptr->text->even)[0];
					a5=(tmp_sphere->mat_ptr->text->even)[1];
					a6=(tmp_sphere->mat_ptr->text->even)[2];
				
					fprintf(fichier,"s%c %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",c,x,y,z,r,fuzz,a1,a2,a3,a4,a5,a6);
			
				}
			}
						
			if (tmp->geo==TRIANGLE){
			
				tmp_triangle=(triangle *) (tmp->obj);
				
				if ((tmp_triangle->mat_ptr->type_mat)==lambertian){
				c='l';
				}
				if  ((tmp_triangle->mat_ptr->type_mat)==metal){
					c='m';
				}
				if  ((tmp_triangle->mat_ptr->type_mat)==dielectic){
					c='d';
				}
				if  ((tmp_triangle->mat_ptr->type_mat)==checker_texture){
					c='c';
				}
				if	((tmp_triangle->mat_ptr->type_mat)==diffuse_light){
					c='i';
				}

				
				x=(tmp_triangle->a)[0];
				y=(tmp_triangle->a)[1];
				z=(tmp_triangle->a)[2];
				
				xa=(tmp_triangle->b)[0];
				ya=(tmp_triangle->b)[1];
				za=(tmp_triangle->b)[2];
				
				xb=(tmp_triangle->c)[0];
				yb=(tmp_triangle->c)[1];
				zb=(tmp_triangle->c)[2];
				fuzz=(tmp_triangle->mat_ptr->fuzz);
		
				
				a1=(tmp_triangle->mat_ptr->albedo)[0];
				a2=(tmp_triangle->mat_ptr->albedo)[1];
				a3=(tmp_triangle->mat_ptr->albedo)[2];
			
				fprintf(fichier,"t%c %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",c,x,y,z,xa,ya,za,xb,yb,zb,fuzz,a1,a2,a3);
			
				
			}
		tmp=tmp->suiv;
	}
	fclose(fichier);
	
}


void charge_fichier_ply(char *nom,hittable **liste){
	FILE *fichier=fopen(nom,"r");
	
	int nb_objets;
	int nb_sommets;
	int cpt=0;
	double a,b,c;
	int tmp,x,y,z;
	
	fscanf(fichier,"%d\n",&nb_sommets);
	fscanf(fichier,"%d\n",&nb_objets);
	
	materieau *mat=(materieau *)malloc(sizeof(materieau));
	
	mat->type_mat=lambertian;
	mat->albedo=(double *) malloc(sizeof(double)*3);
	(mat->albedo)[0]=0.79;
	(mat->albedo)[1]=0.79;
	(mat->albedo)[2]=0.79;
	mat->scatter=scatter_lambertian;
	mat->fuzz=1.000;
	mat->text=NULL;	
	
	double **tab_points=(double **) malloc(sizeof(double*)*nb_sommets);
	while (cpt<nb_sommets) {
		fscanf(fichier,"%lf %lf %lf\n",&a,&b,&c);
		tab_points[cpt]=(double *) malloc(sizeof(double)*3);
		(tab_points[cpt])[0]=a;
		(tab_points[cpt])[1]=b;
		(tab_points[cpt])[2]=c;
		cpt++;
	}
	
	
	
	cpt=0;
	while (cpt<nb_objets) {
		fscanf(fichier,"%d %d %d %d",&tmp,&x,&y,&z);
		triangle *tmp_triangle=(triangle *) malloc(sizeof(triangle));
		tmp_triangle->a=tab_points[x];
		tmp_triangle->b=tab_points[y];
		tmp_triangle->c=tab_points[z];
		
		tmp_triangle->mat_ptr=mat;
		add(liste,tmp_triangle,TRIANGLE);
		cpt++;
	}
	fclose(fichier);
}

void ecrire_arbre(char *nom,hittable *liste){
	
	FILE* fichier=fopen(nom,"w");
	int cpt=len(liste);
	fprintf(fichier,"%d\n",cpt);
	
	hittable *tmp=liste;
	attribue_id(liste);
	
	double x,y,z,xa,ya,za,xb,yb,zb,r,fuzz,a1,a2,a3,a4,a5,a6;
	char c;
	
	sphere *tmp_sphere=NULL;
	triangle *tmp_triangle=NULL;
	printf("inscription des objets\n");
	
	while (tmp!=NULL) {
				
						
				if (tmp->geo==SPHERE){
				
					tmp_sphere=(sphere *) (tmp->obj);
					
					if ((tmp_sphere->mat_ptr->type_mat)==lambertian){
						c='l';
					}
					if  ((tmp_sphere->mat_ptr->type_mat)==metal){
						c='m';
					}
					if  ((tmp_sphere->mat_ptr->type_mat)==dielectic){
						c='d';
					}
					if  ((tmp_sphere->mat_ptr->type_mat)==checker_texture){
						c='c';
					}
					if	((tmp_sphere->mat_ptr->type_mat)==diffuse_light){
						c='i';
					}

					
					x=(tmp_sphere->centre)[0];
					y=(tmp_sphere->centre)[1];
					z=(tmp_sphere->centre)[2];
					r=(tmp_sphere->rayon);
					fuzz=(tmp_sphere->mat_ptr->fuzz);
			
					if (c!='c'){
						a1=(tmp_sphere->mat_ptr->albedo)[0];
						a2=(tmp_sphere->mat_ptr->albedo)[1];
						a3=(tmp_sphere->mat_ptr->albedo)[2];
				
						fprintf(fichier,"s%c %lf %lf %lf %lf %lf %lf %lf %lf\n",c,x,y,z,r,fuzz,a1,a2,a3);
				
					}else{
						a1=(tmp_sphere->mat_ptr->text->odd)[0];
						a2=(tmp_sphere->mat_ptr->text->odd)[1];
						a3=(tmp_sphere->mat_ptr->text->odd)[2];
				
						a4=(tmp_sphere->mat_ptr->text->even)[0];
						a5=(tmp_sphere->mat_ptr->text->even)[1];
						a6=(tmp_sphere->mat_ptr->text->even)[2];
					
						fprintf(fichier,"s%c %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",c,x,y,z,r,fuzz,a1,a2,a3,a4,a5,a6);
				
					}
				}
							
				if (tmp->geo==TRIANGLE){
				
					tmp_triangle=(triangle *) (tmp->obj);
					
					if ((tmp_triangle->mat_ptr->type_mat)==lambertian){
						c='l';
					}
					if  ((tmp_triangle->mat_ptr->type_mat)==metal){
						c='m';
					}
					if  ((tmp_triangle->mat_ptr->type_mat)==dielectic){
						c='d';
					}
					if	((tmp_triangle->mat_ptr->type_mat)==diffuse_light){
						c='i';
					}

					
					x=(tmp_triangle->a)[0];
					y=(tmp_triangle->a)[1];
					z=(tmp_triangle->a)[2];
					
					xa=(tmp_triangle->b)[0];
					ya=(tmp_triangle->b)[1];
					za=(tmp_triangle->b)[2];
					
					xb=(tmp_triangle->c)[0];
					yb=(tmp_triangle->c)[1];
					zb=(tmp_triangle->c)[2];
					fuzz=(tmp_triangle->mat_ptr->fuzz);
			
					
					a1=(tmp_triangle->mat_ptr->albedo)[0];
					a2=(tmp_triangle->mat_ptr->albedo)[1];
					a3=(tmp_triangle->mat_ptr->albedo)[2];
					
					fprintf(fichier,"t%c %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",c,x,y,z,xa,ya,za,xb,yb,zb,fuzz,a1,a2,a3);
				
					
				}
			tmp=tmp->suiv;
		}

	
	noeud *arbre=NULL;
	liste_noeud *l=NULL;
	int id=0;
	printf("terminée\n");
	printf("construction noeud\n");
	cpt=construction_noeud(0,&arbre,&liste,-1,&id,&l);
	printf("terminée\n");
	printf("inscription arbre\n");
	fprintf(fichier,"%d\n",cpt);
	liste_noeud *tmp_n=l;
	
	
	while (tmp_n!=NULL) {
		if (tmp_n->n->fils_droit!=NULL){
			fprintf(fichier,"b\t %d\n",tmp_n->n->id);
			fprintf(fichier,"%d %d\n",tmp_n->n->fils_droit->id,tmp_n->n->fils_gauche->id);
			
		}else{
			fprintf(fichier,"f\t %d\n",tmp_n->n->id);
			hittable *tmp_hit=tmp_n->n->liste;
			while (tmp_hit!=NULL) {
				if (tmp_hit->geo==SPHERE){
					tmp_sphere=(sphere *) (tmp_hit->obj);
					fprintf(fichier,"%d\n",tmp_sphere->id);
				}
				
				if (tmp_hit->geo==TRIANGLE){
					tmp_triangle=(triangle *) (tmp_hit->obj);
					fprintf(fichier,"%d\n",tmp_triangle->id);
				}
				
				tmp_hit=tmp_hit->suiv;
			}
			fprintf(fichier,"-1\n");
		}
		fprintf(fichier,"%lf %lf %lf %lf %lf %lf \n",(tmp_n->n->cig)[0],(tmp_n->n->cig)[1],(tmp_n->n->cig)[2],(tmp_n->n->csd)[0],(tmp_n->n->csd)[1],(tmp_n->n->csd)[2]);
		tmp_n=tmp_n->suiv;
	}
	printf("terminée\n");
	fclose(fichier);
	
}

int charge_fichier_arbre(char *nom_f,hittable ***tab_s,noeud ***tab_n,int *ts,int *tn){
	
	FILE* fichier=fopen(nom_f,"r");
	int cpt=0;
	char c=' ';
	double x=0.,y=0.,z=0.,r=0.,fuzz=0.,a1=0.,a2=0.,a3=0.,a4=0.,a5=0.,a6=0.,xa=0.,ya=0.,za=0.,xb=0.,yb=0,zb=0.;
	int id=0;
	
	int nb_obj=0;
	fscanf(fichier,"%d\n",&nb_obj);
	sphere *tmp_sphere=NULL;
	triangle *tmp_triangle=NULL;
	
	*ts=nb_obj;
	hittable **obj_tab=(hittable **) malloc(sizeof(hittable*)*nb_obj);
	*tab_s=obj_tab;
	
	while ((c!=EOF)&&(cpt<nb_obj)) {
		
		if ((c=fgetc(fichier))=='s'){
			
			c=fgetc(fichier);
			hittable *new_hit=(hittable *) malloc(sizeof(hittable));
			sphere *new_sph=(sphere *) malloc(sizeof(sphere));
			materieau *new_mat=(materieau *) malloc(sizeof(materieau));
			
			new_hit->geo=SPHERE;
			new_hit->suiv=NULL;
			
			new_hit->obj=new_sph;
			new_sph->mat_ptr=new_mat;
			
			//add(L,new_sph,SPHERE);
			if (c!='c'){
				fscanf(fichier,"%lf %lf %lf %lf %lf %lf %lf %lf\n",&x,&y,&z,&r,&fuzz,&a1,&a2,&a3);
				if (c=='i'){
					new_mat->type_mat=diffuse_light;
					new_mat->scatter=scatter_lambertian;
				}
				//lambertian
				if (c=='l'){
					new_mat->type_mat=lambertian;
					new_mat->scatter=scatter_lambertian;
				}
				//dialectic
				if (c=='d'){
					new_mat->type_mat=dielectic;
					new_mat->scatter=scatter_dielectic;
				}
				//metal
				
				if (c=='m'){
					new_mat->type_mat=metal;
					new_mat->scatter=scatter_metal;
				}
				new_mat->albedo=(double *) malloc(sizeof(double)*3);
				(new_mat->albedo)[0]=a1;
				(new_mat->albedo)[1]=a2;
				(new_mat->albedo)[2]=a3;
				new_mat->fuzz=fuzz;
				new_mat->text=NULL;	
			}else{
				//checkered
				if (c=='c'){
						
						fscanf(fichier," %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",&x,&y,&z,&r,&fuzz,&a1,&a2,&a3,&a4,&a5,&a6);
						new_mat->type_mat=checker_texture;
						new_mat->scatter=scatter_lambertian;
						new_mat->text=(texture *)malloc(sizeof(texture));
						new_mat->text->odd=(double *) malloc(sizeof(double)*3);
						new_mat->text->even=(double *) malloc(sizeof(double)*3);
						(new_mat->text->odd)[0]=a1;
						(new_mat->text->odd)[1]=a2;
						(new_mat->text->odd)[2]=a3;
						
						(new_mat->text->even)[0]=a4;
						(new_mat->text->even)[1]=a5;
						(new_mat->text->even)[2]=a6;
				}
			}
										
			new_sph->rayon=r;
			new_sph->centre=(double *) malloc(sizeof(double)*3);
			new_sph->id=cpt;
			(new_sph->centre)[0]=x;
			(new_sph->centre)[1]=y;
			(new_sph->centre)[2]=z;
			
			obj_tab[cpt]=new_hit;
			cpt++;			
	}
	
	if (c=='t'){
	
		hittable *new_hit=(hittable *) malloc(sizeof(hittable));
		triangle *new_tri=(triangle *) malloc(sizeof(triangle));
		materieau *new_mat=(materieau *) malloc(sizeof(materieau));
		new_hit->obj=new_tri;
		new_hit->geo=TRIANGLE;
		new_hit->suiv=NULL;
		c=fgetc(fichier);
		
		//add(L,new_sph,TRIANGLE);
		
		fscanf(fichier," %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",&x,&y,&z,&xa,&ya,&za,&xb,&yb,&zb,&fuzz,&a1,&a2,&a3);
		if (c=='i'){
			new_mat->type_mat=diffuse_light;
			new_mat->scatter=scatter_lambertian;
		}
		//lambertian
		if (c=='l'){
			new_mat->type_mat=lambertian;
			new_mat->scatter=scatter_lambertian;
		}
		//dialectic
		if (c=='d'){
				
			new_mat->type_mat=dielectic;
			new_mat->scatter=scatter_dielectic;
		}
		//metal
		if (c=='m'){
			
			new_mat->type_mat=metal;
			new_mat->scatter=scatter_metal;
		}
		new_mat->albedo=(double *) malloc(sizeof(double)*3);
		(new_mat->albedo)[0]=a1;
		(new_mat->albedo)[1]=a2;
		(new_mat->albedo)[2]=a3;
		
		new_mat->text=NULL;	
		
	
		new_tri->a=(double *) malloc(sizeof(double)*3);
		new_tri->b=(double *) malloc(sizeof(double)*3);
		new_tri->c=(double *) malloc(sizeof(double)*3);
		new_tri->id=cpt;
		(new_tri->a)[0]=x;(new_tri->a)[1]=y;(new_tri->a)[2]=z;
		(new_tri->b)[0]=xa;(new_tri->b)[1]=ya;(new_tri->b)[2]=za;
		(new_tri->c)[0]=xb;(new_tri->c)[1]=yb;(new_tri->c)[2]=zb;
		new_mat->fuzz=fuzz;
		new_tri->mat_ptr=new_mat;
		
		obj_tab[cpt]=new_hit;
		cpt++;

		}
	
	
	}
		
	
	
	fscanf(fichier,"%d\n",&nb_obj);
	*tn=nb_obj;
	cpt=0;

	noeud **tab_noeud=(noeud **)malloc(sizeof(noeud*)*nb_obj);
	*tab_n=tab_noeud;
	id=0;
	
	while ((c!=EOF)&&(cpt<nb_obj)){
		
	
		
		noeud *new=(noeud *) malloc(sizeof(noeud));
		
		
		fscanf(fichier,"%c\t%d\n",&c,&id);
		
		new->fils_droit=NULL;
		new->fils_gauche=NULL;
		new->liste=NULL;
		new->id=id;
		
		tab_noeud[id]=new;
		if (c=='f'){
			
			int nombre=0;
			fscanf(fichier,"%d\n",&nombre);
			while (nombre!=-1) {
				
				if ((obj_tab[nombre])->geo==SPHERE){
					tmp_sphere=(sphere *) ((obj_tab[nombre])->obj);
					add(&(new->liste),tmp_sphere,SPHERE);
				}else{
					tmp_triangle=(triangle *) ((obj_tab[nombre])->obj);
					add(&(new->liste),tmp_triangle,TRIANGLE);
					
				}
				fscanf(fichier,"%d\n",&nombre);
				
			}
		}else{
			int filsd=0;
			int filsg=0;
			
			fscanf(fichier,"%d %d\n",&filsd,&filsg);
			new->fils_gauche=tab_noeud[filsg];
			new->fils_droit=tab_noeud[filsd];
		}
		new->csd=(double *) malloc(sizeof(double)*3);
		new->cig=(double *) malloc(sizeof(double)*3);
		fscanf(fichier,"%lf %lf %lf %lf %lf %lf\n",&((new->cig)[0]),&((new->cig)[1]),&((new->cig)[2]),&((new->csd)[0]),&((new->csd)[1]),&((new->csd)[2]));
		cpt++;
		
	}
	
	fclose(fichier);
	
	return cpt;
}

void saut_prochaine_ligne(FILE *fichier,char c){
	while ((c!='\n')&&(c!=EOF)){
		c=fgetc(fichier);
	}
}



void add_point_fichier(point_fichier **liste,double x,double y,double z){
	point_fichier *new=(point_fichier *) malloc(sizeof(point_fichier));
	new->x=x;
	new->y=y;
	new->z=z;
	
	if ((*liste)==NULL){
		new->id=1;
		
	}else {
		new->id=((*liste)->id)+1;
	}
	
	new->suiv=*liste;
	
	(*liste)=new;
}

void clear_liste_fichier(point_fichier **liste){
	point_fichier *tmp=*liste;
	point_fichier *del=NULL;
	
	while (tmp!=NULL) {
		del=tmp;
		tmp=tmp->suiv;
		free(del);
	}
}


point_fichier *trouve_point_fichier(point_fichier **liste,int id){
	point_fichier *tmp=*liste;
	
	while (tmp!=NULL) {
		if (tmp->id==id){
			return tmp;
		}
		tmp=tmp->suiv;
	}
	printf("point non trouvé : %d\n",id);
	return NULL;
}

void creer_triangle_fichier(point_fichier **liste_fichier,hittable**liste,int id1,int id2,int id3,materieau *mat){
	
	point_fichier *p1=trouve_point_fichier(liste_fichier,id1);
	point_fichier *p2=trouve_point_fichier(liste_fichier,id2);
	point_fichier *p3=trouve_point_fichier(liste_fichier,id3);
	
	triangle* new_tri=(triangle *) malloc(sizeof(triangle));
	
	new_tri->a=(double *) malloc(sizeof(double)*3);
	new_tri->b=(double *) malloc(sizeof(double)*3);
	new_tri->c=(double *) malloc(sizeof(double)*3);
	
	
	(new_tri->a)[0]=p1->x ; (new_tri->a)[1]=p1->y ; (new_tri->a)[2]=p1->z ; 
	(new_tri->b)[0]=p2->x ; (new_tri->b)[1]=p2->y ; (new_tri->b)[2]=p2->z ; 
	(new_tri->c)[0]=p3->x ; (new_tri->c)[1]=p3->y ; (new_tri->c)[2]=p3->z ; 
	
	new_tri->mat_ptr=mat;
	
	add(liste,new_tri,TRIANGLE);
	
}

void charge_fichier_obj(char *nom,hittable **liste,materieau *mat){
	FILE *fichier=fopen(nom,"r");
	
	char c=' ';
	
	point_fichier *liste_pts_fichier=NULL;
	
	double x,y,z;
	int v1,v2,v3,vt1,vt2,vt3,vn1,vn2,vn3;

	while(c!=EOF){
		c=fgetc(fichier);
		
		if ((c!='v')&&(c!='f')){
			saut_prochaine_ligne(fichier,c);
			continue;
		}
		
		if (c=='v'){
			fscanf(fichier," %lf %lf %lf\n",&x,&y,&z);
			add_point_fichier(&liste_pts_fichier,x,y,z);
			continue;
		}
		
		if (c=='f'){
			fscanf(fichier," %d/%d/%d  %d/%d/%d  %d/%d/%d\n",&v1,&vt1,&vn1,&v2,&vt2,&vn2,&v3,&vt3,&vn3);
			creer_triangle_fichier(&liste_pts_fichier,liste,v1,v2,v3,mat);
		}
		
	}
	
	clear_liste_fichier(&liste_pts_fichier);
	
	
}