#include "../inc/pdeSolver.h"

int main(int argc, char* argv[])
{

	int nx, ny, ni, j;
	char mod;
	FILE *saida;

	if (argc < 11)
	{
		fprintf(stderr, "O numero de argumentos eh invalido\n");
		exit(NARGC_ERROR);
	}

	if (strcmp(argv[1],"-nx"))
	{
		fprintf(stderr, "Argumento -nx invalido\n");
		exit(NX_ERROR);
	}

	for(j = 0; j < strlen(argv[2]); ++j)
  		if(!(argv[2][j] >= 48 && argv[2][j] <= 57))
    	{
  			fprintf(stderr, "-nx contem caracter nao numerico\n");
  			exit(NX_LETRA);
    	}

	if (strcmp(argv[3],"-ny"))
	{
		fprintf(stderr, "Argumento -ny invalido\n");
		exit(NY_ERROR);
	}

	for(j = 0; j < strlen(argv[4]); ++j)
  		if(!(argv[4][j] >= 48 && argv[4][j] <= 57))
    	{
  			fprintf(stderr, "-ny contem caracter nao numerico\n");
  			exit(NY_LETRA);
    	}

	if(strcmp(argv[5],"-i"))
	{
		fprintf(stderr, "Argumento -i invalido\n");
		exit(NI_ERROR);
	}

	for(j = 0; j < strlen(argv[6]); ++j)
  		if(!(argv[6][j] >= 48 && argv[6][j] <= 57))
    	{
  			fprintf(stderr, "-i contem caracter nao numerico\n");
  			exit(NI_LETRA);
    	}

	if(strcmp(argv[7],"-m"))
	{
		fprintf(stderr, "Argumento -m invalido\n");
		exit(M_ERROR);
	}

	if(strcmp(argv[8],"gs"))
		if(strcmp(argv[8],"sor"))
		{
			fprintf(stderr, "Modalidade da solucao invalida\n");
			exit(M_TYPE_ERROR);
		}

	if(strcmp(argv[9],"-o"))
	{
		fprintf(stderr, "Argumento -o invalido\n");
		exit(O_ERROR);
	}

	strcat(argv[10],"/solution.txt");

	if(!(saida = fopen(argv[10], "w")))
	{
		fprintf(stderr, "Erro ao abrir arquivo de saida\n");
		exit(ARQ_ERROR);
	}

	nx = atoi(argv[2]);
	ny = atoi(argv[4]);
	ni = atoi(argv[6]);
	mod = argv[8][0];

	gauss_seidel_ssor(nx, ny, ni, mod, saida);
}
