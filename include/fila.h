#include "aux.h"

typedef struct fila {
    int fim;
    int v[N_HEROIS]; // O máximo que a fila pode suportar é o número máximo de heróis
} fila_t;

bool eh_cheia(struct fila *f);

bool eh_vazia(struct fila *f);

bool ve_inicio(struct fila *f, int *conteudo);

bool enfileirar(struct fila *f, int conteudo);

void deslocar(struct fila *f);

bool desenfileirar(struct fila *f, int *conteudo);

void imprimirFila(struct fila *f);
