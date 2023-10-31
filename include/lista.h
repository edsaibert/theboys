#ifndef LISTA_H
#define LISTA_H

#include "atributos.h"
#include "theboys.h"

typedef struct Entidades {
   heroi_t* heroi;
   base_t* base;
} entidade_t;

typedef struct lista {
   int tempo;
   int idFuncao;
   struct lista* prox;
   entidade_t* entidade;
} lista_t;


lista_t* inicializaLista(void);

void imprimeLista(lista_t* inicio);

bool eh_vazia(lista_t* inicio);

bool insereInicio(lista_t** inicio, int tempo);

bool criaEntidade(entidade_t** entidade, heroi_t* heroi, base_t* base);

bool criaNodo(lista_t** nodo, entidade_t* entidade, int tempo, int idFuncao);

bool insereOrdenado(lista_t** inicio, int tempo, int idFuncao, heroi_t* heroi, base_t* base);

// bool removerNodo(lista_t** inicio, lista_t* nodo);

bool removeInicio(lista_t** inicio);

bool buscar(lista_t* inicio, lista_t** nodo, int tempo);

bool freeLista(lista_t** inicio);

#endif
