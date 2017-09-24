#ifndef LU_H
#define LU_H

#include "bool.h"
#include "matriz.h"

//gera matriz positiva definida
extern void positivaDef_gerar(Matriz *matriz);

//efetua fatoracao LU
extern void lu(Matriz *matriz, Matriz *l, Matriz *u);

#endif
