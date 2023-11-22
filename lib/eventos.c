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
    // printf("%6d: MISSAO\n", (*inicio)->tempo);
    return false;
};      

// Evento ESPERA(H, B)
bool espera(lista_t** inicio){
    heroi_t* heroi;
    base_t* base;
    entidade_t* entidade;
    v_bases_t* v_bases = (*inicio)->v_bases;   

    // "Descobre heroi e base"
    heroi = (*inicio)->v_herois[(*inicio)->entidade->heroiId].heroi;
    base =  v_bases[(*inicio)->entidade->baseId].base;

    // Adiciona heroi na lista de espera da base
    if (!enfileirar(base->espera, heroi->id))
        return false;

    printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) ESPERA\n", 
            (*inicio)->tempo, heroi->id, base->id, 
            tamanhoConjunto(base->presentes), base->lotacao);

    entidade = criaEntidade(NULL, base->id, NULL);

    (*inicio)->v_herois[(heroi->id)].heroi = heroi;
    
    // Cria evento AVISA(B)
    if (!insereOrdenado(inicio, (*inicio)->tempo, 4, v_bases, (*inicio)->v_herois, entidade))
        return false;

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
           tamanhoConjunto(base->presentes), base->lotacao);

    // Escolhe outra base aleatória
    idNovaBase = rand() % (N_BASES);

    // Cria evento VIAJA(H, B)
    entidade = criaEntidade(heroi->id, idNovaBase, NULL);
    if (!insereOrdenado(inicio, (*inicio)->tempo, 7, (*inicio)->v_bases, (*inicio)->v_herois, entidade)){
        return false;
    }

    return true;
};     

// Evento AVISA(B)
bool avisa(lista_t** inicio){
    base_t* base;
    heroi_t* heroi;
    entidade_t* entidade;

    // Busca base
    base = (*inicio)->v_bases[(*inicio)->entidade->baseId].base;

    // MENSAGEM (Precisa estar antes)
    // --------
    printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA [ ",
           (*inicio)->tempo, base->id, tamanhoConjunto(base->presentes), base->lotacao);

    // Aviso de Fila
    for (int i = 0; i < tamanhoFila(base->espera); i++){
        int idHeroi;
        desenfileirar(base->espera, &idHeroi);
        printf("%2d ", idHeroi);
        enfileirar(base->espera, idHeroi);
    }
    printf("]\n");
    // --------

    // Enquanto houver heróis na fila e vagas na base
    while (!ehVaziaFila(base->espera) && (tamanhoConjunto(base->presentes) < base->lotacao)){
        int idHeroi;

        desenfileirar(base->espera, &idHeroi);
        heroi = (*inicio)->v_herois[idHeroi].heroi; 

        if (!insereConjunto(&(base->presentes), heroi->id))
            return false;

        printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n",
               (*inicio)->tempo, base->id, idHeroi);

        // Cria evento ENTRA(H, B, M)
        entidade = criaEntidade(NULL, base->id, NULL);
        insereOrdenado(inicio, (*inicio)->tempo, 5, (*inicio)->v_bases, (*inicio)->v_herois, entidade);
    }

    return true;
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