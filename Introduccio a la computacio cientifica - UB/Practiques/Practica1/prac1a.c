/*COGNOM1:Gomez COGNOM2:Farrus NOM:Victor DNI:49184353A*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prac1funs.c"

int resoltrisup (int n, double **A, double *b, double *x, double tol); /*es declara funcio resoltrisup*/

void prodMatVec(int n,double **A, double *x, double *y);/*es declara la funcio prodMatVec*/


int main(void) {
    int n, i, j, res;
    double **A, *b, *x, *y, tol;
	
    printf("Doneu les dimensions de les matriu quadrada A, (n,n) = \n");
    scanf("%d", &n);
	
	/*s'assigna un tamany de memoria per les variables A,b,x i y*/
    A = (double **)malloc( n*sizeof(double *));
	/*es mira que no sigui NULL el valor obtingut*/
    if(A == NULL ){
        printf("No hi ha pru memoria");
        exit(1);
    } 
    
    for (i = 0; i< n; i++){
        A[i] = (double * )malloc(n*sizeof(double));
        if(A[i] == NULL){
            printf("No hi ha pru memoria");
            exit(2);
        }
    }
    
    x = (double* )malloc(n*sizeof(double));
    b = (double* )malloc(n*sizeof(double));
	y = (double* )malloc(n*sizeof(double));
    
    if(x == NULL || b == NULL || y == NULL){
        printf("No hi ha pru memoria");
        exit(3);
    }
    
    printf("Doneu els (%d %d) elements de la matriu A \n", n , n);
    
    for(i = 0; i< n; i++){
        for(j = 0 ; j<n; j++){
            scanf(" %lf", &A[i][j]);
        }
    }
    
    printf("Doneu els %d elements de vector b \n", n);

    for(i = 0; i<n; i++){
        scanf(" %lf", &b[i]);
	}
    printf("Tolerancia:\n");
    
    scanf(" %lf", &tol);
    
	/*es crida a la funcio resoltrisup*/
    res = resoltrisup(n, A, b, x, tol);
	/*es comprova que les funcions s'han realitzat amb exit i es mostra per pantalla.*/
    if(res == 1){
      printf("No es pot resoldre.\n");
    }else{
		
        for(i = 0; i<n; i++){
            printf("x[%i]: %e ", i,x[i]);
        }
		/*es crida a la funció prodMatVec, per trobar la matriu y*/
		prodMatVec(n,A,x,y);
		printf("\n");
		
		for(i = 0; i<n; i++){
			printf("y[%i]: %e ", i,y[i]);
        }
		/*es calcula i es motra per pantalla la bondat ||Ax-b||*/
		double bondat = 0.;
		double count = 0.;
		for(i = 0; i<n; i++){
			bondat=y[i]-x[i];
			bondat = pow(bondat,2);
			count = count + bondat;
        }
		printf("\nEl valor de ||Ax-b|| com a indicador de la bondat es: %e\n", sqrt(count));
    }
}
