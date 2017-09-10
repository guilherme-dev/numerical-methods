#include <stdio.h>
#include <math.h>
#define E 0.0005

float fun(float x){
	// f(x) = x³ - 4x - 9
	return (x*x*x - 4*x - 9);
}

void  bisection(float *x, float a, float b, int *count){
	*x = (a + b)/2;
	++(*count);
	printf("Iteration no. %d X = %7.5f\n", *count, *x);
}

int main(){
	// count -> Counter, max -> Max iterations
	// xl and xu -> initial guess, xnew -> previous x, e -> given error
	int count = 0, max;  
	float x, xl, xu, xnew; 
	printf("\nEnter the values of xl, xu and maximum iterations:\n");
    scanf("%f %f  %d", &xl, &xu, &max);

    bisection(&x, xl, xu, &count);
    do {
    	if (fun(xl) * fun(x) < 0)
    		xu = x;
    	else
    		xl = x;
    	bisection(&xnew, xl, xu, &count);
    	if (fabs(xnew - x) < E){
    		printf("After %d iterations, root = %6.4f\n", count, xnew);
            return 0;
    	}
    	x = xnew;
    }while (count < max);
    printf("The solution does not converge or iterations are not sufficient");
    return 1;
}