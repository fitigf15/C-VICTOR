/*COGNOM1:Gomez COGNOM2:Farrus NOM:Victor DNI:49184353A*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*funcio per resoldre una Ax = b on A és una matriu amb 0's per sota de la diagonal*/
int resoltrisup (int n, double **A, double *b, double *x, double tol){
    int j, k;
    double resultat;
    	
    for(j = n-1; j>=0; j--){
        resultat = 0.f;
		x[j] = 0.f;
        if(fabs(A[j][j])<tol){
            return 1;
        }else{
            for(k = j+1; k<n; k++){
                resultat = resultat + A[j][k]*x[k];
            }
            resultat = b[j]-resultat;
            x[j] = resultat / A[j][j];
        }
    }
    return 0;

}

/*funcio per resoldre el producte d'una matriu per un vector*/
void prodMatVec(int n,double **A, double *x, double *y){
	int i, j;
	for(i=0;i<n;i++){/*columnes*/
		y[i] = 0.f;
		for(j=0; j<n;j++){/*files*/
			y[i] = y[i] + A[i][j]*x[j]; 
		}
	}
}

/*funcio per resoldre el producte de dos matrius (en aquest cas iguals)*/
void prodMatMat(int n, double **A, double **B, double **C){
	int i, j, k;
	for(i=0;i<n;i++){
		for(j=0; j<n;j++){
			C[i][j]= 0.f;
			for(k=0; k<n;k++){
				C[i][j] = C[i][j] + A[i][k] * B[k][j];
			}
		}
	}
}

