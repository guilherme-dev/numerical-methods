#include <stdio.h>
#include <stdlib.h>

#define VALOR 0.6f
#define NUM_ELEMENTOS 10000000

float somaSequencia( float *dados, unsigned int tam )
{
	float soma = 0.0;
	while ( tam-- )
	{
		soma += dados[tam];
	}
}

float somaPar( float *dados, unsigned int tam )
{
	if (tam == 2)
		return dados[0] + dados[1];
	if (tam == 1)
		return dados[0];

	unsigned int div = tam / 2;
	return somaPar(dados, div) + somaPar(dados+div, tam-div);
}

void main()
{
	// Preenche um vetor
	unsigned int i;
	float *dados = (float*) malloc(NUM_ELEMENTOS * sizeof(float));
	for (i = 0; i < NUM_ELEMENTOS; ++i)
		dados[i] = VALOR;

	float soma1 = somaSequencia( dados, NUM_ELEMENTOS );
	printf("Soma sequencia: %1.15f\n", soma1);

	float soma2 = somaPar( dados, NUM_ELEMENTOS );
	printf("Soma par: %1.15f\n", soma2);

	free (dados);
} 