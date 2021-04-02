CC=gcc 
CFLAGS = -W -Wall -Ofast


all : main charge



vecteurs.o: vecteurs.c vecteurs.h types.h
	$(CC) $(CFLAGS) -c vecteurs.c

hittable.o: hittable.c hittable.h triangle.h vecteurs.h sphere.h types.h
	$(CC) $(CFLAGS) -c hittable.c

tri.o: tri.c tri.h types.h vecteurs.h hittable.h
	$(CC) $(CFLAGS) -c tri.c	

materiaux.o: materiaux.c materiaux.h vecteurs.h types.h
	$(CC) $(CFLAGS) -c materiaux.c
	
sphere.o: sphere.c sphere.h vecteurs.h types.h hittable.h 
	$(CC) $(CFLAGS) -c sphere.c  

triangle.o: triangle.c triangle.h types.h utilitaires.h hittable.h
	$(CC) $(CFLAGS) -c triangle.c

rayons.o: rayons.c rayons.h types.h vecteurs.h sphere.h hittable.h triangle.h camera.h utilitaires.h
	$(CC) $(CFLAGS) -c rayons.c
	
fichier.o: fichier.c fichier.h  arbre.h types.h hittable.h materiaux.h
	$(CC) $(CFLAGS) -c fichier.c

camera.o: camera.c camera.h types.h 
	$(CC) $(CFLAGS) -c camera.c 

utilitaires.o: utilitaires.c utilitaires.h fichier.h sphere.h vecteurs.h camera.h arbre.h types.h hittable.h rayons.h materiaux.h
	$(CC) $(CFLAGS) -c   utilitaires.c	

arbre.o: arbre.c arbre.h types.h tri.h 
	$(CC) $(CFLAGS) -c arbre.c
	
main.o: main.c sphere.h vecteurs.h fichier.h utilitaires.h camera.h types.h hittable.h triangle.h
	$(CC) $(CFLAGS) -c  main.c

charge.o: charge.c arbre.h fichier.h types.h hittable.h
	$(CC) $(CFLAGS) -c charge.c
	
main: main.o vecteurs.o sphere.o fichier.o utilitaires.o camera.o arbre.o hittable.o materiaux.o tri.o rayons.o triangle.o 
	$(CC) -o main main.o vecteurs.o sphere.o fichier.o utilitaires.o camera.o arbre.o hittable.o materiaux.o tri.o rayons.o triangle.o

charge: charge.o vecteurs.o sphere.o arbre.o fichier.o utilitaires.o hittable.o materiaux.o tri.o rayons.o triangle.o
	$(CC) -o charge charge.o vecteurs.o sphere.o arbre.o fichier.o utilitaires.o hittable.o materiaux.o tri.o rayons.o triangle.o
	
clean:
	rm -f *.o main