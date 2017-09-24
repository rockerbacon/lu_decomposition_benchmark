#include <stdio.h>
#include <papi.h>
#include "matriz.h"
#include "lu.h"

#define TESTE_DIM_INICIO	1
#define TESTE_DIM_FIM		14
#define Neventos 3
#define ARQUIVO "luResult.txt"

int main (void) {

	unsigned int i, k;
	double tempoSegundos, dadosSegundos;
	long long int *ciclos, *flops, *flips;
	long long int tamanho;

	int eventos[Neventos] = { PAPI_FP_OPS, PAPI_FP_INS, PAPI_TOT_CYC };
	long long int SaidaEvento[Neventos];

	FILE *saida = fopen(ARQUIVO, "w");

	Matriz matriz, l, u;

	PAPI_library_init(PAPI_VER_CURRENT);

	time_t tempo;
	srand((unsigned)time(&tempo));
	
	printf("-------------FATORACAO LU---------------\n");
	fprintf(saida, "-------------FATORACAO LU---------------\n");

	flops = &SaidaEvento[0];
	flips = &SaidaEvento[1];
	ciclos = &SaidaEvento[2];

	for(i = TESTE_DIM_INICIO, tamanho = 1<<TESTE_DIM_INICIO; tamanho <= 1<<TESTE_DIM_FIM; i++, tamanho <<= 1 ) {
				
		fprintf(stderr, "\rRodando fatoracao LU tamanho: %lldx%lld = %lld kb",
			tamanho, tamanho, tamanho*tamanho*3*sizeof(double)/1024);
		
		Matriz_init(&matriz, tamanho);
		Matriz_init(&l, tamanho);
		Matriz_init(&u, tamanho);

		positivaDef_gerar(&matriz);
		//fprintf (stdout, "\n");		//debug
		//Matriz_print(stdout, &matriz, '\n');	//debug
	
		PAPI_start_counters(eventos, Neventos);
		tempo = PAPI_get_real_usec();

		lu(&matriz, &l, &u);

		tempo = PAPI_get_real_usec() - tempo;
		PAPI_stop_counters(SaidaEvento, Neventos);

		//Matriz_print(stdout, &l, '\n');	//debug
		//Matriz_print(stdout, &u, '\n');	//debug
	
		tempoSegundos = (double)tempo/1000000;
		dadosSegundos = (tamanho*tamanho*3*sizeof(double)/tempoSegundos)/(1 << 20);
		
		fprintf(saida, "Tamanho: %lldx%lld = %lld kb\n", tamanho, tamanho,
								 tamanho*tamanho*3*sizeof(double)/1024);
		fprintf(saida, "Dados por segundo: %lf Mb/s\n", dadosSegundos);
		fprintf(saida, "Tempo: %lf segundos\n", tempoSegundos);
		fprintf(saida, "Ciclos: %lld\n", *ciclos);
		fprintf(saida, "FLOPS: %lld\n", *flops);
		fprintf(saida,"FLIPS: %lld\n\n", *flips);
		fflush(saida);

		Matriz_free(&matriz);
		Matriz_free(&l);
		Matriz_free(&u);

	}
	
	fprintf (stderr, "\n");
	fclose(saida);
	PAPI_shutdown();

	return 0;

}
