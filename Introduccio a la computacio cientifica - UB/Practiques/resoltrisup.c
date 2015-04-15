/* COGNOM1 : Lorenzo COGNOM2 : Català NOM : Ferran DNI : 47958477-G */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Funció per resoldre el producte Ax=b quan la matriu A és triangular superior*/
/*n = dimensió = int*/
/*A= matriu = A[i][j]*/
/*x= vector pel que multipliquem la matriu = null*/
/*b= vector resultant = b[i]*/
int resoltrisup (int n, double **A, double *b, double *x, double tol){
    int i,j,k;

	for(i=n-1;(i=0);i--){
		for(j=n-1;(j=0);j--){
			if(fabs(A[i][j]<tol)){
				A[i][j] = 0;
			}
		}
	}

	for(i=1;i<n;i++){
		for(j=0;j<i;j++){
			if(fabs(A[i][j])>0.f){
				return 1;
			}
		}
	}

    for (j= n-1; j>=0;j--){
	  	x[j]=0.f;
	  	for(k=j+1;k<n;k++){
	    	x[j]+=(A[j][k]*x[k]);
	  	}
	x[j] = 1/A[j][j]*(b[j]-x[j]);
	}
	printf("El vector x resultant sera:\n");
	for(i=0;i<n;i++){
		printf("x[%d] = %f\n", i, x[i]);			
	}
    return 0;
}



int main(void){
	int n, i, j, res;
	double **A, *b, *x, tol;

	printf("Doneu la dimensio de la matriu (n)\n");
	scanf("%d", &n);

	A = (double **)malloc( n*sizeof(double *));
	if ( A==NULL){
		printf("No hi ha prou memoria");
		exit(1);
	}

	for (i=0; i<n;i++){
		A[i] = (double*)malloc(n*sizeof(double));
		if (A[i]==NULL){
			printf("No hi ha prou memoria");
			exit(2);
		}
	}
	b=(double*)malloc(n*sizeof(double));
	x=(double*)malloc(n*sizeof(double));
	if(b==NULL||x==NULL){
		printf("No hi ha prou memoria");
		exit(3);
	}
	printf("Doneu els (%d x %d) elements de la matriu A \n",n,n);
	for(i = 0; i<n; i++){
		for(j=0;j<n;j++){
			scanf("%lf",&A[i][j]);
		}
	}
	printf("Doneu el valor de la tolerancia\n");
	scanf("%lf", &tol);
	printf("Doneu els %d elements del vector b \n", n);

	for (i = 0; i<n;i++){
		scanf("%lf", &b[i]);
	}

	for(i=0;i<n;i++){
		x[i]=0.f;
	}
	res = resoltrisup(n, A, b, x, tol);
	printf("%d\n", res);
	return 0;
}