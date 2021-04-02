#include "tri.h"

void insert(hittable **element,hittable **liste,int clef){

	if (*element==NULL){
		return;
	}
	
	if (*liste==NULL){
		*liste=*element;
		return; 
	}
	
	double var_liste;
	double var_elem;
	sphere *tmp_sphere;
	triangle *tmp_triangle;
	
	if ((*liste)->geo==SPHERE){
		tmp_sphere=(sphere *) (( *liste)->obj);
		var_liste=(tmp_sphere->centre)[clef]-(tmp_sphere->rayon);
	}else{
		tmp_triangle=(triangle *) (( *liste)->obj);
		var_liste=min3((tmp_triangle->a)[clef],(tmp_triangle->b)[clef],(tmp_triangle->c)[clef]);
		
		var_liste=(tmp_triangle->a)[0];
	}
		
		if ((*element)->geo==SPHERE){
		tmp_sphere=(sphere *) (( *element)->obj);
		var_elem=(tmp_sphere->centre)[clef]-(tmp_sphere->rayon);
	}else{
		tmp_triangle=(triangle *) (( *element)->obj);
		var_elem=min3((tmp_triangle->a)[clef],(tmp_triangle->b)[clef],(tmp_triangle->c)[clef]);
		var_elem=(tmp_triangle->a)[0];
	}
		
	if (var_liste>=var_elem){
		(*element)->suiv=*liste;
		(*liste)=*element;
		
		return;
	}

	hittable *tmp=*liste;
	
	while 
		(tmp->suiv!=NULL){
		if (tmp->geo==SPHERE){
			tmp_sphere=(sphere *) (tmp->obj);
			var_liste=(tmp_sphere->centre)[clef]-(tmp_sphere->rayon);
		}else{
			tmp_triangle=(triangle *) (tmp->obj);
			var_liste=min3((tmp_triangle->a)[clef],(tmp_triangle->b)[clef],(tmp_triangle->c)[clef]);
		}
	
		if (var_liste>=var_elem) break;
	
		tmp=tmp->suiv;
	}
	(*element)->suiv=tmp->suiv;
	tmp->suiv=(*element);
	
	
}

hittable *merge(hittable **liste1,hittable **liste2,int clef){
	if ((*liste1)==NULL){
		return *liste2;
	}
	
	if ((*liste2)==NULL){
		return *liste1;
	}
	while (*liste1!=NULL) {
		hittable *elem=*liste1;
		(*liste1)=(*liste1)->suiv;
		elem->suiv=NULL;
		insert(&elem,liste2,clef);
	}

	return *liste2;
	
	
}

hittable	*merge_sort(hittable **droite,int clef){

	int longueur=len(*droite);
	
	if (longueur<2){
		return *droite;
	}
	
	int cpt=0;
	hittable *tmp=*droite;
	int valeur=((int)(longueur/2.0))-1;
	while (cpt<valeur) {
		cpt++;
		tmp=tmp->suiv;
	}
	
	hittable *new=tmp->suiv;
	tmp->suiv=NULL;
	
	hittable *tmp2=merge_sort(&new,clef);
	hittable *tmp1=merge_sort(droite,clef);
	
	
	
	return merge(&tmp1,&tmp2,clef);
	
}