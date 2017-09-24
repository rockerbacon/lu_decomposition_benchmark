#ifndef MATRIZ_H
#define MATRIZ_H

#define swap(a, b) { long int aux_swap = a; a = b; b = aux_swap; }

#define CACHE_SIZE 2048*1024

#include "bool.h"
#include <stdio.h>

/*DEFINICAO MATRIZ*/
typedef struct _Matriz {

	double *valor;
	unsigned int n;

}Matriz;

/*OPERACOES MATRIZ*/
//inicializar matriz, retorna false em caso de erro durante alocacao de memoria
extern bool Matriz_init(Matriz *matriz, unsigned int n);

//liberar espaco alocado pela matriz
extern void Matriz_free(Matriz *matriz);

//imprime matriz na saida desejada
//char c eh impresso apos o termino da impressao da matriz
extern void Matriz_print(FILE *saida, Matriz *matriz, char c);

//Transpoe a matriz
extern void Matriz_transpor(Matriz *transp, Matriz *matriz);

//multiplicacao de matrizes
extern void Matriz_mult(Matriz *resultado, Matriz *a, Matriz *b);

#endif
