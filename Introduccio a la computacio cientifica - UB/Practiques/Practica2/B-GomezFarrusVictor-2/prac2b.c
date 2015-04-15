/* COGNOM1: Gomez COGNOM2: Farrus NOM: Victor DNI: 49184353A */
/*grup B, practica 2 part b*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prac2funs.c"

double aval(double *x, double *z, int n, double t);
void dif_dividides(double *x, double *y, int n);

/*retorna la data juliana corresponent a les 00 hores del dia passat*/
double datajuliana(int dia, int mes, int any){
    int a, m, y, d;
    double dataj;
    a = (14-mes)/12;
    m = mes+(12*a)-3;
    y = any+4800-a;
    d = dia + ((153*m+2)/5) +365*y +y/4 -y/100 +y/400 -32045;
    dataj= d-0.5;
    return dataj; 
}

int main(void) {
    int n, i, j; /*n,i,j serviran per iterar, n tambe servira per determinar el grau del polinomi interpolador*/
	int first_line;  /*first_line servira per trobar la primera linia on hem d'obtenir dades de l'arxiu */
    double t0,t1; /* t0, t1 serviran per calcular data juliana*/
	double t,x,y,z;  /*t,x,y,z serviran per obtenir temporalment dades del fitxer dades_apophis.dat*/
	double *pt,*px,*py,*pz; /* pt,px,py,pz serviran per acumular les dades temporals i si fos necessari operar amb elles*/
	FILE * dades, * result_file; /* dades sera l'arxiu dades_apophis.dat i result_file sera on guardarem els resultats*/
	
	/*obrim l'arxiu dades_apophis.dat per llegir i comprovem que l'operacio pugui ser efectuada*/
	dades = fopen ("dades_apophis.dat","r");
	if(dades==NULL){
		printf("Error obtenint les dades del fitxer \"dades_apophis.dat\"");
	}
	/*obrim l'arxiu result.txt per escriure, si no existeix es creara un de nou */
	result_file = fopen("result.txt","w");
    for(n=6;n<=15;n+=3){
    	/*posem els iteradors a 0*/
    	i=0;
    	j=0;
    	/*reservem memoria i comprovem que l'operacio pugui ser efectuada*/
    	pt = (double *)malloc( (n+1)*sizeof(double *));
    	px = (double *)malloc( (n+1)*sizeof(double *));
    	if(px == NULL || py == NULL){
       		printf("No hi ha suficent memoria");
       		exit(1);
    	} 
    	/*obtenim les dades de l'arxiu*/
    	while(fscanf(dades, "%lf %le %le %le", &t,&x,&y,&z)!=EOF) {
    		
    		if(i>=(414-n-1)){
    			pt[j]=t; 
				px[j]=x;
				j++;
			}
    		i++;
    	}
    	/*fem els calculs pertinents i guardem a l'arxiu*/
    	dif_dividides(pt,px,n);
    	fprintf(result_file,"n=%d\tt=%f\tpn(t)=%e\n", n,2462225.5f,aval(pt,px,n,2462225.5f));
    	/*alliberem memoria*/
    	free(pt);
    	free(px);
    	/*posicionem l'apuntador al principi del fitxer*/
    	rewind(dades); 	
	}
	/* polinomi de grau 7, reservem espai i comprovem que l'operacio pugui ser efectuada */
	n = 7;
	pt = (double *)malloc( (n+1)*sizeof(double *));
    px = (double *)malloc( (n+1)*sizeof(double *));
    py = (double *)malloc( (n+1)*sizeof(double *));
    pz = (double *)malloc( (n+1)*sizeof(double *));
    
    if(pt ==NULL || px == NULL || py == NULL || pz == NULL){
       printf("No hi ha suficent memoria");
       exit(1);
    } 
    
    t0 = 2453979.5f;
    /* Ryan Giggs - Centrecampista del Manchester United - 29/11/1973*/
    
    t1 = datajuliana(29,11,2020);
    /* posem els iteradors a 0 i escanejarem les linies que necesitem de dades_apophis.dat a partir de first_line */
    first_line  = (t1-t0)/20-3; /* primera linia a escanejar= linia desitjada -3 */
    i = 0; 
    j = 0;
    while((fscanf(dades, "%lf %le %le %le", &t,&x,&y,&z)!=EOF)&&i<=(first_line+7)) {
      /* es demana linia desitjada t-1=-3 fins a t a linia desitjada +4 (4 dades*/
      
      if(i>=first_line && i<=first_line+7){
      	/* per comprovar que agafem be la linia es poden utilitzar aquests prints orientatius
      	if(i == first_line+3){
      		printf("t-1 = %f\t line = %d\n",t,i);
      		printf("t   = %f\n",t1);
    		}else if(i == first_line+4){
          		printf("t+1 = %f\t line = %d\n",t,i);
    		}
    		*/
      	pt[j] = t;
      	px[j] = x;
      	py[j] = y;
      	pz[j] = z;
      	j++;
      }
      i++;
	}
	/*tanquem l'arxiu dades_apophis.dat*/
	fclose(dades);
	/* apliquem diferencies dividides i escrivim els resultats de la funcio aval a l'arxiu result.txt*/
	dif_dividides(pt,px,n);
	dif_dividides(pt,py,n);
	dif_dividides(pt,pz,n);
	fprintf(result_file,"Dades de l'asteroide apophis a la data juliana %f (29,11,2020):\nx=%e\ty=%e\tz=%e",t1,aval(pt,px,n,t1),aval(pt,py,n,t1),aval(pt,pz,n,t1));
	/* tanquem l'arxiu result.txt*/
	fclose(result_file);
	/*final del main*/
    return 0;
}
    
                        
