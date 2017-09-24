#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

/*OPERACOES MATRIZ*/
//inicializar matriz
bool Matriz_init(Matriz *matriz, unsigned int n) {

	posix_memalign((void**)&matriz->valor, CACHE_SIZE, n*n*sizeof(double));
	if (matriz->valor == NULL) {
		return false;
	}

	matriz->n = n;

	return true;

}

//liberar espaco alocado pela matriz
void Matriz_free(Matriz *matriz) {

	free(matriz->valor);
	matriz->n = 0;

}

//imprime matriz na saida desejada
void Matriz_print(FILE *saida, Matriz *matriz, char c) {

	unsigned int i, linha;
	unsigned long long int tamanho;

	linha = matriz->n-1;
	tamanho = (matriz->n) * (matriz->n);

	for (i = 0; i < tamanho; i++) {

		fprintf(saida, "%.2f ", matriz->valor[i]);
		if(i % matriz->n == linha) {
			fprintf(saida, "\n");
		}

	}

	fprintf(saida, "\n%c", c);

}

void Matriz_transpor(Matriz *transp, Matriz *matriz) {

	unsigned int i, j;
	double *cursorM, *cursorT;

	cursorT = transp->valor;
	for (j = 0; j < matriz->n; j++) {

		cursorM = matriz->valor+j;

		for (i = 0; i < matriz->n; i++) {
			*cursorT = *cursorM;

			cursorM += matriz->n;
			cursorT++;
		}

	}

}

//multiplicacao de matrizes
void Matriz_mult(Matriz *resultado, Matriz *a, Matriz *b) {

	unsigned int i, j, k;
	double *cursorA, *cursorB, *cursorR, *linhaA;
	double *fimA, *fimB, *fimR;
	Matriz bt;

	//transposicao da matriz b
	Matriz_init(&bt, b->n);
	Matriz_transpor(&bt, b);
	//Matriz_print(stdout, &bt, '\n');	//debug

	//multiplicacao a*bt
	linhaA = a->valor;
	cursorR = resultado->valor;
	fimR = resultado->valor + resultado->n*resultado->n;
	fimB = bt.valor + bt.n*bt.n;
	while (cursorR < fimR) {
		cursorB = bt.valor;
			
		while (cursorB < fimB) {

			*cursorR = 0;
			cursorA = linhaA;
			fimA = linhaA + a->n;
			while (cursorA < fimA) {

				*cursorR += *(cursorA) * *(cursorB);

				cursorA++;
				cursorB++;

			}

			cursorR++;

		}

		linhaA += a->n;

	}

	Matriz_free(&bt);

}
