#include "../include/eventos.h"


// Evento CHEGA(H, B)
bool chega(lista_t** inicio){
    // Struct auxiliar
    heroi_t* heroi;
    base_t* base;
    entidade_t* entidade;

    bool espera = false;
    // TESTE (TIRAR DEPOIS)
    if (inicio == NULL || (*inicio) == NULL){
        return false;
    }

    // Atualiza base do herói
    if ((*inicio)->v_herois == NULL){
        return false;
    }
    heroi = (*inicio)->v_herois[(*inicio)->entidade->heroiId].heroi;           // "Descobre" herói
    heroi->idBase = (*inicio)->entidade->baseId;

    base = (*inicio)->v_bases[(*inicio)->entidade->baseId].base;               // "Descobre" base

    // Verifica se há vagas em B e se a fila está vazia
    if ((tamanhoFila(base->espera)) < base->lotacao) {
        if (ehVaziaFila(base->espera)) {
            // Se a fila está vazia, é criado o evento de entrada
            espera = true;
        } else {
            //espera = (paciência de H) > (10 * tamanho da fila em B) 
            espera = (heroi->paciencia) > (10 * (tamanhoFila(base->espera))); 
        }
    }

    // Decide se o herói entra na fila ou procura outra base
   entidade = criaEntidade(heroi->id, heroi->idBase, NULL); 
    if (espera) {
        // Cria evento ESPERA(H, B)
        if (!insereOrdenado(inicio, (*inicio)->tempo, 2, (*inicio)->v_bases, (*inicio)->v_herois, entidade))
            return false;
    }
    else {
        // Cria evento DESISTE(H, B)
        if (!insereOrdenado(inicio, (*inicio)->tempo, 3, (*inicio)->v_bases, (*inicio)->v_herois, entidade)) 
            return false;
    }

    return true;
};       

bool missao(lista_t** inicio){
    printf("%6d: MISSAO\n", (*inicio)->tempo);
    return false;
};      

// Evento ESPERA(H, B)
bool espera(lista_t** inicio){
    heroi_t* heroi;
    base_t* base;
    entidade_t* entidade;

    // "Descobre heroi e base"
    heroi = (*inicio)->v_herois[(*inicio)->entidade->heroiId].heroi;
    base =  (*inicio)->v_bases[(*inicio)->entidade->baseId].base;

    // Adiciona heroi na lista de espera da base
    if (!enfileirar(base->espera, heroi->id))
        return false;

    printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) ESPERA\n", 
            (*inicio)->tempo, heroi->id, base->id, 
            tamanhoFila(base->espera), base->lotacao);

    entidade = criaEntidade(heroi->id, base->id, NULL);
    
    // Cria evento AVISA(B)
    // if (!insereOrdenado(inicio, (*inicio)->tempo, 4, (*inicio)->v_bases,
    //                     NULL, (*inicio)->entidade->base, NULL))
    //     return false;

    return true;
};      

// Evento DESISTE(H, B)
bool desiste(lista_t** inicio){
    heroi_t* heroi;
    base_t* base;
    entidade_t* entidade;

    int idNovaBase;
    
    // Busca heroi e base
    heroi = (*inicio)->v_herois[(*inicio)->entidade->heroiId].heroi;
    base = (*inicio)->v_bases[(*inicio)->entidade->baseId].base;

    printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) DESISTE\n",
           (*inicio)->tempo, heroi->id, base->id,
           tamanhoFila(base->espera), base->lotacao);

    // Escolhe outra base aleatória
    idNovaBase = rand() % (N_BASES);

    // Cria evento VIAJA(H, B)
    entidade = criaEntidade(heroi->id, idNovaBase, NULL);
    if (!insereOrdenado(inicio, (*inicio)->tempo, 7, (*inicio)->v_bases, (*inicio)->v_herois, entidade)){
        return false;
    }

    return true;
};     

bool avisa(lista_t** inicio){
    return false;
};       

bool entra(lista_t** inicio){
    return false;
};       

bool sai(lista_t** inicio){
    return false;
};         

bool viaja(lista_t** inicio){
    return false;
};