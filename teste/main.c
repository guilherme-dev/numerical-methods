#include "functions.h"

int main(int argc, char const *argv[])
{
	/* code */
	double **A, *b;
	int i, n = 5;

		

	// printf("Insira o tamanho do SL\n");
	// scanf("%d", &n);
	// if (n < 3)
		// return -1;

	
	A = (double **) malloc (n * sizeof(double*));
	b = (double *) malloc(n * sizeof(double));
	if (!A || !b)
		return -1;	
	for (i = 0; i < n; i++){
		A[i] = (double *) malloc(n * sizeof(double));
		// generate_equation(n, A[i]);
	}

	//Cria valores do vetor b
    // for (i = 0; i < n; i++){
    //     b[i] = f((i*M_PI)/n);
    // }

    // for (i = 0; i < n; i++){
    //     for (j = 0; j < n; j++){
    //         printf("%.10g ", A[i][j]);
    //     }
    //     printf("%.5g\n", b[i]);
    // }

	create_linear_system(A, b, n);
	return 0;
}