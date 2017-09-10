// 1º trabalho de icc - Henrique Colodetti Escanferla e Israel Barth Rubio

#include "../inc/pdeSolver.h"

double timestamp(void){ // Funcao obtém tempos baseados no relogio da cpu.
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return((double)(tp.tv_sec + tp.tv_usec/1000000.0));
}


void init_inc(double *pts, int ult_pt_bord_dir, int tam_inc, double delta_x) // Inicializador do vetor de incognitas com o ghost layer.
{
	int i; // Iterador de loop; 
	double dx; //distancia no eixo x da borda.
	for(i = 0; i < ult_pt_bord_dir; ++i) // Zera todas as posicoes exceto a borda x de cima.
		pts[i] = 0;
	for(dx = delta_x; i < tam_inc; ++i, dx += delta_x) // Borda de cima de x tem valores gerados pela eq. de acordo com o slide.
		pts[i] = sin(_2PI * dx) * sinh(_2PI);
	pts[i] = 0; // Zerar ponto inutil superior direito.
}

void imprime_inc(double *inc, int tam_x, int tam_y) // Imprime inc com seu formato.
{
	int i ,j;
	
	for(i = tam_y - 1; i >= 0; --i)
	{
		for(j = 0; j < tam_x; ++j)
			printf("%.8f\t\t", inc[i * (tam_x) + j]);
		printf("\n");
	}
}

