
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

	// Inicializa todos os heróis da simulação
    for (int i = 0; i < N_HEROIS; i++) {
        heroi_t* heroi;

        inicializaHeroi(i, &heroi);		// Cria a struct Heroi
		v_herois[i].heroi = heroi;		// Adiciona herói ao vetor v_herois 
    }

    // Realiza o evento CHEGA de cada heroi
	for (int i = 0; i < N_HEROIS; i++){
		entidade_t* entidade = NULL;
        heroi_t* heroi;
		int n_base;
		
		heroi = v_herois[i].heroi;
		n_base = rand() % (N_BASES);	// Sorteia uma base para a chegada do heroi
		heroi->idBase = n_base;			// Atualiza a base do heroi

        int tempo = rand() % 4320;		// 3 dias em minutos

		// Insere ordenado na LEF (Lista de Eventos Futuros)
		criaEntidade(&entidade, heroi->id, n_base, NULL);
        insereOrdenado(&lef, tempo, 0, v_bases, v_herois, entidade);
	}

	// Gera todas as missões 
	for (int i = 0; i < N_MISSOES; i++){
		missao_t* missao;
		entidade_t* entidade = NULL;

		inicializaMissao(i, &missao);

		int tempo = rand() % T_FIM_DO_MUNDO;

		// Insere ordenado na LEF (Lista de Eventos Futuros)
		criaEntidade(&entidade, -1, -1, missao);
		insereOrdenado(&lef, tempo, 1, v_bases, v_herois, entidade);
	}

	// ******************************************************
	// RELÓGIO DA SIMULAÇÃO

	int tempo = 0;
	lista_t* aux = lef;
	lista_t* temp;

	while (tempo <= 1000 && aux != NULL){
		// Enquanto o tempo do evento for igual ao tempo atual ( eventos simultâneos )
		int backup = aux->tempo;
		while (aux != NULL && aux->tempo == tempo) {
			executa(&aux); 			// Executa o evento
			aux = aux->prox;
		}
		// Incrementa o tempo
		if (tempo == 0)
			tempo += aux->tempo;
		else
			tempo += aux->tempo - backup;
	}

	// ******************************************************
	// EVENTOS FINAIS (free)

	while (lef != NULL){
		temp = lef->prox;

		if (lef->idFuncao == 1){ 
			freeEntidade(lef->entidade);
		} else if (!(lef->idFuncao == 7)){
			if (lef->entidade != NULL)
			free(lef->entidade);
		}
		free(lef);
		lef = temp;
	}
	freeVherois(v_herois);
	freeVbases(v_bases);

	return 1;
}


