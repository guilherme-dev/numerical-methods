#include <stdio.h>
#include <math.h>
#define E 0.0005

float fun(float x){
	return (x*x + x -6); //f(x) = x² - x + 6
}

float fi(float x){
	return x + (-1)*fun(x);
}

void main(){

	int cont = 1, max;
	float x1, x;
	printf("\nEnter the values of x0 and maximum iterations:\n");
    scanf("%f %d", &x, &max);

    do{
    	x1 = fi(x);
    	if (fabs(x1 - x) < E){
    		printf("After %d iterations, root = %6.4f\n", cont, x1);
            break;
    	}
    	++cont;
    	x = x1;
    }while(cont < max);
}