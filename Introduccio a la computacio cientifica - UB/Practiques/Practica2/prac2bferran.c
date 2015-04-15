#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prac2funs.c"



double datajuliana(int dia, int mes, int any){
	int a,m,y,D,data;
	a = (14-mes)/12;
	m= ((mes+12)*a)-3;
	y=any+4800-a;
	D=dia+((153*m+2)/5)+365*y+y/4-y/100+y/400-32045;
	data = D-0.5;
	return data;
}

int main(void){
	int i,j,n,primera;
	double t, t0, t1, x , y, z, pn;
	double *pt, *px, *py, *pz;
	FILE *arxiu, *resultat;
	
	arxiu = fopen("dades_apophis.dat","r");
	resultat = fopen("resultat.dat","w");
	i=0;
	j=0;
	t0=2462225.5f;

	printf("Escriu el grau del polinomi\n");
	scanf("%d",&n);

	pt = (double*)malloc((n+1)*sizeof(double*));
	px = (double*)malloc((n+1)*sizeof(double*));

	if (pt==NULL || px==NULL){
		printf("No hi ha prou memòria");
		exit(1);
	}

	while(fscanf(arxiu, "%lf %le %le %le", &t, &x, &y, &z) != EOF){
		if (i>=(414-n-1)){
			pt[j]=t;
			px[j]=x;
			j++;
		}
		i++;
	}
	dif_dividides(pt,px,n);
	pn = aval(pt,px,n,2462225.5f);
	fprintf(resultat,"n= %d t= %f pn(t)= %f\n",n,t0,pn);
	free(pt);
	free(px);

	n=7;
	pt = (double*)malloc((n+1)*sizeof(double*));
	px = (double*)malloc((n+1)*sizeof(double*));
	py = (double*)malloc((n+1)*sizeof(double*));
	pz = (double*)malloc((n+1)*sizeof(double*));

	if (pt==NULL || px==NULL || py==NULL || pz==NULL){
		printf("No hi ha prou memòria");
		exit(1);
	}

	t0=2453979.5;
	t1 = datajuliana(28,1,2020);

	primera = (t1-t0)/20-3;
	i=0;
	j=0;

	while((fscanf(arxiu, "%lf %le %le %le", &t, &x, &y, &z) != EOF)&& i<=(primera+7)){
		if (i>=primera && i<=(primera+7)){
			pt[j]=t;
			px[j]=x;
			py[j]=y;
			pz[j]=z;
			j++;
		}
		i++;
	}
	fclose(arxiu);
	dif_dividides(pt,px,n);
	dif_dividides(pt,py,n);
	dif_dividides(pt,pz,n);

	fprintf(resultat,"Dades de l'asteroide a la data juliana = %f x= %f y= %f z= %f", t1,aval(pt,px,n,t1),aval(pt,py,n,t1),aval(pt,pz,n,t1));
	fclose(resultat);


	return 0;
}

