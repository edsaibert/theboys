#ifndef LISTA_H
#define LISTA_H

#include "atributos.h"
#include "entidades.h"

typedef struct lista {
   int tempo;
   int idFuncao;
   struct lista* prox;
   v_bases_t* v_bases;
   entidade_t* entidade;
} lista_t;

#include "eventos.h"

lista_t* inicializaLista(void);

void imprimeLista(lista_t* inicio);

bool eh_vazia(lista_t* inicio);

bool criaNodo(lista_t** nodo, entidade_t* entidade, int tempo, int idFuncao, v_bases_t* v_bases);

bool insereOrdenado(lista_t** inicio, int tempo, int idFuncao, v_bases_t* v_bases, 
                     heroi_t* heroi, base_t* base, missao_t* missao);

bool removeInicio(lista_t** inicio);

bool buscar(lista_t* inicio, lista_t** nodo, int tempo);

bool executa(lista_t** inicio);

void freeLista(lista_t* inicio);

#endif
