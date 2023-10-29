#include "../include/fila.h"

bool eh_cheia(struct fila *f) {
    return (f->fim == N_HEROIS);
}

bool eh_vazia(struct fila *f) {
    return (f->fim == 0);
}

bool ve_inicio(struct fila *f, int *conteudo) {

    //teste fila vazia
    if (!eh_vazia(f)) {
        *conteudo = f->v[0];
        return true;
    }
    //

    conteudo = NULL;
    return false;
}

bool enfileirar(struct fila *f, int conteudo) {

    //teste fila cheia
    if (!eh_cheia(f)) {
       f->v[f->fim] = conteudo;
       (f->fim)++;

       return true;
    }
    return false;
}

void deslocar(struct fila *f) {

    //desloca a fila em 1 posição
    for (int i = 0; i < f->fim; i++) {
        f->v[i] = f->v[i+1];
    }
}

bool desenfileirar(struct fila *f, int *conteudo) {

    // teste fila vazia
    if (!eh_vazia(f)) {
        *conteudo = f->v[0];
        deslocar(f);

        (f->fim)--;

        return true;
    }

    conteudo = NULL;
    return false;
}

void imprimirFila(struct fila *f) {
    for (int i = 0; i < f->fim; i++) {
       printf("%d ", f->v[i]);
    }
    printf("\n");
}

