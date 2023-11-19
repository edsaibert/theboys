#include "../include/fila.h"

fila_t* inicializaFila(){
    return NULL;
}

// Checa se a fila está cheia
bool ehCheiaFila(struct fila *f) {
    return (f->fim == N_HEROIS);
}

// Checa se a fila está vazia
bool ehVaziaFila(struct fila *f) {
    return (f->fim == 0);
}

// Vê o primeiro elemento da fila
bool veInicio(struct fila *f, int *conteudo) {

    //teste fila vazia
    if (!ehVaziaFila(f)) {
        *conteudo = f->v[0];
        return true;
    }
    //

    conteudo = NULL;
    return false;
}

// Enfileira um elemento na fila
bool enfileirar(struct fila *f, int conteudo) {

    //teste fila cheia
    if (!ehCheiaFila(f)) {
       f->v[f->fim] = conteudo;
       (f->fim)++;

       return true;
    }
    return false;
}

// Desloca a fila em 1 posição
void deslocar(struct fila *f) {

    //desloca a fila em 1 posição
    for (int i = 0; i < f->fim; i++) {
        f->v[i] = f->v[i+1];
    }
}

// Desenfileira um elemento da fila
bool desenfileirar(struct fila *f, int *conteudo) {

    // teste fila vazia
    if (!ehVaziaFila(f)) {
        *conteudo = f->v[0];
        deslocar(f);

        (f->fim)--;

        return true;
    }

    conteudo = NULL;
    return false;
}

// Imprime a fila
void imprimirFila(struct fila *f) {
    for (int i = 0; i < f->fim; i++) {
       printf("%d ", f->v[i]);
    }
    printf("\n");
}

// Retorna o tamanho da fila
int tamanhoFila(struct fila *f) {
    return f->fim;
}
