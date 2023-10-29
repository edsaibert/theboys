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
} lista_t;


lista_t* inicializa (void); 

void imprimeLista(lista_t* l1, bool cont);

bool insereInicio(lista_t** inicio, int conteudo);

bool uniao(lista_t* l1, lista_t* l2, lista_t** l3);

bool existe(lista_t* l, int conteudo);

bool interseccao(lista_t* l1, lista_t* l2, lista_t** l3);

bool contem(lista_t* l1, lista_t* l2);

bool igual(lista_t* l1, lista_t* l2);

bool duplicados(lista_t* l1, lista_t** l2);

#endif