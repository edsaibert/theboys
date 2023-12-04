#include "../include/eventos.h"


// Evento CHEGA(H, B)
bool chega(lista_t** inicio){
    // Struct auxiliar
    heroi_t* heroi;
    base_t* base;
    entidade_t* entidade = NULL;
    v_herois_t* v_herois = (*inicio)->v_herois;

    bool espera = false;
    // TESTE (TIRAR DEPOIS)
    if (inicio == NULL || (*inicio) == NULL){
        return false;
    }

    // Atualiza base do herói
    *(&(v_herois[(*inicio)->entidade->heroiId].heroi->idBase)) = (*inicio)->entidade->baseId;           

    heroi = v_herois[(*inicio)->entidade->heroiId].heroi;           // "Descobre" herói
    base = (*inicio)->v_bases[(*inicio)->entidade->baseId].base;    // "Descobre" base

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
   criaEntidade(&entidade, heroi->id, heroi->idBase, NULL); 
    if (espera) {
        // Cria evento ESPERA(H, B)
        if (!insereOrdenado(inicio, (*inicio)->tempo, 2, (*inicio)->v_bases, v_herois, entidade))
            return false;
    }
    else {
        // Cria evento DESISTE(H, B)
        if (!insereOrdenado(inicio, (*inicio)->tempo, 3, (*inicio)->v_bases, v_herois, entidade)) 
            return false;
    }

    return true;
};       

bool missao(lista_t** inicio){
    int vDistancias[N_BASES];
    int BMP;

    // MENSAGEM
    printf("%6d: MISSAO %d HAB REQ: [ ", (*inicio)->tempo, (*inicio)->entidade->missao->id);
    imprimeConjunto((*inicio)->entidade->missao->habilidades, false);
    printf("]\n");
    // --------

    criaVetor(vDistancias, (*inicio)->v_bases, (*inicio)->entidade->missao->local);
    BMP = encontraBMP((*inicio)->tempo, vDistancias, (*inicio)->v_herois, (*inicio)->entidade->missao);

    if (BMP != -1){
        incrementaExp((*inicio)->tempo, (*inicio)->v_herois, (*inicio)->entidade->missao, BMP);
        return true;
    }
    // CRIA EVENTO MISSAO PARA O DIA SEGUINTE
    printf("%6d: MISSAO %d IMPOSSIVEL\n", (*inicio)->tempo, (*inicio)->entidade->missao->id);
    return false;
};      

// Evento ESPERA(H, B)
bool espera(lista_t** inicio){
    heroi_t* heroi;
    base_t* base;
    entidade_t* entidade = NULL;

    // "Descobre heroi e base"
    heroi = (*inicio)->v_herois[(*inicio)->entidade->heroiId].heroi;
    base =  (*inicio)->v_bases[(*inicio)->entidade->baseId].base;

    // Adiciona heroi na lista de espera da base
    if (!enfileirar(base->espera, heroi->id))
        return false;

    printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) ESPERA\n", 
            (*inicio)->tempo, heroi->id, base->id, 
            tamanhoConjunto(base->presentes), base->lotacao);

    criaEntidade(&entidade, -1, base->id, NULL);

    (*inicio)->v_herois[(heroi->id)].heroi = heroi;
    
    // Cria evento AVISA(B)
    if (!insereOrdenado(inicio, (*inicio)->tempo, 4, (*inicio)->v_bases, (*inicio)->v_herois, entidade))
        return false;

    return true;
};      

// Evento DESISTE(H, B)
bool desiste(lista_t** inicio){
    heroi_t* heroi;
    base_t* base;
    entidade_t* entidade = NULL;

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
    criaEntidade(&entidade, heroi->id, idNovaBase, NULL);
    if (!insereOrdenado(inicio, (*inicio)->tempo, 7, (*inicio)->v_bases, (*inicio)->v_herois, entidade)){
        return false;
    }

    return true;
};     

// Evento AVISA(B)
bool avisa(lista_t** inicio){
    base_t* base;
    heroi_t* heroi;
    entidade_t* entidade = NULL;

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

        // Cria evento ENTRA(H, B)
        criaEntidade(&entidade, idHeroi, base->id, NULL);
        if (!insereOrdenado(inicio, (*inicio)->tempo, 5, (*inicio)->v_bases, (*inicio)->v_herois, entidade))
            return false;
    }

    return true;
};       

