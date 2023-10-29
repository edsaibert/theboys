#include "../include/lef.h"

lista_t* inicializa(void) {
	return NULL;
}


void imprimirLista(lista_t* inicio) {
	lista_t* aux;

	for (aux = inicio; aux != NULL; aux = aux->prox) {
		printf("%d ", aux->elem);
	}
	printf("\n");
}


bool inserirOrdenado(lista_t** inicio, int elem){
	lista_t *nodo, *aux;

	nodo = (lista_t*) malloc(sizeof(lista_t));
	if (!nodo)
			return false;

	// Caso se insira no início da lista
	if (*inicio == NULL) {

		nodo->elem = elem;
		(*inicio) = nodo;

		return true;
	}

	// Caso se existe apenas um elemento na lista
	if ((*inicio)->elem > elem) {
		nodo->elem = elem;
		nodo->prox = (*inicio);
		(*inicio) = nodo;

		return true;
	}

	aux = *inicio;

	// Caso se insira no meio ou final da lista
	while (aux->prox != NULL && aux->prox->elem < elem) 
		aux = aux->prox;

	nodo->elem = elem;
	nodo->prox  = aux->prox;
	aux->prox = nodo;

	return true;

};

