
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

	v_bases_t* v_bases;		// Cria vetor que contém as bases 
	v_herois_t* v_herois;	// Cria vetor que contém os heróis

	v_bases = (v_bases_t*) malloc(sizeof(v_bases_t) * (N_BASES));
	v_herois = (v_herois_t*) malloc(sizeof(v_herois_t) * (N_HEROIS));

	if (v_bases == NULL || v_herois == NULL)
		return 1;

	// Inicializa todas as bases da simulação
	for (int i = 0; i < N_BASES; i++) {
		base_t* base;

		inicializaBase(i, &base);
		v_bases[i].base = base;			// Mantém todas as bases no vetor v_bases
	}

    
    // Realiza o evento CHEGA de cada heroi
    for (int i = 0; i < N_HEROIS; i++) {
        heroi_t* heroi;

        inicializaHeroi(i, &heroi);		// Cria a struct Heroi
		v_herois[i].heroi = heroi;		// Adiciona herói à lista
    }

	// Insere ordenado na LEF (Lista de Eventos Futuros)
	for (int i = 0; i < N_HEROIS; i++){
		entidade_t* entidade;
        heroi_t* heroi;
		int n_base;
		
		heroi = v_herois[i].heroi;
		n_base = rand() % (N_BASES);	// Sorteia uma base para a chegada do heroi
        int tempo = rand() % 4320;		// 3 dias em minutos

		entidade = criaEntidade(heroi->id, n_base, NULL);
        insereOrdenado(&lef, tempo, 0, v_bases, v_herois, entidade);
	}

	// Gera todas as missões 
	for (int i = 0; i < N_MISSOES; i++){
		missao_t* missao;
		entidade_t* entidade;

		inicializaMissao(i, &missao);

		int tempo = rand() % T_FIM_DO_MUNDO;

		// Insere ordenado na LEF (Lista de Eventos Futuros)
		entidade = criaEntidade(0, 0, missao);
		insereOrdenado(&lef, tempo, 1, v_bases, v_herois, entidade);
		
	}

	// ******************************************************
	// RELÓGIO DA SIMULAÇÃO

	int tempo = 0;
	lista_t* aux;

	while (tempo <= T_FIM_DO_MUNDO && lef->prox != NULL){
		// Enquanto o tempo do evento for igual ao tempo atual ( eventos simultâneos )
		int backup = lef->tempo;
		while (lef->tempo == tempo && lef->prox != NULL){
			aux = lef;
			executa(&lef); 			// Executa o evento
			lef = lef->prox;

			free(aux);	
			// necessario free nas entidades
			// necessario free na lista v_bases
		}
		// Incrementa o tempo
		if (tempo == 0)
			tempo += lef->tempo;
		else
			tempo += lef->tempo - backup;
	}

	// ******************************************************
	// EVENTOS FINAIS (free)

	for (int i = 0; i < N_BASES; i++) {
		free(v_bases[i].base->espera);
		free(v_bases[i].base);
	}	

    return 1;
}


