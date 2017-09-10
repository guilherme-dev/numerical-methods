#include "functions.h"

/***********************
 * Funcao adaptada de generateRandomDiag() para criar linhas do SL
 * N: tamanho do sistema linear
 * line: vetor para armazenar os valores da linha da matriz A. Deve ser alocado por quem chama a função.
 ***********************/
void generate_equation ( int N, double *line )
{
  if (!line)
    return;

  /* garante valor dominante para diagonal principal */
  // double fator = (k == 0) ? ((double)(nBandas-1)) : (0.0);

  double invRandMax = 1.0 / (double)RAND_MAX;
  int i;

  for (i=0; i < N; ++i)
  {
    line[i] = (double)rand() * invRandMax;
  }
}

double f (double x){
    return 4*(M_PI*M_PI)*(sin((2*M_PI)*x) + sin(2*M_PI*(M_PI-x)));
}



void create_linear_system (double **A, double *b, int n)
{
	int i, j; 

	for (i = 0; i < n; i++){
		printf("linha %d\n", i);
		for (j = 0; j < n; j++){
			printf("insira o coeficiente a[%d][%d]\n", i, j);
			scanf("%lf", &A[i][j]);
		}
		printf("insira o termo independente b[%d]\n", i);
		scanf("%lf", &b[i]);
	}
}