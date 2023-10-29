#include <stdio.h>
#include <stdlib.h>
#include "fila.h"


typedef struct lef {
	int tempo;
	struct lef *prox;
} lef_t;


// incluir bib separada para conjuntos
typedef struct conjuntos {
    int conteudo;
    int cont; // Para o caso das duplicatas
    struct conjuntos* prox;
} conjunto_t;


typedef struct heroi {
	int id;
	int experiencia;
	int paciencia;
	int velocidade;
	conjunto_t* habilidades;	
} heroi_t;

typedef struct base {
	int id;
	int local[2];
	int lotação;
	conjunto_t* presentes;
	fila_t* espera; // incluir bib separada para fila
} base_t;

typedef struct missao {
	int id;
	int local[2];
	conjunto_t* habilidades; 
} missao_t;





















