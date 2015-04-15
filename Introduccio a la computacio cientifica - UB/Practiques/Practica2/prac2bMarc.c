/*COGNOM1:Guell COGNOM2:Jimenez NOM:Marc DNI:47959864B*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prac2funs.c"

/*a partir d'una formula donada per el professor, obtenim la data julinana a partir d'una data georgina*/
double datajuliana(int dia, int mes, int any){
	int a, m, y, d;
	double D;
	a = (14-mes)/12;
	m = ((mes+12)*a)-3;
	y = any+4800-a;
	d = dia + ((153*m+2)/5);
	d= d+365*y;
	d= d+y/4;
	d= d-y/100;
	d= d+y/400;
	d= d-32045;
	D= d-0.5;
	return D;	
}

double aval(double *x, double *z, int n, double t);/*es fa referencia a la funció aval*/


void dif_dividides(double *x, double *y, int n);/*es fa referencia a la funció dif_dividides*/

int main(void) {
    int n, i,h,count,count2,linia, linia2;
    double *x, *y, *t, *z, val1, val2, val3, val4, pn, data;

    /*s'obre el fitxer on es té totes les dades*/
    FILE *fitxer = fopen("dades_apophis.dat","r");
    FILE *resultat = fopen("resultats.dat","w");
    if(fitxer==NULL){ /*es comprova que el fitxer*/
    	printf("Error a l'obrir el fitxer");
    }
    
    /*es fa un bucle per avaluar el polinomi interpolador en les distintes n's*/
    for(i=6;i<=15;i+=3){  
	
	/*s'assigna un tamany de memoria per les variables x i y*/
	x = (double *)malloc( (i+1)*sizeof(double *)); 
	y = (double *)malloc( (i+1)*sizeof(double *));
	
	/*es mira que no sigui NULL el valor obtingut*/
	if(x == NULL || y == NULL){
	    printf("No hi ha prou memoria");
	    exit(1);
	} 
    
	h = 414-(i+1); /*es calula en quina línia s'ha de començar a obtenir les variables */
	
	/*contadors per saber en quina línia s'està llegint*/
	count=0;
	count2=0;
	
	/*es llegeix cada línia i es guarden les variables de t,x,y,z en val1,val2... fins l'última línia*/
	while ((fscanf(fitxer, "%le %le %le %le\n", &val1,&val2,&val3,&val4)) != EOF ){ 
	  if(count>=h){ /*quan s'arriba a la línia es guarden els valors de t i x del fitxer en l'array x i y*/
	    x[count2]=val1;
	    y[count2]=val2;
	    count2++;
	    printf("%d\n",count);
	  }
	  count++;
	}
	printf("end");

	dif_dividides(x,y,i); /*obtenim el polinomi interpolador*/
	pn = aval(x,y,i,2462225.5); /*s'avalua el polinomi interpolador en el punt 2462225.5 */
	
	fprintf(resultat,"Per a n=%i, el resultat en avaluar el polinomi en t=246225.5 es %f\n", i,pn);
	
	/*s'esborra la memoria de les variables x i y per tornar-les a omplir i es començar a llegir el fitxer des del principi*/
	free(x);
	free(y);
	rewind(fitxer);
    }
	
	
    /*Jugador Filipe Luis del Chelsea, va neixer el 09/08/1985*/
    
    n=7;
    
      /*s'assigna un tamany de memoria per les variables t, x, y i z*/
    t = (double *)malloc( (n+1)*sizeof(double *));
    x = (double *)malloc( (n+1)*sizeof(double *));
    y = (double *)malloc( (n+1)*sizeof(double *));
    z = (double *)malloc( (n+1)*sizeof(double *));
	
        data = datajuliana(28,1,2020); /*es crida a la funció datajuliana */
    
    /*es calcula en quina línia es podrià trobar la data del jugador*/
    linia = ((data-2453979.5)/20)-3;/*4 dies per sota de la data del jugador*/
    linia2 = ((data-2453979.5)/20)+4;/*4 dies pe sobre de la dara del jugador*/
    
    count=0;
    count2=0;
    
    while ((fscanf(fitxer, "%le %le %le %le\n", &val1,&val2,&val3,&val4)) != EOF ){ 
    	if(count>=linia && count<=linia2){/*obtenim els valors de les varibles del fitxer de les 8 línies i es guarden en 4 arrays*/
    		t[count2]=val1;
    		x[count2]=val2;
    		y[count2]=val3;
    		z[count2]=val4;
    		count2++;
	}
		count++;
    }
    /*es crea un fitxer anomenat resultats*/
    
    fprintf(resultat,"En la data %f l\'asteroide estara en les cordenades: ",data);
    
    /*es calcula els polinomis interpoladors de x,y i z i s'avalua en la data juliana del jugador i es guarda en el fitxer creat*/
    
    dif_dividides(t,x,n);
    pn = aval(t,x,n,data);
    
    fprintf(resultat,"x:%f ",pn);
    
    dif_dividides(t,y,n);
    pn = aval(t,y,n,data);
    
    fprintf(resultat,"y:%f ",pn);
    
    dif_dividides(t,z,n);
    pn = aval(t,z,n,data);
    
    fprintf(resultat,"z:%f ",pn);

    return 0;
    
}
