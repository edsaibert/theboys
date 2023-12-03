#ifndef STRUCTS_H
#define STRUCTS_H

#include "atributos.h"
#include "fila.h"
#include "conjunto.h"

typedef struct heroi {
	int id;
	int experiencia;
	int paciencia;
	int velocidade;
	int idBase;
	conjunto_t* habilidades;	
} heroi_t;

typedef struct base {
	int id;
	int local[2];
	int lotacao;
	conjunto_t* presentes;
	fila_t* espera; 
} base_t;

typedef struct missao {
	int id;
	int local[2];
	conjunto_t* habilidades; 
} missao_t;

typedef struct v_bases {
	int id;
	base_t* base;
} v_bases_t;

typedef struct v_herois {
	int id;
	heroi_t* heroi;
} v_herois_t;

typedef struct Entidades {
	int heroiId;
	int baseId;
	missao_t* missao;
} entidade_t;

bool inicializaHeroi(int id, heroi_t** heroi);

bool inicializaBase(int id, base_t** base);

bool inicializaMissao(int id, missao_t** missao);

bool criaEntidade(entidade_t** entidade, int heroiId, int baseId, missao_t* missaoId);

void criaVetor(int v[N_BASES], v_bases_t* v_bases, int coord[2]);

int encontraBMP(int v[N_BASES], v_herois_t* v_herois, missao_t* missao);

void incrementaExp(v_herois_t* v_herois, int idBase);

void freeVbases(v_bases_t* v_bases);

void freeVherois(v_herois_t* v_herois);

void freeEntidade(entidade_t* entidade);

#endif




















