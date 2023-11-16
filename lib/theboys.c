#ifndef THEBOYS_H
#define THEBOYS_H

#include "../include/theboys.h"

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
    aux->local[0] = rand() % N_TAMANHO_MUNDO;
    aux->local[1] = rand() % N_TAMANHO_MUNDO;
    aux->lotacao = 3 + rand() % (10 - 3); // [3 .. 10]
    aux->presentes = inicializaConjunto();
    aux->espera = inicializaFila();

    *base = aux;

    return true;
}

#endif
