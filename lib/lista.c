#include "../include/lista.h"


// Retorna uma lista vazia
lista_t* inicializa(void) {
    return NULL; 
}

//Imprime uma lista duplamente encadeada
void imprimeLista(lista_t* inicio){
	lista_t* aux;

	for (aux = inicio; aux != NULL; aux = aux->prox)
		printf("%d ", aux->elem);
	printf("\n");
}

// Retorna se a lista é vazia
bool eh_vazia(lista_t* inicio){
	return (inicio == NULL);
}

// Insere no início um elemento da lista
bool insereInicio(lista_t** inicio, int elem){
	lista_t* nodo;
    nodo = (lista_t*) malloc(sizeof(lista_t));

    if (nodo != NULL) {
        nodo->prox = *inicio;

		// Certifica-se que o ant do primeiro elemento da lista
		// aponte para o novo elemento
        // if (*inicio != NULL){ 
        //     (*inicio)->ant = nodo;
        //         }

        // nodo->ant = NULL;
        nodo->elem = elem;

        *inicio = nodo; 

        return true;
    } 
    return false;
}

bool insereOrdenado(lista_t** inicio, int elem){
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


// Remove um nodo de uma lista
// bool removerNodo(lista_t** inicio, lista_t* nodo) {

// 	if (*inicio == NULL)
// 		return false;

// 	if (nodo->ant != NULL) 
// 		nodo->ant->prox = nodo->prox;

// 	else *inicio = nodo->prox;

// 	if (nodo->prox != NULL)
// 		nodo->prox->ant = nodo->ant;

// 	return true;
// }

// Remove do início da lista
bool removeInicio(lista_t** inicio){
	
	if (*inicio == NULL)
		return false;

	*inicio = (*inicio)->prox;

	return true;
}

//Busca a existência de um valor e retorna o nodo que o contém
bool buscar(lista_t* inicio, lista_t** nodo, int elem){
	lista_t* aux;

	if (inicio == NULL)
		return false;

	for (aux = inicio; aux != NULL; aux = aux->prox) {
		if (aux->elem == elem) {
			*nodo = aux;	
			return true;
		}
	}

	return false;
}