void gauss_seidel_ssor(int nx, int ny, int ni, char mod, FILE *arq)
{
	int i, j, l, k, ci1, ci2, ci3, tam_inc; // Iterador de loop; idem; idem; idem; constante inteira; idem; idem; tamanho do vetor inc.
	long int p1, p2, p3; // Posicoes do arq p/ escrever temp_med_mod, temp_med_res e, no final do arq, o resto da solucao de forma correta.
	char *s;
	
	ci2 = nx - 1; // Necessario para pular bordas.
	ci3 = nx + 1; // Necessario calcular uma vez valores usados repetidas vezes em loop.
	tam_inc = (nx + 1) * (ny + 1); // Ja eh incluido os 4 pontos inuteis - (0,0), (nx,0), (0,ny) e (nx,ny).
	
	double inc[tam_inc], cf1, k2, delta_x, delta_y, inv_delta_x2, inv_delta_y2, dx, dy, r, temp_med_mod, temp_med_res, w, pt_ant, aux_res, cf2;
	
	// "incgs" representa matriz de pts a serem calculados na discretizacao; cfi são consts flt pt calculadas uma vez e usadas varias vezes em loop; dx e dy sao as distancias nos eixos x e y do ponto a ser calculado; r eh o residuo; tempo medio p/ calc de "inc"; tempo medio p/ calc do residuo; constante de relaxamento do metodo SOR; valor da iteracao passada de um pt, auxiliar no calc d res, constante utilizada no calculo do residuo;
	
	delta_x = (double) 2 / nx; // Delta x.
	delta_y = (double) 1 / ny; // Delta y.
	k2 = 4 * PI * PI; // k².
	cf1 = (2 / (delta_x * delta_x)) + (2 / (delta_y * delta_y)) + k2;
	cf2 = cf1;
	cf1 = 1 / cf1; // Constante central do stencil.
	inv_delta_x2 = 1 / (delta_x * delta_x); // 1 / (delta x)² do stencil.
	inv_delta_y2 = 1 / (delta_y * delta_y); // 1 / (delta y)² do stencil.
	ci1 = tam_inc - nx - 2; // O ultimo pt esta antes de uma borda d x, um ponto inutil e um ponto da borda de y => valor final de i.
	init_inc(inc, ci1 + 2, tam_inc - 1, delta_x); // Inicializa bordas e (0,0,0, ... , 0) c/ ghost layer.
	// O primeiro pt esta depois de um pt inutil, uma borda de x e um ponto inutil => valor inicial de i.s
	
	if(mod == 'g') s = GS; else s = SOR; // Definindo o "s" p/ escrever.
	
	fprintf(arq, "###########\n# Tempo Metodo %s: ", s); // Preciso guardar posicao da stream p/ escrever o temp_med_mod; 14 espaços p/ q o num n escreva por cima do resto.
	p1 = ftell(arq); // Obtem posicao da stream.
	fprintf(arq, "               "); // 14 espaços p/ q o num n escreva por cima do resto.
	fprintf(arq, "\n# Tempo Resíduo: "); // Preciso guardar posicao da stream p/ escrever o temp_med_mod;
	p2 = ftell(arq); // Obtem posicao da stream.
	fprintf(arq, "               "); // 14 espaços p/ q o num n escreva por cima do resto.s
	fprintf(arq, "\n\n# Norma do Residuo"); // Cabeçalho antes da impressao dos residuos.
	
	if(mod == 'g') w = 1.0f; else w = 2 -(delta_x + delta_y) / 2; // w = 1 => idem ao metodo GS, senao, sera um valor entre 1 e 2 como fator de relaxacao p/ o metodo SOR.
	
	double start, end; // Marcadores de tempo.
	float a = 0;
	for(l = 0, k = 1, temp_med_mod = 0.0f, temp_med_res = 0.0f; l < ni; ++l, ++k)
	{
		start = timestamp(); // Inicio do contador de tempo.
	
		r = 0.0f; // Começa com zero p/ poder somar c/ si mesmo.
		
		likwid_markerInit();
		likwid_markerStartRegion("GS");

		for(j = 0, i = nx + 2, dx = delta_x, dy = delta_y; i < ci1; ++i, ++j, dx += delta_x) // Loop da iteracao GS.
		{
			a += 1;
			if(j == ci2) { j = 0; i += 2; dx = delta_x; dy += delta_y;} // Pular bordas e ajeitar dx / dy.
			
			pt_ant = inc[i]; // Salva valor anterior para calc.
			inc[i] = inv_delta_x2 * (inc[i - 1] + inc[i + 1]) + inv_delta_y2 * (inc[i - ci3] + inc[i + ci3]) + k2 * sin(_2PI * dx) * sinh(_2PI * dy);
			// Formula do slide, acima => r = f(x ,y) + (1/delta_x²) * (u(x+1,y) + u(x-1,y)) + (1/delta_y²) * (u(x,y+1) + u(x,y+1)) - stencil central * u(x,y).
			inc[i] = inc[i] * cf1; // Dividir pelo valor central do stencil.
			inc[i] = pt_ant + w * (inc[i] - pt_ant); // O metodo SOR da um passo mais largo, mas nao tao largo (entre 1 e 2 vezes), em relacao ao passo do GS por iteracao.

		}
		
		likwid_markerStopRegion("GS");
		
		end = timestamp(); // Fim do contador de tempo.
		
		temp_med_mod += end - start; // Soma do tempo de todas as ni iteracoes p/ obter a media por iteracao.
		
		start = timestamp(); // Inicio do contador de tempo.
	
		likwid_markerStartRegion("Calculo do Residuo");	
		for(j = 0, i = nx + 2, dx = delta_x, dy = delta_y; i < ci1; ++i, ++j, dx += delta_x) // Loop da soma dos residuos.
		{
			if(j == ci2) { j = 0; i += 2; dx = delta_x; dy += delta_y;} // Pular bordas e ajeitar dx / dy.
			
			aux_res = - (k2 * sin(_2PI * dx) * sinh(_2PI * dy)) - (inv_delta_x2 * (inc[i - 1] + inc[i + 1])) - (inv_delta_y2 * (inc[i - ci3] + inc[i + ci3])) + (inc[i] * cf2);
			r += aux_res * aux_res; // Soma dos quadrados dos residuos.
		}
		r = sqrt(r); // Tirando a raiz para obter a norma da soma dos residuos.
		likwid_markerStopRegion("Calculo do Residuo");
		likwid_markerClose();

		fprintf(arq, "\n# i=%d: %.20f", k, r); // Imprime residuo atual.
		
		end = timestamp();
		
		temp_med_res += end - start; // Soma do tempo de todas as ni iteracoes p/ obter a media por iteracao.
	}
	
	temp_med_mod = temp_med_mod / ni; // Tempo medio de cada iteracao do modo GS.
	temp_med_res = temp_med_res / ni; // Tempo medio de cada iteracao do calc do res.
	
	p3 = ftell(arq); // Posicao final atual do arq.
	fseek(arq, p1, SEEK_SET); // Posição p1 do arq pq escrever temp_med_mod.
	fprintf(arq, "%.8f", temp_med_mod); // Escrever temp_med_mod.
	fseek(arq, p2, SEEK_SET); // Posicao p2 (apos alterar em p1) p/ escrever temp_med_res.
	fprintf(arq, "%.8f", temp_med_res); // Escrever temp_med_res.
	fseek(arq, p3, SEEK_SET); // Posicao p3 apos escrever temp_med_mod e temp_med_res p/ escrever o resto da solucao.
	
	for(i = 0, dy = 0; i < tam_inc; dy += delta_y) // Escrita dos tam_inc pts da solucao no formato adequado p/ plotagem usando gnuplot.
		for(j = 0, dx = 0; j < ci3; ++j, ++i, dx += delta_x)
			fprintf(arq, "\n%.8f %.8f %.8f", dx, dy, inc[i]); // Escrita de um pt no arq.
	
}


