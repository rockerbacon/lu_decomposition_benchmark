#include "lu.h"

void positivaDef_gerar(Matriz *matriz){

	unsigned int i;

	for (i = 0; i < matriz->n*matriz->n; i++) {
		matriz->valor[i] = 0;
	}

	for(i = 0; i < matriz->n; i++) {
	
	  	matriz->valor[i*matriz->n + i] = 7.283034;
	
		if(i < matriz->n-1){
	  		matriz->valor[ i*matriz->n + i + 1 ] = -3.141517;
	  		matriz->valor[ matriz->n + i*matriz->n + i ] = -3.141517;
	  	}

	}
}


void lu(Matriz *matriz, Matriz *l, Matriz *u) {

	long int k, i, j, limite;

	//inicializar valores de l e u
	for (i = 0; i < matriz->n; i++) {
		for (j = 0; j < matriz->n; j++) {

			if (i != j) {
				l->valor[i*l->n + j] = 0;
			}else{
				l->valor[i*l->n + j] = 1;
			}

			u->valor[i*u->n + j] = matriz->valor[i*matriz->n + j];

		}
	}

	limite = matriz->n-1;
	for (i = 0; i < limite; i++) {

		for (j = i+1; j < matriz->n; j++) {

			l->valor[j*l->n + i] = u->valor[j*u->n + i] / u->valor[i*u->n + i];

			for (k = i; k < matriz->n; k++) {
				u->valor[j*u->n + k] -= l->valor[j*l->n + i]*u->valor[i*u->n + k];
			}

		}

	}
	

}
