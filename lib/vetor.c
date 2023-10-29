#include "../include/vetor.h"

void imprimeVetor(int *v, int tam){
    for (int i = 0; i < tam; i++)
        printf("%d ", v[i]);
    printf("\n");
}