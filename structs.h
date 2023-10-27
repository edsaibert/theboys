#include <stdio.h>
#include <stdlib.h>


#define T_INICIO		0
#define T_FIM_DO_MUNDO	525600
#define N_TAMANHO_MUNDO 200000
#define N_HABILIDADES	10
#define N_HEROIS		N_HABILIDADES * 5
#define N_BASES			N_HEROIS / 6
#define N_MISSOES		T_FIM_DO_MUNDO / 100

#define MAX_PACIENCIA	100
#define MAX_VELOCIDADE	5000

#define MIN_VELOCIDADE	50
#define MIN_HAB_MISSAO	6



typedef struct lef {
	int tempo;
	struct lef *prox;
}, lef_t;


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
}

typedef struct base {
	int id;
	int local[2];
	int lotação;
	conjunto_t* presentes;
	fila_t* espera; // incluir bib separada para fila
}

typedef struct missao {
	int id;
	int local[2];
	conjunto_t* habilidades; 
}





















