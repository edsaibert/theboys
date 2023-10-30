
#include "./include/atributos.h"
#include "./include/theboys.h"
#include "./include/conjunto.h"
#include "./include/fila.h"
#include "./include/lista.h"
#include "./include/vetor.h"

/*
##############################################
Trabalho The Boys 
Feito em 11/2023 para a disciplina de Prog1
Por Eduarda Saibert =D
##############################################
*/

int main() {
    lista_t* lef;
    srand(0);
    
    for (int i = 0; i < N_HEROIS; i++) {
        // Realiza o evento CHEGA de cada heroi
        heroi_t* heroi;
        base_t* base;

        inicializaHeroi(i, &heroi);

        int base = rand() % N_HEROIS;
        inicializaBase(i, &base);

        int tempo = rand() % 4320; // 3 dias em minutos


        // insereOrdenado(&lef, tempo, tipo, entidades);
    }

    imprimeLista(lef);

    return 0;

}