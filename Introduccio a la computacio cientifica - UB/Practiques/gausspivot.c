int gausspivot(int n, double **A, double *v, double tol){
	int j,k,l;
	double m;

	for(k=0;k<n;k++){
		if(fabs(A[k][k]) ==0){
			return 1;
		}
		if(k>0){
			for(l=0;l<k;l++){
				A[k][j]=0;
			}
		}
		for(l=k+1;l<n;l++){
			m= A[l][k]/A[k][k];
			if(fabs(m)<tol){
				m=0;
			}
			for(j=k;j<n;j++){ 
				A[l][j]+=-m*A[k][j];
			}	
			v[l]=m*v[k];
		}	

	}

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