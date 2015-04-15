/*COGNOM1:Gomez COGNOM2:Farrus NOM:Victor DNI:49184353A*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prac1funs.c"

int resoltrisup (int n, double **A, double *b, double *x, double tol); /*es declara funcio resoltrisup*/

void prodMatVec(int n,double **A, double *x, double *y);/*es declara la funcio prodMatVec*/

int gausspivot(int n, double **A, double *v, double tol){
	int r,i,j,dfila,res;
	double pivot, *aux ,m, *x;
	/*s'assigna un tamany de memoria per la variable x*/
	x = (double* )malloc(n*sizeof(double));
	/*es mira que no sigui NULL el valor obtingut*/
	if(x == NULL){
		printf("No hi ha prou memoria");
		exit(3);
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

			m = v[r];
			v[r] = v[dfila];
			v[dfila] = m;
		}
		/*Fa els calculs i en el cas de la matriu A, posa 0 per sota de la diagonal.*/
		for(i = r+1; i<n; i++){
			/*comprova que el primer valor de la diagonal sigui mes gran que la tolerancia, si no es el cas retorna un 1.*/
			if(fabs(A[r][r])<tol){
				return 1;
			/*es busca el valor de m, que  es la posicio on es vol posar un 0, dividit per el valor de la diagonal que estigui per sobre*/
			}else{
				m = A[i][r]/A[r][r];
				A[i][r] = 0.f;
				for(j=r+1; j<n; j++){
					A[i][j] = A[i][j] - m*A[r][j];
				}
				/*en el cas de la matriu v, es fa el mateix que en el anterior pas, pero nomes en una posicio, ja que es una matriu nx1 */
				v[i] = v[i]-m*v[r];
			}
		} 
	}
	/*es crida la funcio resoltrisup per trobar les x*/
	res = resoltrisup(n, A, v, x, tol);
	for(i=0; i<n; i++){
		v[i] = x[i];
	}
	if(res == 1){
		return 1;
	}else{
		return 0;
	}
}

int main(void) {
    int n, i, j, res;
    double **A, *b, tol, *y, *v;
    printf("Doneu les dimensions de les matriu quadrada A, (n,n) = \n");
    scanf("%d", &n);
	
	/*s'assigna un tamany de memoria per les variables A i b, y i v*/
	
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
    
    y = (double* )malloc(n*sizeof(double));
    b = (double* )malloc(n*sizeof(double));
    v = (double* )malloc(n*sizeof(double));
    
    if(b == NULL || y == NULL || v == NULL){
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

    for(i = 0; i<n; i++)
        scanf(" %lf", &b[i]);

    printf("Tolerancia:\n");
    
    scanf(" %lf", &tol);
    
	/*es crida a la funcio gausspivot*/
    res = gausspivot(n,A,b,tol);
	/*es comprova que les funcions s'han realitzat amb exit i es mostra per pantalla.*/
    if(res == 1){
		printf("No es pot resoldre.\n");
    }else{
        for(i = 0; i<n; i++){
            printf("x[%i]: %e ", i,b[i]);
        }
	/*es crida a la funcio prodMatVec, per trobar la matriu y*/
	prodMatVec(n,A,b,y);
	printf("\n");
	for(j = 0; j<n; j++){
	    printf("y[%i]: %e ", j,y[i]);
    }
	/*es calcula i es motra per pantalla la bondat ||Ax-b||*/
	double bondat = 0.;
	double count = 0.;
	for(i = 0; i<n; i++){
	    bondat=y[i]-v[i];
	    bondat = pow(bondat,2);
	    count = count + bondat;
    }
	printf("\nEl valor de ||Ax-b|| com a indicador de la bondat es: %e\n", sqrt(count));
    }
    
    
}
