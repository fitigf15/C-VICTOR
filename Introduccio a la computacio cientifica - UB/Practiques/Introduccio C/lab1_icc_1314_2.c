/* Calcul d'una successio en precisio simple
* es llegeixen a, b, x0 */
# include <stdio .h>
# include <math .h>
void exit (int );
int main ( void ) {
	int n, k;
	float a, b, x0 , y0 , x1 , y1 , t, aux0 , aux1 ;
	k = scanf ("%f %f %f" ,&a ,&b ,& x0 );
	aux0 = x0 / a;
	if ( fabs ( aux0 ) > 1.){
		printf ("No es  pot  fer l'arrel   quadrada \n");
		exit (1);
	}
	y0 = b* sqrt (1. f - aux0 * aux0 );
	aux1 = y0 / b;
	printf ("%3s%18s\n","#n","t");
	t = aux0 * aux0 + aux1 * aux1 ;
	printf ("%3d%18.6e\n", 0, t);
	for (n = 1; n <= 30; n++) {
		aux0 = x0 / a;
		aux1 = y0 / b;
		x1 = 2.f*x0*y0 / b;
		y1 = aux0 * aux0 - aux1 * aux1 ;
		aux0 = x1 / a;
		aux1 = y1 / b;
		t = aux0 * aux0 + aux1 * aux1 ;
		printf ("%3d %18.6 e\n", n, t);
		x0 = x1;
		y0 = y1;
	}
	return 0;
}