/*COGNOM1:Gomez COGNOM2:Farrus NOM:Victor DNI:49184353A*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prac1funs.c"

void prodMatMat(int n, double **A, double **B, double **C); /*es declara la funcio prodMatMat*/

int resoltrisup (int n, double **A, double *b, double *x, double tol); /*es declara la funcio resoltrisup*/

int inversaA(int n, double **A, double **B, double tol){
	int r, i, j, dfila, res;
	double pivot, *aux, m, *b, *x, **C;
	
	/*s'assigna un tamany de memoria per les variables b,x i C*/
	b = (double* )malloc(n*sizeof(double)); 
	x = (double* )malloc(n*sizeof(double));
	
	/*es mira que no sigui NULL el valor obtingut*/
	if(b == NULL || x == NULL){
		printf("No hi ha pru memoria");
		exit(3);
	}
	
	C = (double **)malloc( n*sizeof(double *));
	if(C == NULL ){
	    printf("No hi ha pru memoria");
	    exit(1);
	} 
	
	for (i = 0; i< n; i++){
	    C[i] = (double * )malloc(n*sizeof(double));
	    if(C[i] == NULL){
			printf("No hi ha pru memoria");
			exit(2);
	    }
	}
	
	/*es fa una copia de la matriu A en la matriu C, ja que posteriorment necesitarem A, pero aquesta estara  modificada.*/
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			C[i][j] = A[i][j];
		}
	}
	
	for(r=0; r<n-1; r++){
		dfila=r; 
		pivot= fabs(A[r][r]);
		/*Busca el max de cada fila, i si troba un mes gran que el primer, canvia el valor de la variable dfila i pivot.*/
		for(i=r; i<n; i++){
			if(fabs(A[i][r])>pivot){ 
				dfila = i;
				pivot = fabs(A[i][r]);
			}
		}
		/*Fa el canvi de files, si el valor de les variables s'han modificat*/
		if(dfila != r){
			aux = A[r];
			A[r] = A[dfila];
			A[dfila] = aux;      
		  
			aux = B[r];
			B[r] = B[dfila];
			B[dfila] = aux; 
		}
		
		/*Fa els calculs i en el cas de la matriu A, posa 0 per sota de la diagonal transformant-la en triangular superior.*/
		for(i = r+1; i<n; i++){
			/*comprova que el primer valor de la diagonal sigui mes gran que la tolerancia, si no es el cas retorna un 1.*/
			if(fabs(A[r][r])<tol){
				return 1;
			/*per altre banda, es busca el valor de m, que  esta la posicio on es vol posar un 0, dividit per el valor de la diagonal que estigui per sobre*/
			}else{
				m = A[i][r]/A[r][r];
				A[i][r] = 0.f;
				for(j=r+1; j<n; j++){
					A[i][j] = A[i][j] - m*A[r][j];
				}
				for(j=0; j<n; j++){
					B[i][j] = B[i][j] - m*B[r][j];
				}
			}
		} 
	}
	for(i=0; i<n; i++){
		/*es copien tants cops com n, les columnes de B en b, per trobar les x, que a la vegada son els valors de la columna de la matriu inversa*/
		for(j=0; j<n; j++){
			b[j] = B[j][i];
		}
		/*es crida la funcio resoltrisup per trobar les x*/
		res = resoltrisup (n,A,b,x,tol);
		if(res == 1){
			return 1;
		}else{
			/*com a la sortida s'utilitza B, es copien a B els resultats que s'obtinguin de resoltrisup*/
			for(j=0; j<n; j++){
				B[j][i] = x[j];
			}
		}
	}
	/*per comprovar que la matriu obtinguda realment sigui la matriu inversa, es fa el producte de la matriu A per la seva inversa (en aquest cas B) i el resultat ha de ser la matriu identitat*/
	prodMatMat(n,C,B,A);
	
	
	return 0;
	
}

int main(void) {
    int n, i, j, res;
    double **A, **B, tol;
    printf("Doneu les dimensions de les matriu quadrada A, (n,n) = \n");
    scanf("%d", &n);
	/*s'assigna un tamany de memoria per les variables A i B*/
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
	
    printf("Doneu els (%d %d) elements de la matriu A \n", n , n);
    
    for(i = 0; i< n; i++){
        for(j = 0 ; j<n; j++){
            scanf(" %lf", &A[i][j]);
        }
    }
	
	B = (double **)malloc( n*sizeof(double *));
    if(B == NULL ){
        printf("No hi ha pru memoria");
        exit(1);
    } 
    
    for (i = 0; i< n; i++){
        B[i] = (double * )malloc(n*sizeof(double));
        if(B[i] == NULL){
            printf("No hi ha pru memoria");
            exit(2);
        }
    }
    /*S'omple la matiru B, amb els valor de la matriu identitat*/
	for(i = 0; i<n; i++){
		for(j = 0; j<n; j++){
			if(i == j){
				B[i][j] = 1;
			}else{
				B[i][j] = 0;
			}
		}
	}
	
	printf("Tolerancia:\n");
    
    scanf(" %lf", &tol);
	/*es crida a la funcio inversa A*/
	res = inversaA(n,A,B,tol);
	/*es comprova que les funcions s'han realitzat amb exit i es mostra per pantalla.*/
	if(res == 0){
		for(i=0; i<n; i++){
			printf("\n");
			for(j=0; j<n; j++){
				printf("B[%d][%d]=%f ", i, j, B[i][j]);
			}
		}
		for(i=0; i<n; i++){
			printf("\n");
			for(j=0; j<n; j++){
				printf("C[%d][%d]=%f", i ,j,A[i][j]);
			}
		}
	}else{
		printf("No es pot resoldre.\n");
	}
   
}
    
