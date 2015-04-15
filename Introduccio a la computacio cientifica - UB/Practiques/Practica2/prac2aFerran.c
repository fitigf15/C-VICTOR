#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prac2funs.c"

void dif_dividides(double *x, double *y, int n);
double aval(double *x, double *z, int n, double t);

double f(double t){
	double funcio;
	funcio = exp(sin(t)+cos(t));
	return funcio;
}

int main(void){
	int n,i;
	double t, ft, pnt, ert, *x, *y;

	printf("Escriu el grau del polinomi: \n");
	scanf("%i", &n);

	x = (double*)malloc((n+1)*sizeof(double*));
	y = (double*)malloc((n+1)*sizeof(double*));

	if (x==NULL || y==NULL){
		printf("No hi ha prou memòria");
		exit(1);
	}

	for(i=0;i<n+1;i++){
		x[i]=i*((2*acos(-1))/1000);
		y[i]=f(x[i]);
	}

	dif_dividides(x,y,n);

	for (i=0;i<1000;i++){
		t = i*((2*acos(-1))/1000);
		pnt = aval(x,y,n,t);
		ft = f(t);
		ert = fabs((pnt-ft)/ft);
		printf("%e %e %e %e\n",t, ft, pnt, ert);
	}
	return 0;
}
