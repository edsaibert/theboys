#include "../include/eventos.h"


bool chega(lista_t** inicio){
    int espera = false;
    // Struct auxiliar
    entidade_t* entidade = (*inicio)->entidade;

    // Atualiza base do herói
    (*(&entidade))->heroi->idBase = entidade->base->id;

    // Verifica se há vagas em B e se a fila está vazia
    if ((tamanhoFila(entidade->base->espera)) < entidade->base->lotacao) {
        if (ehVaziaFila(entidade->base->espera)) {
            // Se a fila está vazia, é criado o evento de entrada
            espera = true;
        } else {
            //espera = (paciência de H) > (10 * tamanho da fila em B) 
            espera = (entidade->heroi->paciencia) > (10 * (tamanhoFila(entidade->base->espera))); 
        }
    }

    // Decide se o herói entra na fila ou procura outra base
    
    if (espera) {
        // Cria evento ESPERA(H, B)
        if (!insereOrdenado(inicio, (*inicio)->tempo, 2, entidade->heroi, entidade->base, NULL))
            return false;
    }
    else
        // Cria evento DESISTE(H, B)
        if (!insereOrdenado(inicio, (*inicio)->tempo, 3, entidade->heroi, entidade->base, NULL))
            return false;

    return true;
    
};       

bool missao(lista_t** inicio){};      

bool espera(lista_t** inicio){
    // Adiciona heroi na lista de espera da base
    if (!enfileirar((*inicio)->entidade->base->espera, (*inicio)->entidade->heroi->id))
        return false;

    printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) ESPERA\n", 
            (*inicio)->tempo, (*inicio)->entidade->heroi->id, (*inicio)->entidade->base->id, 
            tamanhoFila((*inicio)->entidade->base->espera), (*inicio)->entidade->base->lotacao);
    
    // Cria evento AVISA(B)
    return true;
};      

bool desiste(lista_t** inicio){
    printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) DESISTE\n",
           (*inicio)->tempo, (*inicio)->entidade->heroi->id, (*inicio)->entidade->base->id,
           tamanhoFila((*inicio)->entidade->base->espera), (*inicio)->entidade->base->lotacao);

    // Escolhe outra base aleatória
    // Cria evento VIAJA(H, B)
};     

bool avisa(lista_t** inicio){};       

bool entra(lista_t** inicio){};       

bool sai(lista_t** inicio){};         

bool viaja(lista_t** inicio){};