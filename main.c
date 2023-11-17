
#include "./include/atributos.h"
#include "./include/entidades.h"
#include "./include/conjunto.h"
#include "./include/fila.h"
#include "./include/lista.h"
#include "./include/vetor.h"
#include "./include/eventos.h"

/*
##############################################
Trabalho The Boys 
Feito em 11/2023 para a disciplina de Prog1
Por Eduarda Saibert =D
##############################################
*/

int main() {
	srand(time(NULL));	
    lista_t* lef;

	// ******************************************************
	// EVENTOS INICIAIS

	// Cria vetor que contém as bases
	v_bases_t* v_bases;
	v_bases = (v_bases_t*) malloc(sizeof(v_bases_t) * N_BASES);

	if (v_bases == NULL)
		return 1;

	// Inicializa todas as bases da simulação
	for (int i = 0; i < N_BASES; i++) {
		base_t* base;

		inicializaBase(i, &base);
		printf("%d", base->id);
		v_bases[i].base = base;			// Mantém todas as bases no vetor v_bases
	}
    
    // Realiza o evento CHEGA de cada heroi
    for (int i = 0; i < N_HEROIS; i++) {
        heroi_t* heroi;
		int n_base;

        inicializaHeroi(i, &heroi);		// Cria a struct Heroi

		n_base = rand() % N_BASES;		// Sorteia uma base para a chegada do heroi

        int tempo = rand() % 4320;		// 3 dias em minutos

		// Insere ordenado na LEF (Lista de Eventos Futuros)
        insereOrdenado(&lef, tempo, 0, heroi, v_bases[n_base].base, NULL);
    }

	// Gera todas as missões 
	for (int i = 0; i < N_MISSOES; i++){
		missao_t* missao;

		inicializaMissao(i, &missao);

		int tempo = rand() % T_FIM_DO_MUNDO;

		// Insere ordenado na LEF (Lista de Eventos Futuros)
		insereOrdenado(&lef, tempo, 1, NULL, NULL, missao);
		
	}

	// ******************************************************
	// RELÓGIO DA SIMULAÇÃO

	int tempo = 0;

	while (tempo <= T_FIM_DO_MUNDO && lef->prox != NULL){
		// Enquanto o tempo do evento for igual ao tempo atual ( eventos simultâneos )
		int backup = lef->tempo;
		while (lef->tempo == tempo && lef->prox != NULL){
			executa(&lef); 			// Executa o evento

			lef = lef->prox;
		}
		// Incrementa o tempo
		if (tempo == 0)
			tempo += lef->tempo;
		else
			tempo += lef->tempo - backup;
	}

	// ******************************************************
	// EVENTOS FINAIS (free)

    return 1;
}


