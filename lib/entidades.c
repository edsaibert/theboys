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
    
    int maxHabilidade = 1 + rand() % 3; // Sorteia o máximo de habilidades [1 .. 3] 

    // Cria o conjunto de habilidades
    habilidades = inicializaConjunto();    

    int i = 0;
    while (i < maxHabilidade){
        int aleat = 1 + rand() % (N_HABILIDADES - 1); // Sorteia uma habilidade [1 .. 10]
        if (!existe(habilidades, aleat)){
            insereConjunto(&habilidades, aleat); // insere no conjunto de habilidades 
            i++;
        }
    }

   aux->habilidades = habilidades;
   *heroi = aux;

   return true; 
}

// Inicializa a entidade base
bool inicializaBase(int id, base_t** base) {
    base_t* aux;
    fila_t* espera;

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

    if (inicializaFila(&espera))
        aux->espera = espera;
    else 
        return false;

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

    int i = 0;
    while (i < maxHabilidade){
        int aleat = 1 + rand() % (N_HABILIDADES - 1); // Sorteia uma habilidade [1 .. 10]
        if (!existe(habilidades, aleat)){
            (insereConjunto(&habilidades, aleat)); // insere no conjunto de habilidades 
            i++;
        }
    }

    aux->habilidades = habilidades;
    *missao = aux;

    return 1;
}

// Cria struct entidade para ser armazenada na lista de eventos futuros
bool criaEntidade(entidade_t** entidade, int heroiId, int baseId, missao_t* missao) {
    entidade_t* aux;
    aux = (entidade_t*) malloc(sizeof(entidade_t));

    if (aux == NULL) 
        return false;

    aux->heroiId = heroiId;
    aux->baseId = baseId;
    aux->missao = missao;

    *entidade = aux;

    return true;
}

// Libera o vetor de bases
void freeVbases(v_bases_t* v_bases) {
    for (int i = 0; i < N_BASES; i++) {
        if (v_bases[i].base == NULL)
            continue;

        free(v_bases[i].base->espera);
        freeConjunto(v_bases[i].base->presentes);
        free(v_bases[i].base);
        // v_bases[i].base = NULL;
    }
    free(v_bases);
}

void freeVherois(v_herois_t* v_herois) {
    for (int i = 0; i < N_HEROIS; i++) {
        if (v_herois[i].heroi == NULL)
            continue;

        if (v_herois[i].heroi->habilidades != NULL)
            freeConjunto(v_herois[i].heroi->habilidades);
        free(v_herois[i].heroi);
    }
    free(v_herois);
}

void freeEntidade(entidade_t* entidade) {
    if (entidade == NULL)
        return;
    
    if (entidade->missao != NULL){
        if (entidade->missao->habilidades != NULL){
            freeConjunto(entidade->missao->habilidades);
        }
        free(entidade->missao);
    }
    free(entidade);
};

#endif
