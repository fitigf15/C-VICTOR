#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double datajuliana(int dia, int mes, int any){
    int a, m, y, d;
    double dataj;
    a = (14-mes)/12;
    m = ((mes+12)*a)-3;
    y = any+4800-a;
    d = dia + ((153*m+2)/5) +365*y +y/4 -y/100 +y/400 -32045;
    dataj= d-0.5;
    return dataj; 
}

int main(void) {

    double t,x,y,z;
    FILE * arxiu;
    arxiu = fopen ("dades_apophis.dat","w+");
    fscanf(arxiu, "%lf %le %le %le", &t,&x,&y,&z);
    fclose (arxiu);
    printf("%f %e %e %e\n", t,x,y,z);    
    //t = (double *)malloc( (n+1)*sizeof(double *));
    //ft = (double *)malloc( (n+1)*sizeof(double *));
    return 0;
}
    
                        
