#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct lista {

   struct lista* ant;
   struct lista* prox;
   int elem;

} lista_t;


lista_t* inicializa(void);

void imprimir(lista_t* inicio);

bool eh_vazia(lista_t* inicio);

bool inserir(lista_t** inicio, int elem);

bool removerNodo(lista_t** inicio, lista_t* nodo);

bool buscar(lista_t* inicio, lista_t** nodo, int elem);
