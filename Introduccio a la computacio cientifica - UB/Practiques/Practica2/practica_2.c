#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void exit (int );
void dif_dividides(double*, double*, int);
double aval(double*, double*, int, double);
int main ( void ) {
	int n;//i
	double *x,*y;
	/*printf("Numero n de punts que vols escriure: ");
  	scanf("%d",&n);
  	*/
  	n=4;
  	x = (double*)malloc(n*sizeof(double*));
  	y = (double*)malloc(n*sizeof(double*));
	/*for(i=0; i<n; i++)
	{
	   	printf("\n\nValor de X%d: ",i);
	   	scanf("%f",&x[i]);
	   	printf("\n\nValor de f(X%d): ",i);
	   	scanf("%f",&y[i]);
	}*/
	
	x[0]=30.0;
	x[1]=40.0;
	x[2]=50.0;
	x[3]=60.0;
	y[0]=-9.5;
	y[1]=-15.4;
	y[2]=-21.9;
	y[3]=-33.6;
	dif_dividides(x,y,3);
	free(x);
	free(y);
	return 0;
}

void dif_dividides(double *x, double *y, int n){
	int i,j,k=0,m=3;//f,m;
	//double sum,p,u,temp;
	double **c;
	c = (double**)malloc(m*sizeof(double**));
	printf("%u\n",m*sizeof(double** ));
	for(i=0;i<m;i++){
		c[0][i]=y[i];
		printf("%f \n", c[0][i]);
	}

	

	
	for(i=1;i<n;i++)
	{
		k=i;
	    for(j=0;j<n-i;j++)
	    {
	    	c[i][j]=(c[i-1][j+1]-c[i-1][j])/(x[k]-x[j]);
	    	k++;
	    }
	}

	printf("\n_____________________________________________________\n");
	printf("\n  x(i)\t   y(i)\t    y1(i)    y2(i)    y3(i)    y4(i)");
	printf("\n_____________________________________________________\n");
	for(i=0;i<n;i++)
	{
		printf("\n %.3f",x[i]);
		for(j=0;j<n-i;j++)
		{
		 printf("   ");
		 printf(" %.3f",c[j][i]);
		}
		printf("\n");
	}

	/*
	while(k != 1){
		if(x[i]<p && p<x[i+1])
    		k=1;
   		else
    		i++;
	}

	f=i;
 
  	sum=0;
	for(i=0;i<n-1;i++){
		k=f;
   		temp=1;
   		for(j=0;j<i;j++){
   			temp = temp * (p - x[k]);
    		k++;
   		}
   		sum = sum + temp*(c[i][f]);
	}


	//printf("%u",sizeof(x)/sizeof(double));
	//printf("%f \n",sizeof(x));
	double c[sizeof(y)][sizeof(y)];
	int i,j,k=0;
	for(i=0; i<sizeof(y); i++){
		c[k][i]=y[i];
	}*/
		

}
double aval(double *x, double *z, int n, double t){
	return 0.f;
}
