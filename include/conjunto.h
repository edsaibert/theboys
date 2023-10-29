// Arquivo de headers
#ifndef LIB_LISTA_H
#define LIB_LISTA_H

#include "aux.h"

typedef struct conjunto {
    int conteudo;
    int cont; // Para o caso das duplicatas
    struct conjunto* prox;
} conjunto_t;


conjunto_t* inicializaConjunto (void); 

void imprimeConjunto(conjunto_t* l1, bool cont);

bool insereConjunto(conjunto_t** inicio, int conteudo); 

bool uniao(conjunto_t* l1, conjunto_t* l2, conjunto_t** l3);

bool existe(conjunto_t* l, int conteudo);

bool interseccao(conjunto_t* l1, conjunto_t* l2, conjunto_t** l3);

bool contem(conjunto_t* l1, conjunto_t* l2);

bool igual(conjunto_t* l1, conjunto_t* l2);

bool duplicados(conjunto_t* l1, conjunto_t** l2);

#endif