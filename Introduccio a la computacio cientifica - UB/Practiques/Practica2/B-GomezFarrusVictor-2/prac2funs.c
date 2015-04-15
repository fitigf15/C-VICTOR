/* COGNOM1: Gomez COGNOM2: Farrus NOM: Victor DNI: 49184353A */
/*grup B, practica 2 funcions*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* donats x = {x0,...,xn} (nodes) i y={f(x0),...,f(xn)} (valors d'una funcio en
aquests nodes), retorna en el mateix vector y les diferencies dividides de Newton*/
void dif_dividides(double *x, double *y, int n){
    int i,j; /* i, k serviran per iterar */
    for(i=1;i<=n;i++){
        /*printf("y[%d]:\n",i );*/
      for(j=n;j>=i;j--){
        y[j]=(y[j]-y[j-1])/(x[j]-x[j-i]);
        /*printf("y[%d] = %f \n",j, y[j]);*/
      }
      /*printf("guardem a y[%d] = %f \n",i, y[i]);*/
    }
}
/*donats el vector x (dels nodes) i el vector z que conte les diferencies dividides, avalua
el polinomi interpolador en el punt t (algorisme de Horner) */
double aval(double *x, double *z, int n, double t){
    double result; /* result emmagatzema el resultat de l'avaluacio del polinomi interpolador en el punt t*/
    int i; /* i servira per iterar*/
    result = z[n];
    for(i=n-1; i>=0; i--){
        result = result*(t-x[i]) + z[i];
    }
    return result;
}
