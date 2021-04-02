#include <stdio.h>

typedef struct vect{
	int tab[3];
	int c;
}vect;

void test2(vect *tab){
	
	(a->tab)[0]+=1;
	(a->tab)[1]+=1;
	(a->tab)[2]+=1;
	printf("%d %d %d\n",(a->tab)[0],(a->tab)[1],(a->tab)[2]);
}

void test(){
	int tab[3];
	vect *a;
	a->tab=tab;
	a->c=5;
	
	tab[0]=1;
	tab[1]=1;
	tab[2]=1;
	printf("%d %d %d\n",(a->tab)[0],(a->tab)[1],(a->tab)[2]);
	test2(tab);
	printf("%d %d %d\n",(a->tab)[0],(a->tab)[1],(a->tab)[2]);
}




int main(int argc, char *argv[]) {
	test();
	return 0;
}