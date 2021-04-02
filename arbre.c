#include "arbre.h"


#define abs(x) (x<0?-x:x)
#define min(x,y) (x>y?y:x)
#define max(x,y) (x>y?x:y)








int cmp(hittable * l1,hittable *l2){
	hittable *tmp1=l1;	
	hittable *tmp2=l2;
	int id1;
	int id2;
	
	sphere *tmp_sphere=NULL;
	triangle *tmp_triangle=NULL;
	
	
	while ((tmp1!=NULL)&&(tmp2!=NULL)) {
		
		if (tmp1->geo==SPHERE){
			tmp_sphere=(sphere *) (tmp1->obj);
			id1=tmp_sphere->id;
		}
		
		if (tmp1->geo==TRIANGLE){
			tmp_triangle=(triangle *) (tmp1->obj);
			id1=tmp_triangle->id;
		}
		
		if (tmp2->geo==SPHERE){
			tmp_sphere=(sphere *) (tmp2->obj);
			id2=tmp_sphere->id;
		}
		
		if (tmp2->geo==TRIANGLE){
			tmp_triangle=(triangle *) (tmp2->obj);
			id2=tmp_triangle->id;
		}
		
		if (id1!=id2)return  0;
		tmp2=tmp2->suiv;
		tmp1=tmp1->suiv;
	}
	
	if ((tmp1==NULL)&&(tmp2!=NULL)) return 0;
	if ((tmp1!=NULL)&&(tmp2==NULL)) return 0;
	
	return 1;
	
		
}



void trouver_box(hittable *liste,double *min_coin,double *max_coin){
	hittable *tmp=liste;
	
	sphere *tmp_sphere=NULL;
	triangle *tmp_triangle=NULL;
	double min_tri;
	
	while (tmp!=NULL) {
		if (tmp->geo==SPHERE){
			tmp_sphere=(sphere *)(tmp->obj);
			min_coin[0]=min(min_coin[0],(tmp_sphere->centre)[0]-(tmp_sphere->rayon));
			min_coin[1]=min(min_coin[1],(tmp_sphere->centre)[1]-(tmp_sphere->rayon));
			min_coin[2]=min(min_coin[2],(tmp_sphere->centre)[2]-(tmp_sphere->rayon));
	
			max_coin[0]=max(max_coin[0],(tmp_sphere->centre)[0]+(tmp_sphere->rayon));
			max_coin[1]=max(max_coin[1],(tmp_sphere->centre)[1]+(tmp_sphere->rayon));
			max_coin[2]=max(max_coin[2],(tmp_sphere->centre)[2]+(tmp_sphere->rayon));
		}else{
			tmp_triangle=(triangle *)(tmp->obj);
			
			min_tri=min3((tmp_triangle->a)[0],(tmp_triangle->b)[0], (tmp_triangle->c)[0]);
			min_coin[0]=min(min_coin[0],min_tri);
			min_tri=min3((tmp_triangle->a)[1],(tmp_triangle->b)[1], (tmp_triangle->c)[1]);
			min_coin[1]=min(min_coin[1],min_tri);
			min_tri=min3((tmp_triangle->a)[2],(tmp_triangle->b)[2], (tmp_triangle->c)[2]);
			min_coin[2]=min(min_coin[2],min_tri);
			
			min_tri=max3((tmp_triangle->a)[0],(tmp_triangle->b)[0], (tmp_triangle->c)[0]);
			
			max_coin[0]=max(max_coin[0],min_tri);
			min_tri=max3((tmp_triangle->a)[1],(tmp_triangle->b)[1], (tmp_triangle->c)[1]);
			max_coin[1]=max(max_coin[1],min_tri);
			min_tri=max3((tmp_triangle->a)[2],(tmp_triangle->b)[2], (tmp_triangle->c)[2]);
			max_coin[2]=max(max_coin[2],min_tri);
		}
			
		tmp=tmp->suiv;
	}
}



void ajouter_liste_noeud(liste_noeud **l,noeud *n){
	liste_noeud *tmp=(liste_noeud *) malloc(sizeof(liste_noeud));
	tmp->n=n;
	
	tmp->suiv=*l;
	*l=tmp;
}

