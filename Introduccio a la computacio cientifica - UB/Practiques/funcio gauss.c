/* triangular superior */
int gauss(double **A, double **L, int n, double tol){
	int k , l, j;
	double  Mul;

	for(k=0;k<n;k++){
		if(fabs(A[k][k]) ==0){
			return 1;
		}		
		for(l= k+1; l<n;l++){
			Mul = -A[l][k]/A[k][k];
			if(fabs(Mul)<tol){
				Mul=0;
			}
			L[l][k]=-Mul;  /* posem a la matriu L el multiplicador */

			for(j=k;j<n;j++){  /*Apliquem les operacions a les files de la matriu A*/
				A[l][j]+=Mul*A[k][j];
			}	
		}
	}
	return 0;
}

/* Triangular Inferior */
int gauss(double **A, double **L, int n, double tol){
	int k , l, j;
	double  Mul;

	for(k=n-1;k>0;k--){
		if(fabs(A[k][k]) == 0){
			return 1;
		}		
		for(l=k-1; l>=0;l--){
			Mul = -A[l][k]/A[k][k];
			if(fabs(Mul)<tol){
				Mul=0;
			}

			for(j=k;j>=0;j--){  /*Apliquem les operacions a les files de la matriu A*/
				A[l][j]+=Mul*A[k][j];
			}	
		}
	}
	return 0;
}
