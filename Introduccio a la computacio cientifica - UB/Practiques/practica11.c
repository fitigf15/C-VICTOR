#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*C\` alcul del producte d'una matriu per un vector usant mem \` oria din \` amica */
int main(void){

	return 0;
}


/*Funcio per resoldre el sistema d'equacions Ax=b quan A es triangular superior*/
/* n = dimensio */
/* A = matriu */
/* x = vector multiplicador de la matriu */
/* b = vector resultant */
int resoltrisup (int n, double **A, double *b, double *x, double tol){
    int i,j;
    for(i=n-1;i=0;i--){
        if(fabs(A[i][i]<tol)){
            return 1;
        }
    }
    for(j=n-1;j=0;j--){
    	for(i=j;i=n-1;i++){

    	}
        x[j]=1/A[i][j];
	}
 
    return 0;
}