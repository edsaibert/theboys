#include "../include/lista.h"


// Retorna uma lista vazia
lista_t* inicializaLista(void) {
    return NULL; 
}

//Imprime uma lista encadeada
void imprimeLista(lista_t* inicio){
	lista_t* aux;

	for (aux = inicio; aux != NULL; aux = aux->prox)
		printf("%d ", aux->tempo);
	printf("\n");
}

// Retorna se a lista é vazia
bool eh_vazia(lista_t* inicio){
	return (inicio == NULL);
}

// Insere no início um elemento da lista
bool insereInicio(lista_t** inicio, int tempo){
	lista_t* nodo;
    nodo = (lista_t*) malloc(sizeof(lista_t));

    if (nodo != NULL) {
        nodo->prox = *inicio;

		// Certifica-se que o ant do primeiro tempoento da lista
		// aponte para o novo tempoento
        // if (*inicio != NULL){ 
        //     (*inicio)->ant = nodo;
        //         }

        // nodo->ant = NULL;
        nodo->tempo = tempo;

        *inicio = nodo; 

        return true;
    } 
    return false;
}

// Cria um nodo com base nos seus parâmetros
bool criaNodo(lista_t** nodo, entidade_t* entidade, int tempo, int idFuncao) {
	lista_t* aux;

	aux = (lista_t*) malloc(sizeof(lista_t));

	if (aux != NULL) {
		aux->entidade = entidade;
		aux->tempo = tempo;
		aux->idFuncao = idFuncao;

		*nodo = aux;
		return true;
	}

	return false;
}

// Insere na Lista de Eventos Futuros 
bool insereOrdenado(lista_t** inicio, int tempo, int idFuncao, heroi_t* heroi, base_t* base, missao_t* missao){
	lista_t *nodo, *aux;
	entidade_t* entidade;

	// cria as entidades heroi ,base e missao que servem de parametros de eventos 
	if (!criaEntidade(&entidade, heroi, base, missao))
		return false;

	// cria o nodo a ser inserido
	if (!criaNodo(&nodo, entidade, tempo, idFuncao))
		return false;

	// Caso se insira no início da lista
	if (*inicio == NULL) {
		(*inicio) = nodo;

		return true;
	}

	// Caso se existe apenas um elemento na lista
	if ((*inicio)->tempo > tempo) {
		nodo->prox = (*inicio);
		(*inicio) = nodo;

		return true;
	}

	aux = *inicio;

	// Caso se insira no meio ou final da lista
	while (aux->prox != NULL && aux->prox->tempo < tempo) 
		aux = aux->prox;

	nodo->prox = aux->prox;
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
bool buscar(lista_t* inicio, lista_t** nodo, int tempo){
	lista_t* aux;

	if (inicio == NULL)
		return false;

	for (aux = inicio; aux != NULL; aux = aux->prox) {
		if (aux->tempo == tempo) {
			*nodo = aux;	
			return true;
		}
	}

	return false;
}

bool freeLista(lista_t** inicio){
	lista_t* aux;

	if (*inicio == NULL)
		return false;

	while (*inicio != NULL) {
		aux = *inicio;
		*inicio = (*inicio)->prox;
		free(aux);
	}

	return true;
}