// Evento ENTRA(H, B)
bool entra(lista_t** inicio){
    heroi_t* heroi;
    base_t* base;
    entidade_t* entidade = NULL;
    int tempoBase;      // Tempo de permanência na base
    
    // Busca heroi e base
    heroi = (*inicio)->v_herois[(*inicio)->entidade->heroiId].heroi;
    base = (*inicio)->v_bases[(*inicio)->entidade->baseId].base;

    tempoBase = heroi->paciencia * (1 + rand() % ( 20 - 1 )); // [1 .. 20] * paciência

    // MENSAGEM 
    printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n",
           (*inicio)->tempo, heroi->id, heroi->idBase, tamanhoConjunto(base->presentes), 
           base->lotacao, (*inicio)->tempo + tempoBase);
    // --------

    // Cria evento SAI(H, B)
    criaEntidade(&entidade, heroi->id, heroi->idBase, NULL);
    if (!insereOrdenado(inicio, (*inicio)->tempo + tempoBase, 6, (*inicio)->v_bases, (*inicio)->v_herois, entidade))
        return false;

    return true;
};       

bool sai(lista_t** inicio){
    base_t* base;
    entidade_t* entidade = NULL;

    // Retira heroi do conjunto de presentes da base
    base = (*inicio)->v_bases[(*inicio)->entidade->baseId].base;
    if (!retiraConjunto(&(base->presentes), (*inicio)->entidade->heroiId))
        return false;

    // MENSAGEM
    printf("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n", 
          (*inicio)->tempo, (*inicio)->entidade->heroiId, (*inicio)->entidade->baseId,
          tamanhoConjunto(base->presentes), base->lotacao);
    // --------

    // Escolhe uma base destino aleatória
    int idNovaBase = rand() % (N_BASES);

    criaEntidade(&entidade, (*inicio)->entidade->heroiId, idNovaBase, NULL);

    // Cria evento VIAJA(H, B)
    if (!insereOrdenado(inicio, (*inicio)->tempo, 7, (*inicio)->v_bases, (*inicio)->v_herois, entidade))
        return false; 

    // Cria evento AVISA(B)
    // entidade->heroiId = -1;
    if (!insereOrdenado(inicio, (*inicio)->tempo, 4, (*inicio)->v_bases, (*inicio)->v_herois, entidade))
        return false;


    return false;
};         

bool viaja(lista_t** inicio){
    int dist, tempoViagem;
    heroi_t* heroi;
    base_t* origem, *destino;

    // Busca heroi e base
    heroi = (*inicio)->v_herois[(*inicio)->entidade->heroiId].heroi;
    destino = (*inicio)->v_bases[(*inicio)->entidade->baseId].base;
    origem = (*inicio)->v_bases[heroi->idBase].base;

    // calcula a duração da viagem
    dist = sqrt(pow((origem->local[0] - destino->local[0]), 2) + pow((origem->local[1] - destino->local[1]), 2));
    tempoViagem = dist / heroi->velocidade;

    // MENSAGEM
    printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", 
           (*inicio)->tempo, heroi->id, heroi->idBase, destino->id, 
           dist, heroi->velocidade, (*inicio)->tempo + tempoViagem);

    // --------

    // Cria evento CHEGA(H, B)
    if (!insereOrdenado(inicio, (*inicio)->tempo + tempoViagem, 0, (*inicio)->v_bases, (*inicio)->v_herois, (*inicio)->entidade))
        return false; 

    return true;
};

// Realiza as Estatísticas da simulação
void fim(lista_t* inicio, int numMissao){
    printf("%6d: FIM\n", T_FIM_DO_MUNDO);
    
    for (int i = 0; i < N_HEROIS; i++){
        printf("HEROI %2d PAC %3d VEL %4d EXP %4d HABS [ ", 
        inicio->v_herois[i].heroi->id, inicio->v_herois[i].heroi->paciencia, 
        inicio->v_herois[i].heroi->velocidade, inicio->v_herois[i].heroi->experiencia);

        imprimeConjunto(inicio->v_herois[i].heroi->habilidades, false);
        printf("]\n");
    } 

    // MENSAGEM 
    float porcentagem = (float) (numMissao * 100) / (N_MISSOES * 100) * 100;
    printf("%d/%d MISSOES CUMPRIDAS (%.2f%%)", 
           numMissao, N_MISSOES, porcentagem); 

}