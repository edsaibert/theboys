// Arquivo de headers

#ifndef LIB_LISTA_H
#define LIB_LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct lista {
    int conteudo;
    int cont; // Para o caso das duplicatas
    struct lista* prox;
} conjunto_t;


conjunto_t* inicializa (void); 

void imprimeLista(conjunto_t* l1, bool cont);

bool insereInicio(conjunto_t** inicio, int conteudo);

bool uniao(conjunto_t* l1, conjunto_t* l2, conjunto_t** l3);

bool existe(conjunto_t* l, int conteudo);

bool interseccao(conjunto_t* l1, conjunto_t* l2, conjunto_t** l3);

bool contem(conjunto_t* l1, conjunto_t* l2);

bool igual(conjunto_t* l1, conjunto_t* l2);

bool duplicados(conjunto_t* l1, conjunto_t** l2);

#endif