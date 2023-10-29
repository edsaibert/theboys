#ifndef LISTA_H
#define LISTA_H

#include "aux.h"

typedef struct lista {

   // struct lista* ant;
   struct lista* prox;
   int elem;

} lista_t;


lista_t* inicializaLista(void);

void imprimeLista(lista_t* inicio);

bool eh_vazia(lista_t* inicio);

bool insereInicio(lista_t** inicio, int elem);

bool insereOrdenado(lista_t** inicio, int elem);

// bool removerNodo(lista_t** inicio, lista_t* nodo);

bool removeInicio(lista_t** inicio);

bool buscar(lista_t* inicio, lista_t** nodo, int elem);

bool freeFila(lista_t** inicio);

#endif