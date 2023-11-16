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

bool inicializaHeroi(int id, heroi_t** heroi);

bool inicializaBase(int id, base_t** base);

#endif




















