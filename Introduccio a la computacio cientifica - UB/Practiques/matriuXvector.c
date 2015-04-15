/*C\` alcul del producte d'una matriu per un vector usant mem \` oria din \` amica */
#include <stdio.h>
#include <stdlib.h>
int main(void){
	int n, m, i, j;
	float **a, *u, *v;

	printf("Doneu les dimensions de la matriu, (n,m)\n");
	scanf("%d %d", &n ,&m);

	a = (float **)malloc( n*sizeof(float *));
	if ( a==NULL){
		printf("No hi ha prou memoria");
		exit(1);
	}

	for (i=0; i<n;i++){
		a[i] = (float*)malloc(m*sizeof(float));
		if (a[i]==NULL){
			printf("No hi ha prou memoria");
			exit(2);
		}
	}
	u=(float*)malloc(m*sizeof(float));
	v=(float*)malloc(m*sizeof(float));
	if(u==NULL||v==NULL){
		printf("No hi ha prou memoria");
		exit(3);
	}
	printf("Doneu els (%d x %d) elements de la matriu A \n",n,m);
	for(i = 0; i<n; i++){
		for(j=0;j<m;j++){
			scanf("%f",&a[i][j]);
		}
	}
	printf("Doneu els %d elements del vector u \n", m);
	for (i = 0; i<m;i++){
		scanf("%f", &u[i]);
	}
	for(i=0;i<n;i++){
		v[i]=0.f;
		printf("V[ %d ] :\n",i);
		for(j=0;j<m;j++){
			v[i] += a[i][j]*u[j];
			printf(" %16.7e", u[j]);
			printf("   x");
			printf(" %16.7e", a[i][j]);
			printf("   =");
			printf(" %16.7e",v[i]);
			printf("\n");
			
		}
		printf("\n");
	}

	printf("El producte de la matriu A = \n");

	for(i = 0; i<n;i++){
		for(j=0;j<m;j++){
			printf(" %16.e ", a[i][j]);
		}
		printf("\n");
	}

	printf("pel vector u = \n");

	for (i =0;i<m;i++){
		printf(" %16.7e \n", u[i]);
	}

	printf("Ens dona v = \n");

	for ( i=0; i<n;i++)
		printf(" %16.7e \n", v[i]);

	for ( i=0; i<n;i++)
		free (a[i]);

	free(a);
	free(u);
	free(v);
	return 0;
}