int construction_noeud(int prof,noeud **n,hittable **liste,int clef,int *id,liste_noeud **l){
	//tri de la liste
	printf("%d\n",*id);
	int longueur=len(*liste);
	*n=(noeud *) malloc(sizeof(noeud));
	ajouter_liste_noeud(l,*n);
	double *min_coin=(double *) malloc(sizeof(double)*3);
	double *max_coin=(double *) malloc(sizeof(double)*3);
	double res_tri;
	(*n)->cig=min_coin;
	(*n)->csd=max_coin;
	(*n)->id=*id;
	(*id)+=1;
	(*n)->clef=clef;
	sphere *tmp_sphere=NULL;
	triangle *tmp_triangle=NULL;
	if ((*liste)->geo==SPHERE){
		tmp_sphere=(sphere*) ((*liste)->obj);
		min_coin[0]=(tmp_sphere->centre)[0]-(tmp_sphere->rayon);
		min_coin[1]=(tmp_sphere->centre)[1]-(tmp_sphere->rayon);
		min_coin[2]=(tmp_sphere->centre)[2]-(tmp_sphere->rayon);
	
		max_coin[0]=(tmp_sphere->centre)[0]+(tmp_sphere->rayon);
		max_coin[1]=(tmp_sphere->centre)[1]+(tmp_sphere->rayon);
		max_coin[2]=(tmp_sphere->centre)[2]+(tmp_sphere->rayon);
	}else{
		tmp_triangle=(triangle *) ((*liste)->obj);
		min_coin[0]=(tmp_triangle->a)[0];
		min_coin[1]=(tmp_triangle->a)[1];
		min_coin[2]=(tmp_triangle->a)[2];
		
		max_coin[0]=(tmp_triangle->b)[0];
		max_coin[1]=(tmp_triangle->b)[1];
		max_coin[2]=(tmp_triangle->b)[2];	
	}
	
	trouver_box(*liste,min_coin,max_coin);
	
	hittable *liste_gauche;
	hittable *liste_droite;
	
	do{
		
		clef+=1;
		(*n)->fils_gauche=NULL;
		(*n)->fils_droit=NULL;
		liste_gauche=NULL;
		liste_droite=NULL;
		
		double clef_tmp=0;
		int cpt=0;
	
		*liste=merge_sort(liste,clef);
		hittable *tmp=*liste;
		
		int median=(int)(longueur/2.0)-1;
		
		while (tmp!=NULL) {
			if (cpt==median){
				if (tmp->geo==SPHERE){
					tmp_sphere=(sphere *) (tmp->obj);
					clef_tmp=(tmp_sphere->centre)[clef%3];//-(tmp->obj->rayon);
				}else{
					tmp_triangle=(triangle *) (tmp->obj);
					clef_tmp=(tmp_triangle->a)[clef];

				}
				break;
			}
			cpt++;
			tmp=tmp->suiv;
		}
	
		
	
		if ((prof>=profondeur)||(longueur<=longueur_noeud)){
			(*n)->liste=*liste;	
			return 1;
		}	
		
		tmp=*liste;

		while (tmp!=NULL) {
			if (tmp->geo==SPHERE){
				tmp_sphere= (sphere *) (tmp->obj);
				if (((tmp_sphere->centre)[clef%3]-tmp_sphere->rayon)<=clef_tmp){
					add(&liste_gauche,tmp->obj,SPHERE);
				}
				
				if (((tmp_sphere->centre)[clef%3]-tmp_sphere->rayon)>=clef_tmp){
					add(&liste_droite,tmp->obj,SPHERE);
				}
			}else{
				tmp_triangle=(triangle *) (tmp->obj);
				res_tri=min3((tmp_triangle->a)[clef],(tmp_triangle->b)[clef],(tmp_triangle->c)[clef]);
				
				if (res_tri<=clef_tmp){
					add(&liste_gauche,tmp->obj,TRIANGLE);
				}
				
				if (res_tri>=clef_tmp){
					add(&liste_droite,tmp->obj,TRIANGLE);
				}
			}
			tmp=tmp->suiv;
		}	
		
		
		int len_gauche=len(liste_gauche);
		int len_droite=len(liste_droite);
		if (((len_gauche==longueur))||(len_droite==longueur)){
			detruire_conteneur(&liste_droite);
			detruire_conteneur(&liste_gauche);
		}else {
			
			detruire_conteneur(liste);
			
			break;	
		}
		
	
	}while (1);
	(*n)->liste=NULL;
	
	return 1+construction_noeud(prof+1,&((*n)->fils_gauche),&liste_gauche,clef%3,id,l)+
			construction_noeud(prof+1,&((*n)->fils_droit),&liste_droite,clef%3,id,l);
	
}

