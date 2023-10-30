#ifndef FILA_H
#define FILA_H

#include "atributos.h"

typedef struct fila {
    int fim;
    int v[N_HEROIS]; // O máximo que a fila pode suportar é o número máximo de heróis
} fila_t;

fila_t* inicializaFila(void);

bool ehCheiaFila(struct fila *f);

bool ehVaziaFila(struct fila *f);

bool veInicio(struct fila *f, int *conteudo);

bool enfileirar(struct fila *f, int conteudo);

void deslocar(struct fila *f);

bool desenfileirar(struct fila *f, int *conteudo);

void imprimirFila(struct fila *f);

#endif
