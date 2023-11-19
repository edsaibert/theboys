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
	if (!criaEntidade(&entidade, heroi, base, missao)) 		// arquivo entidades.h
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


/*	Executa o evento de acordo com o idFuncao
 	Funcoes definidas em eventos.h	*/ 
bool executa(lista_t** inicio){

	switch ((*inicio)->idFuncao) {
		case 0:
			// CHEGA
			if (!chega(inicio))
				return false;
			break;
		case 1:
			// MISSAO
			if (!missao(inicio))
				return false;
			break;
		case 2:
			// ESPERA
			if (!espera(inicio))
				return false;
			break;
		case 3:
			// DESISTE
			if (!desiste(inicio))
				return false;
			break;
		case 4:
			// AVISA
			if (!avisa(inicio))
				return false;
			break;
		case 5: 
			// ENTRA
			if (!entra(inicio)) 
				return false;
			break;
		case 6:
			// SAI
			if (!sai(inicio))
				return false;
			break;
		case 7:
			// VIAJA
			if (!viaja(inicio))
				return false;
			break;
		
		default:
			printf("Erro ao executar evento\n");
			return false;
	}
	return true;
}
