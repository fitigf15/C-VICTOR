#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prac2funs.c"
/* COGNOM1: Gomez COGNOM2: Farrus NOM: Victor DNI: 49184353A */
/* grup B, practica 2 part a */
double aval(double *x, double *z, int n, double t);
void dif_dividides(double *x, double *y, int n);

/* avalua la funcio f en el punt t */
double f(double t){
    double result;
    result = exp(sin(t)+cos(t)); 
    return result;
}

int main(void) {
    int n, i; /*n sera el grau del polinomi, i servira per iterar*/
    double t, pt, ft, er; /* t, fx, pn i er serviran per guardar i printar amb precisio el nodes t equidistants entre 0 i 2*PI, el resultat de f(t), el resultat del polinomi interpolador p(t) i l'error relatiu entre p(t) i f(t), sobretot en el cas d'error relatiu*/
	double *px, *py; /* els punters px i py serviran per guardar tots els nodes t i els seus respectius f(t)
    
    /*demanem i escanegem el grau del polinomi interpolador*/
    printf("Grau del polinomi:\n");
    scanf("%i", &n);
    /*alternativament, en comptes d'escanejar n, aquest exercici es podria fer amb una iteracio de n de l'estil:
    for(n=4;n<=6;n++){
		contingut de l'exercici
	}
    /*reservem memoria i comprovem que l'operacio pugui ser efectuada*/
	
    px = (double *)malloc( (n+1)*sizeof(double *));
    py = (double *)malloc( (n+1)*sizeof(double *));
    
    if(px == NULL || py == NULL){
       printf("No hi ha pru memoria");
       exit(1);
    } 
    /* volem que x tingui els n+1 primers nodes t equidistants entre 0 i 2*PI i que y tingui f(xi) en cada node i de x, no cal utilitzar la variable t en aquesta iteracio ja que es implicita */
    for(i=0;i<(n+1);i++){ 

    	px[i]=i*((2*acos(-1))/(1000)); /* t = i*((2*acos(-1))/(1000)) */
    	py[i]=f(px[i]); 
    }
	/* apliquem diferencies dvidides*/
    dif_dividides(px,py,n);
    /* printem una especie de capcelera de taula*/
    printf("\t_____________________________________________________________\n\n");
    printf("\t\tt\t\tf(t)\t\tPn(t)\t\ter(t)\n");
    printf("\t_____________________________________________________________\n\n");
    /* calculem t, pn(t), f(t), er(t) i ho printem en una linia seguint la forma de la taula que hem printat abans*/
    for(i=0;i<=20;i++){
        t = i *(2*acos(-1))/(1000);
    	pt = aval(px,py,n,t);
    	ft = f(t);
    	er = (fabs(pt-ft))/ft;
    	printf("\t%e \t%e \t%e \t%e\n",t,ft,pt,er);
    }
    /*final del main*/
    return 0;
    
}
	
    
    
                        
