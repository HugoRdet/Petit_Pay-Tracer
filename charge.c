#include <stdio.h>
#include "arbre.h"
#include "fichier.h"
#include <time.h>

int main(void) {
	srand(time(NULL));
	
	hittable *world=NULL;	
	
	materieau *mat=(materieau *)malloc(sizeof(materieau));
	
	mat->type_mat=lambertian;
	mat->albedo=(double *) malloc(sizeof(double)*3);
	(mat->albedo)[0]=0.48;
	(mat->albedo)[1]=0.83;
	(mat->albedo)[2]=0.53;
	mat->scatter=scatter_lambertian;
	mat->fuzz=0.30000;
	mat->text=NULL;

	charge_fichier_obj("uploads_files_2399303_CH_20.obj",&world,mat);
	
	//charge_fichier_spheres("4_spheres.txt",&world);
	
		
		
	//sol_cube(&world,mat);
	
	
	/*
	hittable *rec1=NULL;
	hittable *rec2=NULL;
	charge_fichier_ply("petit_cube.ply",&rec1);
	charge_fichier_ply("grand_cube.ply",&rec2);
	add_liste(&rec1,&world);
	add_liste(&rec2,&world);
	cornell_box(&world);
	*/
	
	/*
	double a[3]={-82.500,0.000,-82.500};
	creer_pave(a,165.0+82.500,330.0,165+82.500,&rec1,mat);
	rotation_y(-18.0,rec1);
	translation(265.0,0.0,295.0,rec1);
	add_liste(&rec1,&world);
	
	a[0]=-82.500;
	a[1]=0.00;
	a[2]=-82.500;
	
	creer_pave(a,165.0+82.500,165.0,165.0+82.500,&rec2,mat);
	rotation_y(15.0,rec2);
	translation(130.0,0.0,65.0,rec2);
	add_liste(&rec2,&world);
	*/
	//afficher(world);
	//scene_alea(&world);
	//ecris_fichier_sphere("scene_aleatoire.txt",world);
	
	
	
	//ecris_fichier_sphere("4_spheres.txt",world);
	//sol_cube(&world,mat);
	//ecris_fichier_sphere("sol_pave.txt",world);
	//charge_fichier_spheres("sol_pave.txt",&world);
	//charge_fichier_spheres("test_triangles.txt",&world);
	//afficher(world);
	//charge_fichier_ply("sandal.ply",&world);
	//charge_fichier_ply("dragon_vrip_res2.ply",&world);
	//scene_alea(&world);
	//attribue_id(world);
	//afficher(world);
	//printf("\n\n\n\n");
	//world=merge_sort(&world,0);
	//afficher(world);
	
	ecrire_arbre("test_arbre.txt",world);
	/*
	sphere **tab_s=NULL;
	noeud **tab_n=NULL;
	
	int ns=0;
	int nn=0;
	charge_fichier_arbre("test_arbre.txt",&tab_s,&tab_n,&ns,&nn);
	afficher_noeud(tab_n[0]);
	*/

	return 0;
}