#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void create_linear_system (double **A, double *b, int n)
{
	int i, j; 

	for (i = 0; i < n; i++)
	{
		printf("linha %d\n", i);
		for (j = 0; j < n; j++)
		{
			printf("insira o coeficiente a[%d][%d]\n", i, j);
			scanf("%lf", &A[i][j]);
		}
		printf("insira o termo independente b[%d]\n", i);
		scanf("%lf", &b[i]);
	}
}

void print_matrix (double **A, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			printf("%.17g ", A[i][j]);
		printf("\n");
	}
}

void print_vector (double *b, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%.17g ", b[i]);
	}
	printf("\n");
}

void swap_lines (double **A, double *b, int n, int k, int l)
{
	double aux;
	int j;
	for (j = 0; j < n; ++j)
	{
		aux = A[k][j];
		A[k][j] = A[l][j];
		A[l][j] = aux;
	}
	aux = b[k];
	b[k] = b[l];
	b[l] = aux;
	printf("Trocou linhas %d -> %d\n", k, l);
}

int main(int argc, char const *argv[])
{
	int i, j, k, l, n;
	double **A, *b, *x;
	double maior, m, soma;

	printf("Digite o n:\n");
	scanf("%d", &n);

	b = (double *) malloc (n * sizeof(double));
	x = (double *) malloc (n * sizeof(double));
	A = (double **) malloc (n * sizeof(double *));
	for (i = 0; i < n; ++i)
		A[i] = (double *) malloc (n * sizeof(double));
	if (!b || !x || !A)
		exit(-1);
	printf("Alocadas estruturas\n");
	create_linear_system(A, b, n);
	print_matrix(A, n);
	print_vector(b, n);

	
	for (k = 0; k < n - 1; ++k)
	{
		//Pivotamento Parcial
		maior = fabs(A[k][k]);
		printf("maior :%.17g\n", maior);
		l = k;
		for (i = k; i < n; ++i){
			if (fabs(A[i][k]) > maior)
			{
				maior = fabs(A[i][k]);
				l = i;
			}
		}
		printf("l: %d\n", l);
		if (l != k) 
			swap_lines(A, b, n, k, l);
		//Eliminacao de Gauss
		for (i = k + 1; i < n; ++i)
		{
			printf("A[k][k]: %.17g\n", A[k][k]);
			m = A[i][k] / A[k][k];
			for (j = 0; j < n; ++j)
			{
				A[i][j] = A[i][j] - m * A[k][j];
			}
			b[i] = b[i] - m * b[k];
		}
	}

	x[n-1] = b[n-1] / A[n-1][n-1];
	for (k = n-2; k >= 0; --k)
	{
		soma = b[k];
		for (j = k + 1; j < n; ++j)
		{
			soma = soma - A[k][j] * x[j];
		}
		x[k] = soma / A[k][k];
	}

	print_vector(x, n);

	return 0;
}