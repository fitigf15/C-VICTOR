/*C\` alcul del producte d'una matriu per un vector usant mem \` oria din \` amica */
#include <stdio.h>
#include <stdlib.h>
int main(void){
	int n, m, i, j, det;
	float **a, **trans, **inversa;

	//printf("Doneu les dimensions de la matriu, (n,m)\n");
	//scanf("%d %d", &n ,&m);
	n = 3 
	m = 3
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
	det =  a[0][0]*a[1][1]*a[2][2]
	+a[2][0]*a[2][1]*a[1][2]
	+a[1][0]*a[2][1]*a[0][3]
	-a[2][0]*a[1][1]*a[0][2]
	-a[1][0]*a[0][1]*a[2][2]
	-a[0][0]*a[2][1]*a[1][2]

	for ( i=0; i<n;i++)
		free (a[i]);
		free (trans[i]);
		free (inversa[i]);

	free(a);
	free(trans);
	free(inversa);
	return 0;
}