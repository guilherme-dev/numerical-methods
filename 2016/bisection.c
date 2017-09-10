#include <stdio.h>
#include <math.h>

// 1- Choose xl e xu as the initial guess such that f(xl)*f(xu) < 0
// 2- xm = (xl + xu)/2
// 3- Find f(xl)*f(xm)
// if f(xl)*f(xm) < 0 then xl = xl; xu = xm;
// if f(xl)*f(xm) > 0 then xu = xu; xl = xm;
// if f(xl)*f(xm) == 0 then root = xm; Very rare
// 4- Find xm (step 2)
// 5- Find |Ea| = |(xm_new - xm_old)/xm_new)|*100
// 6- Check if |Ea| < Es --> Specified

 int main(){

 	// xl and xu: starting points
 	// xm: medium point
 	// ea: aproximate error
 	// es: given error defined 6365858

 	float f(float x){
 		return (x*x*x - 4*x - 9); 
 	}

 	float result, xl, xu, xm, ea, es;
 	int cont = 0;
 	int iteracoes;

 	printf("Insira os pontos iniciais:\n");
 	scanf("%f %f", &xl, &xu);

 	printf("Numero de interacoes:\n");
 	scanf("%d", &iteracoes);

 	result = f(xl) * f(xm);
 	if( result < 0 ){
	 	while (cont < iteracoes){
	 		xm = (xl - xu)/2;
	 		result = f(xl) * f(xm);
	 		if ( result < 0 )
	 			xu = xm;
	 		else 
	 			xl = xm;
	 		cont++;
		}
 	}
 	printf("xl: %.4f - xu: %.4f - xm: %.4f \n", xl, xu, xm);


    return 0;
 }
