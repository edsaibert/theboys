#ifndef THEBOYS_H
#define THEBOYS_H

#include "../include/entidades.h"

// Inicializa a entidade heroi
bool inicializaHeroi(int id, heroi_t** heroi){
    heroi_t* aux;
    conjunto_t* habilidades;

    aux = (heroi_t*) malloc(sizeof(heroi_t));

    if (aux == NULL) {
        printf("Erro ao alocar memória para o heroi %d\n", id);
        return false;    
    }

    aux->id = id;
    aux->experiencia = 0;
    aux->paciencia = rand() % MAX_PACIENCIA;
    aux->velocidade = MIN_VELOCIDADE + rand() % (MAX_VELOCIDADE - MIN_VELOCIDADE); // [50 .. 5000]
    
    int maxHabilidade = 1 + rand() % 3; // [1 .. 3] 

    // Cria o conjunto de habilidades
    habilidades = inicializaConjunto();
    for (int i = 0; i < maxHabilidade; i++) 
        insereConjunto(&habilidades, 1 + rand() % (N_HABILIDADES - 1)); // Sorteia uma habilidade [1 .. 10] 

   aux->habilidades = habilidades;

    *heroi = aux;
    return true; 

}

// Inicializa a entidade base
bool inicializaBase(int id, base_t** base) {
    base_t* aux;

    aux = (base_t*) malloc(sizeof(base_t));

    if (aux == NULL) {
        printf("Erro ao alocar memória para a base %d\n", id);
        return false;    
    }
    
    aux->id = id;
    aux->local[0] = rand() % N_TAMANHO_MUNDO;       // Coordenada x
    aux->local[1] = rand() % N_TAMANHO_MUNDO;       // Coordenada y
    aux->lotacao = 3 + rand() % (10 - 3);           // [3 .. 10]
    aux->presentes = inicializaConjunto();
    aux->espera = inicializaFila();

    *base = aux;

    return true;
}

// Inicializa a entidade missao
bool inicializaMissao(int id, missao_t** missao) {
    missao_t* aux;
    conjunto_t* habilidades;

    aux = (missao_t*) malloc(sizeof(missao_t));

    if (aux == NULL) {
        printf("Erro ao alocar memória para a missao %d\n", id);
        return false;
    }

    aux->id = id;
    aux->local[0] = rand() % N_TAMANHO_MUNDO;       // Coordenada x
    aux->local[1] = rand() % N_TAMANHO_MUNDO;       // Coordenada y

    int maxHabilidade = MIN_HAB_MISSAO + rand() % (N_HABILIDADES - MIN_HAB_MISSAO); // [6 .. 10]
    // Cria o conjunto de habilidades
    habilidades = inicializaConjunto();
    for (int i = 0; i < maxHabilidade; i++)
        insereConjunto(&habilidades, 1 + rand() % (N_HABILIDADES - 1)); // Sorteia uma habilidade [1 .. 10]

    return 1;
}

// Cria struct entidade para ser armazenada na lista de eventos futuros
bool criaEntidade(entidade_t** entidade, heroi_t* heroi, base_t* base, missao_t* missao) {
	entidade_t* aux;

	aux = (entidade_t*) malloc(sizeof(entidade_t));

	if (aux != NULL) {
		aux->heroi = heroi;
		aux->base = base;
		aux->missao = missao;

		*entidade = aux;
		return true;
	}

	return false;
}

#endif
