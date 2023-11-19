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

typedef struct Entidades {
   heroi_t* heroi;
   base_t* base;
   missao_t* missao;
} entidade_t;

typedef struct v_bases {
	int id;
	base_t* base;
} v_bases_t;

bool inicializaHeroi(int id, heroi_t** heroi);

bool inicializaBase(int id, base_t** base);

bool inicializaMissao(int id, missao_t** missao);

bool criaEntidade(entidade_t** entidade, heroi_t* heroi, base_t* base, missao_t* missao);


#endif




















