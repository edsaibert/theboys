#ifndef LISTA_H
#define LISTA_H

#include "atributos.h"
#include "entidades.h"

typedef struct lista {
   int tempo;
   int idFuncao;
   struct lista* prox;
   entidade_t* entidade;
   v_bases_t* v_bases;
   v_herois_t* v_herois;
} lista_t;

#include "eventos.h"

lista_t* inicializaLista(void);

void imprimeLista(lista_t* inicio);

bool eh_vazia(lista_t* inicio);

bool criaNodo(lista_t** nodo, entidade_t* entidade, int tempo, int idFuncao, v_bases_t* v_bases, v_herois_t* v_herois);

bool insereOrdenado(lista_t** inicio, int tempo, int idFuncao, v_bases_t* v_bases, v_herois_t* v_herois, entidade_t* entidade);

bool removeInicio(lista_t** inicio);

bool buscar(lista_t* inicio, lista_t** nodo, int tempo);

bool executa(lista_t** inicio);

void freeLista(lista_t* inicio);

#endif
