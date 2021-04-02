#include "hittable.h"

int len(hittable *liste){
	int cpt=0;
	hittable *tmp=liste;
	while (tmp!=NULL) {
		cpt++;
		tmp=tmp->suiv;
	}
	return cpt;
}

void detruire_conteneur(hittable **liste){
	hittable *tmp=*liste;
	hittable *a_supp;
	
	while (tmp!=NULL) {
		a_supp=tmp;
		tmp=tmp->suiv;
		free(tmp);
	}
}

void add(hittable **L,void *sph,enum geometrie type){
	hittable *new=(hittable *) malloc(sizeof(hittable));
	new->obj=sph;
	new->suiv=*L;
	
	if (type==SPHERE){
		new->geo=SPHERE;
	}
	
	if (type==TRIANGLE){
		new->geo=TRIANGLE;
	}
		
	(*L)=new;
}

void add_liste(hittable **L,hittable **dest){
	if (*L==NULL){
		return ;
	}
	hittable *tmp=*L;
	while (tmp->suiv!=NULL) {
		tmp=tmp->suiv;
	}
	tmp->suiv=*dest;
	*dest=*L;
}

void libere_liste(hittable **L){
	hittable *tmp=*L;
	hittable *del=NULL;
	
	while (tmp!=NULL) {
		del=tmp;
		tmp=tmp->suiv;
		if (del->geo==SPHERE){
			libere_sphere((sphere *) (del->obj));
		}
		
		if (del->geo==TRIANGLE){
			libere_triangle((triangle *) (del->obj));
		}
		free(del->obj);
	}
}