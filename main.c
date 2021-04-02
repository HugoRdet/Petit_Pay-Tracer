#include "vecteurs.h"
#include "types.h"
#include "sphere.h"
#include "fichier.h"
#include "utilitaires.h"
#include "camera.h"
#include "arbre.h"
#include "hittable.h"
#include <time.h>
#include <math.h>
#include <stdio.h>




int main(int argc,char *argv[]) {

	srand(time(NULL));
	clock_t	temps_initial ; /* Temps initial en micro-secondes */
	clock_t	temps_final;   /* Temps final en micro-secondes */
	temps_initial = clock ();
	
	if (argc!=2) return 0;
	
	
	
	camera *cam=NULL;
	
	//largeur image en pixels
	int hauteur_image=atoi(argv[1]);
	
	//spheres
	/*
	double look_from[3]={-13,2.,-3};
	double look_at[3]={0.,0.,0.};
	double vup[3]={0.,1.,0.};
	*/
	
	
	
	//cornell
	/*
	double look_at[3]={278.,278.,0.};
	double look_from[3]={278.,278.,-800.};
	double vup[3]={0.,1.,0.};
	*/
	
	
	/*double look_from[3]={13,10.,3};
	double look_at[3]={0.5,0.5,0.5};
	double vup[3]={0.,0.,0.};
	*/
	/*
	//sandales
	double look_at[3]={0.,0.10,0.};
	double look_from[3]={-20/5.0,-10.,30};
	double vup[3]={10.,10.,0.};
	*/
	
	
	//vache
	double look_at[3]={0.,0.,0.};
	double look_from[3]={100,100,100};
	double vup[3]={0,0,0};
	

	

	
	double dist_focus=10.0;
	double aperture=0.00;
	// 40 -> 25
	camera_init(&cam,40.0,ASPECT_RATIO,look_from,look_at,vup,aperture,dist_focus);
	int largeur_image=(int) (hauteur_image*(cam-> aspect_ratio));
	//ouverture du fichier .ppm
	FILE *fichier=fopen("test.ppm","w");
	
	fprintf(fichier,"P3\n%d %d\n255\n",largeur_image,hauteur_image);
	
	
	//liste des objets qui compensent le monde
	
	
	hittable *world=NULL;	
	
	//charge_fichier_spheres("4_spheres.txt",&world);
	//charge_fichier_spheres("scene_aleatoire.txt",&world);
	hittable **tab_s=NULL;
	noeud **tab_n=NULL;
		
	int ns=0;
	int nn=0;
	
	charge_fichier_arbre("test_arbre.txt",&tab_s,&tab_n,&ns,&nn);
	printf("hauteur : %d , largeur : %d\n",hauteur_image,largeur_image);
	calcul_scene(hauteur_image,largeur_image,fichier,tab_n[0],cam);	
	
	fclose(fichier);
	libere_liste(&world);
	clear_camera(&cam);
	
	temps_final = clock ();
	
	float temps_cpu;     /* Temps total en secondes */
	temps_cpu = ((double)(temps_final - temps_initial)/CLOCKS_PER_SEC);
	printf("temps d execution: %f\n",temps_cpu);
	return 0;
}